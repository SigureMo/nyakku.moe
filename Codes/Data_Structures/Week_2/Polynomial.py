'''
# 一元多项式的乘法与加法运算
设计函数分别求两个一元多项式的乘积与和。
输入格式:
输入分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零
项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。

输出格式:
输出分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字
间以空格分隔，但结尾不能有多余空格。零多项式应输出0 0。

输入样例:
4 3 4 -5 2  6 1  -2 0
3 5 20  -7 4  3 1
输出样例:
15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
5 20 -4 4 -5 2 9 1 -2 0
'''
# 真的懒地用C实现了（emmmm主要是课件里已经实现了不想“照抄”） 本周前几道题做的心态有点崩 最后一个让我用Python写下缓会儿……

import re

class Polynomial():
    def __init__(self, args = []):
        self.args = {}
        for i in range(len(args)//2):
            self.args[int(args[2*i+1])] = int(args[2*i])
        # print(self.args)

    def add(self, poly):
        p = Polynomial()
        p.args = self.args
        for k, v in poly.args.items():
            if p.args.get(k):
                p.args[k] += v
                if p.args[k] == 0:
                    del p.args[k]
            else:
                p.args[k] = v
        if not len(p.args):
            p.args[0] = 0
        return p

    def multiplication(self, poly):
        p = Polynomial()
        for k2, v2 in poly.args.items():
            for k1, v1 in self.args.items():
                if p.args.get(k1+k2):
                    p.args[k1+k2] += v1 * v2
                    if p.args[k1+k2] == 0:
                        del p.args[k1+k2]
                else:
                    p.args[k1+k2] = v1 * v2
        if not len(p.args):
            p.args[0] = 0
        return p

    def __str__(self):
        argsList = []
        args = sorted(self.args.items(), key = lambda item:item[0],reverse=True)
        for k, v in args:
            argsList.append(v)
            argsList.append(k)
        return ' '.join(list(map(str, argsList)))
                    
def main():
    poly1 = Polynomial(re.split(r" +",input())[1:])
    poly2 = Polynomial(re.split(r" +",input())[1:])
    print(poly1.multiplication(poly2))
    print(poly1.add(poly2))

if __name__ == '__main__':
    main()

'''
Tests
6 1 2 1 1
3 1 1 -1 0
'''
