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
from utils.imager import tailor


CONFIG = Config('baidu_image').conf
GLOBAL = Config('baidu_image').glob

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.167 Safari/537.36',
    'Referer': 'https://image.baidu.com/search/acjson',
}

GLOBAL['data_dir'] = touch_dir(CONFIG['data_dir'])
GLOBAL['urls'] = asyncio.Queue()
GLOBAL['cnt'] = 0
GLOBAL['consumer_num'] = 40

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
                    print(f"Put {cnt:04}/{GLOBAL['cnt']:04} {url} ", end="\r")
                    GLOBAL['cnt'] += 1
                except:
                    pass
        except json.decoder.JSONDecodeError as e:
            pass

async def get_all_urls(session, keyword, urls, page_num=1):
    """ 获取全部图片 url """
    for page in range(page_num):
        await get_url(session, keyword, urls, page)
    for i in range(GLOBAL['consumer_num']):
        await urls.put((i, None))

async def get_all_imgs(session, base_dir, urls, size=(64, 64), formats=['.jpg', '.png', '.jpeg']):
    """ 下载全部图片 """
    while True:
        cnt, url = await urls.get()
        if url is None:
            print(f'{cnt:02} Done! ', end="\r")
            break
        print(f"Get {cnt:04}/{GLOBAL['cnt']:04} {url} ", end="\r")
        for ext in formats:
            if ext in url:
                break
        else:
            continue
        file_path = os.path.join(base_dir, "{}{:04d}{}".format(GLOBAL['keyword'], cnt, ext))
        try:
            await download_bin(session, url, file_path)
            if not GLOBAL['no_tailor']:
                im = tailor(Image.open(file_path), size).convert("RGB")
                im.save(file_path)
        except Exception as e:
            print(e)

def run():
    coroutine = Coroutine()
    coroutine.set_task([
        Crawler_async(
            Task(get_all_urls, (GLOBAL['keyword'], GLOBAL['urls'], GLOBAL['page_num'])), headers = headers
        ),
        *[Crawler_async(
            Task(get_all_imgs, (GLOBAL['data_dir'], GLOBAL['urls'], GLOBAL['size']))
        ) for i in range(GLOBAL['consumer_num'])],
    ])
    coroutine.run()
    print('Done! ')

if __name__ == '__main__':
    t = time.time()
    parser = argparse.ArgumentParser(description='baidu image')
    parser.add_argument('keyword', help='关键词')
    parser.add_argument('--page', default=5, help='页数（每页60）')
    parser.add_argument('--size', default='(64, 64)', help='分辨率')
    parser.add_argument('--grey', action="store_true", default=False, help='转化为灰度图')
    parser.add_argument('--no-tailor', action="store_true", default=False, help='保存原图')
    args = parser.parse_args()
    GLOBAL['keyword'] = args.keyword
    GLOBAL['page_num'] = int(args.page)
    GLOBAL['size'] = eval(args.size)
    GLOBAL['no_tailor'] = args.no_tailor
    run()
    print(time.time() - t)
