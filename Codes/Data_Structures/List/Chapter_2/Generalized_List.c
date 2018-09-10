#include<stdio.h>
#include<stdlib.h>

#define ElementType int
#define MAXSIZE 100

typedef struct _node{
	int Tag;           //用以标记该结点数据是另一个广义表还是单元素（0->单元素,1->广义表） 
	union{             //子表指针域SubLIst与单元素数据域Data复用，即共用存储空间 
		ElementType Data;
		struct _node *SubList;
	};
	struct _node *Next; 
} Node, *List;

int Length(List PtrL); 
List FindKth(int K, List PtrL);
List Find(ElementType X, List PtrL);
List Insert(ElementType X, int i, List PtrL);
List Delete(int i, List PtrL);

int main(){
	printf("1\n");
	List PtrL;
	return 0;
}

