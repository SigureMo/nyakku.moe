#define MaxVertexNum 100

typedef char VertexType;
typedef int InfoType;

// 边结点，每条边指示下一条边
typedef struct _arcnode {
  int adjvex;
  struct _arcnode *next;
  InfoType info;
} ArcNode;

// 顶点结点，每个顶点有着第一条指向的边
typedef struct VNode {
  VertexType data;
  ArcNode *first;
} VNode, AdjList[MaxVertexNum];

// 图，记录着邻接表
typedef struct {
  AdjList vertices;
  int vexnum, arcnum;
} ALGraph;
