#include <iostream>
#include <queue>
#include <cstring>
#define MaxVertexNum 100

using namespace std;
typedef int Vertex;
typedef int Edge;

class Graph {
  public:
    int vexnum, arcnum;
    Vertex vertices[MaxVertexNum];
    Edge edges[MaxVertexNum][MaxVertexNum];
    Graph(int size) {
      /** 初始化一个 size * size 的图 */
      vexnum = size;
      arcnum = 0;
      for (int i = 0; i < vexnum; i++) {
        for (int j = 0; j < vexnum; j++) {
          edges[i][j] = 0;
        }
      }
      for (int i = 0; i < vexnum; i++) {
        vertices[i] = 0;
      }
    }
    void addEdge(Edge e, Vertex v, Vertex w) {
      /** 向图中添加边 */
      edges[v][w] = edges[w][v] = e;
      arcnum++;
    }
    Vertex firstNeighbor(Vertex v) {
      /** 寻找顶点 v 的第一个邻接结点 */
      for (int i = 0; i < vexnum; i++) {
        if (edges[v][i]) return i;
      }
      return -1;
    }
    Vertex nextNeighbor(Vertex v, Vertex w) {
      /** 根据顶点 v 的当前邻接结点 w 寻找下一个邻接结点 */
      for (int i = w+1; i < vexnum; i++) {
        if (edges[v][i]) return i;
      }
      return -1;
    }
    void print() {
      /** 以邻接矩阵方式打印图的状态 */
      for (int i = 0; i < vexnum; i++) {
        for (int j = 0; j < vexnum; j++) {
          cout << edges[i][j] << " ";
        }
        cout << endl;
      }
    }
};

bool visited[MaxVertexNum] = {false};
void BFS(Graph G, Vertex v);
void DFS(Graph G, Vertex v);
void visit(Vertex v);

int main() {
  Graph G(8);
  int edges[][2] = {{0, 1}, {0, 2}, {1, 3}, {1, 4},
                    {2, 5}, {2, 6}, {3, 7}, {4, 7}, {5, 6}};
  for (auto edge : edges) {
    G.addEdge(1, edge[0], edge[1]);
  }
  G.print();
  cout << "BFS:\t";
  BFS(G, 0);
  cout << endl;
  memset(visited, 0, sizeof(visited));
  cout << "DFS:\t";
  DFS(G, 0);
  cout << endl;
  return 0;
}
// BFS_BLOCK
void BFS(Graph G, Vertex v) {
  /** 从顶点 v 开始对图 G 进行广度优先遍历 */
  queue<Vertex> Q;
  visit(v);             // 注意，放进队列之前就已经访问了，而不是拿出来才访问
  visited[v] = true;
  Q.push(v);
  while (!Q.empty()) {
    Vertex v = Q.front();
    Q.pop();
    for (Vertex w = G.firstNeighbor(v); w >= 0; w = G.nextNeighbor(v, w)) {
      if (!visited[w]) {
        visit(w);
        visited[w] = true;
        Q.push(w);
      }
    }
  }
}
// BFS_BLOCK
// DFS_BLOCK
void DFS(Graph G, Vertex v) {
  /** 从顶点 v 开始对图 G 进行深度优先遍历 */
  visit(v);
  visited[v] = true;
  for (Vertex w = G.firstNeighbor(v); w >= 0; w = G.nextNeighbor(v, w)) {
    if (!visited[w]) {
      DFS(G, w);
    }
  }
}
// DFS_BLOCK
void visit(Vertex v) {
  /** 访问顶点 v */
  cout << v << "\t";
}
