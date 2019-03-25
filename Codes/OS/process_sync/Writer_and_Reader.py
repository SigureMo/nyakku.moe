import random
import time

from utils.primitive import *
from utils.process import Process, all_start

"""
# 读者-写者问题

主要的问题是写的条件比较苛刻，如果将读的时间设置太短就会导致写者干等大家读的问题，所以可以将读的时间设置小点以解决该问题
"""

class Reader(Process):

    def __init__(self, num):
        self.num = num
        super().__init__()

    def run(self):
        global readcount
        while True:
            wait(self, rmutex)
            if readcount == 0:
                wait(self, wmutex)
            readcount += 1
            signal(self, rmutex)

            self.read()

            wait(self, rmutex)
            readcount -= 1
            if readcount == 0:
                signal(self, wmutex)
            signal(self, rmutex)

    def read(self):
        print("Reader %s is reading..." % self.num)
        time.sleep(random.randint(0, 20) / 1000)

class Writer(Process):

    def __init__(self, num):
        self.num = num
        super().__init__()

    def run(self):
        while True:
            wait(self, wmutex)
            self.write()
            signal(self, wmutex)

    def write(self):
        print("Writer %s is writing..." % self.num)
        time.sleep(random.randint(0, 1000) / 1000)

rmutex = Semaphore(1)
wmutex = Semaphore(1)
readcount = 0

all_start(
    *[Writer(i) for i in range(3)],
    *[Reader(i) for i in range(3)],
    )
