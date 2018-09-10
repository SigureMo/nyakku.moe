//Maximum Subsequence Sum 
//Given a sequence of K integers .The Maximum Subsequence is the continuous subsequence which has the largest sum of its elements. 
//IN:Each input file contains one test case. Each case occupies two lines. The first line contains a positive integer K (≤10000). The second line contains K numbers, separated by a space.
//OUT:For each test case, output in one line the largest sum, together with the first and the last numbers of the maximum subsequence. The numbers must be separated by one space, but there must be no extra space at the end of a line. In case that the maximum subsequence is not unique, output the one with the smallest indices i and j (as shown by the sample case). If all the K numbers are negative, then its maximum sum is defined to be 0, and you are supposed to output the first and the last numbers of the whole sequence.
//Sample:
//    IN:
//	    10
//        -10 1 2 3 4 -5 -23 3 7 -21
//    OUT:
//        10 1 4

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100001
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
ElementType* MaxSubList( List L, ElementType *p);

int main()
{
    List L;

    L = ReadInput();
    ElementType *p = (ElementType *)malloc(sizeof(ElementType)*3);
    p = MaxSubList(L, p);
    printf("%d %d %d\n", p[0], p[1], p[2]);
    free(p);
    free(L);

    return 0;
}

List ReadInput(){
    int N;
    ElementType i;
    scanf("%d",&N);
    List L = (struct LNode*)malloc(sizeof(struct LNode));
    L->Last = N;
    for(i=0;i<N;i++){
        scanf("%d",&L->Data[i]);
    }
    return L;
}

/* 你的代码将被嵌在这里 */
ElementType* MaxSubList( List L, ElementType *p){
	ElementType Max = L->Data[0];
	ElementType sum = 0;
	ElementType start_t = L->Data[0];
	ElementType start = L->Data[0];
	ElementType stop = L->Data[0];
	Position i;
	Position negative_num = 0;
	for(i=0;i<L->Last;i++){
		if(L->Data[i]<0){
			negative_num++;
		}
		if (sum < 0){
			sum = 0;
			start_t = L->Data[i];
		}
		sum += L->Data[i];
		if (sum > Max){
			start = start_t;
			stop = L->Data[i];
			Max = sum;
		}
	}
	p[0] = Max;
	p[1] = start;
	p[2] = stop;
	if(negative_num == L->Last){
		p[0] = 0;
	    p[1] = L->Data[0];
	    p[2] = L->Data[L->Last-1];
	}
	return p;
}

