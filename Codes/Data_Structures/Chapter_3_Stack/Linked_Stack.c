#include<stdio.h>
#include<stdlib.h>

#define ElementType int
#define MAXSIZE 100

typedef struct _node{
	ElementType Data;
	struct _node *Next;
} SNode, *Stack;

Stack CreateStack();
int IsEmpty(Stack S);
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

Stack CreateStack(){
	Stack S;
	S = (Stack)malloc(sizeof(SNode));
	S->Next = NULL;
	return S;
}

int IsEmpty(Stack S){
	return (S->Next == NULL);
}

void Push(Stack PtrS, ElementType item){
	Stack TmpCell;
	TmpCell = (Stack)malloc(sizeof(SNode));
	TmpCell->Data = item;
	TmpCell->Next = PtrS->Next;
	PtrS->Next = TmpCell;
}

ElementType Pop(Stack PtrS){
	Stack FirstCell;
	ElementType TopElem;
	if (IsEmpty(PtrS)){
		printf("¶ÑÕ»¿Õ");
	}
	else{
		FirstCell = PtrS->Next;
		PtrS->Next = FirstCell->Next;
		TopElem = FirstCell->Data;
		free(FirstCell);
		return TopElem;
	}
} 
