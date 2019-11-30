import random
import time

from utils.primitive import *
from utils.process import Process, all_start

"""
# 读者-写者问题

需求变更，要求最多 RN 个读者同时读，这里使用信号量集完成该内容

根据 Debug 的 print 内容，容易看出最多 RN 个读者同时读， 1 个写者在写
"""

file = "tmp/test.txt"
open(file, 'w').close()

class Reader(Process):

    def __init__(self, num):
        self.num = num
        super().__init__()

    def run(self):
        while True:
            Swait(self, SemaphoreSet(L, 1, 1), SemaphoreSet(mx, 1, 0))

            self.read()

            Ssignal(self, SemaphoreSet(L, None, 1))
            time.sleep(random.randint(0, 1000) / 1000)

    def read(self):
        rlist.append(self.num)
        # print("Reader %s is reading..." % self.num)
        with open(file, 'r') as f:
            print("Reader %s get %s" % (self.num, f.read()))
        time.sleep(random.randint(0, 20) / 1000)
        print('r:{}, w:{}'.format(rlist, wlist))
        rlist.pop(rlist.index(self.num))

class Writer(Process):

    def __init__(self, num):
        self.num = num
        super().__init__()

    def run(self):
        while True:
            Swait(self, SemaphoreSet(mx, 1, 1), SemaphoreSet(L, RN, 0))

            self.write()

            Ssignal(self, SemaphoreSet(mx, None, 1))
            time.sleep(random.randint(0, 1000) / 1000)

    def write(self):
        wlist.append(self.num)
        print("Writer %s is writing..." % self.num)
        with open(file, 'w') as f:
            f.write("I'm writer%02d" % self.num)
        time.sleep(random.randint(0, 1000) / 1000)
        print('r:{}, w:{}'.format(rlist, wlist))
        wlist.pop(wlist.index(self.num))


RN = 3
rlist = [] # 仅做 debug 之用
wlist = [] # 仅做 debug 之用
rmutex = Semaphore(1)
L = Semaphore(RN)
mx = Semaphore(1)

all_start(
    *[Writer(i) for i in range(5)],
    *[Reader(i) for i in range(5)],
    )
