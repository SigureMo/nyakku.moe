---
title: Linear Algebra
categories:
   - 经纶·注
tags:
   - Basic Subject
   - Math
   - kaoyan
---

# Linear Algebra <Badge text="alpha" type="warn"/> <Badge text="0.0.0"/>

## 1 行列式

### 1.1 主线梳理

#### 1.1.1 行列式的性质

-  下三角行列式、对角行列式值为对角元素的乘积
-  $|A^T| = |A|$
-  对换行列式的两行（列），行列式变号
-  如果有两行（列）完全相同，则此行列式等于零
-  行列式的某一行（列）中所有的元素都乘同一数 $k$ ，等于用数 $k$ 乘此行列式
-  行列式中如果有两行（列）元素成比例，则此行列式等于零
-  若行列式的某一行（列）的元素都是两数之和，那么可以拆成两个行列式，他们的其余行（列）均与原式相同，该行（列）分别是两数之一
-  把行列式的某一行（列）的各元素乘同一数然后加到另一行（列）对应的元素上去，行列式不变

#### 1.1.2 按行（列）展开

-  行列式等于它的任一行（列）的各元素与其对应的代数余子式乘积之和
   > 注意，代数余子式 $A_{ij}$ 是将负号加上过的
   > 我们计算代数余子式之和的时候，是不关心该行（列）的，所以可以放心的将该行（列）换为代数余子式的系数，那么新的行列式就是代数余子式之和
-  范德蒙德行列式（暂略）

## 2 矩阵及其运算

### 2.1 主线梳理

#### 2.1.1 矩阵的运算

-  矩阵的加法
   -  $\mathbf{A} + \mathbf{B} = \mathbf{B} + \mathbf{A}$
   -  $(\mathbf{A} + \mathbf{B}) + \mathbf{C} = \mathbf{A} + (\mathbf{B} + \mathbf{C})$
-  数与矩阵相乘 $\lambda \mathbf{A} = \mathbf{A} \lambda$
-  矩阵与矩阵相乘
   -  若 $\mathbf{A}\mathbf{B} = \mathbf{B}\mathbf{A}$ 则称 $\mathbf{A}$ 与 $\mathbf{B}$ 是可交换的
   -  若 $\mathbf{A}\mathbf{B} = \mathbf{O}$ ，并不等于得出 $\mathbf{A} = \mathbf{O}$ 或 $\mathbf{B} = \mathbf{O}$ 的结论
   -  $(\mathbf{A}\mathbf{B})\mathbf{C} = \mathbf{A}(\mathbf{B}\mathbf{C})$
   -  $\lambda (\mathbf{A}\mathbf{B}) = (\lambda \mathbf{A})\mathbf{B} = \mathbf{A}(\lambda\mathbf{B})$
   -  $\mathbf{A}(\mathbf{B}+\mathbf{C}) = \mathbf{A}\mathbf{B} + \mathbf{A}\mathbf{C}$
   -  $(\mathbf{B} + \mathbf{C})\mathbf{A} = \mathbf{B}\mathbf{A} + \mathbf{C}\mathbf{A}$
-  矩阵的转置
   -  $(\mathbf{A}^T)^T = \mathbf{A}$
   -  $(\mathbf{A} + \mathbf{B})^T = \mathbf{A}^T + \mathbf{B}^T$
   -  $(\lambda \mathbf{A})^T = \lambda \mathbf{A}^T$
   -  $(\mathbf{A}\mathbf{B})^T = \mathbf{B}^T\mathbf{A}^T$
   -  对称阵 $\mathbf{A}^T = \mathbf{A}$
-  方阵的行列式
   -  $|\mathbf{A}^T| = |\mathbf{A}|$
   -  $|\lambda \mathbf{A}| = \lambda^n |\mathbf{A}|$
   -  $|\mathbf{A}\mathbf{B}| = |\mathbf{A}||\mathbf{B}|$
      > 伴随阵 $\mathbf{A}^*$，是代数余子式所构成的矩阵，注意，并不是在对应位置上，需要有一个转置操作
   -  $\mathbf{A}\mathbf{A}^* = \mathbf{A}^*\mathbf{A} = |\mathbf{A}|\mathbf{E}$

