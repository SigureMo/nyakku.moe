#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct{
	ElementType Data;
	int Parent;
} SetType;

int Find(SetType S[], ElementType X){
	int i;
	for (i=0; i<MaxSize && S[i].Data != X; i++);
	if (i >= MaxSize) return -1;
	for(;S[i].Parent >= 0; i = S[i].Parent);
	return i;
}

void Union(SetType S[], ElementType X1, ElementType X2){
	int Root1, Root2;
	Root1 = Find(S, X1);
	Root2 = Find(S, X2);
	if (Root1 != Root2) S[Roor2].Parent = Root1;
}


// 优化1：按秩归并 
// 这样的Union可能会导致树不断长高使得Find效率不断降低，所以就需要一种方法减缓树的增长
// 可以在Union的时候判断两棵树哪个更高，将低的“嫁接”到高的那棵上面就好
/* 
具体实现嘛，就是要在树的根节点获取到树的高度信息，这就需要重新组织下结构，
原来根是存储的-1以表示根结点，现在可以存储 树高度的相反数 喵喵喵 
*/
// 另外还可以比规模，不过都一样啦 

// 优化2：路径压缩
// 每一次Find的时候利用尾递归将该路径上的各结点贴到根结点上
