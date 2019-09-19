typedef int ElemType;
typedef struct DNode {
  ElemType data;
  struct DNode *prior, *next;
} DNode, *DLinkList;
