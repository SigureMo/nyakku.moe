#include<stdio.h>
#include<stdlib.h>

#define ElementType int
#define MAXSIZE 100

typedef struct{
	ElementType Data[MAXSIZE];
	int Top; 
} SNode, *Stack;

void Push(Stack PtrS, ElementType item); 
ElementType Pop(Stack PtrS);

int main(){
	printf("1\n");
	Node* PtrL = MakeEmpty();
	Insert(3, 1, PtrL);
	Insert(37, 1, PtrL);
	printf("%d", Find(3, PtrL));
	return 0;
}

void Push(Stack PtrS, ElementType item){
	if (PtrS->Top == MAXSIZE-1){
		printf("¶ÑÕ»Âú");
		return ;
	}
	else{
		PtrS->Data[++(PtrS->Top)] = item;
		return;
	}
}

ElementType Pop(Stack PtrS){
	if (PtrS->Top == -1){
		printf("¶ÑÕ»¿Õ");
		return ERROR;
	}
	else{
		return PtrS->Data[(PtrS->Top)--];
	}
} 
