from threading import Thread, Event

class Process(Thread):
    """ 伪进程类
    为了在 Python 中更容易地实现并发操作，故使用多线程来模拟（大概可以？）
    """

    def __init__(self):
        super().__init__()
        self.__singal = Event()
        self.__singal.set()

    def pause(self):
        self.__singal.clear()

    def restart(self):
        self.__singal.set()

    def wait(self):
        self.__singal.wait()

def all_start(*pros):
    for pro in pros:
        pro.start()
    for pro in pros:
        pro.join()
