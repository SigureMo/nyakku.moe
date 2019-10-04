import h5py
import numpy as np

from PIL import Image

def imgs2pdf(img_path_list, pdf_path):
    """ 将图片列表转为 PDF 文件 """
    img_01 = Image.open(img_path_list[0])
    img_others = []
    for img_path in img_path_list[1:]:
        img = Image.open(img_path)
        if img.mode == "RGBA" or img.mode == "P":
            img = img.convert('RGB')
            img_others.append(img)
        else:
            img_others.append(img)
    img_01.save(pdf_path, "PDF", resolution=100.0, save_all=True, append_images=img_others)

def tailor(im, shape):
    """ 中心裁剪 """
    width = int(im.size[0])
    height = int(im.size[1])
    if width < shape[0] or height < shape[1]:
        return
    length = min(im.size)
    region = im.crop(((width-length) / 2, (height-length) / 2, length + (width-length) / 2,  length + (height-length) / 2))
    region.thumbnail(shape, Image.ANTIALIAS)
    return region

def reshape_circle(im):
    """ 将图片变成圆形 """
    circle = lambda x, y, size :(x-size/2)**2 + (y-size/2)**2 < (size/2)**2
    im = im.convert("RGBA")
    size = min(im.size)
    om = Image.new('RGBA', (size, size),(255,255,255,0))
    for i in range(size):
        for j in range(size):
            if circle(i, j, size):
                om.putpixel((i,j),im.getpixel((i,j)))
            else:
                om.putpixel((i,j), (0, 0, 0, 0))
    return om
