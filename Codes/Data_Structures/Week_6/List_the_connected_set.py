'''
# 列出连通集
给定一个有N个顶点和E条边的无向图，请用DFS和BFS分别列出其所有的连通集。假设顶点从
0到N−1编号。进行搜索时，假设我们总是从编号最小的顶点出发，按编号递增的顺序访问邻
接点。
# 输入格式:
输入第1行给出2个整数N(0<N≤10)和E，分别是图的顶点数和边数。随后E行，每行给出一条
边的两个端点。每行中的数字之间用1空格分隔。
# 输出格式:
按照"`${v_1 v_2 ... v_k}$`"的格式，每行输出一个连通集。先输出DFS的结果，再输出
BFS的结果。
# 输入样例:
```
8 6
0 7
0 1
2 0
4 1
2 4
3 5
```
# 输出样例:
```
{ 0 1 4 2 7 }
{ 3 5 }
{ 6 }
{ 0 1 2 7 4 }
{ 3 5 }
{ 6 }
```
'''

def DFS(vertex):
    visited[vertex] = True
    t.append(str(vertex))
    for i in sorted(graph[vertex]):
        if not visited[i]:
            DFS(i)

def BFS():
    while Queue:
         vertex = Queue.pop()
         if visited[vertex]:
             continue
         visited[vertex] = True
         t.append(str(vertex))
         for i in sorted(graph[vertex]):
             if not visited[i]:
                 Queue.insert(0, i)
    

N, E = list(map(int, input().split(' ')))
t = []
visited = [False] * N
Queue = []
graph = dict(zip([i for i in range(N)], [[] for i in range(N)]))
for i in range(E):
    k = list(map(int, input().split(' ')))
    graph[k[0]].append(k[1])
    graph[k[1]].append(k[0])

# print(graph)

for i in sorted(graph.keys()):
    if not visited[i]:
        DFS(i)
        print('{ ' + ' '.join(t) + ' }')
        t.clear()

visited.clear()
visited = [False] * N
    
for i in sorted(graph.keys()):
    if not visited[i]:
        Queue.insert(0, i)
        BFS()
        print('{ ' + ' '.join(t) + ' }')
        t.clear()
