import sys
import os

from cv2 import cv2

img_dir = "docs/Images/"
bak_dir = "docs/Images_bak/"
img_names = sys.argv[1: ]

W = 800

def process(img_name):
    """ 处理一张图片 """

    bak_path = os.path.join(bak_dir, img_name)
    img_path = os.path.join(img_dir, img_name)
    # 备份
    with open(img_path, 'rb') as fr, open(bak_path, 'wb') as fw:
        fw.write(fr.read())
    # 读取
    img = cv2.imread(img_path)
    # 缩小
    h, w = img.shape[: 2]
    if w > W:
        h = h * W // w
        w = W
        img = cv2.resize(img, (w, h),interpolation=cv2.INTER_CUBIC)
    # 滤波
    img = cv2.bilateralFilter(img, 40, 30, 75)
    # 转为灰度
    img = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
    # 过滤背景
    img[img > 220] = 255
    # 展示
    cv2.imshow('im', img)
    cv2.waitKey(0)
    # 写入
    cv2.imwrite(img_path, img)

for img_name in img_names:
    print(f"processing img {img_name}", end="\r")
    process(img_name)
