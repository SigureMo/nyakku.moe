// See PAT_B 1025

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


// 建立临时 HEAD front 用于记录排好序的部分
// 另外设一个 rear 记录已完成排序的尾结点 以便向后插入新的排好序的结点
// L 则是未排好序的部分
// 注意：为了保证 L 的完整性 把排序找到的结点要绕过去 完成这个则需要 m->Next = m->Next->Next;
//       因此另设立移动指针 m 但为了修改其指针并不紧随
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


// 原来以为是只修改链表结构 后来才发现居然链表的后续地址也要改，就采用了只修改链表内容，链修改交由Sort处理的方案，相对来说简单了许多
// List Reverse(List L){
// 	int K = L->Meta.K;
// 	int cnt, t;
// 	int num = L->Data/K;
// 	List blockHead, Front, Rear, p, next, tmp;
// 	blockHead = Front = Rear = L;
// 	while(num--){
// 		p = blockHead->Next;
// 		next = p->Next;
// 		cnt = K-1;
// 		Rear = blockHead->Next;
// 		while(cnt--){
// 			tmp = next->Next;
// 			next->Next = p;
// 			Front = next;
// 			next = tmp;
// 			p = Front;
// 		}
// 		blockHead->Next = Front;
// 		blockHead = Rear;
// 	}
// 	if (next){
// 		Rear->Next = next;
// 	}
// 	return L;
// }

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
			ad = p->Meta.Address;
			p = p->Next;
			p->NextAddress = ad;
		}
		pH->NextAddress = p->Meta.Address;
		if (p->Next){
			pR->NextAddress = p->Next->Meta.Address;
		}
		else{
			pR->NextAddress = -1;
		}
	}
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
