import h5py
import numpy as np

from PIL import Image

def imgs2pdf(img_path_list, pdf_path):
    img_01 = Image.open(img_path_list[0])
    img_others = []
    for img_path in img_path_list[1:]:
        img = Image.open(img_path)
        if img.mode == "RGBA":
            img = img.convert('RGB')
            img_others.append(img)
        else:
            img_others.append(img)
    img_01.save(pdf_path, "PDF", resolution=100.0, save_all=True, append_images=img_others)

def tailor(im, shape):
    width = int(im.size[0])
    height = int(im.size[1])
    if width < shape[0] or height < shape[1]:
        return
    length = min(im.size)
    region = im.crop(((width-length) / 2, (height-length) / 2, length + (width-length) / 2,  length + (height-length) / 2))
    region.thumbnail(shape, Image.ANTIALIAS)
    return region

def reshape_circle(im):
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

def imgs2h5(im_list, label_list, h5_path):
    assert len(im_list) == len(label_list)
    X = np.zeros(shape=(len(im_list), *np.array(im_list[0]).shape))
    Y = np.zeros(shape=(len(im_list)))

    for i, im in enumerate(im_list):
        X[i] = np.array(im)
        im.close()

    f = h5py.File(h5_path, 'w')
    f['X'] = X
    f['Y'] = Y
    f.close()
