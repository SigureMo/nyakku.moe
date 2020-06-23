"""
# 购物问题

某超级市场，可容纳 100 人同时购物
- 入口处备有篮子，每个购物者可持一个篮子入内购物
- 出口处结帐，并归还篮子（出、入口仅容纳一个人通过，篮子有无限多个）

1. 请用 PV 操作解决购物问题
2. 若顾客最多为 N 个人，写出算法中同步信号量值的可能变化范围（*说明算法中所定义信号量的含义和初值*）
"""

import random
import time

from utils.primitive import *
from utils.process import Process, all_start

N = 300
empty = Semaphore(100) # Range [100-N, 100]
in_ = Semaphore(1) # Range [1-min(N, 100), 1]
out = Semaphore(1) # Range [1-min(N, 100), 1]
customers = []

class Customer(Process):

    def __init__(self, num):
        self.num = num
        super().__init__()

    def walk(self):
        time.sleep(random.randint(0, 50))

    def enter(self):
        wait(self, empty)
        wait(self, in_)

        print("in：%s" % self.num)
        time.sleep(random.randint(0, 1000) / 1000)

        signal(self, in_)

    def shopping(self):
        customers.append(self.num)
        print("shopping：%s" % self.num)
        print("Empty %s" % empty.value)
        print("shopping_num %s" % len(customers))
        time.sleep(random.randint(0, 100))
        customers.pop(customers.index(self.num))

    def exit(self):
        wait(self, out)

        print("out：%s" % self.num)
        time.sleep(random.randint(0, 1000) / 1000)

        signal(self, out)
        signal(self, empty)

    def run(self):
        while True:
            self.walk()
            self.enter()
            self.shopping()
            self.exit()
            self.walk()

all_start(*[Customer(i) for i in range(N)])
