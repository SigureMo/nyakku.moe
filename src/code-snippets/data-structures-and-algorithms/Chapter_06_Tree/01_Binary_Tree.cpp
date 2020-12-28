#include <iostream>
#include <queue>
#include <stack>

using namespace std;

typedef int ElemType;
typedef struct _node {
  ElemType data;
  struct _node *left;
  struct _node *right;
} BTNode, *BinTree;

BinTree Create();
int GetDepth(BinTree BT);
void Visit(BinTree BT);
void PreOrderTraversal(BinTree BT);
void InOrderTraversal(BinTree BT);
void PostOrderTraversal(BinTree BT);
void LevelOrderTraversal(BinTree BT);
void PreOrderTraversalNonRecursion(BinTree BT);
void InOrderTraversalNonRecursion(BinTree BT);
void PostOrderTraversalNonRecursion(BinTree BT);

int main() {
  BinTree BT = Create();
  cout << "Depth: " << GetDepth(BT) << endl;
  cout << "PreOrderTraversal:\t\t";
  PreOrderTraversal(BT);
  cout << endl;
  cout << "InOrderTraversal:\t\t";
  InOrderTraversal(BT);
  cout << endl;
  cout << "PostOrderTraversal:\t\t";
  PostOrderTraversal(BT);
  cout << endl;
  cout << "LevelOrderTraversal:\t\t";
  LevelOrderTraversal(BT);
  cout << endl;
  cout << "PreOrderTraversalNonRecursions:\t";
  PreOrderTraversalNonRecursion(BT);
  cout << endl;
  cout << "InOrderTraversalNonRecursions:\t";
  InOrderTraversalNonRecursion(BT);
  cout << endl;
  cout << "PostOrderTraversalNonRecursions:";
  PostOrderTraversalNonRecursion(BT);
  cout << endl;
  return 0;
}

BinTree Create() {
  /** 建立一棵树（根据先序遍历序列）
   * 示例输入 1 2 4 -1 -1 5 -1 -1 3 6 -1 -1 7 -1 -1
   */
  int a;
	scanf("%d", &a);
	if (a == -1) return NULL;
	BinTree BT = (BinTree)malloc(sizeof(BTNode));
	BT->data = a;
	BT->left = Create();
	BT->right = Create();
	return BT;
}

int GetDepth(BinTree BT) {
  /** 获取深度（实际上是后序遍历的一种应用） */
  if (!BT) return 0;
  int LD = GetDepth(BT->left);
  int RD = GetDepth(BT->right);
  return (LD > RD? LD: RD) + 1;
}

