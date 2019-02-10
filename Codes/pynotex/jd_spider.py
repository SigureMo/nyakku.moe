import json
import re
import os

from bs4 import BeautifulSoup
from utils.crawler import Crawler
from utils.config import Config
from utils.db import SQLite, BigintField, StringField, DoubleField, Model
from utils.filer import touch_dir


spider = Crawler()
CONFIG = Config('jd_spider').conf
GLOBAL = Config('jd_spider').glob

GLOBAL['data_dir'] = touch_dir(CONFIG['data_dir'])

class AirConditioning(Model):

    skuid = BigintField('skuid', primary_key=True, not_null=True)
    brand = StringField('brand')
    kind = StringField('kind')
    horsepower = StringField('horsepower')
    mode = StringField('mode')
    EEI = BigintField('EEI')
    EER = DoubleField('EER')
    rfc = BigintField('rfc')
    rfp = BigintField('rfp')
    noise = BigintField('noise')
    price = BigintField('price')
    vip_price = BigintField('vip_price')
    discount_price = BigintField('discount_price')
    vip_discount_price = BigintField('vip_discount_price')
    pc_price = BigintField('pc_price')
    vip_pc_price = BigintField('vip_pc_price')
    speciality = StringField('speciality')

    def __init__(self, db, **kw):
        self.db = db
        super().__init__(**kw)


def get_skuids(kw, stop_num=3, deep=False):
    skuid_list = []
    for page_num in range(1, stop_num*2 + 1, 2):
        get_one_page_skuids(skuid_list, kw, page_num, deep)
    return skuid_list


def get_one_page_skuids(skuid_list, kw, page_num, deep):
    params = {
        'keyword': kw,
        'enc': 'utf-8',
        'page': page_num
    }
    res = spider.get('https://search.jd.com/Search', params=params)
    res.encoding = 'utf-8'
    soup = BeautifulSoup(res.text, 'html.parser')
    ul = soup.find('ul', class_='gl-warp')
    for li in ul.find_all('li'):
        if deep:
            skuid_list.extend(get_more_skuids(li.attrs['data-sku']))
        else:
            skuid_list.append(int(li.attrs['data-sku']))


def get_more_skuids(skuid):
    skuids = []
    url = 'https://item.jd.com/{}.html'.format(skuid)
    res = spider.get(url)
    color_size_re = re.compile(r'colorSize: (\[\{.+?\}\]),')
    if color_size_re.search(res.text):
        data = json.loads(color_size_re.search(res.text).group(1))
        for item in data:
            skuids.append(item['skuId'])
    else:
        skuids.append(int(skuid))
    return skuids


def get_price(skuid, d):
    url = 'https://p.3.cn/prices/mgets?skuIds=J_{}'.format(skuid)
    prices = json.loads(spider.get(url).text)
    d['price'] = prices[0]['p']
    d['vip_price'] = prices[0].get('tpp')


def get_promotion(skuid, d):
    d['promotions'] = {}
    url = 'https://item.jd.com/{}.html'.format(skuid)
    res = spider.get(url)
    vender_id = re.search(r'venderId:(\d+),', res.text).group(1)
    cat = re.search(r'cat: \[(.+?)\],', res.text).group(1)
    promotion_url = 'https://cd.jd.com/promotion/v2'
    params = {
        'skuId': skuid,
        'area': '1_72_2799_0',
        'venderId': vender_id,
        'cat': cat,
    }
    res = spider.get(promotion_url, params=params)
    promotion = json.loads(res.text)
    for conpon in promotion['skuCoupon']:
        d['promotions'][conpon['quota']] = conpon['discount']


def get_params(skuid, d):
    url = 'https://item.jd.com/{}.html'.format(skuid)
    res = spider.get(url)
    soup = BeautifulSoup(res.text, 'html.parser')
    ptable = soup.find('div', class_='Ptable')
    for ptable_item in ptable.find_all('div', class_='Ptable-item'):
        dl_list = ptable_item.find_all('dl', class_='clearfix')
        for dl in dl_list:
            title = dl.find('dt')
            data = dl.find('dd', class_='')
            d[title.string] = data.string


def write_db(skuid, d):
    skuid = int(skuid) # int
    brand = d.get('品牌', '未知') # string
    kind = d['类别'] # string
    horsepower = d['匹数'] # string
    mode = d['定频/变频'] # string
    EEI = int(d.get('能效等级', '6级').rstrip('级')) # int
    EER = eval(re.search(r'\d+\.\d+', d.get(mode + '机能效比', '0.0')).group(0)) # float
    rfc = int(re.search(r'\d+', d['制冷量(W)']).group(0)) # int
    rfp = int(re.search(r'\d+', d['制冷功率(W)']).group(0)) # int
    noise = max(list(map(int, re.findall(r'\d+', d.get('内机噪音(dB(A)', '99')))), default=99) # int
    price = int(eval(d['price'])) # int
    vip_price = int(eval(d['vip_price'])) if d['vip_price'] else price
    promotion = max(list(map(lambda x: d['promotions'][x], filter(lambda x: x<=price, d['promotions']))), default=0)
    vip_promotion = max(list(map(lambda x: d['promotions'][x], filter(lambda x: x<=vip_price, d['promotions']))), default=0)
    discount_price = price - promotion
    vip_discount_price = vip_price - vip_promotion
    pc = int(rfp / 1000 * 10 * 40 * 0.55 * 10) # 10 年耗电价 按 每天 10 小时
    pc_price = price + pc
    vip_pc_price = vip_price + pc
    speciality = d.get('特性')
    AirConditioning(
        GLOBAL['db'], skuid=skuid, brand=brand, kind=kind, horsepower=horsepower, mode=mode,
        EEI=EEI, EER=EER, rfc=rfc, rfp=rfp, noise=noise, price=price, vip_price=vip_price,
        discount_price=discount_price, vip_discount_price=vip_discount_price,
        pc_price=pc_price, vip_pc_price=vip_pc_price, speciality=speciality
    ).insert()


def get_data():
    kw = '空调柜机'
    db = SQLite(os.path.join(GLOBAL['data_dir'], 'AirConditioning.db'))
    GLOBAL['db'] = db
    try:
        AirConditioning(db).create()
    except:
        pass
    d = {}
    for skuid in set(get_skuids(kw, stop_num=20, deep=True)):
        print(skuid)
        try:
            get_params(skuid, d)
            get_price(skuid, d)
            get_promotion(skuid, d)
        except KeyboardInterrupt:
            del db
            raise
        except:
            print('获取数据错误！')
        try:
            write_db(skuid, d)
        except KeyboardInterrupt:
            del db
            raise
        except Exception as e:
            print('写数据错误！{}'.format(e))
            print(d)
        d.clear()

def touch(skuid):
    d = {}
    get_params(skuid, d)
    get_price(skuid, d)
    get_promotion(skuid, d)
    print(d)
    write_db(skuid, d)

def select():
    db = SQLite(os.path.join(GLOBAL['data_dir'], 'AirConditioning.db'))
    for item in AirConditioning(db,
    skuid=True, brand=True, kind=True, horsepower=True, mode=True,
    EEI=True, EER=True, rfc=True, rfp=True, vip_discount_price=True, speciality=True).select(
        conditional="NOT brand in ('长虹', 'TCL') AND horsepower in ('2匹', '大2匹', '3匹', '大3匹') AND mode='变频' AND EEI <= 2 AND price <= 7000 AND price >= 4000",
        order=['price DESC']
        ):
        print(item)

if __name__ == '__main__':
    # touch(4071336)
    # get_data()
    select()
    # test()
