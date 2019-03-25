'''
# 进程同步
用信号量 PV 操作解决下述进程之间的同步与互斥问题

三个进程P1 P2 P3

- P1 进程通过计算将产生的整数（可能是奇数或偶数）送到容量为 200 的缓冲区 buff1 中
- P2 从 buff1 中取出偶数数据加 1 后送回到缓冲区 buff1 中
- P3 负责从 buff1 中取出奇数数据进行打印

要求：各进程不能同时进入 buff1 中 请写出每个进程的动作序列
'''

import random
import time

from utils.primitive import *
from utils.process import Process, all_start

mutex = Semaphore(1)
full = Semaphore(0)
empty = Semaphore(200)
buff1 = [] # 右侧待处理，左侧已处理

class P1(Process):

    def __init__(self):
        super().__init__()

    def run(self):
        while True:
            print_sems()
            wait(self, empty)
            wait(self, mutex)

            self.generate()

            signal(self, mutex)
            signal(self, full)

    def generate(self):
        num = random.randint(0, 99999)
        buff1.append(num)
        time.sleep(random.randint(0, 1000) / 1000)
        print("Generate %s" % num)

class P2(Process):

    def __init__(self):
        super().__init__()

    def run(self):
        while True:
            print_sems()
            wait(self, full)
            wait(self, mutex)

            self.process()

            signal(self, mutex)
            signal(self, full) # 注意

    def process(self):
        num = buff1.pop()
        if num % 2 == 0:
            num = num + 1
        buff1.insert(0, num)
        print("Process %s" % num)
        time.sleep(random.randint(0, 1000) / 1000)

class P3(Process):

    def __init__(self):
        super().__init__()

    def run(self):
        while True:
            print_sems()
            wait(self, full)
            wait(self, mutex)

            self.print()

            signal(self, mutex)
            signal(self, empty)

    def print(self):
        num = buff1.pop(0)
        if num % 2 == 0:
            buff1.append(num)
        else:
            print(num)
        time.sleep(random.randint(0, 1000) / 1000)

def print_sems():
    print(mutex.value, full.value, empty.value)

all_start(P1(), P2(), P3())