void Visit(BinTree BT) {
  /** 访问某一结点
   * 比如输出其值
   */
  printf("\t%d", BT->data);
}
// PRE_ORDER_BLOCK
void PreOrderTraversal(BinTree BT) {
  /** 先序遍历的递归实现 */
  if (BT) {
    Visit(BT);
    PreOrderTraversal(BT->left);
    PreOrderTraversal(BT->right);
  }
}
// PRE_ORDER_BLOCK
// IN_ORDER_BLOCK
void InOrderTraversal(BinTree BT) {
  /** 中序遍历的递归实现 */
  if (BT) {
    InOrderTraversal(BT->left);
    Visit(BT);
    InOrderTraversal(BT->right);
  }
}
// IN_ORDER_BLOCK
// POST_ORDER_BLOCK
void PostOrderTraversal(BinTree BT) {
  /** 后序遍历的递归实现 */
  if (BT) {
    PostOrderTraversal(BT->left);
    PostOrderTraversal(BT->right);
    Visit(BT);
  }
}
// POST_ORDER_BLOCK
// LEVEL_ORDER_BLOCK
void LevelOrderTraversal(BinTree BT) {
  /** 层序遍历 */
  queue<BinTree> Q;   // 为了方便测试，这里直接使用 C++ STL 中的 queue
  BinTree p = BT;
  if (!p) return;
  Q.push(p);
  while (!Q.empty()) {
    // 简单地说，就是每次拿出来一个，放进去俩（如果有的话）
    p = Q.front();   // 该方法只返回不删除
    Q.pop();          // 该方法只删除不返回
    Visit(p);
    if (p->left) Q.push(p->left);
    if (p->right) Q.push(p->right);
  }
}
// LEVEL_ORDER_BLOCK
// PRE_ORDER_NOREC_BLOCK
void PreOrderTraversalNonRecursion(BinTree BT) {
  /** 先序遍历的非递归实现 */
  stack<BinTree> S;
  BinTree p = BT;
  while (p || !S.empty()) {   // 准备好了就出发！
    while (p) {               // 这里可以落脚，看看下一步往哪走！
      S.push(p);              // 嗯，在地图上标记一下这里(っ•̀ω•́)っ✎⁾⁾
      Visit(p);               // 逛一逛咯
      p = p->left;          // 逛完往左走走
    }                         // 噫，这里不能落脚啊！肿么办
    if (!S.empty()) {         // 拿起地图，看看有没有地方可以去
      p = S.top();            // 往回走，回到刚刚过来的地方
      S.pop();                // 地图上划掉刚刚那里~(っ•̀ω•́)っ✎⁾⁾
      p = p->right;          // 往右走试试看！
    }                         // 到啦！这是个什么样的地方呢？
  }                           // 既没有落脚点，也没退路了，不过这一路好开心的说！
}
// PRE_ORDER_NOREC_BLOCK
// IN_ORDER_NOREC_BLOCK
void InOrderTraversalNonRecursion(BinTree BT) {
  /** 中序遍历的非递归实现 */
  stack<BinTree> S;
  BinTree p = BT;
  while (p || !S.empty()) {   // 准备好了就出发！
    while (p) {               // 这里可以落脚，看看下一步往哪走！
      S.push(p);              // 嗯，在地图上标记一下这里(っ•̀ω•́)っ✎⁾⁾
      p = p->left;          // 今天没空，直接往左走，下次再逛
    }                         // 噫，这里不能落脚啊！肿么办
    if (!S.empty()) {         // 拿起地图，看看有没有地方可以去
      p = S.top();            // 往回走，回到刚刚过来的地方
      S.pop();                // 地图上划掉刚刚那里~(っ•̀ω•́)っ✎⁾⁾
      Visit(p);               // 我又来啦！这回好好逛一下！
      p = p->right;          // 逛完往右走试试看！
    }                         // 到啦！这是个什么样的地方呢？
  }                           // 既没有落脚点，也没退路了，不过这一路好开心的说！
}
// IN_ORDER_NOREC_BLOCK
// POST_ORDER_NOREC_BLOCK
void PostOrderTraversalNonRecursion(BinTree BT) {
  /** 后序遍历的非递归实现
   * 基本上将大部分特殊情况都标出来了，三次遇到以及需要回退的空指针情况
   * 后序遍历之所以难是因为前序中序在第二次遇到就将结点抛出了，而后序就必须一直保留结点，
   * 直至第三次遇到，但是栈是容易保存两个状态（在栈中或者不在栈中）的，三个状态就比较难了，
   * 相应地，实现起来就比较麻烦
   * 在第二次遇到的时候仅仅是看看栈顶，而不取出（也可以拿出来再放回去），然后就去遍历右子树了，
   * 当卡在右侧空指针的时候，需要不断回退（前序和中序早就把没用的扔掉了），但是回退到哪呢？
   * 由于指针已经指在右侧了，所以左子树一定已经全部抛出过了，现在连续抛出的路径应该是一个右下到左上的过程，
   * 当回到左上角的时候，将指针指向右面的兄弟（也许是姐妹？）即可
   */
  stack<BinTree> S;
  BinTree p = BT;
  while (p || !S.empty()) {             // 准备好了就出发！
    if (!p) {                           // [右侧空指针]怎么这里不能落脚啊？
      while (p == S.top()->right) {    // 看看地图，之前走过哪里？
        p = S.top();                    // 那个方向，往回走~
        Visit(p);                       // [第三次遇到]唔，都第三次来了，逛一下吧~
        S.pop();                        // 地图上划掉刚刚那里~(っ•̀ω•́)っ✎⁾⁾
        if (S.empty()) return;          // 呀，没路啦，不过这一路收获好多，今天步数可以破 3w 啦~
      }                                 // 总算退回来了
      p = S.top()->right;              // 往右走走看
    }                                   // 到啦！这是个什么样的地方呢？
    while (p) {                         // 这里可以落脚，看看下一步往哪走！
      S.push(p);                        // 嗯，在地图上标记一下这里(っ•̀ω•́)っ✎⁾⁾
      // Visit(p);                      // [第一次遇到]今天没空，以后再逛
      p = p->left;                    // 直接往左走
    }                                   // [左侧空指针]噫，这里不能落脚啊！肿么办
    if (!S.empty()) {                   // 拿起地图，看看有没有地方可以去
      p = S.top();                      // 往回走，回到刚刚过来的地方
      // Visit(p);                      // [第二次遇到]我很忙哒！不逛！
      p = p->right;                    // 往右走试试看！
    }                                   // 到啦！这是个什么样的地方呢？
  }                                     // 既没有落脚点，也没退路了，不过这一路好开心的说！
}
// POST_ORDER_NOREC_BLOCK
