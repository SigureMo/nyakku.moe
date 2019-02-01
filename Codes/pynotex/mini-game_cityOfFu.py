import math
import time
import cv2
import numpy as np

from utils.adb import ADB

""" 《穿越福城》 小游戏辅助
19 年春节前夕福袋活动，由于玩法类似前两年微信跳一跳，故参考 2018 最具潜力的项目之一，
[wechat_jump_game](https://github.com/wangshub/wechat_jump_game)略作尝试，并顺便学习下这方面的知识
"""

def get_penguin(cvimg):
    lower_penguin = np.array([0, 0, 40])
    upper_penguin = np.array([31, 20, 70])
    hsv = cv2.cvtColor(cvimg, cv2.COLOR_BGR2HSV)  # 转到HSV空间
    mask_blue = cv2.inRange(hsv, lower_penguin, upper_penguin)
    cnts = cv2.findContours(mask_blue, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
    if len(cnts) > 0:
        c = max(cnts, key = cv2.contourArea)   # 找到面积最大的轮廓
        ((x, y), radius) = cv2.minEnclosingCircle(c)  # 确定面积最大的轮廓的外接圆

        center = (int(x), int(y))
        # cv2.circle(cvimg, center, int(radius), (0, 0, 255), 3) #画出圆心
        # cv2.circle(cvimg, center, 3, (0, 0, 255), -1)
        # cv2.imshow('cvimg',cvimg)
        # if cv2.waitKey(0)==ord('q'):
        #     cv2.destroyAllWindows()
        return center, radius

def get_end_point(cvimg):
    lower_red = np.array([0, 190, 254])
    upper_red = np.array([5, 195, 255])
    hsv = cv2.cvtColor(cvimg, cv2.COLOR_BGR2HSV)  # 转到HSV空间
    mask_blue = cv2.inRange(hsv, lower_red, upper_red)
    cnts = cv2.findContours(mask_blue, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
    if len(cnts) > 0:
        cnts = list(filter(lambda cnt : cv2.contourArea(cnt) > 3, cnts))
        c = min(cnts, key = lambda cnt: cnt[0][0][1])
        ((x, y), radius) = cv2.minEnclosingCircle(c)  # 确定外接圆

        center = (int(x), int(y))
        # cv2.circle(cvimg, center, int(radius), (0, 0, 255), 3) #画出圆心
        # cv2.circle(cvimg, center, 3, (0, 0, 255), -1)
        # cv2.imshow('cvimg',cvimg)
        # if cv2.waitKey(0)==ord('q'):
        #     cv2.destroyAllWindows()
        return center

def main():
    adb = ADB()
    if not adb.is_connected():
        return
    # run!
    # adb.click((int(w * 0.5), int(h * 0.78)))
    while True:
        start_time = time.time()
        img = adb.screenshot()
        w, h = img.size
        img.save('tmp/adb/screencap.png')
        cvimg = cv2.imread('tmp/adb/screencap.png')
        start_point, radius = get_penguin(cvimg)
        end_point = get_end_point(cvimg)
        # distance = math.sqrt((start_point[0] - end_point[0]) ** 2 + (start_point[1] - end_point[1]) ** 2) / radius
        distance = math.sqrt((abs(start_point[0] - end_point[0]) - radius) ** 2 + (start_point[1] - end_point[1]) ** 2) / radius
        end_time = time.time()
        k = 88# 83.5
        t = int(k * distance)
        spend = end_time - start_time
        print('{} to {} r={:.4f}pix dis={:.4f} spend {}ms press {}ms'.format(
            start_point, end_point, radius,
            distance, int(spend * 1000), t))
        adb.swipe((int(w * 0.5)-10, int(h * 0.78)-10), (int(w * 0.5)+10, int(h * 0.78)+10), t)
        time.sleep(5)

if __name__ == '__main__':
    main()
