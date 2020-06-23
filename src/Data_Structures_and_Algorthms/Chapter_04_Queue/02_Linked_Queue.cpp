#include <iostream>

using namespace std;
typedef int ElemType;

struct Node {
  ElemType data;
  struct Node *next;
};

typedef struct QNode {
  struct Node *front;
  struct Node *rear;
} LinkNode, *LinkQueue;

LinkQueue InitQueue();
bool isEmpty(LinkQueue PtrQ);
bool EnQueue(LinkQueue PtrQ, ElemType x);
bool DeQueue(LinkQueue PtrQ, ElemType &x);

int main() {
  LinkQueue PtrQ = InitQueue();
  ElemType x;
  EnQueue(PtrQ, 100);
  DeQueue(PtrQ, x);
  cout << x << endl;
  cout << boolalpha << isEmpty(PtrQ) << endl;
  return 0;
}

LinkQueue InitQueue() {
  /** 初始化空队列 */
  // 建立头结点
  struct Node *PtrHead = (struct Node *)malloc(sizeof(struct Node));
  PtrHead->next = NULL;
  // 建立队列
  LinkQueue PtrQ = (LinkQueue)malloc(sizeof(LinkNode));
  PtrQ->front = PtrHead;
  PtrQ->rear = PtrHead;
  return PtrQ;
}

bool isEmpty(LinkQueue PtrQ) {
  /** 判断队列是否为空 */
  return PtrQ->front == PtrQ->rear;
}

bool EnQueue(LinkQueue PtrQ, ElemType x) {
  /** 入队 */
  // 新建结点
  struct Node *PtrNode = (struct Node *)malloc(sizeof(struct Node));
  PtrNode->data = x;
  PtrNode->next = NULL;
  // 串起来
  PtrQ->rear->next = PtrNode;
  PtrQ->rear = PtrQ->rear->next;
  return true;
}

bool DeQueue(LinkQueue PtrQ, ElemType &x) {
  /** 出队 */
  if (isEmpty(PtrQ)) return false;
  struct Node *PtrNode = PtrQ->front->next;
  x = PtrNode->data;
  PtrQ->front = PtrQ->front->next;
  free(PtrNode);
  return true;
}
