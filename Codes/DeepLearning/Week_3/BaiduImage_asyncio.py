import asyncio
import aiohttp # pip install aiohttp
import aiofiles # pip install aiofiles
import async_timeout
import queue
import json
import os
import time
from PIL import Image

async def get_url(keyword: str, urls: asyncio.Queue, page: int, cnt: int = 0) -> int:
    url = 'https://image.baidu.com/search/acjson'
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36',
        'Referer': url,
        }
    params = {
        'tn': 'resultjson_com',
        'ipn': 'rj',
        'queryWord': keyword,
        'word': keyword,
        'pn': str(page * 30),
        'rn': '30',
        }
    async with aiohttp.ClientSession(connector=aiohttp.TCPConnector(ssl=False)) as session:
        async with session.get(url, params=params) as response:
            try:
                json_obj = json.loads(await response.text())
                for data in json_obj['data']:
                    try:
                        url = data['thumbURL']
                        print(f'Put {url}')
                        await urls.put((cnt, url))
                        cnt += 1
                    except:
                        pass
                return cnt
            except json.decoder.JSONDecodeError as e:
                pass

async def download(path: str, filename: str, url: str, session: aiohttp.ClientSession) -> bool:
    try:
        with async_timeout.timeout(10):
            async with session.get(url, timeout=10) as response:
                async with aiofiles.open(os.path.join(path, filename), 'wb') as f:
                # with open(os.path.join(path, filename), 'wb') as f:
                    content = await response.read()
                    await f.write(content)
                    return True
    except (SystemExit, KeyboardInterrupt):
        raise
    except SyntaxError as se:
        print('SyntaxError:'+se)
    except asyncio.TimeoutError:
        print(f'{filename}无法抓取,url -> {url}')
    except:
        print(f'{filename}无法抓取,url -> {url}')
        return False

def thumbnail(path: str, filename: str, target: str, resolution: tuple) -> None:
    try:
        im = Image.open(os.path.join(path, filename))
        width = int(im.size[0])
        height = int(im.size[1])
        length = min(im.size)
        region = im.crop(((width-length) / 2, (height-length) / 2, length + (width-length) / 2,  length + (height-length) / 2))
        region.thumbnail(resolution, Image.ANTIALIAS)
        region = region.convert('L')
        region.save(os.path.join(os.path.join(target, filename)))
    except:
        print('图片{}无法处理'.format(filename))
    finally:
        try:
            im.close()
        except:
            pass

async def get_all_urls(keyword: str, urls: asyncio.Queue, page_num:int = 1, consumer_num: int = 1) -> None:
    sem = asyncio.Semaphore(10)
    cnt = 0
    for page in range(page_num):
        async with sem:
            cnt = await get_url(keyword, urls, page, cnt)
    for i in range(consumer_num):
        await urls.put(None)

async def get_all_imgs(root: str, name: str, urls: str, resolution: tuple = (64, 64)) -> None:
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36',
        }
    session = aiohttp.ClientSession(connector=aiohttp.TCPConnector(ssl=False), headers = headers)
    sem = asyncio.Semaphore(10)
    path = os.path.join(root, name)
    postfix = '_' + 'x'.join(map(str, resolution))
    target = path + postfix
    if not os.path.exists(path):
        os.mkdir(path)
    if not os.path.exists(target):
        os.mkdir(target)
    while True:
        async with sem:
            res = await urls.get()
            if res == None:
                print('Done!')
                break
            cnt, url= res
            print(f'Get {url}')
            for ext in formats:
                if ext in url:
                    break
            filename = name + str(cnt) + ext
            print(f'Downloading {filename}')
            if await download(path, filename, url, session):
                print(f'Making thumbnail {filename}')
                thumbnail(path, filename, target, resolution)
    await session.close()

t = time.time()
keyword = '猫'
name = 'Cat'                   # dir name
page_num = 30                  # image page number
resolution = (64, 64)          # image resolution
root = 'D:/Pictures/Train_Set' # the store path
formats = ['.jpg', '.png', '.jpeg', '.ico']
consumer_num = 30              # consumer number

urls = asyncio.Queue()

event_loop = asyncio.get_event_loop()
try:
    to_do = [
        get_all_urls(keyword, urls, page_num, consumer_num),
        *[get_all_imgs(root, name, urls, resolution) for i in range(consumer_num)],
        ]
    # future = asyncio.ensure_future(main(event_loop))
    event_loop.run_until_complete(asyncio.wait(to_do))
finally:
    event_loop.close()

print(time.time() - t)
input('喵喵喵！')
