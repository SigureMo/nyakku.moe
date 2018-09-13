/*
# Pop Sequence
Specification
[IN]
    Each input file contains one test case. For each case, the first line contains 3 numbers (all no 
	more than 1000): M (the maximum capacity of the stack), N (the length of push sequence), and K 
	(the number of pop sequences to be checked). Then K lines follow, each contains a pop sequence 
	of N numbers. All the numbers in a line are separated by a space.
[OUT]
    For each pop sequence, print in one line "YES" if it is indeed a possible pop sequence of the stack,
	 or "NO" if not.
Sample
[IN]
5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2
[OUT]
YES
NO
NO
YES
NO
*/


#include <stdio.h>
#include <stdlib.h>

int MAXSIZE;

typedef int ElementType;
typedef int Status;

typedef struct{
	ElementType Data[1000];
	int Top; 
} SNode, *Stack;

Stack InitStack();
Status Push(Stack PtrS, ElementType item); 
ElementType Pop(Stack PtrS);
Status Check(int N);

int main(){
	int N, K;
	scanf("%d %d %d",&MAXSIZE, &N, &K);
	while(K--){
		if (Check(N)){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
	return 0;
}

Stack InitStack(){
	Stack S;
	S = (Stack)malloc(sizeof(SNode));
	S->Top = -1;
	return S;
}

Status Push(Stack PtrS, ElementType item){
	if (PtrS->Top == MAXSIZE-1){
		return 0;
	}
	else{
		PtrS->Data[++(PtrS->Top)] = item;
		return 1;
	}
}

ElementType Pop(Stack PtrS){
	if (PtrS->Top == -1){
		return 0;
	}
	else{
		return PtrS->Data[(PtrS->Top)--];
	}
} 

Status Check(int N){
	Stack S = InitStack();
	ElementType this, t;
	Status flag = 1;
	t = 1;
	while(N--){
		scanf("%d", &this);
		while (this >= t){
			if (!Push(S, t++)){
				flag = 0;
				break;
			}
		}
		if (this < t){
			if(Pop(S)!=this){
				flag = 0;
				continue;
			}
		}
	}
	return flag;
}
//因为输入数据是从1-N已经排好序的数据 所以可以根据this与1-N的关系得出
//比如读入的第一个数是6 那么就一定要先把123456全部压人栈中 然后进行pop 才可能实现 
