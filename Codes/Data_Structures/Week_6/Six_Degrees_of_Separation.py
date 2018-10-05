'''
# 六度空间
“六度空间”理论又称作“六度分隔（Six Degrees of Separation）”理论。这个理论可
以通俗地阐述为：“你和任何一个陌生人之间所间隔的人不会超过六个，也就是说，最多通
过五个人你就能够认识任何一个陌生人。”如图1所示。
![图1 六度空间示意图]()
“六度空间”理论虽然得到广泛的认同，并且正在得到越来越多的应用。但是数十年来，
试图验证这个理论始终是许多社会学家努力追求的目标。然而由于历史的原因，这样的研究
具有太大的局限性和困难。随着当代人的联络主要依赖于电话、短信、微信以及因特网上即
时通信等工具，能够体现社交网络关系的一手数据已经逐渐使得“六度空间”理论的验证成
为可能。

假如给你一个社交网络图，请你对每个节点计算符合“六度空间”理论的结点占结点总数的
百分比。
# 输入格式:
输入第1行给出两个正整数，分别表示社交网络图的结点数N（1<N≤10
​4
​​ ，表示人数）、边数M（≤33×N，表示社交关系数）。随后的M行对应M条边，每行给出一
对正整数，分别是该条边直接连通的两个结点的编号（节点从1到N编号）。
# 输出格式:
对每个结点输出与该结点距离不超过6的结点数占结点总数的百分比，精确到小数点后2位。
每个结节点输出一行，格式为“结点编号:（空格）百分比%”。
# 输入样例:
```
10 9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
```
# 输出样例:
```
1: 70.00%
2: 80.00%
3: 90.00%
4: 100.00%
5: 100.00%
6: 100.00%
7: 100.00%
8: 90.00%
9: 80.00%
10: 70.00%
```
'''
import time
def BFS(v):
    Queue.insert(0, v)
    last = v
    counter = 0
    while Queue and counter <= 6:
        vertex = Queue.pop()
        if visited[vertex]:
            continue
        visited[vertex] = True
        t.append(vertex)
        for i in sorted(graph[vertex]):
            if not visited[i]:
                Queue.insert(0, i)
                tail = i
        if vertex == last:
            counter += 1
            last = tail
    
N, E = list(map(int, input().split(' ')))
visited = [False] * N
t = []
Queue = []
ti = time.time()
graph = dict(zip([i for i in range(N)], [[] for i in range(N)]))
for i in range(E):
    k = list(map(lambda x : int(x) - 1, input().split(' ')))
    graph[k[0]].append(k[1])
    graph[k[1]].append(k[0])

# print(graph)

for i in sorted(graph.keys()):
    BFS(i)
    print('{}: {:4.2f}%'.format(i+1,len(t)/N*100))
    Queue.clear()
    t.clear()
    visited.clear()
    visited = [False] * N

print((time.time()-ti)*1000)
