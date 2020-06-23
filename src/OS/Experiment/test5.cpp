#include <iostream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#define randint(start, end) (rand()%(end-start) + start)
#define BLOCK_NUM 500
#define BLOCK_SIZE 2000

using namespace std;

typedef struct {
  string name;
  int size;
  int num_block;
  int address[100];
} iNode;

typedef struct node_ {
  int address;
  struct node_ *next;
} Node, *List;

typedef struct item_ {
  int startAddress;
  int num_block;
} Item, *Table;


vector<iNode> FCB;

iNode search(string name);
void remove(string name);
void Print();

Table FTM_init();
void FTM_create(string name, int size, Table T, int& tabel_size);
void FTM_remove(string name, Table T, int& table_size);
void FTM_print(Table T, int table_size);
void FTM_free(Table T);

List FLLM_init();
void FLLM_create(string name, int size, List L);
void FLLM_remove(string name, List L);
void FLLM_print(List L);
void FLLM_free(List L);

void BIT_create(string name, int size, bool* bitmap);
void BIT_remove(string name, bool* bitmap);
void BIT_print(bool* bitmap);

int main(int argc, char* argv[]){
  if (argc < 2) {
    cout << "Please input file management algorithm and retry" << endl;
    return 1;
  }
  string mode = argv[1];
  cout << mode << endl;
  srand(1);

  Table T = FTM_init();
  int table_size = 1;
  List L = FLLM_init();
  bool bitmap[BLOCK_NUM] = {false};

  for (int i = 0; i < 50; i++) {
    int size = randint(2000, 5001);
    stringstream namestream;
    string name;
    namestream << i+1 << ".txt";
    name = string(namestream.str());
    if (mode == "FTM") FTM_create(name, size, T, table_size);
    else if (mode == "FLLM") FLLM_create(name, size, L);
    else if (mode == "BIT") BIT_create(name, size, bitmap);
  }

  for (int i = 1; i < 50; i += 2) {
    stringstream namestream;
    string name;
    namestream << i << ".txt";
    name = string(namestream.str());
    if (mode == "FTM") FTM_remove(name, T, table_size);
    else if (mode == "FLLM") FLLM_remove(name, L);
    else if (mode == "BIT") BIT_remove(name, bitmap);
  }

  string names[5] = {"A.txt", "B.txt", "C.txt", "D.txt", "E.txt"};
  int sizes[5] = {7000, 5000, 2000, 9000, 3500};
  for (int i = 0; i < 5; i++) {
    if (mode == "FTM") FTM_create(names[i], sizes[i], T, table_size);
    else if (mode == "FLLM") FLLM_create(names[i], sizes[i], L);
    else if (mode == "BIT") BIT_create(names[i], sizes[i], bitmap);
  }

  Print();
  if (mode == "FTM") FTM_print(T, table_size);
  else if (mode == "FLLM") FLLM_print(L);
  else if (mode == "BIT") BIT_print(bitmap);

  FTM_free(T);
  FLLM_free(L);
  return 0;
}

// FCB 操作函数
iNode search(string name) {
  for (int i = 0; i < FCB.size(); i++) {
    if (FCB[i].name == name) {
      return FCB[i];
    }
  }
}

void remove(string name) {
  for (int i = 0; i < FCB.size(); i++) {
    if (FCB[i].name == name) {
      FCB.erase(FCB.begin() + i);
      break;
    }
  }
}

void Print() {
  for (int i = 0; i < FCB.size(); i++) {
    cout << FCB[i].name << " " ;
    for (int j = 0; j < FCB[i].num_block; j++) cout << FCB[i].address[j] << " ";
    cout << endl;
  }
}

// 空闲表法
Table FTM_init() {
  Table T = new Item[BLOCK_NUM];
  T[0].num_block = BLOCK_NUM;
  T[0].startAddress = 0;
  return T;
}

void FTM_create(string name, int size, Table T, int& table_size) {
  int block_num = ceil(1.0 * size / BLOCK_SIZE);

  iNode i_node;
  i_node.name = name;
  i_node.size = size;
  i_node.num_block = block_num;

  for (int i = 0; i < table_size; i++) {
    if (T[i].num_block >= block_num) {
      for (int j = 0; j < block_num; j++) {
        i_node.address[j] = T[i].startAddress + j;
      }
      if (T[i].num_block == block_num) {
        for (int j = i; j < table_size-1; j++) T[j] = T[j+1];
        table_size--;
      }
      else {
        T[i].num_block -= block_num;
        T[i].startAddress += block_num;
      }
      break;
    }
  }
  FCB.push_back(i_node);
}

