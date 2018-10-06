#-*- coding: UTF-8 -*- 
from PIL import Image 
from PIL import ImageDraw 
from PIL import ImageFont
import matplotlib.pyplot as plt
import numpy as np
import time
 
def happyNewYear(srd_img_file_path, dst_img_file_path = None, scale = 2, sample_step = 3):
 start_time = int(time.time())
 
 #读取图片信息
 old_img = Image.open(srd_img_file_path)
 pix = old_img.load()
 width = old_img.size[0]
 height = old_img.size[1]
 print ("width:%d, height:%d" % (width, height))
 
 #创建新图片
 canvas = np.ndarray((height*scale, width*scale, 3), np.uint8)
 canvas[:, :, :] = 255
 new_image = Image.fromarray(canvas)
 draw = ImageDraw.Draw(new_image)
 
 #创建绘制对象
 font = ImageFont.truetype("consola.ttf", 10, encoding="unic")
 char_table = list('happy new year ')
 # font = ImageFont.truetype('simsun.ttc', 10)
 # char_table = list(u'新年快乐')
 
 #开始绘制
 pix_count = 0
 table_len = len(char_table)
 for y in range(height):
  for x in range(width):
   if x % sample_step == 0 and y % sample_step == 0:
    draw.text((x*scale, y*scale), char_table[pix_count % table_len], pix[x, y], font)
    pix_count += 1
 
 # 保存
 if dst_img_file_path is not None:
  new_image.save(dst_img_file_path)
 
 print("used time : %d second, pix_count : %d" % ((int(time.time()) - start_time), pix_count))
 print(pix_count)
 new_image.show()
 
 
happyNewYear("timg.jpeg", "output.jpg")