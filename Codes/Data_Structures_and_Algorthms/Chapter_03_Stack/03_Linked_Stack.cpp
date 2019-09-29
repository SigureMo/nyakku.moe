#include <iostream>

using namespace std;
typedef int ElemType;
typedef struct _node {
  ElemType data;
  struct _node *next;
} LinkNode, *LiStack;

LiStack InitStack();
bool isEmpty(LiStack PtrS);
bool Push(LiStack PtrS, ElemType x);
bool Pop(LiStack PtrS, ElemType &x);
bool GetTop(LiStack PtrS, ElemType &x);
void DestroyStack(LiStack PtrS);

int main() {
  ElemType x;
  LiStack PtrS = InitStack();
  Push(PtrS, 100);
  GetTop(PtrS, x);
  Pop(PtrS, x);
  cout << x << endl;
  cout << isEmpty(PtrS) << endl;
  DestroyStack(PtrS);
  return 0;
}

LiStack InitStack() {
  /** 初始化一个空栈 */
  LiStack PtrS = (LiStack)malloc(sizeof(LinkNode));
  PtrS->next = NULL;
  return PtrS;
}

bool isEmpty(LiStack PtrS) {
  /** 判断一个栈是否为空
   * 若为空返回 true
   * 否则返回 false
   */
  return PtrS->next == NULL;
}

bool Push(LiStack PtrS, ElemType x) {
  /** 进栈
   * 将 x 加入使之成为新栈顶
   */
  PtrS->next = (LiStack)malloc(sizeof(LinkNode));
  PtrS->next->data = x;
  PtrS->next->next = NULL;
  return true;
}

bool Pop(LiStack PtrS, ElemType &x) {
  /** 出栈
   * 若栈非空，则弹出栈顶元素，并用 x 返回
   */
  if (isEmpty(PtrS)) return false;
  LiStack curr = PtrS;
  while (curr->next->next) {
    curr = curr->next;
  }
  x = curr->next->data;
  free(curr->next);
  curr->next = NULL;
  return true;
}

bool GetTop(LiStack PtrS, ElemType &x) {
  /** 读栈顶元素
   * 若栈非空，则用 x 返回栈顶元素
   */
  if (isEmpty(PtrS)) return false;
  LiStack curr = PtrS;
  while (curr->next) {
    curr = curr->next;
  }
  x = curr->data;
  return true;
}

void DestroyStack(LiStack PtrS) {
  /** 销毁栈 */
  LiStack curr = PtrS;
  while (curr->next) {
    LiStack PtrDest = curr;
    curr = curr->next;
    free(PtrDest);
  }
}
