# 限于 Robots.txt 协议 不作深度爬取

import requests
from PIL import Image

def imgs2pdf(imgs, name):
    im_01 = Image.open(imgs[0])
    im_list = []
    for img_path in imgs[1:]:
        img = Image.open(img_path)
        if img.mode == "RGBA":
            img = img.convert('RGB')
            im_list.append(img)
        else:
            im_list.append(img)
    im_01.save("tmp/{}.pdf".format(name), "PDF", resolution=100.0, save_all=True, append_images=im_list)

headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36',
    }

session = requests.Session()
session.headers.update(headers)
imgs = []

api = 'https://wenku.baidu.com/browse/getbcsurl?doc_id=3e710092be23482fb5da4c77&pn=1&rn=99999&type=ppt'
name = '固态相变原理'

for page_info in session.get(api).json():
    zoom, page = page_info.values()
    img_data = session.get(zoom).content
    img_path = 'tmp/{}{:02}.jpg'.format(name, page)
    with open(img_path, 'wb') as f:
        f.write(img_data)
    imgs.append(img_path)
    print(img_path)

imgs2pdf(imgs, name)



