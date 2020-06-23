#include <iostream>
#define MaxSize 50

using namespace std;

// :::
typedef int ElemType;
typedef struct {
  ElemType data[MaxSize];
  int length;
} SqNode, *SqList;

SqList Init();
void Print(SqList PtrL);
bool Insert(SqList PtrL, int i, ElemType e);
bool Delete(SqList PtrL, int i, ElemType &e);
int Locate(SqList PtrL, ElemType e);

int main() {
  SqList PtrL = Init();
  Insert(PtrL, 1, 100);
  Insert(PtrL, 2, 45);
  Print(PtrL);
  ElemType e;
  if (Delete(PtrL, 1, e)) {
    cout << "Delete successful, value is " << e << endl;
  };
  Print(PtrL);
  return 0;
}

SqList Init() {
  /**
   * 返回新建顺序表的指针
   */
  SqList PtrL;
  PtrL = (SqList)malloc(sizeof(SqNode));
  PtrL->length = 0;
  return PtrL;
}

void Print(SqList PtrL) {
  /**
   * 打印列表
   */
  if (PtrL->length == 0) {
    cout << "List is empty!" << endl;
    return;
  }
  cout << "Data:";
  for (int i=0; i < PtrL->length; i++) {
    cout << PtrL->data[i] << " ";
  }
  cout << endl;
}

bool Insert(SqList PtrL, int i, ElemType e) {
  /**
   * 将新的元素插入列表中
   */
  if (i > PtrL->length+1 || i < 1) {
    cout << "位置非法" << endl;
    return false;
  }
  if (PtrL->length >= MaxSize) {
    cout << "存储已满" << endl;
    return false;
  }
  for (int j=PtrL->length-1; j>=i; j--) {
    PtrL->data[j] = PtrL->data[j-1];
  }
  PtrL->data[i-1] = e;
  PtrL->length++;
  return true;
}

bool Delete(SqList PtrL, int i, ElemType &e) {
  /** 删除 PtrL 所指顺序表中第 i 个元素
   * 如果成功，则返回 true ，并使用引用变量 e 返回被删除元素的值
   * 否则返回 false
   */
  if (i < 1 || i > PtrL->length) {
    cout << "位置不合法";
    return false;
  }
  e = PtrL->data[i-1];
  for (int j=i; j<PtrL->length; j++) {
    PtrL->data[j-1] = PtrL->data[j];
  }
  PtrL->length--;
  return true;
}

int Locate(SqList PtrL, ElemType e) {
  /** 在查找顺序表第一个元素值等于 e 的元素，并返回其位序
   * 如果失败，返回 0
   */
  for (int i = 0; i < PtrL->length; i++) {
    if (PtrL->data[i] == e) {
      return i+1;
    }
  }
  return 0;
}
// :::
