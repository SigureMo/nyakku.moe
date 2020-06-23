import random

from utils.primitive import *
from utils.process import Process, all_start

"""
# 生产者消费者问题

使用多线程模拟进程并发引发的同步问题，其中的生产者消费者问题是其中最为经典的模型，故尝试解决之

虽然说并不是真正的线程并发，但是在调试过程中确实遇到了并发带来的临界资源以及 utils 开发不成熟引发的死锁问题
"""

class WorkQueue(list):

    def __init__(self, size):
        super().__init__()
        self.size = size
        self.index = 0
        self.extend([None for i in range(size)])

    def put(self, item):
        self[self.index] = item
        self.index += 1
        self.check_index()

    def get(self):
        if self.index < self.size:
            self[self.index] = None
        self.index -= 1
        self.check_index()
        return self[self.index]

    def empty(self):
        return self.index == 0

    def full(self):
        return self.index == self.size

    def check_index(self):
        print("index: %s" % self.index)
        print(self)
        assert self.index >= 0 and self.index <= self.size

class Proceducer(Process):

    def __init__(self):
        super().__init__()

    def run(self):
        while True:
            wait(self, empty)
            wait(self, mutex)

            # 临界区
            i = random.randint(0, 100)
            work_queue.put(i)
            print(f"Put {i}")

            signal(self, mutex)
            signal(self, full)
            print_sem(mutex, full, empty)


class Consumer(Process):

    def __init__(self):
        super().__init__()

    def run(self):
        while True:
            wait(self, full)
            wait(self, mutex)

            # 临界区
            print("Get {}".format(work_queue.get()))

            signal(self, mutex)
            signal(self, empty)
            print_sem(mutex, full, empty)


def print_sem(*sems):
    print("sems: " + ' '.join([str(sem.value) for sem in sems]))

size = 20
work_queue = WorkQueue(size)
mutex = Semaphore(1)
full = Semaphore(0)
empty = Semaphore(size)

c1 = Consumer()
p1 = Proceducer()
p2 = Proceducer()
p3 = Proceducer()

all_start(c1, p1, p2, p3)

print("Done!")
