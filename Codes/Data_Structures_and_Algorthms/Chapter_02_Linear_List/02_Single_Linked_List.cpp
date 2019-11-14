#include <iostream>

using namespace std;
// :::
typedef int ElemType;
typedef struct _node {
  ElemType data;
  struct _node *next;
} LinkNode, *LinkList;

LinkList Init();
void Print(LinkList PtrL);
void HeadInsert(LinkList PtrL, ElemType e);
void TailInsert(LinkList PtrL, ElemType e);
LinkList Get(LinkList PtrL, int i);
int Locate(LinkList PtrL, ElemType e);
bool Insert(LinkList PtrL, int i, ElemType e);
bool Delete(LinkList PtrL, int i, ElemType &e);
int Length(LinkList PtrL);


int main() {
  LinkList PtrL = Init();
  HeadInsert(PtrL, 1);
  TailInsert(PtrL, 2);
  Print(PtrL);
  LinkList PtrN = Get(PtrL, 2);
  if (PtrN) {
    cout << "Get successful, value is " << PtrN->data << endl;
  };
  cout << "Elem 2 is at " << Locate(PtrL, 2) << endl;
  Insert(PtrL, 2, 3);
  Print(PtrL);
  ElemType e;
  if (Delete(PtrL, 2, e)) {
    cout << "Delete successful, value is " << e << endl;
  };
  Print(PtrL);
  cout << "Total length is " << Length(PtrL) << endl;
  return 0;
}

LinkList Init() {
  LinkList PtrL;
  PtrL = (LinkList)malloc(sizeof(LinkNode));
  PtrL->next = NULL;
  return PtrL;
}

void Print(LinkList PtrL) {
  /**
   * 打印列表
   */
  if (PtrL->next == NULL) {
    cout << "List is empty!" << endl;
    return;
  }
  LinkList curr = PtrL;
  cout << "Data: ";
  while (curr->next) {
    cout << curr->next->data << " ";
    curr = curr->next;
  }
  cout << endl;
}

void HeadInsert(LinkList PtrL, ElemType e) {
  /** 头插法插入元素
   * 将新的元素插入头结点之后
   */
  LinkList PtrNewNode;
  PtrNewNode = (LinkList)malloc(sizeof(LinkNode));
  PtrNewNode->data = e;
  PtrNewNode->next = PtrL->next;
  PtrL->next = PtrNewNode;
}

void TailInsert(LinkList PtrL, ElemType e) {
  /** 尾插法插入元素
   * 将新的元素插入尾部
   */
  LinkList curr = PtrL;
  while (curr->next) {
    curr = curr->next;
  }
  curr->next = (LinkList)malloc(sizeof(LinkNode));
  curr->next->data = e;
  curr->next->next = NULL;
}

LinkList Get(LinkList PtrL, int i) {
  /** 获取表中第 i 个位置指针
   * 如果失败，返回 NULL
   */
  LinkList curr = PtrL->next;
  int j = 1;
  while (curr) {
    if (j == i) {
      return curr;
    }
    j++;
    curr = curr->next;
  }
  return NULL;
}

int Locate(LinkList PtrL, ElemType e) {
  /** 在查找顺序表第一个元素值等于 e 的元素，并返回其位序
   * 如果失败，返回 0
   */
  int i = 1;
  LinkList curr = PtrL->next;
  while (curr) {
    if (curr->data == e) {
      return i;
    }
    i++;
    curr = curr->next;
  }
  return 0;
}

bool Insert(LinkList PtrL, int i, ElemType e) {
  /**
   * 将新的元素到第 i 个位置
   */
  LinkList PtrFront = Get(PtrL, i-1);
  if (PtrFront == NULL) return false;
  LinkList PtrNewNode = (LinkList)malloc(sizeof(LinkNode));
  PtrNewNode->data = e;
  PtrNewNode->next = PtrFront->next;
  PtrFront->next = PtrNewNode;
  return true;
}

bool Delete(LinkList PtrL, int i, ElemType &e) {
  /** 删除 PtrL 所指顺序表中第 i 个元素
   * 如果成功，则返回 true ，并使用引用变量 e 返回被删除元素的值
   * 否则返回 false
   */
  LinkList PtrFront = Get(PtrL, i-1);
  if (PtrFront == NULL || PtrFront->next==NULL) return false;
  LinkList tmp = PtrFront->next;
  PtrFront->next = tmp->next;
  e = tmp->data;
  free(tmp);
  return true;
}

int Length(LinkList PtrL) {
  /** 获取列表长度
   */
  int i = 0;
  LinkList curr = PtrL;
  while (curr->next) {
    i++;
    curr = curr->next;
  }
  return i;
}
// :::
