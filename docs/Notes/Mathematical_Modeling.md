<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/KaTeX/0.9.0/katex.min.css">

# Mathematical Modeling <Badge text="alpha" type="warn"/> <Badge text="1.1.2"/>

## 1 线性规划

### 1.1 线性规划问题

#### 1.1.1 线性规划的标准型

1. 要求解的目标函数（max or min）
2. 约束等式或不等式

#### 1.1.2 线性规划的 Matlab 标准型及其求解

$min\ f^Tx$
$s.t.$

1. $A\cdot x\leq b$
2. $Aeq\cdot x=beq$
3. $lb\leq x\leq ub$

$f$ $x$ $b$ beq lb ub 为列向量，A Aeq 为矩阵

---

Matlab 下的求解命令为：

```matlab
[x, fval] = linprog(f, A, b)
[x, fval] = linprog(f, A, b, Aeq, beq)
[x, fval] = linprog(f, A, b, Aeq, beq, lb, ub)
```

-  x 返回决策向量的取值；
-  fval 返回目标函数的最优值；
-  f 为价值向量；
-  A 和 b 对应线性不等式约束；
-  Aeq 和 beq 对应线性等式约束；
-  lb 和 ub 分别对应决策向量的下界向量和上界向量

---

Example：

$$
\begin{aligned}
max\ z & =2x_1+3x_2-5x_3 \\
x_1+x_2+x_3 & =7 \\
2x_1-5x_2+x_3 & \geq10 \\
x_1+3x_2+x_3 & \leq12 \\
x_1,x_2,x_3 & \geq0 \\
\end{aligned}
$$

---Matlab 标准型--->
$min\ w=-2x_1-3x_2+5x_3$
然后……不会用有道云画矩阵……先空着吧

---Matlab 实现--->

```matlab
f = [-2; -3; 5];
a = [-2, 5, -1; 1, 3, 1];
b = [-10; 12];
aeq = [1, 1, 1];
beq = 7;
[x, y] = linprog(f, a, b, aeq, beq, zeros(3, 1));
x, y = -y
```

# Amendant Record

18xxxx #0 Finished

# Reference

1. 《数学建模算法与应用（第二版）》 司守奎 孙兆亮
