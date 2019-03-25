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

N = 100
full = Semaphore(0) # Range [-1, N]
empty = Semaphore(N) # Range [-1, N]
in_ = Semaphore(1) # Range [-N+1, 1]
out = Semaphore(1) # Range [-N+1, 1]
customers = []

class Customer():

    def __init__(self):
        self.num = '{:5d}'.format(random.randint(0, 99999))

    def __str__(self):
        return "Customer" + self.num

class Enter(Process):
    """ 仅指进入动作， 不指入口实体，下同"""
    def __init__(self):
        super().__init__()

    def run(self):
        while True:
            # print(list(map(lambda x:str(x), customers)))
            print(in_.value, out.value, empty.value, full.value)
            wait(self, empty)
            wait(self, in_)

            customer = Customer()
            customers.append(customer)
            print("%s is shopping..." % customer)

            signal(self, full)
            signal(self, in_)

            time.sleep(random.randint(0, 1000) / 1000)

class Exit(Process):
    def __init__(self):
        super().__init__()

    def run(self):
        while True:
            # print(list(map(lambda x:str(x), customers)))
            print(in_.value, out.value, empty.value, full.value)
            wait(self, full)
            wait(self, out)

            index = random.randint(0, len(customers)-1)
            customer = customers.pop(index)
            print("%s was exited." % customer)

            signal(self, empty)
            signal(self, out)

            time.sleep(random.randint(0, 1000) / 1000)

all_start(Enter(), Exit())
