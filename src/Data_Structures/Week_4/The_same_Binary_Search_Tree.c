/*
# 是否同一棵二叉搜索树
给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到
。例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。于是对于输入的各种插
入序列，你需要判断它们是否能生成一样的二叉搜索树。
# 输入格式:
输入包含若干组测试数据。每组数据的第1行给出两个正整数N (≤10)和L，分别是每个序列插入元素的个数和需要检
查的序列个数。第2行给出N个以空格分隔的正整数，作为初始插入序列。最后L行，每行给出N个插入的元素，属于L
个需要检查的序列。

简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入结束，这组数据不要处理。
# 输出格式:
对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，否则输出“No”。
# 输入样例：
```
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0
```
# 输出样例：
```
Yes
No
No
```
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
