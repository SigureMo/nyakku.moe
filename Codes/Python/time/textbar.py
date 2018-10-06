import random
import time
l=50
count=0
print('Pi值的计算'.center(l+14,'-'))
try:
    n=eval(input('请输入一个正整数作为计算次数：'))
    print("计算开始".center(l+14,"-"))
    start=time.perf_counter()
    for i in range(n):
        x=random.random()
        y=random.random()
        if x*x+y*y<1:
            count+=1
            a=i/n*100
            b='*'*int(i*l/n)
            c='.'*int((n-i)*(l/n))
            end=time.perf_counter()
            t=end-start
            print("\r{:>6.2f}%[{}->{}]{:>6.2f}s ".format(a,b,c,t),end='')
    print('\n'+"计算完毕".center(l+14,'-'))
    print('圆周率Pi约为{}\n耗时{:.2f}s'.format(count/n*4,end-start))
except Exception:
    print("请输入一个正整数！")
finally:
    input("Press <enter>")
