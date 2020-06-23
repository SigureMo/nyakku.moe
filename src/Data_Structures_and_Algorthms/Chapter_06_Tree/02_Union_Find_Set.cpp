#include <iostream>
#define MaxSize 50
using namespace std;
typedef int ElemType;
typedef struct {
  ElemType data;
  int parent;
} Set;

void Initial(Set S[]);
int Find(Set S[], int x);
void Union(Set S[], ElemType x1, ElemType x2);

int main() {
  Set S[MaxSize];
  Initial(S);
  Union(S, 1, 2);
  cout << Find(S, 1) << endl;
  return 0;
}

void Initial(Set S[]) {
  /** 初始化 MaxSize 个互不重合的子集 */
  for (int i = 0; i < MaxSize; i++) {
    S[i].data = i;
    S[i].parent = -1;
  }
}

int Find(Set S[], ElemType x) {
  /** 查找并返回包含元素 x 的树的根 */
  int idx = 0;
  for (; idx < MaxSize && S[idx].data != x; idx++);
  if (idx == MaxSize) return -1;
  for (; S[idx].parent != -1; idx = S[idx].parent);
  return idx;
}

void Union(Set S[], ElemType x1, ElemType x2) {
  /** 求两个不相交子集合的并集 */
  int root1 = Find(S, x1);
  int root2 = Find(S, x2);
  if (root1 != root2)
    S[root1].parent = root2;
}
