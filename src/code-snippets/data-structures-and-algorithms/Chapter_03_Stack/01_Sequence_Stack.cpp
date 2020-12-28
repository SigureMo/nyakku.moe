#include <iostream>
#define MaxSize 50

using namespace std;
typedef int ElemType;
typedef struct {
  ElemType data[MaxSize];
  int top;
} SNode, *SqStack;

SqStack InitStack();
bool isEmpty(SqStack PtrS);
bool Push(SqStack PtrS, ElemType x);
bool Pop(SqStack PtrS, ElemType &x);
bool GetTop(SqStack PtrS, ElemType &x);
void DestroyStack(SqStack PtrS);

int main() {
  ElemType x;
  SqStack PtrS = InitStack();
  Push(PtrS, 100);
  GetTop(PtrS, x);
  Pop(PtrS, x);
  cout << x << endl;
  cout << isEmpty(PtrS) << endl;
  DestroyStack(PtrS);
  return 0;
}

SqStack InitStack() {
  /** 初始化一个空栈 */
  SqStack PtrS = (SqStack)malloc(sizeof(SNode));
  PtrS->top = -1;
  return PtrS;
}

bool isEmpty(SqStack PtrS) {
  /** 判断一个栈是否为空
   * 若为空返回 true
   * 否则返回 false
   */
  return PtrS->top == -1;
}

bool Push(SqStack PtrS, ElemType x) {
  /** 进栈
   * 若栈未满，则将 x 加入使之成为新栈顶
   */
  if (PtrS->top == MaxSize-1) return false;
  PtrS->data[++(PtrS->top)] = x;
  return true;
}

bool Pop(SqStack PtrS, ElemType &x) {
  /** 出栈
   * 若栈非空，则弹出栈顶元素，并用 x 返回
   */
  if (isEmpty(PtrS)) return false;
  x = PtrS->data[PtrS->top--];
  return true;
}

bool GetTop(SqStack PtrS, ElemType &x) {
  /** 读栈顶元素
   * 若栈非空，则用 x 返回栈顶元素
   */
  if (isEmpty(PtrS)) return false;
  x = PtrS->data[PtrS->top];
  return true;
}

void DestroyStack(SqStack PtrS) {
  /** 销毁栈 */
  free(PtrS);
}
