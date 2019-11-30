from threading import Thread, Event
from utils.primitive import MUTEX

class Process(Thread):
    """ 伪进程类
    为了在 Python 中更容易地实现并发操作，故使用多线程来模拟（大概可以？）
    """

    def __init__(self):
        super().__init__()
        self.setDaemon(True)
        self.__flag = Event()
        self.__flag.set()

    def pause(self):
        self.__flag.clear()
        MUTEX.release()
        self.__flag.wait()
        MUTEX.acquire()

    def restart(self):
        self.__flag.set()

def all_start(*pros):
    for pro in pros:
        pro.start()

    try:
        for pro in pros:
            while True:
                pro.join(2)
                if not pro.isAlive:
                    break
    except (SystemExit, KeyboardInterrupt):
        print("Ctrl-C pressed")