#### 2.1.2 逆矩阵

-  如果 $\mathbf{A}\mathbf{B} = \mathbf{B}\mathbf{A} = \mathbf{E}$ ，则称矩阵 $\mathbf{A}$ 可逆
-  $|\mathbf{A}| \not= 0$ $\iff$ 矩阵 $\mathbf{A}$ 可逆，且 $\mathbf{A}^{-1} = \frac{1}{|\mathbf{A}|}\mathbf{A}^*$
-  若 $|\mathbf{A}| = 0$， 我们称其为奇异矩阵，否则为非奇异矩阵，很明显，非奇异矩阵可逆

#### 2.1.3 克拉默法则

用于求解线性方程组，$x_1 = \frac{|\mathbf{A_1}|}{|\mathbf{A}|}$ ，$x_2 = \frac{|\mathbf{A_2}|}{|\mathbf{A}|}$ ，$\cdots$ ，$x_n = \frac{|\mathbf{A_n}|}{|\mathbf{A}|}$

其中 $\mathbf{A}_j$ 是把系数矩阵 $\mathbf{A}$ 中第 $j$ 列的元素用方程组右端的常数项代替后所得到的 $n$ 阶矩阵

#### 2.1.4 矩阵分块法

-  分块矩阵的运算规则与普通矩阵的运算规则相类似
   -  加法
   -  乘法
-  分块对角矩阵
   -  $|\mathbf{A}| = |\mathbf{A}_1| |\mathbf{A}_2| \cdots |\mathbf{A}_s|$
-  矩阵 $\mathbf{A} = \mathbf{O}$ 的充要条件是 $\mathbf{A}^T \mathbf{A} = \mathbf{O}$

### 2.2 一些小技巧

-  使用已有表达式求解方阵的逆矩阵，可以将表达式化为 $\mathbf{A}\mathbf{X} = k\mathbf{E}$ 的形式，此时 $\frac{\mathbf{X}}{k}$ 即为其逆矩阵
-  因为 $\mathbf{E}\mathbf{A} = \mathbf{A}\mathbf{E}$ ，所以含 $\mathbf{E}$ 的多项式很多是可交换的，依此可对式子进行因式分解等操作
-  $|\mathbf{A}^*| = |\mathbf{A}|^{n-1}$

## 3 矩阵的初等变换与线性方程组

### 3.1 主线梳理

#### 3.1.1 矩阵的初等变换

-  初等行变换
   -  对换两行
   -  以数 $k$ 乘某一行中的所有元
   -  将某一行的所有元的 $k$ 被加到另一行的对应元上去
-  行最简形
   -  非零行的首非零元为 1
   -  首非零元所在的列的其他元均为 0
-  初等行变换可以等效为左乘一个可逆矩阵，类似地，初等列变换可以等效为右乘一个可逆矩阵

#### 3.1.2 矩阵的秩

-  最高阶非零子式的阶数即为矩阵的秩
-  $0 \leq R(\mathbf{A}_{m \times n}) \leq min \{m, n\}$
-  $R(\mathbf{A}^T) = R(\mathbf{A})$
-  若 $\mathbf{A}\text{\textasciitilde}\mathbf{B}$，则 $R(\mathbf{A}) = R(\mathbf{B})$
-  $max \{ R(\mathbf{A}), R(\mathbf{B}) \} \leq R(\mathbf{A}, \mathbf{B}) \leq R(\mathbf{A}) + R(\mathbf{B})$
-  $R(\mathbf{A} + \mathbf{B}) \leq R(\mathbf{A}) + R(\mathbf{B})$
-  $R(\mathbf{A} \mathbf{B}) \leq min \{R(\mathbf{A}), R(\mathbf{B}))\}$
-  若 $\mathbf{A}_{m \times n} \mathbf{B}_{n \times l} = \mathbf{O}$ ，则 $R(\mathbf{A}) + R(\mathbf{B}) \leq n$

# Change Log

1. 190527 #1 Finished

# Reference

1. 《线性代数》 同济第六版
