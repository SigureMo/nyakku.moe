from threading import Lock

MUTEX = Lock() # 为保证“原语”的完整执行，使用线程锁，但请不要在原语内调用原语，否则会死锁

class Semaphore():
    """ 信号量类
    """

    def __init__(self, value):
        self.value = value
        self.block_list = []

def primitive(func):
    def new_func(process, *args):
        MUTEX.acquire()
        func(process, *args)
        MUTEX.release()
        process.wait()
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
def Swait(process, *sems):
    # while True:
    if all([sem.value >=1 for sem in sems]):
        for sem in sems:
            sem.value -= 1
        # break
    else:
        for sem in sems:
            sem.block_list.append(process)
        process.pause()

def Ssignal(process, *sems):
    for sem in sems:
        sem.value += 1
        if len(sem.block_list):
            sem.block_list.pop(0).restart()
