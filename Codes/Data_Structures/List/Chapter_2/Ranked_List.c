#include<stdio.h>
#include<stdlib.h>

#define ElementType int
#define MAXSIZE 100

typedef struct{
	ElementType Data[MAXSIZE];
	int Last; 
} Node;

Node* MakeEmpty();
ElementType FindKth(int K, Node* L);
int Find(ElementType X, Node* L);
void Insert(ElementType X, int i, Node* L);
void Delete(int i, Node* L);

int main(){
	printf("1\n");
	Node* PtrL = MakeEmpty();
	Insert(3, 1, PtrL);
	Insert(37, 1, PtrL);
	printf("%d", Find(3, PtrL));
	return 0;
}

Node* MakeEmpty(){
	Node* PtrL;
	PtrL = (Node*)malloc(sizeof(Node));
	PtrL -> Last = -1;
	return PtrL;
} 

ElementType FindKth(int K, Node* L){
	return L->Data[K];
}

int Find(ElementType X, Node* L){
	int i;
	for(i=0; i<=L->Last; i++){
		if(L->Data[i]==X){
			return i;
		}
	}
	return -1;
}

void Insert(ElementType X, int i, Node* L){
	int j;
	if(L->Last == MAXSIZE-1){
		printf("表满！");
		return;
	}
	if(i<1 || i > L->Last+2){
		printf("位置不合法！");
		return;
	}
	for(j=L->Last; j>=i-1; j--){
		L->Data[j+1] = L->Data[j];
	}
	L->Data[i-1] = X;
	L->Last++;
	return;
}

void Delete(int i, Node* L){
	int j;
	if(i<1 || i > L->Last+1){
		printf("位置不合法！");
		return;
	}
	for(j=i-1; j<L->Last; j++){
		L->Data[j] = L->Data[j+1];
	}
}
