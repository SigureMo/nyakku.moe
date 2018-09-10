#include<stdio.h>
#include<stdlib.h>

#define ElementType int
#define MAXSIZE 100
#define ERROR 0

struct Node{
	ElementType Data;
	struct Node *Next;
};

struct QNode{
	struct Node *Rear;
	struct Node *Front;
};

typedef struct QNode *Queue;

ElementType DeleteQ(Queue PtrQ);
void AddQ(Queue PtrQ, ElementType item);

int main(){
	return 0;
}

ElementType DeleteQ(Queue PtrQ){
	struct Node *FrontCell;
	ElementType FrontElem;
	if (PtrQ->Front == NULL){
		printf("╤сап©у");
		return ERROR;
	}
	FrontCell = PtrQ->Front;
	if(PtrQ->Front == PtrQ->Rear){
		PtrQ->Front = PtrQ->Rear = NULL;
	}
	else{
		PtrQ->Front = PtrQ->Front->Next;
	}
	FrontElem = FrontCell->Data;
	free(FrontCell);
	return FrontElem;
}

void AddQ(Queue PtrQ, ElementType item){
	struct Node *RearCell;
	RearCell = (struct Node *)malloc(sizeof(struct Node));
	RearCell->Data = item;
	RearCell->Next = NULL;
	PtrQ->Rear->Next = RearCell;
}
