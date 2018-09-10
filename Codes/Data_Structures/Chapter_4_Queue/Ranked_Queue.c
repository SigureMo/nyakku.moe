#include<stdio.h>
#include<stdlib.h>

#define ElementType int
#define MAXSIZE 100

typedef struct{
	ElementType Data[MAXSIZE];
	int Rear;
	int Front; 
} QNode, *Queue;

void AddQ(Queue PtrQ, ElementType item);
ElementType DeleteQ(Queue PtrQ);

void AddQ(Queue PtrQ, ElementType item){
	if ((PtrQ->Rear+1)%MAXSIZE == PtrQ->Front){
		printf("队列满");
		return;
	}
	PtrQ->Rear = (PtrQ->Rear)%MAXSIZE;
	PrtQ->Data[PtrQ->Rear] = item;
}

ElementType DeleteQ(Queue PtrQ){
	if (PtrQ->Front==PtrQ->Rear){
		printf("队列空");
		return ERROR;
	}
	PtrQ->Front=(PtrQ->Front+1)%MAXSIZE;
	return PtrQ->Data[PtrQ->Front];
}
