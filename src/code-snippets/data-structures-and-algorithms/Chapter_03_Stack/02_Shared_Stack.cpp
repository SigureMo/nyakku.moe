#define MaxSize 50

typedef int ElemType;
typedef struct {
  ElemType data[MaxSize];
  int top0;
  int top1;
} SNode, *SaStack;
