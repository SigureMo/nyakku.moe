// 两个有序链表序列的合并（木有仔细看题 花了半天才发现有头结点…………） 
//本题要求实现一个函数，将两个链表表示的递增整数序列合并为一个非递减的整数序列。
//Sample:
//    IN:
//	    3
//        1 3 5
//        5
//        2 4 6 8 10
//    OUT:
//        1 2 3 4 5 6 8 10 
//        NULL
//        NULL


#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data; /* 存储结点数据 */
    PtrToNode   Next; /* 指向下一个结点的指针 */
};
typedef PtrToNode List; /* 定义单链表类型 */

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
} 

List Read(){
	int size;
	List L, t, tmp;
	L = (List)malloc(sizeof(struct Node));
	scanf("%d", &size);
	t = L;
	while(size--){
		scanf("%d", &(t->Data));
		if(size){
			t->Next = (List)malloc(sizeof(struct Node)); 
			t = t->Next;
		}
		else{
			t->Next = NULL;
		}
	}
	return L;
}

void Print( List L ){
	if(L){
		int flag = 0;
		while(L){
			if(flag){
				printf(" ");
			}
			flag = 1;
			printf("%d",L->Data);
			L = L->Next;
		}
		printf("\n");
	}
	else{
		printf("NULL");
	}
}

/* 你的代码将被嵌在这里 */
List Merge( List L1, List L2 ){
	List front, rear, tmp;
	front = (List)malloc(sizeof(struct Node));
	rear = front;
	while(L1 && L2){
		if( L1->Data>L2->Data){
			rear->Next = L2;
			tmp = L2;
			rear = L2;
			L2 = L2->Next;
			tmp->Next = NULL;
		}
		else{
			rear->Next = L1;
			tmp = L1;
			rear = L1;
			L1 = L1->Next;
			tmp->Next = NULL;
		}
	}
//	if(L1) rear->Next = L1;
//	else rear->Next = L2;
	for(;L1;L1=L1->Next){
		rear->Next = L1;
		rear = rear->Next; 
	}
	for(;L2;L2=L2->Next){
		rear->Next = L2;
		rear = rear->Next; 
	}
	rear->Next = NULL;
	tmp = front;
	front = front->Next;
	free(tmp);
	return front;
}
