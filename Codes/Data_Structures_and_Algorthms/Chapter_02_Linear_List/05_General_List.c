#define MaxSize 100

typedef ElemType int
typedef struct _node{
	int tag;      // 用以标记该结点数据是另一个广义表还是单元素（0->单元素,1->广义表）
	union{        // 子表指针域subList与单元素数据域Data复用，即共用存储空间
		ElemType data;
		struct _node *subList;
	};
	struct _node *next;
} GNode, *GList;