void FTM_remove(string name, Table T, int& table_size) {
  iNode i_node = search(name);
  remove(name);

  for (int i = 0; i < i_node.num_block; i++) {
    int item_index = table_size;
    T[item_index].num_block = 1;
    T[item_index].startAddress = i_node.address[i];
    for (int j = 0; j < table_size; j++) {
      if (T[j].startAddress + T[j].num_block == i_node.address[i]) {
        T[j].num_block++;
        item_index = j;
        break;
      }
    }
    if (item_index == table_size) {
      table_size++;
    }
    for (int j = 0; j < table_size; j++) {
      if (T[j].startAddress - 1 == i_node.address[i]) {
        T[j].startAddress = T[item_index].startAddress;
        T[item_index].num_block += T[j].num_block;
        for (int k = j; k < table_size-1; k++) T[k] = T[k+1];
        table_size--;
        break;
      }
    }
  }
}

void FTM_print(Table T, int table_size) {
  int cnt = 0;
  for (int i = 0; i < table_size; i++) {
    for (int j = 0; j < T[i].num_block; j++) {
      printf("%3d ", T[i].startAddress + j);
      cnt++;
      if (cnt % 20 == 0) cout << endl;
    }
  }
  cout << endl << "free block number:" << cnt << endl;
}

void FTM_free(Table T) {
  delete [] T;
}

// 空闲链表法
List FLLM_init() {
  List head = new Node;
  head->address = BLOCK_NUM;
  List rear = head;
  for (int i = 0; i < BLOCK_NUM; i++) {
    List node = new Node;
    node->address = i;
    rear->next = node;
    rear = node;
  }
  rear->next = NULL;
  return head;
}

void FLLM_create(string name, int size, List L) {
  int block_num = ceil(1.0 * size / BLOCK_SIZE);
  if (L->address < block_num) return;
  List rear = L;

  iNode i_node;
  i_node.name = name;
  i_node.size = size;
  i_node.num_block = block_num;

  for (int i = 0; i < block_num; i++) {
    List tmp = rear->next;
    rear->next = rear->next->next;
    i_node.address[i] = tmp->address;
    L->address--;
    delete tmp;
  }
  FCB.push_back(i_node);
}

void FLLM_remove(string name, List L) {
  iNode i_node = search(name);
  remove(name);

  List rear = L;
  while (rear->next) rear = rear->next;
  for (int i = 0; i < i_node.num_block; i++) {
    List node = new Node;
    node->address = i_node.address[i];
    rear->next = node;
    rear = node;
    L->address++;
  }
  rear->next = NULL;
}

void FLLM_print(List L) {
  List rear = L->next;
  int cnt = 0;
  while (rear) {
    printf("%3d ", rear->address);
    cnt++;
    if (cnt % 20 == 0) cout << endl;
    rear = rear->next;
  }
  cout << endl << "free block number:" << L->address << endl;
}

void FLLM_free(List L) {
  List rear = L->next;
  while (L) {
    delete L;
    L = rear;
    if (rear) rear = rear->next;
  }
}

// 位示图法
void BIT_create(string name, int size, bool* bitmap) {
  int block_num = ceil(1.0 * size / BLOCK_SIZE);
  int blocks[block_num];
  for (int i = 0; i < block_num; i++) {
    blocks[i] = -1;
  }
  // 这里不能直接使用 int blocks[block_num] = {-1};
  // 因为只有全赋值为 0 是有效的，其余值只是给第一个位置赋值

  iNode i_node;
  i_node.name = name;
  i_node.size = size;
  i_node.num_block = block_num;

  int ad = 0, i = 0;
  while (blocks[block_num - 1] == -1 && ad < BLOCK_NUM) {
    if (!bitmap[ad]) {
      blocks[i] = ad;
      i++;
    }
    else {
      i = 0;
    }
    ad++;
  }
  for (int i = 0; i < block_num; i++) {
    i_node.address[i] = blocks[i];
    bitmap[blocks[i]] = true;
  }
  FCB.push_back(i_node);
}

void BIT_remove(string name, bool* bitmap) {
  iNode i_node = search(name);
  remove(name);

  for (int i = 0; i < i_node.num_block; i++) {
    bitmap[i_node.address[i]] = false;
  }
}

void BIT_print(bool* bitmap) {
  int cnt = 0;
  for (int i = 0; i < BLOCK_NUM; i++) {
    if (!bitmap[i]) {
      printf("%3d ", i);
      cnt++;
      if (cnt % 20 == 0) cout << endl;
    }
  }
  cout << endl << "free block number:" << cnt << endl;
}
