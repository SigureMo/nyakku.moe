#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct TreeNode *HuffmanTree;
typedef TreeNode{
	int Weight;
	HuffmanTree Left, Right;
}; 

HuffmanTree Huffman(MinHeap H){
	int i;
	HuffmanTree T;
	BuildMinHeap(H);
	for (i = 1; i<H->Size; i++){
		T = malloc(sizeof(struct TreeNode));
		T->Left = DeleteMin(H);
		T->Right = DeleteMin(H);
		T->Weight = T->Left->Weight+T->Right->Weight;
		Insert(H, T);
	}
	T = DeleteMin(H);
	return T;
}

// 利用了最小堆对数据进行排序，并逐渐将堆内数据组织成一棵树
// 当然，堆内数据存储的是树结点或者说是已组织好的树Root与未组织好的零散Node 
