# Data Structures <Badge text="beta" type="tip"/> <Badge text="10.2.9"/>

-  Data Structures

   -  [Linear List](#_2-线性表（linear-list）)

      -  [Ranked List](#_2-1-顺序表示（ranked-list）)
      -  [Linked List](#_2-2-链式表示（linked-list）)
      -  [Stack](#_3-堆栈（stack）)
      -  [Queue](#_4-队列（queue）)
      -  [String](#_5-串（string）)

   -  [Tree](#_6-树（tree）)
      -  [Binary Tree](#_6-4-二叉树的定义)
         -  [Binary Search Tree](#_6-10-二叉搜索树（binary-search-tree）)
         -  [Heap](#_7-堆（heap）)
            -  Max_Heap
            -  Min_Heap
   -  [Graph](#_8-图（graph）)
      -  [Adjacency matrix representation](#_8-1-2-adjacency-matrix-representation)
      -  [Adjacency list representation](#_8-1-3-adjacency-list-representation)

-  Algorithms
   -  [Sort](#_9-排序（sort）)
   -  [Hashing](#_10-散列查找（hashing）)
-  [Extends](#extends)
-  [Status](#status)
-  [Reference](#reference)

## 1 绪论

-  写在前面
   -  取消了[TOC]，自己重新写的索引，虽然是把数据结构与算法分开了，但是那只是在标题层面上的简单的分类，事实上他们是无法割裂的整体，在**数据结构部分无时无刻不在使用着算法，算法所依赖的基础也是数据结构**
   -  草草过了遍中 M 的《数据结构》，收获颇多，但我也知道这还远远不够，所以，以此为框架，To be Added

## 2 线性表（Linear_List）

### 2.1 顺序表示（Ranked_List）

1. 使用新表可以化插入为复制(时降空增)
2. 排序后的更容易操作，不需要每次都全部搜索

[Ranked_List](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_2_List/Ranked_List.c)

### 2.2 链式表示（Linked_List）

1. 求长度和按 index 查找明显变慢，但是删除和插入操作明显变简单
2. 删除和插入要注意操作顺序

[Linked_List](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_2_List/Linked_List.c)

#### 2.2.1 广义表（General_Lists）

1. 广义表是线性表的推广
2. 对于线性表而言，n 个元素都是基本的单元素
3. 广义表中，这些元素不仅可以是单元素也可以是另一个广义表

[General_Lists](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_2_List/General_Lists.c)

#### 2.2.2 多重链表（Multiple_List）

1. 多重链表中结点的**指针域会有多个**，如前面例子包含了 Next 和 SubList 两个指针域
2. 但包含两个指针域的链表并不一定是多重链表，比如双向链表就不是多重链表。
   > 多重链表有广泛的用途：基本上如**树、图**这样相对复杂的数据结构都可以采用多重链表方式实现存储。
   > Examples:
       稀疏矩阵的存储 -> 使用十字链表（一种典型的多重链表）存储，即使用两个指针域（Right、Down）将同行和同列串起来

## 3 堆栈（Stack）

### 3.1 An Example

对表达式进行求值

1. 由运算符号和运算数构成
2. 使用后缀表达式更容易求（如中缀表达式$a + b * c - d / e$可以转换为$a b c * + d e / -$）

### 3.2 描述

堆栈（Stack）：具有一定操作约束的线性表

> 只在一端（栈顶[Top]）进行插入、删除
> 插入：入栈（Push）
> 删除：出栈（Pop）
> ===>**后入先出**（Last In First Out [LIFO]）

### 3.3 顺序存储

[Ranked_Stack](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_3_Stack/Ranked_Stack.c)

> Extend
> 使用一个数组实现两个堆栈=>
> 一个栈底在左端，一个栈底在右端，可以充分利用数组空间
> [Double_Stack](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_3_Stack/Double_Stack.c)

### 3.4 链式存储

如果使用链尾作为 Top，则难以实现 Pop 操作，故 Top 应在链头

[Linked_Stack](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_3_Stack/Linked_Stack.c)

### 3.5 再探 Example

1. 从左到右读入**后缀表达式**的各项，遇到运算数则入栈，遇到运算符则 pop 适当个数运算数，结果入栈
2. 中缀表达式先转换为后缀表达式： 1. 遇到运算数则输出，遇到运算符比较优先级，若当前符号优先级低于栈顶元素则入栈，否则弹出栈内元素，直至栈顶元素比当前符号优先级低，此时该符号入栈 2. 左括号'('栈外优先级最高，栈外优先级最低，遇到右括号')'则一直出栈直到左括号
   ![Data_Structures01](../Images/Data_Structures01.png)

### 3.6 应用

1. 函数调用及递归实现
2. 深度优先搜索
3. 回溯方法

## 4 队列（Queue）

### 4.1 定义

具有一定操作约束的线性表

> 数据插入：入队列(AddQ)
> 数据删除：出队列（DeleteQ）
> 先来先服务
> **先进先出**：FIFO

### 4.2 顺序存储

为使数组空间得到充分利用，可以使用循环队列，但这使得用参数 Rear 和 Front 不能辨别的满与空的状态（根本原因是不能用 n 个队列的状态表示 n+1 种状态）
解决方案：

1. 增加一个参数
2. 将数组空余一个位置，使得队列减少一种状态

[Seq_Queue](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_4_Queue/Seq_Queue.c)

### 4.3 链式存储

同[Stack](#34-链式存储)，如若需要删除操作的 Front 在链尾则难以继续对新的链尾进行操作，故 Front 在链首，即：

```
graph TD
    A[Front]
    B[Node1]
    C[Node2]
    D[NodeN]
    E[Rear]
    A-->B
    B-->C
    C-->|............|D
    E-->D
```

### 总结

1. 对于链表，要看清是否有头结点，要善于利用 front、rear 指针和临时头结点对链表进行操作 [Merge_Linked_List](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Week_2/Merge_Linked_List.c)

## 5 串（String）

### 5.1 串类型的定义

就是字符串啦，逻辑结构与线性表极为相似，但是串操作对象与操作方式大多对应的是子串

### 5.2 串的表示与实现

#### 5.2.1 定长顺序存储表示

用定长数组表示就好，可在第一位存储串长

#### 5.2.2 堆分配存储表示

结构体存储指针域与串长，解决了定长问题

#### 5.2.3 串的块链存储表示

每个 Node 存储一定位字符，尾结点需要补全。虽然联接等操作简单了，但因为一维模型化为二维了，操作不灵活，而且消耗大量存储空间。

### 5.3 串的模式匹配算法

1. 双指针循环迭代
   i j 两指针分别指向模式串与主串，若不匹配，两指针均需回溯
2. KMP
   指针 i 不需要回溯，模式串向右滑动一段距离

## 6 树（Tree）

### 6.1 引子

#### 6.1.1 什么是树

表征**层次**关系的一种数据结构

#### 6.1.2 查找（Searching）

根据某个给定关键字 K，从集合 R 中找出关键字与 K 相同的记录

1. **静态查找**
   集合中记录是固定的
   没有插入和删除操作，只有查找
   实现： 1. _顺序查找_ 利用数组与指向该数组的结构体进行查找 时间复杂度为$O(n)$ > 可以建立哨兵，（index=0 处放 K，倒序查找）

       2. *二分查找*（Binary Search）
       条件：**有序、连续存放（数组）**
       时间复杂度为$O(logN)$
       > 二分查找的判定树便是一个树结构，待查找元素所在**层数**便是该元素所需查找的次数，最坏情况为该树的**深度**即$[log_2n] + 1$
       平均成功查找次数$ASL = (4*4 + 4*3 + 2*2 + 1)/11 = 3$

       > 如果组织一个像判定树一样的结构，那么很容易达到二分查找的效率，而且很容易插入和删除结点，以实现动态查找

2. **动态查找**
   集合中记录是动态变化的
   除查找，还可能发生插入和删除

### 6.2 树的定义和术语

#### 6.2.1 树的定义

**树（Tree）**：n（n>=0）个结点构成的有限集合
n=0：**空树**
对于**非空树**：

1. 有**根（Root）**，用 r 表示
2. 其余结点可分为 m（m>0）个互不相交的有限集，其中每个集合本身又是一棵树，称为原来树的**子树（SubTree）**
   > 子树是不相交的
   > 除了根节点外，每个结点有且仅有一个父结点
   > 一颗 N 个结点的树有 N-1 条边

> 树是保证结点连通的**边最少**的连接方式

#### 6.2.2 树的一些基本术语

1. **_结点的度（Degree）_**：结点的子树个数
2. **_树的度_**：树的所有结点中**最大的度数**
3. **叶节点（Leaf）**：度为 0 的结点
4. **父结点（Parent）**：有子树的结点是其子树的根结点的父结点
5. **子结点（Child）**：若 A 结点是 B 结点的父结点，则称 B 结点是 A 结点的子结点；子结点也称孩子节点
6. **兄弟结点（Sibling）**：具有同一父结点的各结点彼此是兄弟结点
7. **_路径和路径长度_**：从结点$n_1$到$n_k$的**路径**为一个结点序列$n_1, n_2, ..., n_k$,$n_i$是 n<sub>i+1</sub>的父结点。路径所包含边的个数为**路径的长度**
8. **祖先结点（Ancestor）**：沿树根到某一结点路径上的所有结点都是这个结点的祖先结点
9. **子孙结点（Descendant）**：某一结点的子树中所有结点是这个结点的子孙
10.   **结点的层次（Level）**：规定根节点在 1 层，其它任一结点的层数是其父结点的层数加 1
11.   **_树的深度（Depth）_**：树中所有结点中的**最大层次**是这棵树的深度

### 6.3 树的表示

数组肯定不行了，普通链表放 Data 与 Childs 又可能造成空间上的浪费，故采用以下方法：
儿子-兄弟表示法：

![Data_Structures02](../Images/Data_Structures02.png)
**树->二叉树**

### 6.4 二叉树的定义

#### 6.4.1 定义

**二叉树 T**：一个有穷的结点集合
这个结点可以为空
若不为空，则它是由根节点和称为其左子树$T_L$和右子树$T_R$的两个不相交的二叉树组成

> 二叉树不是度为 2 的树，二叉树子树有左右顺序之分

#### 6.4.2 几种特殊二叉树

1. 斜二叉树（Skewed Binary Tree）
2. 完美二叉树（Perfect Binary Tree） 满二叉树（Full Binary Tree）
3. 完全二叉树（Complete Binary Tree）

#### 6.4.3 二叉树的几个重要性质

1. 一个二叉树第$i$层的最大结点数为：$2_{i-1}$,$i>=1$
2. 由 1 易知：深度为 K 的二叉树有最大的结点总数为：$2^k-1, k>=1$
3. 对任何非空二叉树 T，若$n_0$表示叶结点的个数、$n_2$是度为 2 的非叶节点个数，那么两者满足关系$n_0 = n_2 + 1$

#### 6.4.4 二叉树的抽象数据类型定义

1. 是否为空
2. 创建
3. 遍历
   遍历方法： 1. 先序 根 左子树 右子树 2. 中序 左子树 根 右子树 3. 后序 左子树 右子树 根 4. 层次遍历 从上到下、从左到右

### 6.5 二叉树的存储结构

1. 顺序存储结构
   -  完全二叉树 编号 对应于 Array 的 index
      -  非根节点的父结点的序号是[i/2]
      -  结点（序号为 i）的左孩子结点的序号是 2i，右孩子是 2i+1
   -  一般二叉树 补充成完全二叉树，但是会浪费空间
2. 链表存储
   Left Data Right

### 6.6 二叉树的遍历

1. 先序遍历 1. 访问根节点 2. 先序遍历其左子树 3. 先序遍历其右子树
   很明显是一种递归，那便使用递归程序实现

2. 中序遍历

   1. 中序遍历其左子树
   2. 访问根节点
   3. 中序遍历其右子树

3. 后序遍历
   1. 后序遍历其左子树
   2. 后序遍历其右子树
   3. 访问根节点

> 三种遍历过程路程一样，只不过访问各结点时机不同

[Binary_Tree](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_6_Tree/Binary_Tree.c)

### 6.7 二叉树的非递归遍历

使用**堆栈**
[Binary_Tree_non_recursion](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_6_Tree/Binary_Tree_non_recursion.c)

### 6.8 二叉树的层序遍历

**线性化**

1. 队列实现 1. 根节点入队 2. 循环：结点出队，访问该结点，其左右儿子入队
   => 从上至下，从左到右，一层一层
2. 堆栈实现

### 6.9 Examples

1. 求叶子结点 改改遍历就好啦
2. 求二叉树高度 $Height=max(H_L,H_R)+1$，可通过改造后序遍历实现
3. 二元运算表达式树及其遍历
   1. 先序遍历变成前缀表达式
   2. 中序遍历变成中缀表达式 但是会受到运算符优先级的影响，需要加括号
   3. 后序遍历变成后缀表达式
4. 由两种遍历序列确定二叉树
   前中可以，后中可以，但前后不可以，亦即**必须包含中序遍历** > 因为 前序 根左右，中序 左根右 后序 左右根
   知道前序后序相当于知道 根（左右），（左右）根，左右从未被界定开来，很明显这样的二叉树并不唯一

### 6.10 二叉搜索树（Binary Search Tree）

可以为空，如果不空则满足：

1. 非空左子树的所有键值小于其根节点的键值
2. 非空右子树的所有键值大于其根节点的键值
3. 左、右子树都是二叉搜索树

### 6.11 平衡二叉树（Banlanced Binary Tree）

如果插入次序不同，将导致不同的深度与平均查找长度 ASL（各个结点查找次数统计平均）

#### 6.11.1 平衡因子

平衡因子（BF）：$BF(T) = h_L - h_R$
平衡二叉树：空树或者任一结点左、右子树高度差的绝对值不超过 1，即$|BF(T)| <= 1$

#### 6.11.2 平衡二叉树的调整

看**破坏者**和**被破坏者**（BF>1）的结点的关系

1. 破坏者在被破坏者右子树的右子树，需要 RR 旋转
2. 破坏者在被破坏者左子树的左子树，需要 LR 旋转
3. 破坏者在被破坏者左子树的右子树，需要 LR 旋转
4. 破坏者在被破坏者右子树的左子树，需要 RL 旋转

### 6.12 集合（Set）

#### 6.12.1 集合的表示

使用双亲表示法，孩子直接指向双亲，可使用数组存储 struct

#### 6.12.2 集合的查找

#### 6.12.3 集合的并运算

[set](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_6_Tree/Set.c)

## 7 堆（Heap）

### 7.1 Basic operation of heap

### 7.1.1 What's the heap?

1. 可以解决优先级别队列的问题
2. 堆的两个特性
   1. 结构性： 用数组表示的**完全二叉树**
   2. 有序性: 任一结点的关键字是其子树所有结点的最大值（或最小值）
      -  最大堆（MaxHeap），最大值
      -  最小堆（MinHeap），最小值
         > 这使得从根节点到任意结点路径上结点序列的有序性

#### 7.1.2 Insert of heap

#### 7.1.3 Delete of heap

[Max_Heap](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_7_Heap/Max_Heap.c)

#### 7.1.4 Create of heap

-  如果从空堆不断插入的话，时间复杂度则为 O(n)\*O(logn)
-  可以将复杂度降低到 O(n)，首先使用未排序的数组初始化堆的数据域，然后从最后一个元素的父结点开始依次向左调整

### 7.2 Huffman tree

不是 Heap，只是 Heap 的一种应用而已！

#### 7.2.1 What's the Huffman tree?

1. 可以解决根据频率进行编码问题
2. WPL 要最小

#### 7.2.2 Create of Huffman tree

-  每次把**权值最小**的两棵二叉树合并
-  但是如何最快地找到权值最小的两棵树呢？这可以**利用最小堆，堆的数据域数组存储树结点，以权值为 key 进行初始化排序**
-  特点：
   1. 没有度为 1 的结点
   2. n 个叶子结点的哈夫曼树共有 2n-1 个结点
   3. 哈夫曼树的任意非叶节点的左右字数交换后仍是哈夫曼树
   4. 对同一组权值，可能存在不同构的两棵树的，比如{1, 2, 3, 3}，但是 WPL 是一样的

#### 7.2.3 Huffman coding

1. 如何避免二义性
   使用前缀码：任何字符的编码都不是另一个字符编码的前缀
2. 二叉树用于编码

-  左右分支：0、1
-  字符只在叶结点上

[Huffman_Tree](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_7_Heap/Huffman_Tree.c)

## 8 图（Graph）

### 8.1 What's the graph?

#### 8.1.1 The definition of the graph

-  表示多对多的关系
-  包含
   -  顶点（Vertex）
   -  边（Edge）(v, w)指无向边，<v, w>指 v 指向 w 的边
-  常见术语
   -  有向图
   -  无向图
   -  网络（带权重的图）

#### 8.1.2 Adjacency matrix representation

既然是图，那么就多来几张图吧( • ̀ω•́ )✧
![Data_Structures03](../Images/Data_Structures03.png)
[Adjacency_Matrix.c](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_8_Graph/Adjacency_Matrix.c)
优点很明显呀，就是简单易操作，但是对于稀疏图来说就很浪费空间与时间了，于是就有了下面这种

#### 8.1.3 Adjacency list representation

![Data_Structures04](../Images/Data_Structures04.png)
[Adjacency_List.c](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_8_Graph/Adjacency_List.c)
也就稀疏才合算啦，不然还是很浪费的，而且很多操作是很困难的，比如计算有向图的“入度”、检查任意一对顶点间是否存在边

### 8.2 Traversing graph

#### 8.2.1 DFS

深度优先搜索（Depth First Search）
![Data_Structures05](../Images/Data_Structures05.png)

#### 8.2.2 BFS

广度优先搜索（Breadth First Search）
![Data_Structures06](../Images/Data_Structures06.png)

#### 8.2.3 What if the graph doesn't connect?

先了解一些概念：

1. 连通 有路径
2. 路径 无回路的路径叫简单路径
3. 回路 起点等于终点的路径
4. 连通图 图中任意两顶点均连通
5. 连通分量 包含子图中所有顶点相连的所有边
6. 强连通 有向图中存在双向路径的两顶点
7. 强连通图 有向图的中任意两顶点均强连通
8. 强连通分量 有向图的极大强连通子图

![Data_Structures07](../Images/Data_Structures07.png)

### 8.3 Shortest Path Problem

#### 8.3.1 Single-source shortest Path of Unweighted Graph

使用 BFS 对图上各顶点进行遍历，对每个未访问过的邻接点标记 dist 和 path

```
void Unweighted (Vertex S){
    Enqueue(S, Q);
    while (!IsEmpty(Q)){
        V = Dequeue(Q);
        for ( V 的每个邻接点 W)
            if (dist[W] == -1){
                dist[W] = dist[V] + 1;
                path[W] = V;
                Enqueue(W, Q);
            }
    }
}
```

#### 8.3.2 Single-source shortest Path of Weighted Graph

**Dijkstra 算法**

-  令 S 包含源点和已经确定了最短路径的顶点
-  对于任何没收录的顶点，其最短路径必定只经过 S 内的顶点
-  路径按照递增顺序生成
-  不能解决有负边的情况

```
void Dijkstra(Vertex s){
    while (1) {
        V = 未收录顶点中dist最小者;
        if (这样的V不存在)
            break;
        collected[V] = true;
        for (V 的每个邻接点 W)
            if (collected[W] == false)
                if (dist[V]+E<v,w> < dist[W]){
                    dist[W] = dist[V] + E<v,w>;
                    path[W] = V;
                }
    }
}
```

#### 8.3.3 Multiple-source shortest Path of Weighted Graph

直接单源最短路算法调用|V|遍，对于稀疏图效果好，稠密图嘛，就不太好啦，所以……
**Floyd 算法**

```
void Floyd(){
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            D[i][j] = G[i][j];
            path[i][j] = -1;
        }
    }
    for (k = 0; k < N; k++)
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                if ( D[i][k] + D[k][j] < D[i][j]){
                    D[i][j] = D[i][k] + D[k][j];
                    path[i][j] = k;
                }
}
```

### 8.4 Minimum Spanning Tree

#### 8.4.1 What's the MST

最小生成树

-  首先肯定是一棵树
   -  无回路
   -  |V|个顶点一定有|V|-1 条边
-  然后，它是一棵生成树
   -  包含全部顶点
   -  |V|-1 条边都在图里
-  最后，“最小”表示边的权重和最小

#### 8.4.2 Greedy Algorithm

贪心算法

-  贪：每一步都要最**好**的
-  好：权重最小的边
-  另外：
   -  只能用图里有的边
   -  只能正好用掉|V|-1 条边
   -  不能有回路

#### 8.4.3 Prim Algorithm

(๑╹◡╹)ﾉ"""让一棵小树长大

> 基本实现和 Dijkstra 算法相似，都是从未收录 Vertex 中找 dist 最小的，但是这里的 dist 最小是指距离已经建起来的这棵树的距离，另外要判断下是否能把所有 Vertex 都收录进来

```
void Prim(){
    MST = {s};
    while (1) {
        V = 未收录顶点中dist最小者;
        if (这样的V不存在)
            break;
        将V收录进MST：dist[V] = 0;
        for (V 的每个邻接点W)
            if (dist[W] != 0)
                if (Ev,w < dist[W]){
                    dist[W] = Ev,w;
                    parent[W] = W;
                }
    }
    if (MST中收到的顶点不到|V|个)
        Error("生成树不存在);
}
```

> dist[V] 要设置为无穷或边的权重，当然，不能直接连接到树才设无穷

> 这是一种稠密图合算的算法，下面介绍一种稀疏图合算的算法

#### 8.4.4 Kruskal Algorithm

(๑╹◡╹)ﾉ"""将森林合并成树

> 首先我们认为每一个 Vertex 都是一个树 Node，那么我们整个过程就是不断地将森林合并成树了

```
void Kruskal (Graph G){
    MST = {};
    while (MST 中不到|V|-1条边 && E中还有边){
        从E中取一条权重最小的边Ev,w; // 最小堆
        将Ev,w从E中删除;
        if (Ev,w不在MST中构成回路) // 并查集
            将Ev,w加入MST;
        else
            彻底无视Ev,w;
    }
    if (MST中不到|V|-1条边)
        Error("生成树不存在");
}
```

### 8.5 Topological Sorting

拓扑排序

```
void TopSort(){
    for (cnt = 0; cnt < |V|; cnt++){
        V = 未输出的入度为0的Vertex;
        if (这样的V不存在) {
            Error ("图中有回路");
            break;
        }
        输出V，或者记录V的输出序号;
        for (V 的每个邻接点W)
            Indegree[W]--;
    }
}
```

> 我们可以使用一个容器存放没有前驱结点的结点，这样，我们就不需要每次都查询整个图了，时间复杂度降低了很多

### 8.6 Critical path problem

关键路径问题
![Data_Structures08](../Images/Data_Structures08.png)

## 9 排序（Sort）

### 9.1 简单排序

#### 9.1.1 前提

`void X_Sort(ElementType A[], int N)`

-  大多数情况下，为简单起见，讨论从小到大的证书排序
-  N 是正整数
-  只讨论基于比较的排序（>=<有定义）
-  只讨论内部排序
-  稳定性：任意两个相等的数据，排序前后的相对位置不发生改变
-  没有一种排序是任何情况下都表现最好的

#### 9.1.2 冒泡排序

```C
void Bubble_Sort(ElementType A[], int N){
    for (P = N - 1; P >= 0; P--){
        flag = 0;
        for (i = 0; i < P; i++){
            if (A[i] > A[i+1]){
                Swap(A[i], A[i+1]);
                flag = 1;
            }
        }
        if (flag == 0) break;
    }
}
```

> 每次排指针前后的元素，指针每次遍历后会将遍历数组部分的最大值排到最后，故下次只需要排去掉最后一个的

> 如果中途某次遍历已经得到排序好的数组，那么可通过一个 flag 直接退出

> 其真正价值在于链表的排序

> 大于时候才交换保证了**稳定性**

#### 9.1.3 插入排序

```C
void Insertion_Sort(ElementType A[], int N){
    for (P = 1; i > 0; P++){
        Tmp = A[P];
        for (i = P; i > 0 && A[i-1] > Tmp; i--){
            A[i] = A[i-1];
        }
        A[i] = Tmp;
    }
}
```

> 类似于排扑克牌，将该牌与左面的所有牌比较

> 猜想：与冒泡的区别大概就是一个从 0 到 N 一个从 N 到 0，但是插入排序很容易利用当前所有牌已经排好序了的性质进行分治插入呀

#### 9.1.4 时间复杂度下界

每次**交换相邻两个元素**只能消去一个**逆序对**，时间复杂度将达到$O(N^2)$，故，要争取一次交换较远的元素以消去更多逆序对

### 9.2 希尔排序

> 就是先定义一个增量序列（递减），根据增量序列进行插入排序，这就使得最终使用增量为 1 排序的时候整体上大体有序（递减的增量序列不会破坏之前排好的序列）

> 增量序列要互质才能体现其效果

### 9.3 堆排序

#### 9.3.1 选择排序

遍历未排序部分寻找最小元，之后将最小元换到有序部分的最后位置，但是如果真的这样遍历，那将会达到$O(N^2)$，无所谓最好最坏情况

#### 9.3.2 堆排序

我们可以建立一个最小堆寻找最小元，但是那样额外需要一个数组，我们可以把所有的操作放在一个数组里

比如说，建立一个最大堆，那么 root 一定最大，将它和最后元素交换，之后将除了最后一个元素再调整为最大堆，如此反复。虽然时间复杂度比较低，但是实际效果一般

### 9.4 归并排序

#### 9.4.1 有序子列的归并

利用三个指针即可

#### 9.4.2 递归算法

先利用该算法解决两部分，然后 Merge，另外可以全程使用一个临时数组以减少反复开辟空间的开销

#### 9.4.3 非递归算法

不断增加步长并 Merge

### 9.5 快速排序

#### 9.5.1 算法概述

分而治之

-  从待排序列表中选一个主元
-  对小于主元的列表递归的进行快速排序
-  对大于主元的列表递归的进行快速排序

#### 9.5.2 选主元

主元如果是中间的值，才是最好的情况，但一旦选到了最小的值那可以说是非常糟糕了，所以，选主元很关键，不过要真么做呢？试试玄学用 rand？那也很耗时间，**通常，我们选取首中尾的中位数**：

```C
ElementType Median3(ElementType A[], int Left, int Right){
    int Center = (Left + Right) / 2;
    if (A[Left] > A[Center])
        Swap(&A[Left], &A[Center]);
    if (A[Left] > A[Right])
        Swap(&A[Left], &A[Right]);
    if (A[Center] > A[Right])
        Swap(&A[Center], &A[Right]);
    Swap(&A[Center], &A[Right-1]);
    // 只需考虑A[Left+1]...A[Right-2]
    return A[Right-1];
}
```

#### 9.5.3 子集划分

1. 设两个指针 i、j，分别指在左右两侧
2. 一侧指针该位置处的值是否“应该”在该位置（与主元比较，比主元小应该在左侧，否则在右侧），如果对则继续移动，否则另外一个指针开始校验
3. 当两个指针都指向不“应该”的值的时候，将两个指针所指的值交换，然后重复 2、3
4. 如果 i<j，退出
5. 然后将主元交换到 i 的位置，此时**主元已经放到了最终的正确的位置**，所以快速排序才能说是快速的排序方法

> 几点要注意的：

    1. 如果有元素等于pivot，那么最好是交换，这样保证了最终的指针指在了正确的位置
    2. 对小规模数据可以采用插入排序，因为用递归的话出栈入栈很废资源，也很慢

#### 9.5.4 算法实现

又到了喜闻乐见的，抄代码时间了

```C
void Quick_Sort(ElementType A[], int N){
    Quicksort(A, 0, N-1);
}

void Quicksort(ElementType A[], int Left, int Right){
    if (Cutoff <= Right - Left){
        Pivot = Median3(A, Left, Right);
        i = Left;
        j = Right - 1;
        for (; ; ) {
            while (A[++i] < Pivot) { }
            while (A[--j] > Pivot) { }
            if (i < j)
                Swap(&A[i], &A[j]);
            else break;
        }
        Swap(&A[i], &A[Right - 1]);
        Quicksort(A, Left, i-1);
        Quicksort(A, i+1, Right);
    }
    else
        Insertion_Sort(A+Left, Right-Left+1);
}
```

### 9.6 表排序

#### 9.6.1 算法概述

就是用来排序比较复杂的结构，比如结构体，将整个数据进行改动比较复杂，所以可以使用一个 table 存储其指针，然后根据这个指针索引真正的数据，进行排序，并对 table 的内容进行排序，不需要移动原来的数据

#### 9.6.2 物理排序

-  当我们需要把复杂的数据结构排列到准确的位置的时候，我们可以在使用表排序之后再对数据进行排序
-  我们可以发现，表排序之后，表和对应下标形成若干个独立的环，那么我们可以利用这个性质，对每个环进行物理排序

### 9.7 基数排序

#### 9.7.1 桶排序

-  就是创建一个所有取值的数组，下标就是要比较的 key，扫描输入的所有元素，把元素存入以 key 为下标的位置，不过存的是链表哦，因为该位置可能还存别的元素，等把所有元素读入后，按数组逐个扫描，如果有存指针则把该链表都读出来
-  如果所有可能的取值太多，那么就尴尬了

#### 9.7.2 多关键字的排序

继续前面的问题，我们如何如果可能的取值太多，难道我们要做那么多的“桶”吗，那会有很多的空桶的哦
如果我们排数字的话（假设 0-999），很明显最重要的是百位，其次看十位，最后看个位，我们可以将 10 作为基数，百位看做主关键字，十位个位为次关键字

-  LSD 次位优先，为优先级最低的关键字建立一组桶，并按读入顺序依次放入桶内，然后建立次低优先级的一组桶，并从前一组桶中顺序读入数据，以此类推，直到主关键字
-  MSD 主位优先，与上述过程相反

### 9.8 排序算法的比较

| 排序算法     | 平均时间复杂度 | 最坏情况下时间复杂度 | 额外空间复杂度 | 稳定性 |
| ------------ | -------------- | -------------------- | -------------- | ------ |
| 简单选择排序 | $O(N^2)$       | $O(N^2)$             | $O(1)$         | 不稳定 |
| 冒泡排序     | $O(N^2)$       | $O(N^2)$             | $O(1)$         | 稳定   |
| 直接插入排序 | $O(N^2)$       | $O(N^2)$             | $O(1)$         | 稳定   |
| 希尔排序     | $O(N^d)$       | $O(N^2)$             | $O(1)$         | 不稳定 |
| 堆排序       | $NlogN$        | $NlogN$              | $O(1)$         | 不稳定 |
| 快速排序     | $NlogN$        | $O(N^2)$             | $NlogN$        | 不稳定 |
| 归并排序     | $NlogN$        | $NlogN$              | $O(N)$         | 稳定   |
| 基数排序     | $O(P(N+B))$    | $O(P(N+B))$          | $O(N+B)$       | 稳定   |

## 10 散列查找（Hashing）

### 10.1 散列表

1. 计算位置
2. 解决冲突
   > 时间复杂度几乎是常量 O(1)

-  存：
   -  计算 h(key)
   -  如果 h(key)空，则插入
   -  如果 h(key)非空，则按冲突解决方案计算位置
   -  返回 step2
-  取：
   -  计算 h(key)
   -  如果 h(key)空，则返回不存在
   -  如果 h(key)存储的是 key，则返回该位置
   -  否则，按冲突解决方案计算新的位置
   -  返回 step2

### 10.2 散列函数的构造方法

#### 10.2.1 好的散列函数所需具备的因素

1. **计算简单**，以便提高转换速度
2. 关键词对应的**地址空间分布均匀**，以尽量减少冲突

#### 10.2.2 数字关键词的散列函数构造

1. 直接定址法
   取关键词的某个线性函数值为散列地址

$$
h(key) = a \times key + b
$$

2. 除留余数法

$$
h(key) = key mod p
$$

3. 数字分析法
   分析数字关键字在各位上的变化情况，取比较随机的位作为散列地址

-  Example——手机号：
   -  取 11 位手机号码的后四位作为地址
   $$
   h(key) = atoi(key+7)
   $$
-  Example——身份证号码：
   -  我们可以发现有几位变化比较随机，比如第 6、10、14、16、17、18 位，故：
      ![Data_Structures09](../Images/Data_Structures09.png)

4. 折叠法
   把关键词分割成位数相同的几个部分，然后叠加

-  Example——56793542
   -  拆分为 542、793、056
   -  相加得 1391，取后三位
   -  即$h(56793542)=391$

5. 平方取中法

-  Example——56793542
   -  $56793542^2=3225506412905764$
   -  取 322550**641**2905764 中的中间三位**641**
   -  取中间是因为是要**受更多的数字影响**，比如最后一位，就只受原数字中的最后一位影响，折叠法也是这个原理

#### 10.2.3 字符关键词的散列函数构造

1. ASCII 码加和法

$$
h(key) = (\sum key[i])\ mod\ TableSize
$$

> 冲突严重

2. 前 3 个字符移位法

$$
h(key) = (key[0]\times27^2+key[1]\times27+key[2])\ mod\ TableSize
$$

3. 移位法
   涉及关键词所有 n 个字符，并且分布得很好

$$
h(key)=(\sum_{i=0}^{n-1}key[n-i-1]\times32^i)\ mod\ TableSize
$$

就相当于将字符串看做 32 进制“数”

-  可利用秦九韶算法减少乘法次数以加速运算
-  另外可使用移位运算加速乘 32 的运算（这也是取 322 为底的原因）

```C
Index Hash(const char *Key, int TableSize){
    unsigned int h = 0; /* 散列函数值，初始化为0 */
    while (*Key != '\0') /* 位移映射 */
        h = (h << 5) + *Key++;
    return h % TableSize;
}
```

### 10.3 处理冲突的方法

#### 10.3.1 开放地址法（Open Addressing）

-  若发生了第 i 次冲突，试探的下一个地址将增加$d_i$，基本公式是：$h_i(key) = (h(key)+d_i)\ mod\ TableSize\ (1\leq i \leq TableSize)$
-  $d_i$决定了不同的解决方案

| 线性探测 | 平方探测      | 双散列               |
| -------- | ------------- | -------------------- |
| $d_i=i$  | $d_i=\pm i^2$ | $d_i=i\ast h_2(key)$ |

1. 线性探测法（Linear Probing）

   -  以增量序列$1,2.\cdots,(TableSize-1)$循环试探下一个存储地址
      > 会出现**聚集**现象

2. 平方探测法（Quadratic Probing）

   -  以增量序列$1^2,-1^2,2^2,-2^2,\cdots,q^2,-q^2\ (q\leq TableSize/2)$循环试探下一个存储地址

      > 可能会出现无法探测全部散列表的现象，不过，当散列表长度 TableSize 是某个**4k+3 形式的素数**时，平方探测法就可以**探查到整个散列表空间**

   -  懒惰删除：删除不能真的删除，如果真的删除会使之后的查找产生误判，之后的元素就找不到了，故可以使用一个标记以表示该元素已被删除

3. 双散列探测法（Double Hashing）
   -  $d_i$为$i*h_2(key)$，$h_2(key)$是另一个散列函数，探测序列长：$h_2(key),2h_2(key),3h_2(key),\cdots$
   -  对任意的 key，$h_2(key)\neq0$
   -  探测序列还用改保证所有的散列存储单元都应该能够被探测到。选择以下形式有良好的效果： \* $h_2(key) = p- (key\ mod\ p)$
      其中$p<TableSize$,p、TableSize 都是素数
4. 再散列（Rehashing）

   -  当散列表元素太多（即装填因子$\alpha$太大）时，查找效率会下降

      > 实用最大装填因子一般取$0.5\leq\alpha\leq0.85$

   -  当装填因子过大时，解决的方法是加倍扩大散列表（全部重新计算放置到新表），这个过程叫做再散列

#### 10.3.2 分立链接法（Separate Chaining）

把一个位置上冲突的所有关键词存储在同一个单链表里

### 10.4 散列表的性能分析

#### 10.4.1 平均查找长度（ASL）

-  成功平均查找长度（ASLs）：对表内数据枚举并取平均
-  不成功平均查找长度（ASLu）：认为要查找元素哈希值均匀分布在整个 Table 上，那么计算每个哈希值的查找长度（也就是遇到空的时候）计算取平均即可

#### 10.4.2 影响产生冲突多少的因素

-  散列函数是否均匀
-  处理冲突的方法
-  散列表的装填因子$\alpha$

1. 线性探测法的查找性能
2. 平方探测法和双散列探测法的查找性能
3. 分离链接法的查找性能

#### 10.4.3 散列表的优缺点

-  选择合适的 h(key)，散列法的查找效率期望是常数 O(1)，它几乎与关键字的空间的大小 n 无关！也适合于关键字直接比较计算量大的问题
-  它是以较小的$\alpha$为前提，因此，散列方法是一个以**空间换时间**
-  散列方法的存储对关键字是随机的，不便于顺序查找关键字，也不适合于**范围查找**，或\**最大值最小值*查找

#### 10.4.4 开放地址法和分立链接法的比较

1. 开放地址法
   -  散列表是一个数组，存储效率高，随机查找
   -  散列表有“聚集”现象
2. 分离链接法
   -  散列表是顺序存储和链式存储的结合，链表部分的存储效率和查找效率都比较低
   -  关键字删除不需要“懒惰删除”法，从而没有存储“垃圾”
   -  太小的$\alpha$可能导致空间浪费，大的$\alpha$又将付出更多的时间代价；不均匀的链表长度导致时间效率的严重下降

# Extends

1. [switch-case 实现分段函数](https://blog.csdn.net/xiaochenxiaoren/article/details/53140436)

# Amendant Record

1. 180911 [Chapter_4_Queue](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_4_Queue) Finished
2. 180913 [Week_2](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Week_2) Finished
3. 180915 [Chapter_6_Tree(#6.1-#6.9)](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_6_Tree) Finished
4. 180916 [Week_3](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Week_3) Finished
5. 180918 Chapter_5_String Finished
6. 180922 [Chapter_6_Tree(#6.10-#6.11)](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_6_Tree) Finished
7. 180923 [Week_4](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Week_4) Finished
8. 180929 [PyDS_Linked_List](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_2_List) [PyDS_Heap](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_7_Heap) [Chapter_6_Tree](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_6_Tree) [Chapter_7_Heap](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_7_Heap) Finished
9. 181004 [Week_5](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Week_5) Finished
10.   181005 [Chapter_8_Graph(#8.1-#8.2)](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_8_Graph) Finished
11.   181006 [Week_6](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Week_6) Finished
12.   181010 Chapter_8_Graph(#8.3) Finished
13.   181014 [Week_7](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Week_7) Finished
14.   181018 Chapter_8_Graph(#8.4-#8.6) Finished
15.   181025 Chapter_9_Sort(#9.1-#9.4) Finished
16.   181102 Chapter_9_Sort(#9.5-#9.8) Finished
17.   181110 Chapter_10_Hash(#10) Finished

# Reference

1. [数据结构 - 浙江大学 - 中国大学 MOOC](https://www.icourse163.org/course/ZJU-93001)
2. 《数据结构 (C 语言版)》 严蔚敏 吴伟民 编著
3. [PTA | 程序设计类实验辅助教学平台](https://pintia.cn/)
4. [Python 数据结构 - Python123](https://python123.io/index/topics/data_structure)

<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/katex@0.10.0/dist/katex.min.css">
