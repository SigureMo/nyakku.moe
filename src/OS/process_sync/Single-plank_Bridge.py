'''
# 独木桥问题

两个相对方向的车依次到达一座独木桥的两端

在任一时刻只允许一个方向的车在桥上通行

设计一个交通管制方案，使两个方向的车顺利通过该桥
'''

import random
import time

from utils.primitive import *
from utils.process import Process, all_start

left = Semaphore(1)
right = Semaphore(1)
leftcount = 0
rightcount = 0

class LeftCar(Process):

    def __init__(self, num):
        self.num = num
        super().__init__()

    def run(self):
        global leftcount
        while True:
            # print(left.value, right.value)
            wait(self, left)
            if leftcount == 0:
                wait(self, right)
            leftcount += 1
            signal(self, left)

            self.cross()

            wait(self, left)
            leftcount -= 1
            if leftcount == 0:
                signal(self, right)
            signal(self, left)

            time.sleep(random.randint(0, 1000) / 1000)

    def cross(self):
        print("Car %s ←" % self.num)

class RightCar(Process):

    def __init__(self, num):
        self.num = num
        super().__init__()

    def run(self):
        global rightcount
        while True:
            # print(left.value, right.value)
            wait(self, right)
            if rightcount == 0:
                wait(self, left)
            rightcount += 1
            signal(self, right)

            self.cross()

            wait(self, right)
            rightcount -= 1
            if rightcount == 0:
                signal(self, left)
            signal(self, right)

            time.sleep(random.randint(0, 1000) / 1000)

    def cross(self):
        print("Car %s →" % self.num)

all_start(
    *[LeftCar(i) for i in range(3)],
    *[RightCar(i) for i in range(3)],
    )
