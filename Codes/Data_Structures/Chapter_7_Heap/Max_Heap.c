#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct HeapStruct * MaxHeap;
struct HeapStruct{
	ElementType *Elements;
	int Size;
	int Capacity;
}; 

MaxHeap Create(int MaxSize){
	MaxHeap H = malloc(sizeof(struct HeapStruct));
	H->Elements = malloc((MaxSize+1) * sizeof(ElementType));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Elements[0] = MaxData;
	return H;
}

void Insert(MaxHeap H, ElementType item){
	int i;
	if (IsFull(H)){
		printf("最大堆已满");
		return;
	}
	i = ++H->Size;
	for(;H->Elements[i/2]<item; i/=2)
	    H->Elements[i] = H->Elements[i/2];
	H->Elements[i] = item;
}

ElementType DeleteMax(MaxHeap H){
	int Parent, Child;
	ElementType MaxItem, temp;
	if(IsEmpty(H)){
		printf("最大堆已为空");
		return;
	}
	MaxItem = H->Elements[1];
	temp = H->Elements[H->Size--];
	for(Parent=1; Parent*2<=H->Size;Parent=Child){
		Child = Parent*2;
		if ((Child!=H->Size) && (H->Elements[Child]<H->Elements[Child+1]))
		    Child++;
		if(temp >= H->Elements[Child]) break;
		else
		    H->Elements[Parent] = H->Elements[Child];
	}
	H->Elements[Parent] = temp;
	return MaxItem; 
}
