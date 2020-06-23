// 两个有序链表序列的合并
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
	List L, front, tmp;
	L = (List)malloc(sizeof(struct Node));
	front = L;
	scanf("%d", &size);
	while(size--){
		L->Next = (List)malloc(sizeof(struct Node));
		scanf("%d", &(L->Next->Data));
		L = L->Next;
	}
	L->Next = NULL;
	return front;
}

void Print( List L ){
	L = L->Next; 
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
		printf("NULL\n");
	}
}

/* 你的代码将被嵌在这里 */
List Merge( List L1, List L2 ){
	List front, rear, tmp;
	front = (List)malloc(sizeof(struct Node));
	rear = front;
	tmp = L1;
	L1 = L1->Next;
	tmp->Next = NULL;
	tmp = L2;
	L2 = L2->Next;
	tmp->Next = NULL;
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
	return front;
}
//1. front rear的意义：
//一个指针指向链表头部以便最后return 另外一个指向尾部以便实时向尾部添加元素
//2. 建立临时头结点的意义（这题本身就有头结点，不算临时）： 
//原来很不理解呀，但是一写代码就发现了
//我会在循环体内不自主的使用rear = rear->Next;
//呃等等，rear->Next是谁？rear好像只是一个没有管理内容的指针，emmmmmm所以就给它malloc了一个地方先让他玩会 。
//因为比起来另一个方法：根据是否是第一个元素进行讨论，显然大家都喜欢一致性比较高的循环体，所以啊，就稍稍明白了点
//另外让做了一晚上才发现这题没头结点的我先哭会o(╥﹏╥)o 
