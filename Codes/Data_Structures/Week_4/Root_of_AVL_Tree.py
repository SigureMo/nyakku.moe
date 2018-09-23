'''
# Root of AVL Tree
An AVL tree is a self-balancing binary search tree. In an AVL tree, the heights
of the two child subtrees of any node differ by at most one; if at any time they
differ by more than one, rebalancing is done to restore this property. Figures
1-4 illustrate the rotation rules.

![Figure1]()  
![Figure2]()  
![Figure3]()  
![Figure4]()  

Now given a sequence of insertions, you are supposed to tell the root of the
resulting AVL tree.
# Input Specification:
Each input file contains one test case. For each case, the first line contains
a positive integer N (≤20) which is the total number of keys to be inserted.
Then N distinct integer keys are given in the next line. All the numbers in a
line are separated by a space.
# Output Specification:
For each test case, print the root of the resulting AVL tree in one line.
# Sample Input 1:
```
5
88 70 61 96 120
```
# Sample Output 1:
```
70
```
# Sample Input 2:
```
7
88 70 61 96 120 90 65
```
# Sample Output 2:
```
88
```
'''

class TNode():
    def __init__(self, data):
        self.left = None
        self.right = None
        self.height = 0
        self.data = data

    def getHeight(self):
        if self.left and self.right:
            self.height = max(self.left.getHeight(),self.right.getHeight()) + 1
        elif self.left:
            self.height = self.left.getHeight() + 1
        elif self.right:
            self.height = self.right.getHeight() + 1
        else:
            self.height = 0
        return self.height

    def insert(self, data):
        if data > self.data:
            if self.right:
                self.right = self.right.insert(data)
                if (not self.left) or (abs(self.left.getHeight() - self.right.getHeight())>1):
                    if data > self.right.data:
                        self = self.RR()
                    else:
                        self = self.RL()
            else:
                self.right = TNode(data)
        elif data < self.data:
            if self.left:
                self.left = self.left.insert(data)
                if (not self.right) or (abs(self.left.getHeight() - self.right.getHeight())>1):
                    if data < self.left.data:
                        self = self.LL()
                    else:
                        self = self.LR()
            else:
                self.left = TNode(data)
        return self

    def iot(self):
        if self.left:
            self.left.iot()
        print(self.data)
        if self.right:
            self.right.iot()

    def RR(self):
        t = self.right
        self.right = t.left
        t.left = self
        return t

    def LL(self):
        t = self.left
        self.left = t.right
        t.right = self
        return t

    def LR(self):
        self.left = self.left.RR()
        return self.LL()

    def RL(self):
        self.right = self.right.LL()
        return self.RR()
    
class Tree():
    def __init__(self, root):
        self.root = root

# Test:
# tree = Tree(TNode(1))
# tree.root = tree.root.insert(4)
# tree.root = tree.root.insert(3)
# tree.root = tree.root.insert(2)
# tree.root.iot()
# print(tree.root.getHeight())
N = eval(input())
datas = list(map(int, input().split(' ')))
flag = True
for data in datas:
    if flag:
        tree = Tree(TNode(data))
        flag = False
    else:
        tree.root = tree.root.insert(data)
print(tree.root.data)
