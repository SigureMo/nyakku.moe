import requests
import os
import time
from PIL import Image
# from urllib import parse

def get_url(keyword, page = 1, step = 100):
    url = 'https://image.baidu.com/search/acjson'
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36',
        'Referer': url,
        }
    imgs = []
    for i in range(page):
        amount = page
        cnt = i + 1
        bar = '\r{}{} {:6.2f}% {:5d}/{:5d}  '.format('#'*round(cnt/amount*50), '_'*round((1-cnt/amount)*50), cnt/amount*100, cnt, amount)
        print(bar, end = '')
        # if i % step == 0:
        #     print('当前获取第{}页链接'.format(i))
        params = {
            'tn': 'resultjson_com',
            'ipn': 'rj',
            'queryWord': keyword,
            'word': keyword,
            'pn': str(i * 30),
            'rn': '30',
            }
        try:
            res = requests.get(url, headers = headers, params = params)
            for data in res.json()['data']:
                try:
                    imgs.append(data['thumbURL'])
                except:
                    pass
        except:# requests.json.decoder.JSONDecodeError:
            continue
        time.sleep(0)
    return imgs

def download(root, name, urls, step = 100):
    path = os.path.join(root, name)
    s = requests.Session()
    s.headers.update({
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36',
        })
    if not os.path.exists(path):
        os.mkdir(path)
    for i in range(len(urls)):
        try:
            url = urls[i]
            res = s.get(url)
            amount = len(urls)
            cnt = i + 1
            bar = '\r{}{} {:6.2f}% {:5d}/{:5d}  '.format('#'*round(cnt/amount*50), '_'*round((1-cnt/amount)*50), cnt/amount*100, cnt, amount)
            print(bar, end = '')
            # if (i+1) % step == 0:
            #     print('当前抓取第{}张图片'.format(i+1))
            for ext in formats:
                if ext in url:
                    break
            with open(path + os.sep + name + str(i) + ext, 'wb') as f:
                f.write(res.content)
        except (SystemExit, KeyboardInterrupt):
            raise
        except SyntaxError as se:
            print('SyntaxError:'+se)
        except:
            print('{}无法抓取,url -> {}'.format(name + str(i), url))

def thumbnail(root, name, resolution = (64, 64),step = 100):
    postfix = '_' + 'x'.join(map(str, resolution))
    source = os.path.join(root, name)
    target = source + postfix
    if not os.path.exists(target):
        os.mkdir(target)
    filenames = os.listdir(source)
    cnt = 1
    for filename in filenames:
        amount = len(filenames)
        bar = '\r{}{} {:6.2f}% {:5d}/{:5d}  '.format('#'*round(cnt/amount*50), '_'*round((1-cnt/amount)*50), cnt/amount*100, cnt, amount)
        print(bar, end = '')
        # if cnt % step == 0:
        #     print('正在处理第{}张图片'.format(cnt))
        try:
            im = Image.open(os.path.join(source, filename))
            width = int(im.size[0])
            height = int(im.size[1])
            length = min(im.size)
            region = im.crop(((width-length) / 2, (height-length) / 2, length + (width-length) / 2,  length + (height-length) / 2))
            region.thumbnail(resolution, Image.ANTIALIAS)
            region = region.convert('L')
            region.save(os.path.join(os.path.join(target, filename)))
        except:
            print('\r图片{}无法处理'.format(filename))
            im.close()
        cnt += 1
'''
def img2set(root, resolution = (64, 64),step = 100):
    datas = []
    postfix = '_' + 'x'.join(map(str, resolution))
    dirs = os.listdir(root)
    for dirname in dirs:
        if postfix in dirname:
            path = os.path.join(root, dirname)
            for imgname in os.list(path):
                if
'''
t = time.time()
page = 30
step = 5
resolution = (64, 64)
keyword = '猫'
d = {'Cat': 1}
name = 'Cat'
root = 'D:/Pictures/Train_Set'
formats = ['.jpg', '.png', '.jpeg', '.ico']
print('开始获取链接')
urls = get_url(keyword, page, step)
print('\n链接获取完成')
print('开始下载图片')
download(root, name, urls, step)
print('\n图片下载完成')
print('开始处理图片')
thumbnail(root, name, resolution, step)
print('\n图片处理完成')
print(time.time()-t)

input('喵喵喵！')
