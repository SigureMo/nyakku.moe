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
思路：
1. 中序遍历是升序的，故先升序排序输入序列 
2. 建立完全二叉树（无值） 
3. 中序遍历赋值
4. 层序遍历输出

C++尚在学习中，暂时先使用Python实现
'''
import queue
class TNode():
    def __init__(self):
        self.data = None
        self.index = None
        self.left = None
        self.right = None

    def inOrderTraversal(self, tree, q):
        '''
        if self:
            #print(self.index,self.left,self.right)
            if self.left:
                tree[self.left].inOrderTraversal(tree, q)
            self.data = q.get()
            if self.right:
                tree[self.right].inOrderTraversal(tree, q)
        '''
        if self:
            p = self
            s = []
            while s or p:
                while p:
                    s.append(p)
                    if p.left:
                        p = tree[p.left]
                    else:
                        p = None
                if s:
                    p = s.pop()
                    p.data = q.get()
                    # print(p.index,p.left,p.right)
                    if p.right:
                        p = tree[p.right]
                    else:
                        p = None
            
class Tree():
    def __init__(self):
        self.length = eval(input())
        self.datas = sorted(list(map(int, input().split(' '))))
        self.q = queue.Queue()
        for item in self.datas:
            self.q.put(item)
        self.tree = [None] * (self.length+1)
        self.root = 1
        self.ans = []
        for i in range(self.length):
            i = i + 1
            self.tree[i] = TNode()
            self.tree[i].index = i
            if 2*i <= self.length:
                self.tree[i].left = 2*i
            if 2*i+1 <= self.length:
                self.tree[i].right = 2*i+1
        self.tree[self.root].inOrderTraversal(self.tree, self.q)
        print(' '.join(list(map(getdata, self.tree[1:]))))
'''
    def levelOrderTraversal(self):
        q = queue.Queue()
        q.put(self.tree[self.root])
        while not q.empty():
            t = q.get()
            self.ans.append(str(t.data))
            if t.left:
                q.put(self.tree[t.left])
            if t.right:
                q.put(self.tree[t.right])
'''
def getdata(node):
    return str(node.data)
t = Tree()
#t.levelOrderTraversal()
#print(' '.join(t.ans))
