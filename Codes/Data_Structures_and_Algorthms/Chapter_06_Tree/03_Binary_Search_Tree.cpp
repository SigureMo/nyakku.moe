#include <iostream>

using namespace std;
typedef int ElemType;
typedef struct _node {
  ElemType data;
  struct _node *lchild;
  struct _node *rchild;
} TNode, *BinTree;

BinTree FindMin(BinTree BST);
BinTree FindMax(BinTree BST);
BinTree Search(BinTree BST, ElemType x);
BinTree Insert(BinTree BST, ElemType x);
BinTree Delete(BinTree BST, ElemType x);

int main() {
  ElemType a[10] = {1, 5, 4, 8, 2, 9, 3, 0, 7, 6};
  BinTree BST = NULL;
  for (auto x: a) {
    BST = Insert(BST, x);
  }
  cout << BST->rchild->lchild->data << endl;
  BST = Delete(BST, 5);
  cout << BST->rchild->data << endl;
  return 0;
}

BinTree Insert(BinTree BST, ElemType x) {
  /** 插入元素 x */
  if (!BST) {
    BST = (BinTree)malloc(sizeof(TNode));
    BST->data = x;
    BST->lchild = NULL;
    BST->rchild = NULL;
  }
  else {
    if (x < BST->data) BST->lchild = Insert(BST->lchild, x);
    else if (x > BST->data) BST->rchild = Insert(BST->rchild, x);
  }
  return BST;
}

BinTree FindMin(BinTree BST) {
  /** 获取最小结点（非递归） */
  if (BST)
    while (BST->lchild) BST = BST->lchild;
  return BST;
}

BinTree FindMax(BinTree BST) {
  /** 获取最大结点（非递归） */
  if (BST)
    while (BST->rchild) BST = BST->rchild;
  return BST;
}

BinTree Search(BinTree BST, ElemType x) {
  /** 搜索值为 x 的结点（非递归） */
  while (BST) {
    if (BST->data < x) BST = BST->lchild;
    else if (BST->data > x) BST = BST->rchild;
    else return BST;
  }
  return NULL;
}

BinTree Delete(BinTree BST, ElemType x) {
  /** 删除值为 x 的结点
   * 如果是叶子结点，直接删除
   * 如果只有一个孩子结点，只需要将其孩子放到其父结点上
   * 如果两个孩子都有，可以转化为将·左子树的最大值或者右子树的最小值·
   * 放在删除结点的位置上
  **/
  BinTree Tmp;
  if (!BST) throw "Not Found!";
  else if (x < BST->data) BST->lchild = Delete(BST->lchild, x);
  else if (x > BST->data) BST->rchild = Delete(BST->rchild, x);
  else {
    if (BST->lchild && BST->rchild) {
      Tmp = FindMin(BST->rchild);
      BST->data = Tmp->data;
      BST->rchild = Delete(BST->rchild, BST->data);
    }
    else {
      Tmp = BST;
      if (!BST->lchild) BST = BST->rchild;
      else if (!BST->rchild) BST = BST->lchild;
      free(Tmp);
    }
  }
  return BST;
}
