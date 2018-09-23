'''
# Complete Binary Search Tree
A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

- The left subtree of a node contains only nodes with keys less than the node's key.
- The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
- Both the left and right subtrees must also be binary search trees.
A Complete Binary Tree (CBT) is a tree that is completely filled, with the possible exception of the b
ottom level, which is filled from left to right.

Now given a sequence of distinct non-negative integer keys, a unique BST can be constructed if it is 
required that the tree must also be a CBT. You are supposed to output the level order traversal seque
nce of this BST.
# Input Specification:
Each input file contains one test case. For each case, the first line contains a positive integer N 
(≤1000). Then N distinct non-negative integer keys are given in the next line. All the numbers in a
 line are separated by a space and are no greater than 2000.
# Output Specification:
For each test case, print in one line the level order traversal sequence of the corresponding complete
 binary search tree. All the numbers in a line must be separated by a space, and there must be no 
extra space at the end of the line.
# Sample Input:
```
10
1 2 3 4 5 6 7 8 9 0
```
# Sample Output:
```
6 3 8 1 5 7 9 0 2 4
```
'''

'''
原来那个在N随机时候死活算不出来（蠢了蠢了蠢了，我居然在最开始对每个数据进行str
而不是int……，算了，拿这个方法试下），所以参考网上其他思路做
1. 完全二叉树层序遍历的顺序有着如下规律：
    1. 如果根节点为i，并且2i存在，则其左儿子必然为2i
    2. 如果根节点为i，并且2i+1存在，则其右儿子必然为2i+1
2. 二叉搜索树的中序遍历必然是递增序列
3. 将上述两性质序列对应起来即可
'''

# miaow
import queue

def iot(root):
    if 2 * root <= N:
        iot(2 * root)
    a[root] = datas.get()
    if 2 * root + 1 <= N:
        iot(2 * root + 1)

N = eval(input())
l = sorted(list(map(int, input().split(' '))))
datas = queue.Queue()
for i in l:
    datas.put(i)
a = [None] * (N+1)
iot(1)
print(' '.join(list(map(str, a[1:]))))

# $%^$%@^$#%$#%%$&^%ヽ(#`Д´)ﾉ┌┛〃就这么几行！！！
