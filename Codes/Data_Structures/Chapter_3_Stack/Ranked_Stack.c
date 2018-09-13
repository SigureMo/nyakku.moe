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
