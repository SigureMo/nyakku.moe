from multithreading import ThreadPool

def f():
    pass
    #print('31234\n')
    #print('1\n')

pool = ThreadPool(10)
for i in range(20):
    pool.addTask(f)
pool.run()
pool.join()
input()
