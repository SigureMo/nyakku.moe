//二分查找 
//L是用户传入的一个线性表，其中ElementType元素可以通过>、==、<进行比较，并且题目保证传入的数据是递增有序的。
//函数BinarySearch要查找X在Data中的位置，即数组下标（注意：元素从下标1开始存储）。
//找到则返回下标，否则返回一个特殊的失败标记NotFound。

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}

List ReadInput(){
    int N;
    scanf("%d",&N);
    List L = (struct LNode*)malloc(sizeof(struct LNode));
    L->Last = N;
    for(ElementType i=1;i<=N;i++){
        scanf("%d",&L->Data[i]);
    }
    return L;
}

/* 你的代码将被嵌在这里 */
Position BinarySearch( List L, ElementType X ){
	Position position;
	Position left = 0;
	Position right = L->Last;
	int flag = 0;
	while(left <= right){
		Position mid = (left + right) / 2;
		if (L -> Data[mid] == X){
			position = mid;
			flag = 1;
			break;
		}
		else if (L -> Data[mid] > X){
			right = mid - 1;
		}
		else{
			left = mid + 1;
		}
	}
	if(flag == 0){
		return NotFound;
	}
	return position;
} 
