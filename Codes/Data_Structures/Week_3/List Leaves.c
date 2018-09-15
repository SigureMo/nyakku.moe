/*
# List Leaves 还要自己做queue 烦哦 用java做去了 
Given a tree, you are supposed to list all the leaves in the order of top down, and left to right.
## Specification:
IN
Each input file contains one test case. For each case, the first line gives a positive integer N 
(≤10) which is the total number of nodes in the tree -- and hence the nodes are numbered from 0 to 
N?1. Then N lines follow, each corresponds to a node, and gives the indices of the left and right 
children of the node. If the child does not exist, a "-" will be put at the position. Any pair of 
children are separated by a space.
OUT
For each test case, print in one line all the leaves' indices in the order of top down, and left 
to right. There must be exactly one space between any adjacent numbers, and no extra space at the 
end of the line.
## Sample
IN
8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6
 
OUT
4 1 5

*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define Tree int
#define Null -1



struct TreeNode{
	Tree Left;
	Tree Right;
} T[MAXSIZE];

typedef Tree ElementType;

typedef struct{
	ElementType Data[MAXSIZE];
	int Rear;
	int Front; 
} QNode, *Queue;



Tree BuildTree(struct TreeNode T[]);
void LevelOrderTraversal(Tree t);
void AddQ(Queue PtrQ, ElementType item);
ElementType DeleteQ(Queue PtrQ);
Queue CreatQueue(int m);
int IsEmptyQ(Queue Q);

int main(){
	Tree R;
	R = BuildTree(T);
	
	return 0;
}

Tree BuildTree(struct TreeNode T[]){
	int N, i;
	Tree cl, cr, Root;
	scanf("%d\n",&N);
	if(N){
		int check[N];
		for (i=0; i<N; i++) check[i] = 0;
		for (i=0; i<N; i++){
			scanf("%c %c\n", &cl, &cr);
			if(cl != '-'){
				T[i].Left = cl-'0';
				check[T[i].Left] = 1;
			}
			else T[i].Left = Null;
			if(cr != '-'){
				T[i].Right = cr-'0';
				check[T[i].Right] = 1;
			}
			else T[i].Right = Null;
		}
		for(i=0; i<N; i++){
			if(!check[i]) break;
		}
		Root = i;
	}
	else{
		Root =Null;
	}
	return Root;
}

void LevelOrderTraversal(Tree t){
	Queue Q;
	Tree tmp;
	if (t==Null) return;
	Q = CreatQueue(MAXSIZE);
	AddQ(Q, t);
	while (!IsEmptyQ(Q)){
		tmp = DeleteQ(Q);
		if((T[tmp].Left==Null)&&(T[tmp].Right==Null)){
			printf("%d ", tmp);
		}
		if(T[tmp].Left!=Null) AddQ(Q, T[tmp].Left);
		if(T[tmp].Right!=Null) AddQ(Q, T[tmp].Right);
	}
} 

Queue CreatQueue(int m){
	Queue Q;
	Q = (Queue)malloc(sizeof(QNode));
	Q->Front = Q->Rear = 0;
}

int IsEmptyQ(Queue Q){
	if (Q->Front==Q->Rear){
		return 1;
	}
	else{
		return 0;
	}
}

void AddQ(Queue PtrQ, ElementType item){
	if ((PtrQ->Rear+1)%MAXSIZE == PtrQ->Front){
		return;
	}
	PtrQ->Rear = (PtrQ->Rear)%MAXSIZE;
	PtrQ->Data[PtrQ->Rear] = item;
}

ElementType DeleteQ(Queue PtrQ){
	if (PtrQ->Front==PtrQ->Rear){
		return;
	}
	PtrQ->Front=(PtrQ->Front+1)%MAXSIZE;
	return PtrQ->Data[PtrQ->Front];
}
