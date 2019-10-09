#include <iostream>
#define MaxSize 50
#define EMPTY -1

using namespace std;
typedef int ElemType;
typedef struct {
  ElemType *data;
  int size;
  int capacity;
} HeapStruct, *MaxHeap;

void AdjustDown(MaxHeap H, int k);
void AdjustUp(MaxHeap H, int k);
MaxHeap Create(int size);
MaxHeap CreateFromArray(ElemType a[], int len);
ElemType Delete(MaxHeap H);
void Insert(MaxHeap H, ElemType x);
void Print(MaxHeap H);
void HeapSort(ElemType a[], int len);

int main() {
  int size = 9;
  ElemType a[MaxSize] = {EMPTY, 30, 50, 57, 77, 62, 78, 94, 80, 84};
  // MaxHeap H = Create(MaxSize);
  MaxHeap H = CreateFromArray(a, size);
  Insert(H, 100);
  Insert(H, 1);
  cout << Delete(H) << endl;
  Print(H);
  HeapSort(a, size);
  for (int i = 1; i <= size; i++) {
    cout << a[i] << " ";
  }
  return 0;
}

MaxHeap Create(int size) {
  /** 创建空堆 */
  MaxHeap H = (MaxHeap)malloc(sizeof(HeapStruct));
  H->data = (ElemType *)malloc(sizeof(ElemType) * (size+1));
  H->size = 0;
  H->capacity = size;
  return H;
}

MaxHeap CreateFromArray(ElemType a[], int len) {
  /** 根据数组元素初始化一个堆
   * 之后需要从堆底开始不断向下调整将整个堆调整成真正的堆
  **/
  MaxHeap H = (MaxHeap)malloc(sizeof(HeapStruct));
  H->data = a;
  H->size = len;
  H->capacity = MaxSize;
  for (int i = len/2; i > 0; i--) {
    AdjustDown(H, i);
  }
  return H;
}

void Print(MaxHeap H) {
  /** 打印堆内元素数组 */
  for (int i = 1; i <= H->size; i++) {
    cout << H->data[i] << " ";
  }
  cout << endl;
}

void AdjustDown(MaxHeap H, int k) {
  /** 向下调整
   * k 为需要向下调整的元素下标，也即在调整过程中的父结点
   * i 为下一步需要调整的位置，也即调整过程中的孩子结点，
   * 由于孩子有两个，所以在调整的过程中需要不断校正方向，
   * 调整为两个孩子比较大的那个方向（因为父结点与较大的孩子
   * 交换）
  **/
  H->data[0] = H->data[k];
  for (int i = 2*k; i <= H->size; i *= 2) {
    if (i < H->size && H->data[i] < H->data[i+1])
      i++;
    if (H->data[0] >= H->data[i]) break;
    else {
      H->data[k] = H->data[i];
      k = i;
    }
  }
  H->data[k] = H->data[0];
}

void AdjustUp(MaxHeap H, int k) {
  /** 向上调整
   * k 为需要向下调整的元素下标，也即在调整过程中的孩子结点
   * i 为下一步需要调整的位置，也即调整过程中的父结点
   * 向上调整只有一条可能的路径，不需要校正方向，可对比
   * 向下调整法记忆
  **/
  H->data[0] = H->data[k];
  for (int i = k/2; i > 0; i /= 2) {
    if (H->data[0] <= H->data[i]) break;
    else {
      H->data[k] = H->data[i];
      k = i;
    }
  }
  H->data[k] = H->data[0];
}

void Insert(MaxHeap H, ElemType x) {
  /** 向堆中插入元素 x
   * 只需要将元素插入堆底，然后针对堆底位置向上调整即可
  **/
  if (H->size == H->capacity) throw "Heap is full!";
  H->data[++H->size] = x;
  AdjustUp(H, H->size);
}

ElemType Delete(MaxHeap H) {
  /** 删除堆顶元素
   * 只需要将堆底元素放到堆顶处，然后针对堆顶位置向下调整即可
  **/
  if (H->size == 0) throw "Heap is empty!";
  swap(H->data[1], H->data[H->size--]);
  AdjustDown(H, 1);
  return H->data[H->size+1];
}

void HeapSort(ElemType a[], int len) {
  /** 堆排序
   * 建堆、不断删除堆顶元素（移到堆底）
  **/
  MaxHeap H = CreateFromArray(a, len);
  for (int i = len; i > 1; i--) {
    a[i] = Delete(H);
  }
}
