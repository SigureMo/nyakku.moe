#include <iostream>
#define MaxSize 50

using namespace std;
typedef int ElemType;
typedef struct {
  ElemType data[MaxSize];
  int front;
  int rear;
} QNode, *SqQueue;

SqQueue InitQueue();
bool isEmpty(SqQueue PtrQ);
bool EnQueue(SqQueue PtrQ, ElemType x);
bool DeQueue(SqQueue PtrQ, ElemType &x);

int main() {
  SqQueue PtrQ = InitQueue();
  ElemType x;
  EnQueue(PtrQ, 100);
  DeQueue(PtrQ, x);
  cout << x << endl;
  cout << boolalpha << isEmpty(PtrQ) << endl;
  return 0;
}

SqQueue InitQueue() {
  /** 初始化空队列 */
  SqQueue PtrQ = (SqQueue)malloc(sizeof(QNode));
  PtrQ->front = 0;
  PtrQ->rear = 0;
  return PtrQ;
}

bool isEmpty(SqQueue PtrQ) {
  /** 判断队列是否为空 */
  return PtrQ->front == PtrQ->rear;
}

bool EnQueue(SqQueue PtrQ, ElemType x) {
  /** 入队 */
  if ((PtrQ->rear+1)%MaxSize == PtrQ->front) return false;
  PtrQ->data[PtrQ->rear++] = x;   // 先入队，后移动指针
  PtrQ->rear %= MaxSize;          // 保证没“飞出去”
  return true;
}

bool DeQueue(SqQueue PtrQ, ElemType &x) {
  /** 出队 */
  if (isEmpty(PtrQ)) return false;
  x = PtrQ->data[PtrQ->front++];  // 先出队，后移动指针
  PtrQ->front %= MaxSize;         // 保证没“飞出去”
  return true;
}
