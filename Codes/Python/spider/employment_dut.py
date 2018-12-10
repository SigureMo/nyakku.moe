import requests
import re
import time
from bs4 import BeautifulSoup
from operator import itemgetter

# 暂时就直接把这些放上来了，后期补足爬虫总框架与调度体系（也许）

def get_urls_old(date):
    # 旧接口，居然把几万行数据存在HTML里我也是第一次见（严重影响主页面加载速度）……好在现在改成异步加载方式了
    url = 'http://career.dlut.edu.cn/'
    res = requests.get(url)
    res.encoding = 'utf-8'
    soup=BeautifulSoup(res.text,'html.parser')
    datas = soup.find('ul', class_='pull-left')
    print(datas.find_all('li', attrs = {'data-date': re.compile('d6732419-a7cc-4f5e-8906-5af2f0b2dcc7\|'+date)}))
    urls = list(map(lambda t:'http://202.118.65.2/app/portals/newspage.html?id='+t.attrs.get('data-date').split('|')[0], datas.find_all('li', attrs = {'data-date': re.compile(date)})))
    return urls

def get_urls(date):
    # 获取该日期下的所有招聘信息页面
    url = 'http://202.118.65.2/app/portals/recruiterNews?date=' + date
    res = requests.get(url)
    urls = list(map(lambda j:'http://202.118.65.2/app/portals/newspage.html?id='+j['id'], res.json()))
    return urls

def get_msg(url):
    # 从招聘信息详情页面提取所需信息
    res = requests.get(url)
    res.encoding = 'utf-8'
    msg = []
    soup=BeautifulSoup(res.text,'html.parser')
    enterprise = soup.find('h3', class_ = 'text-center').string
    msg.append(enterprise)
    table = soup.find_all('table')[1]
    tr = table.find('tr')
    msg += map(lambda t:t.string, tr.find_all('th'))
    return msg

# date = '2018-09-28'

date = input('请输入日期(yyyy-mm-dd)：')
if not date:
    date = time.strftime('%Y-%m-%d', time.localtime(time.mktime(time.localtime()) + 60 * 60 * 24))
    print(f'已启用默认值{date}')

urls = get_urls(date)
successful = []
failed = []

for url in urls:
    try:
        msg = get_msg(url)
        successful.append([msg[0], msg[1].split('：')[1], msg[2].split('：')[1]] + list(map(int, msg[3].split('：')[1].split(':'))) + [url])
    except:
        failed.append(url)
    
successful = sorted(successful, key=itemgetter(3,4))

# 命令行输出
print('日期\t\t时间\t地点\t\t\t企业')
for msg in successful:
    print('{}\t{:02}:{:02}\t{:20}\t{}'.format(msg[2], msg[3], msg[4], msg[1],msg[0]))
print('共获取{}条信息，其中{}条信息成功抓取，{}条无法抓取'.format(len(successful) + len(failed), len(successful), len(failed)))
print('未成功抓取的链接有：')
for url in failed:
    print(url)
# csv输出
csv = ','.join(['日期', '时间', '地点', '企业', '网址']) + '\n'
for msg in successful:
    line = []
    line.append(msg[2])
    line.append('{:02}:{:02}'.format(msg[3], msg[4]))
    line.append(msg[1])
    line.append(msg[0])
    line.append(msg[5])
    csv += ','.join(line) + '\n'
for url in failed:
    line = []
    line = ['None', 'None', 'None', 'None']
    line.append(url)
    csv += ','.join(line) + '\n'
with open(date + '.csv', 'w', newline = '\r\n') as f:
    f.write(csv)
input('Press <Enter>')
