typedef int ElemType;
typedef struct _node {
  ElemType data;
  struct _node *prior, *next;
} DNode, *DLinkList;
