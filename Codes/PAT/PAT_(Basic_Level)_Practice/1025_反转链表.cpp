#include <iostream>

using namespace std;

typedef struct node {
  int data;
  int address;
  int nextAddress;
  struct node* next;
} Node, *List;

int N, K, startAddress, cnt;

void sort(List L);
List read();
void print(List L);
void reverse(List L);

int main() {
  List L;
  L = read();
  sort(L);
  if (K != 1) {
    reverse(L);
    sort(L);
  }
  print(L);
  return 0;
}

void sort(List L) {
  cnt = 0;
  List front, rear, m;
  front = L;
  while (front->nextAddress != -1) {
    rear = front;
    while (rear->next->address != front->nextAddress) {
      rear = rear->next;
    }
    m = rear->next;
    rear->next = rear->next->next;
    m->next = front->next;
    front->next = m;
    front = front->next;
    cnt++;
  }
  front->next = NULL;
}

List read() {
  cin >> startAddress >> N >> K;
  List L = new Node;
  List rear;
  L->nextAddress = startAddress;
  L->data = N;
  rear = L;
  for (int i = 0; i < N; i++) {
    List m = new Node;
    scanf("%d %d %d", &m->address, &m->data, &m->nextAddress);
    // cin >> m->address >> m->data >> m->nextAddress;
    rear->next = m;
    rear = m;
  }
  rear->next = NULL;
  return L;
}

void print(List L) {
  List m = L->next;
  while (m) {
    if (m->nextAddress == -1) {
      printf("%05d %d -1\n", m->address, m->data);
    }
    else {
      printf("%05d %d %05d\n", m->address, m->data, m->nextAddress);
    }
    m = m->next;
  }
}

void reverse(List L) {
  List rear = L, front = L;
  List head;
  int address;
  for (int i = 0; i < cnt / K; i++) {
    rear = rear->next;
    head = front;
    front = rear;
    for (int j = 0; j < K - 1; j++) {
      address = rear->address;
      rear = rear->next;
      rear->nextAddress = address;
    }
    head->nextAddress = rear->address;
    if (rear->next) {
      front->nextAddress = rear->next->address;
    }
    else {
      front->nextAddress = -1;
    }
  }
}
