#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define ElementType int

typedef struct _node{
	ElementType Data;
	struct _node* Left;
	struct _node* Right;
}TreeNode , Position,*BinTree; 

Position Find(ElementType X, BinTree BST);
Position FindMin(ElementType X, BinTree BST); 
Position FindMax(ElementType X, BinTree BST);
BinTree Insert(ElementType X, BinTree BST);
BinTree Delete(ElementType X, BinTree BST);

Position Find(ElementType X, BinTree BST){
	/*
	// 递归 
	if(!BST) return NULL;
	if(X > BST->Data) return Find(X, BST->Right);
	else if(X < BST->Data) return Find(X, BST->Left);
	else return BST; 
	*/
	// 非递归
	while (BST){
		if (X>BST->Data) BST = BST->Right;
		else if (X < BST->Right) BST->Left;
		else return BST;
	} 
	return NULL;
}

Position FindMin(ElementType X, BinTree BST){
	/*
	// 递归 
	if(!BST) return NULL;
	else if (!BST->Left) return BST;
	else return FindMin(BST->Left);
	*/
	// 非递归
	if(BST)
	    while(BST->Left) BST = BST->Left;
	return BST;
}
Position FindMax(ElementType X, BinTree BST){
	/*
	// 递归 
	if(!BST) return NULL;
	else if (!BST->Right) return BST;
	else return FindMin(BST->Right);
	*/
	// 非递归
	if(BST)
	    while(BST->Right) BST = BST->Right;
	return BST;
}
BinTree Insert(ElementType X, BinTree BST){
	if(!BST){
		BST = malloc(sizeof(TreeNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
	}else{
		if(X < BST->Data) BST->Left = Insert(X, BST->Left);
		else if(X > BST->Data) BST->Right = Insert(X, BST->Right);
	}
	return BST;
}

BinTree Delete(ElementType X, BinTree BST){
	// 如果是叶节点，直接删除
	// 如果只有一个孩子结点，只需要将其儿子放到其父结点上
	// 如果两个孩子都有，可以转化为从左子树的最大值或者右子树的最小值 放在删除结点的位置上 
	Position Tmp;
	if (!BST) printf("要删除的元素未找到");
	else if(X>BST->Data) BST->Left = Delete(X, BST->Left);
	else if(X<BST->Data) BST->Right = Delete(X, BST->Right);
	else 
	    if(BST->Left && BST->Right){
	        Tmp = FindMin(BST->Right);
	        BST->Data = Tmp->Data;
	        BST->Right = Delete(BST->Data, BST->Right);
		 }
		 else{
		 	Tmp = BST;
		 	if(!BST->Left) BST = BST->Right;
		 	else if(!BST->Right) BST = BST->Left;
		 	free(Tmp);
		 }
	return BST;
}
