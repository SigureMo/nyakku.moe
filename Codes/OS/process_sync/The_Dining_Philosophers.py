import random
import time

from utils.primitive import *
from utils.process import Process, all_start

"""
# 哲学家进餐问题

虽然说普通解决方案可能出现所有人同时拿起左筷子的死锁问题，但是该概率太低，并没有触发

Swait 和 Ssignal 又思索了段时间，算是得到了一个可以用的方案，但可能还是不对的
"""

class Philosopher(Process):

    def __init__(self, num):
        self.num = num
        super().__init__()

    def eat(self):
        print('Philosopher %s is eating...' % self.num)
        time.sleep(random.randint(0, 1000) / 1000)

    def think(self):
        print('Philosopher %s is thinking...' % self.num)
        time.sleep(random.randint(0, 1000) / 1000)

    def run(self):
        while True:
            # wait(self, chopsticks[self.num])
            # wait(self, chopsticks[(self.num + 1) % 5])
            Swait(self, SemaphoreSet(chopsticks[self.num]), SemaphoreSet(chopsticks[(self.num + 1) % 5]))

            self.eat()
            # signal(self, chopsticks[self.num])
            # signal(self, chopsticks[(self.num + 1) % 5])
            Ssignal(self, SemaphoreSet(chopsticks[self.num]), SemaphoreSet(chopsticks[(self.num + 1) % 5]))

            self.think()

chopsticks = [Semaphore(1), Semaphore(1), Semaphore(1), Semaphore(1), Semaphore(1)]

all_start(Philosopher(0), Philosopher(1), Philosopher(2), Philosopher(3), Philosopher(4))

print("Done!")
