import json
import os
import time
import asyncio
import argparse

from PIL import Image
from utils.config import Config
from utils.async_lib.crawler import Crawler_async, download_bin
from utils.async_lib.utils import Coroutine, Task
from utils.filer import touch_dir
from utils.imager import tailor, imgs2h5


CONFIG = Config('baidu_image').conf
GLOBAL = Config('baidu_image').glob

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.167 Safari/537.36',
    'Referer': 'https://image.baidu.com/search/acjson',
}

GLOBAL['tmp_dir'] = touch_dir(CONFIG['tmp_dir'])
GLOBAL['data_dir'] = touch_dir(CONFIG['data_dir'])
GLOBAL['imgs'] = []
GLOBAL['urls'] = asyncio.Queue()
GLOBAL['cnt'] = 0
GLOBAL['consumer_num'] = 40
GLOBAL['keyword'] = '鹅'
GLOBAL['page_num'] = 2
GLOBAL['shape'] = (28, 28)
GLOBAL['grey'] = True
GLOBAL['map'] = {
    '猫': [1, 0, 0, 0, 0],
    '喵': [1, 0, 0, 0, 0],
    '狗': [0, 1, 0, 0, 0],
    '牛': [0, 0, 1, 0, 0],
    '羊': [0, 0, 0, 1, 0],
    '鸡': [0, 0, 0, 0, 1],
    '鸭': [0, 0, 0, 0, 1],
    '鹅': [0, 0, 0, 0, 1],
    '猪': [0, 0, 0, 0, 1],
}

async def get_url(session, keyword, urls, page):
    url = 'https://image.baidu.com/search/acjson'
    params = {
        'tn': 'resultjson_com',
        'ipn': 'rj',
        'queryWord': keyword,
        'word': keyword,
        'pn': str(page * 60),
        'rn': '60',
        }
    async with session.get(url, params=params) as response:
        try:
            json_obj = json.loads(await response.text())
            for data in json_obj['data']:
                try:
                    url = data['thumbURL']
                    cnt = GLOBAL['cnt']
                    await urls.put((cnt, url))
                    print(f'Put {cnt:04} {url}')
                    GLOBAL['cnt'] += 1
                except:
                    pass
        except json.decoder.JSONDecodeError as e:
            pass

async def get_all_urls(session, keyword, urls, page_num=1):
    for page in range(page_num):
        await get_url(session, keyword, urls, page)
    for i in range(GLOBAL['consumer_num']):
        await urls.put((i, None))

async def get_all_imgs(session, base_dir, urls, shape=(64, 64), formats=['.jpg', '.png', '.jpeg']):
    while True:
        cnt, url = await urls.get()
        if url is None:
            print(f'{cnt:02} Done!')
            break
        print(f'Get {cnt:04} {url}')
        for ext in formats:
            if ext in url:
                break
        else:
            continue
        file_path = os.path.join(base_dir, GLOBAL['keyword'] + str(cnt) + ext)
        try:
            await download_bin(session, url, file_path)
            im = tailor(Image.open(file_path), shape).convert("RGB")
            if im.size == shape:
                GLOBAL['imgs'].append(im)
        except Exception as e:
            print(e)

def run():
    coroutine = Coroutine()
    coroutine.set_task([
        Crawler_async(
            Task(get_all_urls, (GLOBAL['keyword'], GLOBAL['urls'], GLOBAL['page_num'])), headers = headers
        ),
        *[Crawler_async(
            Task(get_all_imgs, (GLOBAL['tmp_dir'], GLOBAL['urls'], GLOBAL['shape']))
        ) for i in range(GLOBAL['consumer_num'])],
    ])
    coroutine.run()
    imgs2h5(
        GLOBAL['imgs'],
        [GLOBAL['map'][GLOBAL['keyword']] for i in range(len(GLOBAL['imgs']))],
        os.path.join(GLOBAL['data_dir'], GLOBAL['keyword'] + '.h5'),
        grey = GLOBAL['grey'],
        )
    print('Done!')

if __name__ == '__main__':
    t = time.time()
    parser = argparse.ArgumentParser(description='baidu_image')
    parser.add_argument('kw', help='关键词')
    parser.add_argument('-p', default='5', help='页数（每页60）')
    parser.add_argument('-s', default='(64, 64)', help='分辨率')
    parser.add_argument('-g', default='False', help='是否生成灰度图')
    args = parser.parse_args()
    GLOBAL['keyword'] = args.kw
    GLOBAL['page_num'] = int(args.p)
    GLOBAL['shape'] = eval(args.s)
    GLOBAL['grey'] = eval(args.g)
    run()
    print(time.time() - t)
