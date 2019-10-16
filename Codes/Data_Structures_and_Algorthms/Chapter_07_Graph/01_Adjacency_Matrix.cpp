#define MaxVertexNum 100

typedef char VertexType;
typedef struct {
  VertexType Vex[MaxVertexNum];               // 顶点表
  EdgeType Edge[MaxVertexNum][MaxVertexNum];  // 邻接矩阵，边表
  int vexnum, arcnum;                         // 图中的顶点数、边数
} MGraph;
