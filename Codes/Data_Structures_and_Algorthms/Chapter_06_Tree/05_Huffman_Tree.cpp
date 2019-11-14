#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Node {
  public:
    int weight;
    Node *left;
    Node *right;
    Node(int weight) {
      this->weight = weight;
      this->left = NULL;
      this->right = NULL;
    }
    friend ostream &operator<<(ostream &os, const Node &node);
};

template<typename T>
class Heap {
  /** 堆 STL 的简单封装 */
  private:
    vector<T> data;
    bool (*comp)(T, T);
  public:
    Heap(T a[], int len, bool (*comp)(T, T)) {
      this->comp = comp;
      for (int i = 0; i < len; i++) {
        data.push_back(a[i]);
      }
      make_heap(data.begin(), data.end(), comp);
    }
    void insert(T x) {
      data.push_back(x);
      push_heap(data.begin(), data.end(), comp);
    }
    T pop() {
      pop_heap(data.begin(), data.end(), comp);
      T el = data.back();
      data.pop_back();
      return el;
    }
    void print(bool isPtr=false) {
      for (auto i : data) {
        if (isPtr) cout << *i;
        else cout << i;
        cout << " ";
      }
      cout << endl;
    }
};

typedef Node *HuffmanTree;
HuffmanTree Huffman(int a[], int len);

int main() {
  int a[] = {7, 5, 2, 4, 9};
  HuffmanTree HT = Huffman(a, 5);
  return 0;
}
// :::
HuffmanTree Huffman(int a[], int len) {
  /** 建立哈夫曼树 */
  Node *n[len];
  for (int i = 0; i < len; i++) {
    n[i] = new Node(a[i]);
  }
  auto cmp = [](Node *T1, Node *T2) -> bool {
    return T1->weight > T2->weight;
  };
  Heap<HuffmanTree> H(n, len, cmp);
  for (int i = 0; i < len-1; i++) {
    Node *left = H.pop();
    Node *right = H.pop();
    HuffmanTree T = new Node(left->weight + right->weight);
    T->left = left;
    T->right = right;
    H.insert(T);
    H.print(true);
  }
  return H.pop();
}
// :::
ostream &operator<<(ostream &os, const Node &node) {
  /** 重载 << 以获得方便的数据显示方法 */
  os << node.weight;
  if (node.left || node.right) {
    os << "<";
    if (node.left) os << *node.left;
    else os << " ";
    os << "|";
    if (node.right) os << *node.right;
    else os << " ";
    os << ">";
  }
  return os;
}
