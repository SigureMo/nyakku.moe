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
void LevelOrderTraversal(BinTree BT); //层次 
BinTree CreatBinTree();

void PreOrderTraversal(BinTree BT){
	BinTree T = BT;
	Stack S = CreatStack(MAXSIZE);
	while(T || ! IsEmpty(S)){
		while(T){
			Push(S, T);  //第一次遇到 
			printf("%5d", T->Data);
			T = T->Left;
		}

		if(!IsEmpty(S)){
			T = Pop(S);  //第二次遇到 
//			printf("%5d", T->Data);
			T = T->Right;
		}
	}
}

void InOrderTraversal(BinTree BT){
	BinTree T = BT;
	Stack S = CreatStack(MAXSIZE);
	while(T || ! IsEmpty(S)){   //看看东西都没准备好了没，准备好就出发 
		while(T){               //看看前面有木有路 
			Push(S, T);         //走呀走 
			T = T->Left;        //转向左面
		}
		                        //emmm前面没路了，咋办呢 
		if(!IsEmpty(S)){        //看看有没有退路 
			T = Pop(S);         //后面还有路，往回走啦 
			printf("%5d", T->Data);// do something For Example 在地图上做个标记 到此一游blabla 
			T = T->Right;       //转向右面 
		}
	}
}

//emmmm后序遍历非递归确实很难 还没有验证是否正确 大概就是第二次遇到之后从栈里拿出来看看 然后放回去去遍历右子树
//这就需要知道什么时候右子树遍历完了，右子树遍历完的时候肯定会先遇到一个叶子结点，之后判断自己是不是栈顶元素右孩子
//如果是的话就持续抛出，这个抛出的路径其实就是已经完全遍历过的路径，或者说，这种方法就是把整个遍历的路径实现一遍
//因为先序遍历和后序遍历在第二次遇到根节点就直接抛出了，并没有实现第三次遇到的过程 

void PostOrderTraversal(BinTree BT){
	BinTree T = BT, t;
	Stack S = CreatStack(MAXSIZE);
	while(T || ! IsEmpty(S)){
		if(!T){
			while(1){
				t = Pop(T);
				if (!(T == t->Right)){
					Push(S, T);
					break;
				}
				else{
					T = t; //第三次遇到 
					printf("%5d", T->Data);
				}
			}
		}
		while(T){
			Push(S, T); //第一次遇到 
			T = T->Left;
		}
		if(!IsEmpty(S)){
			T = Pop(S); //第二次遇到 
			Push(S, T);
//			printf("%5d", T->Data);
			T = T->Right;
		}
	}
} 
