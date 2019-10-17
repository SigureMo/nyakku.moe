#define MaxVertexNum 100

typedef char VertexType;
typedef int InfoType;
typedef struct _arcnode {
  bool mark;
  int ivex, jvex;
  struct _arcnode *ilink, *jlink;
  InfoType info;
} ArcNode;

typedef struct VNode {
  VertexType data;
  ArcNode *firstedge;
} VNode;

typedef struct {
  VNode adjmulist[MaxVertexNum];
  int vexnum, arcnum;
} AMLGraph;
