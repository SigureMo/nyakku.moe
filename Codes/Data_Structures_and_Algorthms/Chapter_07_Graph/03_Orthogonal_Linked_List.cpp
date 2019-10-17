#define MaxVertexNum 100

typedef char VertexType;
typedef int InfoType;
typedef struct _arcnode {
  int tailvex, headvex;
  struct _arcnode *hlink, *tlink;
  InfoType info;
} ArcNode;

typedef struct _vnode {
  VertexType data;
  ArcNode *firstin, *firstout;
} VNode;

typedef struct {
  VNode xlist[MaxVertexNum];
  int vexnum, arcnum;
} GLGraph;
