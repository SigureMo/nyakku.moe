#include <iostream>

using namespace std;

typedef struct page {
  union {
    int num;
    int size;
  } Meta;
  struct page* next;
} Page, *Memory;

int N, M, F;

void FIFO(int num, Memory front, Memory rear);
void LRU(int num, Memory front, Memory rear);
void Print(Memory front);

int main(int argc, char* argv[]){
  if (argc < 2) {
    cout << "Please input page replacement algorithm and retry" << endl;
    return 1;
  }
  F = 0;
  Memory front = new Page;
  Memory rear = new Page;
  front->Meta.size = 0;
  front->next = NULL;
  rear->next = front;
  string mode = argv[1];
  cout << mode << endl;
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    int num;
    cin >> num;
    if (mode == "FIFO") {
      FIFO(num, front, rear);
    }
    else if (mode == "LRU") {
      LRU(num, front, rear);
    }
  }
  cout << "Page fault number:" << F << endl;
  cout << "Page fault rate:" << F * 1.0 / N << endl;
}

void FIFO(int num, Memory front, Memory rear) {
  Memory tmp;
  int outPage = -1;
  bool found = false;
  tmp = front->next;

  // 寻找是否已在内存
  while (tmp) {
    if (tmp->Meta.num == num) {
      found = true;
      break;
    }
    tmp = tmp->next;
  }
  if (!found) {
    if (front->Meta.size < M) {
      // 页面加入
      Memory newPage = new Page;
      newPage->Meta.num = num;
      newPage->next = NULL;
      rear->next->next = newPage;
      rear->next = newPage;
      front->Meta.size++;
    }
    else {
      // 页面置换
      Memory t = front->next;
      front->next = front->next->next;
      outPage = t->Meta.num;
      F++;
      delete t;
      Memory newPage = new Page;
      newPage->Meta.num = num;
      newPage->next = NULL;
      rear->next->next = newPage;
      rear->next = newPage;
    }
  }
  cout << "> " << num << " ";
  Print(front);
  if (outPage != -1) {
    cout << " Out:" << outPage << endl;
  }
}

void LRU(int num, Memory front, Memory rear) {
  Memory tmp;
  int outPage = -1;
  bool found = false;
  tmp = front;

  // 寻找是否已在内存
  while (tmp->next) {
    if (tmp->next->Meta.num == num) {
      found = true;
      break;
    }
    tmp = tmp->next;
  }
  if (!found) {
    if (front->Meta.size < M) {
      // 页面加入
      Memory newPage = new Page;
      newPage->Meta.num = num;
      newPage->next = NULL;
      rear->next->next = newPage;
      rear->next = newPage;
      front->Meta.size++;
    }
    else {
      // 页面置换
      Memory t = front->next;
      front->next = front->next->next;
      outPage = t->Meta.num;
      F++;
      delete t;
      Memory newPage = new Page;
      newPage->Meta.num = num;
      newPage->next = NULL;
      rear->next->next = newPage;
      rear->next = newPage;
    }
  }
  else {
    // 页面提前
    Memory t = tmp->next;
    tmp->next = tmp->next->next;
    t->next = NULL;
    rear->next->next = t;
    rear->next = t;
  }
  cout << "> " << num << " ";
  Print(front);
  if (outPage != -1) {
    cout << "Out:" << outPage << endl;
  }
}

void Print(Memory front) {
  Memory tmp = new Page;
  tmp = front->next;
  cout << "[";
  while (tmp) {
    cout << " " << tmp->Meta.num;
    tmp = tmp->next;
  }
  cout << "]" << endl;
  delete tmp;
}
