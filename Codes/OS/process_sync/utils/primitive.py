from threading import Lock

MUTEX = Lock() # 为保证“原语”的完整执行，使用线程锁，但请不要在原语内调用原语，否则会死锁

class Semaphore():
    """ 信号量类
    """

    def __init__(self, value):
        self.value = value
        self.block_list = []

class SemaphoreSet():
    """ 信号量集 """

    def __init__(self, sem, lower=1, demand=1):
        self.sem = sem
        self.lower = lower
        self.demand = demand

def primitive(func):
    def new_func(process, *args):
        MUTEX.acquire()
        func(process, *args)
        MUTEX.release()
    return new_func

@primitive
def block(process):
    process.pause()

@primitive
def wakeup(process):
    process.restart()

@primitive
def wait(process, sem):
    sem.value -= 1
    if sem.value < 0:
        sem.block_list.append(process)
        process.pause() # block(process) 会死锁

@primitive
def signal(process, sem):
    sem.value += 1
    if sem.value <= 0:
        sem.block_list.pop(0).restart()

@primitive
def Swait(process, *semsets):
    if all([semset.sem.value >= semset.lower for semset in semsets]):
        for semset in semsets:
            semset.sem.value -= semset.demand
    else:
        for semset in semsets:
            semset.sem.block_list.append(process)
        process.pause()
        MUTEX.release() # 防止死锁，先释放互斥锁
        Swait(process, *semsets)
        MUTEX.acquire()

@primitive
def Ssignal(process, *semsets):
    for semset in semsets:
        semset.sem.value += semset.demand
        while len(semset.sem.block_list):
            semset.sem.block_list.pop(0).restart()
