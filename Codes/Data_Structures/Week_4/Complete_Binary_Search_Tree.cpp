/*
# Complete Binary Search Tree
A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

- The left subtree of a node contains only nodes with keys less than the node's key.
- The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
- Both the left and right subtrees must also be binary search trees.
A Complete Binary Tree (CBT) is a tree that is completely filled, with the possible exception of the b
ottom level, which is filled from left to right.

Now given a sequence of distinct non-negative integer keys, a unique BST can be constructed if it is 
required that the tree must also be a CBT. You are supposed to output the level order traversal seque
nce of this BST.
# Input Specification:
Each input file contains one test case. For each case, the first line contains a positive integer N 
(≤1000). Then N distinct non-negative integer keys are given in the next line. All the numbers in a
 line are separated by a space and are no greater than 2000.
# Output Specification:
For each test case, print in one line the level order traversal sequence of the corresponding complete
 binary search tree. All the numbers in a line must be separated by a space, and there must be no 
extra space at the end of the line.
# Sample Input:
```
10
1 2 3 4 5 6 7 8 9 0
```
# Sample Output:
```
6 3 8 1 5 7 9 0 2 4
```
*/

/*
思路：
1. 中序遍历是升序的，故先升序排序输入序列 
2. 建立完全二叉树（无值） 
3. 中序遍历赋值
4. 层序遍历输出 
*/

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef int bool;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree Insert( BinTree BST, ElementType X );
BinTree CreatTree(int N);
bool isSameTree(BinTree T1, BinTree T2);

int main()
{
    BinTree BST;
    int N, i;
    while(1){
    	scanf("%d", &N);
    	if (N){
    		scanf("%d", &i);
    		BST = CreatTree(N);
    		while(i--){
    			if (isSameTree(BST, CreatTree(N))){
    				printf("Yes\n");
				}
				else printf("No\n");
			}
		}
		else break;
	}

    return 0;
}

BinTree Insert( BinTree BST, ElementType X ){
	if(BST){
		if (X > BST->Data){
			BST->Right = Insert(BST->Right, X);
		}
		else if (X < BST->Data){
			BST->Left = Insert(BST->Left, X);
		}
	}
	else{
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = NULL;
		BST->Right = NULL;
	}
	return BST; 
}

BinTree CreatTree(int N){
	BinTree BST = NULL;
	ElementType X;
	while(N--){
		scanf("%d", &X);
		BST = Insert(BST, X);
	}
	return BST;
}
bool isSameTree(BinTree T1, BinTree T2){
	if(T1&&T2){
		if((T1->Data == T2->Data)&&(isSameTree(T1->Left, T2->Left)&&isSameTree(T1->Right,T2->Right))) return 1;
		else return 0;
	}
	else if(!T1&&!T2) return 1;
	else return 0;
}
