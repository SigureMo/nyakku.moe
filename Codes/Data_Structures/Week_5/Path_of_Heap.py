'''
# 堆中的路径
将一系列给定数字插入一个初始为空的小顶堆`H[]`。随后对任意给定的下标`i`，打印从
`H[i]`到根结点的路径。
# 输入格式:
每组测试第1行包含2个正整数N和M(≤1000)，分别是插入元素的个数、以及需要打印的路
径条数。下一行给出区间[-10000, 10000]内的N个要被插入一个初始为空的小顶堆的整数。
最后一行给出M个下标。
# 输出格式:
对输入中给出的每个下标`i`，在一行中输出从`H[i]`到根结点的路径上的数据。数字间以
1个空格分隔，行末不得有多余空格。
# 输入样例:
```
5 3
46 23 26 24 10
5 4 3
```
# 输出样例:
```
24 23 10
46 23 10
26 10
```
'''

def insert_heap(data):
    heap.append(data)
    i = len(heap) - 1
    while heap[i] < heap[i//2]:
        heap[i], heap[i//2] = heap[i//2], heap[i]
        i = i//2

def print_heap(index):
    output = []
    while index > 0:
        output.append(heap[index])
        index = index//2
    print(' '.join(list(map(str, output))))

heap = [-10001]
input()
datas = list(map(int, input().split(' ')))
for data in datas:
    insert_heap(data)
indexes = list(map(int, input().split(' ')))
for i in indexes:
    print_heap(i)
