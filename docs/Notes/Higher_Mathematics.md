# Higher Mathematics <Badge text="alpha" type="warn"/> <Badge text="0.0.0"/>

## 1 Basics

### 1.1 定理

- 奇偶性
   - 奇函数 $y=f(x)$ 的图形关于坐标原点对称，当 $f(x)$ 在 $x=0$ 处有定义时，必有 $f'(0)=0$
   - 偶函数 $f=f(x)$ 的图形关于 $y$ 轴对称，且当 $f'(0)$ 存在时，必有 $f'(0)=0$

- 数列基础
   - 等差数列前 $n$ 项和 $S_n = \frac{n}{2}(a_1 + a_n)$
   - 等比数列前 $n$ 项和 $S_n = \frac{a_1(1-r^n)}{1-r} (r\not=1)$
   - 一些数列前 $n$ 项和
      - $\sum\limits_{k=1}^n k = 1+2+3+\cdots+n = \frac{n(n+1)}{2}$
      - $\sum\limits_{k=1}^n (2k-1) = 1+3+5+\cdots+(2n-1) = \frac{n(n+1)}{2}$
      - $\sum\limits_{k=1}^n k^2 = 1^2+2^2+3^2+\cdots+n^2 = \frac{n(n+1)(2n+1)}{6}$
      - $\sum\limits_{k=1}^n k^3 = 1^3+2^3+3^3+\cdots+n^3 = \left[\frac{n(n+1)}{2}\right]^2 = (\sum\limits_{k=1}^n k)^2$

- 三角函数
   - 万能公式
      若 $u=\tan \frac{x}{2} (-\pi < x < \pi)$ ，则 $\sin x = \frac{2u}{1+u^2}$ ， $\cos x = \frac{1-u^2}{1+u^2}$

- 韦达定理
   - $x_1 + x_2 = -\frac{b}{a}$
   - $x_1 x_2 = \frac{c}{a}$

- 二项式定理
   $(a+b)^n=\sum\limits_{k=0}^n C_n^k a^kb^{n-k}$

## 2 Limit and continuity

### 2.1 定理

- 若数列 $\{a_n\}$ 收敛，则其任何子列 $\{a_{n_k}\}$ 也收敛，且 $\lim\limits_{k\rightarrow\infty}a_{n_k} = \lim\limits_{n\rightarrow\infty}a_n$

> 对于一个数列 $\{a_n\}$ ，如果能找到一个发散的子列，则原数列一定发散；如果能找到两个收敛的子列 $\{a_{n_k}\}$ 和 $\{a_{n_k'}\}$ ，但它们收敛到不同极限，则原数列也一定发散

- **单调** **有界** 数列必有极限

- 无穷小运算规则
   - **有限个**无穷小的和是无穷小
   - **有界函数**与无穷小的乘积是无穷小
   - **有限个**无穷小的乘积是无穷小

# Amendant Record

1. 190227 #1 Finished

# Reference

1. 《张宇高等数学 18讲》
