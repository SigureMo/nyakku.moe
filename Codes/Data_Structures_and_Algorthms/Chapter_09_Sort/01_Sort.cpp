#include <iostream>
#include <algorithm>
#define CUTOFF 3

using namespace std;

// SIMPLE_INSERT
template<typename T>
void Insertion_Sort(T a[], int N){
  int i;
  for (int P = 1; P < N; P++){
    T tmp = a[P];
    for (i = P; i > 0 && a[i-1] > tmp; i--){
      a[i] = a[i-1];
    }
    a[i] = tmp;
  }
}
// SIMPLE_INSERT
// HALF_INSERT
template<typename T>
void Half_Insertion_Sort(T a[], int N) {
  int i, low, high, mid;
  for (int P = 1; P < N; P++) {
    T tmp = a[P];
    low = 0;
    high = P;
    while (low <= high) {
      mid = (low + high) / 2;
      if (tmp < a[mid]) high = mid - 1;
      else low = mid + 1;
    }
    for (i = P; i > low; i--) {
      a[i] = a[i-1];
    }
    a[i] = tmp;
  }
}
// HALF_INSERT
// SHELL_INSERT
template<typename T>
void Shell_Sort(T a[], int N) {
  int i;
  for (int D = N/2; D > 0; D /= 2) {
    for (int P = D; P < N; P++) {
      T tmp = a[P];
      for (i = P; i >= D && a[i-D] > tmp; i-=D) {
        a[i] = a[i-D];
      }
      a[i] = tmp;
    }
  }
}
// SHELL_INSERT
// BUBBLE_SWAP
template<typename T>
void Bubble_Sort(T a[], int N) {
  for (int P = N-1; P >= 0; P--) {
    bool flag = false;
    for (int i = 0; i < P; i++) {
      if (a[i] > a[i+1]) {
        swap(a[i], a[i+1]);
        flag = true;
      }
    }
    if (!flag)
      break;
  }
}
// BUBBLE_SWAP
// QUICK_SWAP_PIVOT
template<typename T>
T Median3(T a[], int left, int right) {
  int center = (left + right) / 2;
  if (a[left] > a[center])
    swap(a[left], a[center]);
  if (a[left] > a[right])
    swap(a[left], a[right]);
  if (a[center] > a[right])
    swap(a[center], a[right]);
  swap(a[center], a[right-1]);
  // 只需考虑A[Left+1]...A[Right-2]
  return a[right-1];
}
// QUICK_SWAP_PIVOT
// QUICK_SWAP_DIVIDE
template<typename T>
void Quicksort(T a[], int left, int right) {
  if (right - left >= CUTOFF) {
    T pivot = Median3(a, left, right);
    int i = left;
    int j = right - 1;
    for (; ; ) {
      while (a[++i] < pivot) {}
      while (a[--j] > pivot) {}
      if (i < j)
        swap(a[i], a[j]);
      else break;
    }
    swap(a[i], a[right - 1]);
    Quicksort(a, left, i-1);
    Quicksort(a, i+1, right);
  }
  else
    Insertion_Sort(a+left, right-left+1);
}
// QUICK_SWAP_DIVIDE
// QUICK_SWAP_MAIN
template<typename T>
void Quick_Sort(T a[], int N) {
  Quicksort(a, 0, N-1);
}
// QUICK_SWAP_MAIN
// SIMPLE_SELECT
template<typename T>
void Select_Sort(T a[], int N) {
  for (int i = 0; i < N; i++) {
    int idx_min = i;
    T ele_min = a[idx_min];
    for (int j = i; j < N; j++) {
      if (a[j] < ele_min) {
        ele_min = a[j];
        idx_min = j;
      }
    }
    swap(a[i], a[idx_min]);
  }
}
// SIMPLE_SELECT
// HEAP_SELECT
template<typename T>
void Heap_Sort(T a[], int N) {
  make_heap(a, a+N);
  for (int i = 0; i < N; i++) {
    pop_heap(a, a+N-i);
  }
}
// HEAP_SELECT
// MERGE_SORT_MERGE
template<typename T>
void Merge(T a[], T b[], int low, int mid, int high) {
  int i, j, k;
  for (k=low; k<=high; k++)
    b[k] = a[k];
  for (i=low, j=mid+1, k=i; i<=mid&&j<=high; k++) {
    if (b[i] <= b[j])
      a[k] = b[i++];
    else
      a[k] = b[j++];
  }
  while (i <= mid) a[k++] = b[i++];
  while (j <= high) a[k++] = b[j++];
}
// MERGE_SORT_MERGE
// MERGE_SORT_SUB
template<typename T>
void MergeSort(T a[], T b[], int low, int high) {
	if (low < high) {
    int mid = (low + high) / 2;
    MergeSort(a, b, low, mid);
    MergeSort(a, b, mid+1, high);
    Merge(a, b, low, mid, high);
  }
}
// MERGE_SORT_SUB
// MERGE_SORT_MAIN
template<typename T>
void Merge_Sort(T a[], int N) {
  T b[N];         // 辅助数组，合并专用
  MergeSort(a, b, 0, N-1);
}
// MERGE_SORT_MAIN

template<typename T>
bool check(T a[], T b[], int N) {
  for (int i = 0; i < N; i++) {
    if (a[i] != b[i]) return false;
  }
  return true;
}

template<typename T>
void print(T a[], int N) {
  for (int i = 0; i < N; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

int main(int argc, char* argv[]) {
  string mode = argv[1];
  int a[] = {4, 981, 10, -17, 0, -20, 29, 50, 8, 43, -5};
  int b[] = {-20, -17, -5, 0, 4, 8, 10, 29, 43, 50, 981};
  int N = sizeof(a)/sizeof(a[0]);
  if (mode == "insertion") {
    Insertion_Sort(a, N);
  }
  else if (mode == "half_insertion") {
    Half_Insertion_Sort(a, N);
  }
  else if (mode == "shell") {
    Shell_Sort(a, N);
  }
  else if (mode == "bubble") {
    Bubble_Sort(a, N);
  }
  else if (mode == "quick") {
    Quick_Sort(a, N);
  }
  else if (mode == "select") {
    Select_Sort(a, N);
  }
  else if (mode == "heap") {
    Heap_Sort(a, N);
  }
  else if (mode == "merge") {
    Merge_Sort(a, N);
  }
  else {
    cout << "Invaild mode!" << endl;
    return 1;
  }
  cout << boolalpha << "check " << (check(a, b, N) ? "passed" : "failed") << endl;
  return 0;
}
