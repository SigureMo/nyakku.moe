#define MaxSize 50

typedef ElemType int;
typedef struct _node {
  int tag;
  union {
    ElemType data;            // 用以标记该结点数据是另一个广义表还是单元素（0->单元素,1->广义表）
    struct _node *subList;    // 子表指针域subList与单元素数据域Data复用，即共用存储空间
  };
  struct _node *next;
} GNode, *GList;
