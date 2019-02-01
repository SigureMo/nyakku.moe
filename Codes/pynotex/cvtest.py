import cv2
import numpy as np
# from matplotlib import pyplot as plt
# image=cv2.imread('tmp/adb/screencap.png')
# HSV=cv2.cvtColor(image,cv2.COLOR_BGR2HSV)
# def getpos(event,x,y,flags,param):
#     if event==cv2.EVENT_LBUTTONDOWN:
#         print(HSV[y,x])
# #th2=cv2.adaptiveThreshold(imagegray,255,cv2.ADAPTIVE_THRESH_MEAN_C,cv2.THRESH_BINARY,11,2)
# # res = cv2.resize(HSV, (400, 400), interpolation=cv2.INTER_CUBIC)
# cv2.imshow("imageHSV",HSV)
# cv2.imshow('image',image)

# cv2.setMouseCallback("imageHSV",getpos)
# cv2.waitKey(0)
# #print (image(10,10,10))

frame = cv2.imread('tmp/adb/screencap.png')
lower_1 = np.array([0, 0, 40])
upper_1 = np.array([31, 20, 70])
lower_2 = np.array([0, 190, 254])
upper_2 = np.array([5, 195, 255])

hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)  #转到HSV空间
mask_blue = cv2.inRange(hsv, lower_2, upper_2)
cnts = cv2.findContours(mask_blue, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
if len(cnts) > 0:
    cnts = list(filter(lambda cnt : cv2.contourArea(cnt) > 3, cnts))
    c = min(cnts, key = lambda cnt: cnt[0][0][1])
    # c = max(cnts, key = cv2.contourArea)   #找到面积最大的轮廓
    ((x, y), radius) = cv2.minEnclosingCircle(c)  #确定面积最大的轮廓的外接圆

    center = (int(x), int(y))
    cv2.circle(frame, center, int(radius), (0, 0, 255), 3) #画出圆心
    cv2.circle(frame, center, 3, (0, 0, 255), -1)

cv2.imshow('frame',frame)
if cv2.waitKey(0)==ord('q'):
    cv2.destroyAllWindows()
