#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define ElementType int

typedef struct _node{
	ElementType Data;
	struct _node* Left;
	struct _node* Right;
}TreeNode , Position,*BinTree; 

bool IsEmpty(BinTree BT);
//void Traversal(BinTree BT);
void PreOrderTraversal(BinTree BT);   //先序 
void InOrderTraversal(BinTree BT);    //中序 
void PostOrderTraversal(BinTree BT);  //后序 
void LevelOrderTraversal(BinTree BT); //层序 
BinTree CreatBinTree();

//路径其实一样的 只不过访问（print）时机不一样 

void PreOrderTraversal(BinTree BT){
	if (BT){
		printf("%d", BT->Data);  //只有这一行不一样 
		PreOrderTraversal(BT->Left);
		PreOrderTraversal(BT->Left);
	}
}

void InOrderTraversal(BinTree BT){
	if (BT){
		InOrderTraversal(BT->Left);
		printf("%d", BT->Data);
		InOrderTraversal(BT->Left);
	}
}

void PostOrderTraversal(BinTree BT){
	if (BT){
		PostOrderTraversal(BT->Left);
		PostOrderTraversal(BT->Left);
		printf("%d", BT->Data);
	}
} 

void LevelOrderTraversal(BinTree BT){
	Queue Q;
	BinTree T;
	if (!BT) return;
	Q = CreatQueue(MAXSIZE);
	AddQ(Q, BT);
	while (!IsEmptyQ(Q)){
		T = DeleteQ(Q);
		printf("%d\n", T->Data);
		if(T->Left) AddQ(Q, T->Left);
		if(T->Right) AddQ(Q, T->Right);
	}
} 
