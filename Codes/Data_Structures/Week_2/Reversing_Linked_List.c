// Reversing Linked List
////Given a constant K and a singly linked list L, you are supposed to reverse the links of every K elements on L. For example, given L being 1->2->3->4->5->6, if K=3, then you must output 3?2?1?6?5?4; if K=4, you must output 4-3->2->1->5->6.
//Specification:
//	IN:
//	Each input file contains one test case. For each case, the first line contains the address of the first node, a positive N (=10
//?5
//?? ) which is the total number of nodes, and a positive K (=N) which is the length of the sublist to be reversed. The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.
//
//Then N lines follow, each describes a node in the format:
//
//Address Data Next
//where Address is the position of the node, Data is an integer, and Next is the position of the next node.
//    OUT:
//    For each case, output the resulting ordered linked list. Each node occupies a line, and is printed in the same format as in the input.
//Sample:
//    IN:
//	    00100 6 4
//		00000 4 99999
//		00100 1 12309
//		68237 6 -1
//		33218 3 00000
//		99999 5 68237
//		12309 2 33218
//    OUT:
//        00000 4 33218
//		33218 3 12309
//		12309 2 00100
//		00100 1 99999
//		99999 5 68237
//		68237 6 -1


#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct _node {
	union {
		int Address;
		int K;
	} Meta;
    int Data;
    int NextAddress;
    struct _node* Next;
}Node, *List;

List Read();
List Sort(List L);
List Reverse(List L);
void Print(List L);

int main()
{
    List L;
    L = Read();
    L = Sort(L);
//    Print(L);
	L = Reverse(L);
	L = Sort(L);
    Print(L);
    return 0;
} 

List Read(){
	List L, rear, t;
	int N;
	L = (List)malloc(sizeof(Node));
	scanf("%d %d %d", &L->NextAddress, &L->Data, &L->Meta.K);
	N = L->Data;
	rear = L;
	while(N--){
		t = (List)malloc(sizeof(Node));
		scanf("%d %d %d", &t->Meta.Address, &t->Data, &t->NextAddress);
		rear->Next = t;
		rear = rear->Next;
	}
	rear->Next = NULL;
	return L;
}


//建立临时HEAD front 用于记录排好序的部分 
//另外设一个 rear记录已完成排序的尾结点 以便向后插入新的排好序的结点
//L则是未排好序的部分
//注意：为了保证L的完整性 把排序找到的结点要绕过去 完成这个则需要 m->Next = m->Next->Next; 因此另设立移动指针m 但为了修改其指针并不紧随 
List Sort(List L){
	List front, rear, m;
	int cnt = 0;
	front = (List)malloc(sizeof(Node));
	*front = *L;
	rear = front;
	while(rear->NextAddress != -1){
		m = L;
		while(m->Next){
			if (rear->NextAddress == m->Next->Meta.Address){
				rear->Next = m->Next;
				rear = rear->Next;
				m->Next = m->Next->Next;
				cnt++;
//				printf("---->%d %d\n",m->Next,m->Data);
//				printf("L-----------------------\n");
//				Print(L);
//				printf("end---\n");
				break;
			}
			m = m->Next;
		}
	}
	rear->Next = NULL;
	free(L);
	front->Data = cnt;
	return front;
}
//List Reverse(List L){
//	int K = L->Meta.K;
//	int cnt, t;
//	int num = L->Data/K;
//	List blockHead, Front, Rear, p, next, tmp;
//	blockHead = Front = Rear = L;
//	while(num--){
//		p = blockHead->Next;
//		next = p->Next;
//		cnt = K-1;
//		Rear = blockHead->Next;
//		while(cnt--){
//			tmp = next->Next;
//			next->Next = p;
//			Front = next;
//			next = tmp; 
//			p = Front;
//		}
//		blockHead->Next = Front;
//		blockHead = Rear;
//	}
//	if (next){
//		Rear->Next = next;
//	}
//	return L;
//}
//原来以为是只修改链表结构 后来才发现居然链表的后续地址也要改，就采用了只修改链表内容，链修改交由Sort处理的方案，相对来说简单了许多 

List Reverse(List L){
	int K = L->Meta.K;
	int cnt, ad;
	int num = L->Data/K;
	List p, pH, pR;
	p = pR = L;
	while(num--){
		pH = pR;
		p = p->Next;
		pR = p;
		cnt = K-1;
		while(cnt--){
//			printf("1---->%d %d %d\n",p->Meta.Address, p->Data, p->NextAddress);
			ad = p->Meta.Address;
			p = p->Next;
			p->NextAddress = ad;
//			printf("2---->%d %d %d\n",p->Meta.Address, p->Data, p->NextAddress);
		}
		pH->NextAddress = p->Meta.Address;
		if (p->Next){
			pR->NextAddress = p->Next->Meta.Address;
		}
		else{
			pR->NextAddress = -1;
		}
//		printf("H---->%d %d %d\n",pH->Meta.K, pH->Data, pH->NextAddress);
//	    printf("D---->%d %d %d\n",p->Meta.Address, p->Data, p->NextAddress);
//	    printf("R---->%d %d %d\n",pR->Meta.Address, pR->Data, pR->NextAddress);
	}
//	printf("L---->%d %d %d\n",L->Meta.K, L->Data, L->NextAddress);
	return L;
}

void Print(List L){
	L = L->Next;
	while(L){
		if (L->NextAddress==-1){
			printf("%05d %d %d\n", L->Meta.Address, L->Data, L->NextAddress);
		}
		else{
			printf("%05d %d %05d\n", L->Meta.Address, L->Data, L->NextAddress);
		}
		L = L->Next;
	}
}

/*
Tests:

00100 6 3
00100 1 55555
55555 2 11111
11111 3 12312
12312 4 15151
15151 5 11112
11112 6 -1

00100 7 3
00100 1 55555
55555 2 11111
11111 3 12312
66666 8 88888
12312 4 15151
15151 5 11112
11112 6 -1

*/
