//最大子列和问题
//给定K个整数组成的序列。“最大子列和”则被定义为所有连续子列元素的和中最大者。
//IN:输入第1行给出正整数K (≤100000)；第2行给出K个整数，其间以空格分隔。
//OUT:在一行中输出最大子列和。如果序列中所有整数皆为负数，则输出0。
//Example:
//    IN:
//	    6
//        -2 11 -4 13 -5 -2
//    OUT:
//        20

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
ElementType MaxSubList( List L);

int main()
{
    List L;

    L = ReadInput();
    ElementType Max;
	Max = MaxSubList(L);
    printf("%d\n", Max);

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
ElementType MaxSubList( List L){
	ElementType Max = L->Data[0];
	ElementType sum = 0;
	Position i;
	for(i=0;i<L->Last;i++){
		if (sum <= 0){
			sum = 0;
		}
		sum += L->Data[i];
		if (sum > Max){
			Max = sum;
		}
		
	}
	return Max;
}

