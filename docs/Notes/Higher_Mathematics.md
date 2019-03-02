# Higher Mathematics <Badge text="alpha" type="warn"/> <Badge text="0.0.0"/>

## 1 Basics

### 1.1 定理

#### 1.1.1 奇偶性

-  奇函数 $y=f(x)$ 的图形关于坐标原点对称，当 $f(x)$ 在 $x=0$ 处有定义时，必有 $f'(0)=0$
-  偶函数 $f=f(x)$ 的图形关于 $y$ 轴对称，且当 $f'(0)$ 存在时，必有 $f'(0)=0$

#### 1.1.2 数列基础

-  等差数列前 $n$ 项和 $S_n = \frac{n}{2}(a_1 + a_n)$
-  等比数列前 $n$ 项和 $S_n = \frac{a_1(1-r^n)}{1-r} (r\not=1)$
-  一些数列前 $n$ 项和
   -  $\sum\limits_{k=1}^n k = 1+2+3+\cdots+n = \frac{n(n+1)}{2}$
   -  $\sum\limits_{k=1}^n (2k-1) = 1+3+5+\cdots+(2n-1) = \frac{n(n+1)}{2}$
   -  $\sum\limits_{k=1}^n k^2 = 1^2+2^2+3^2+\cdots+n^2 = \frac{n(n+1)(2n+1)}{6}$
   -  $\sum\limits_{k=1}^n k^3 = 1^3+2^3+3^3+\cdots+n^3 = \left[\frac{n(n+1)}{2}\right]^2 = (\sum\limits_{k=1}^n k)^2$

#### 1.1.3 三角函数

-  万能公式
   若 $u=\tan \frac{x}{2} (-\pi < x < \pi)$ ，则 $\sin x = \frac{2u}{1+u^2}$ ， $\cos x = \frac{1-u^2}{1+u^2}$

#### 1.1.4 韦达定理

-  $x_1 + x_2 = -\frac{b}{a}$
-  $x_1 x_2 = \frac{c}{a}$

#### 1.1.5 二项式定理

$(a+b)^n=\sum\limits_{k=0}^n C_n^k a^kb^{n-k}$

## 2 Limit and continuity

### 2.1 定理

#### 2.1.1 数列

-  若数列 $\{a_n\}$ 收敛，则其任何子列 $\{a_{n_k}\}$ 也收敛，且 $\lim\limits_{k\rightarrow\infty}a_{n_k} = \lim\limits_{n\rightarrow\infty}a_n$

> 对于一个数列 $\{a_n\}$ ，如果能找到一个发散的子列，则原数列一定发散；如果能找到两个收敛的子列 $\{a_{n_k}\}$ 和 $\{a_{n_k'}\}$ ，但它们收敛到不同极限，则原数列也一定发散

-  **单调** **有界** 数列必有极限

#### 2.1.2 无穷小

-  无穷小运算规则

   -  **有限个**无穷小的和是无穷小
   -  **有界函数**与无穷小的乘积是无穷小
   -  **有限个**无穷小的乘积是无穷小
   -  无穷小的运算
      -  $\omicron(x^m) \pm \omicron(x^n), l=min\{m,n\}$
      -  $\omicron(x^m) \cdot \omicron(x^n) = \omicron(x^{m+n}), x^m \cdot \omicron(x^n) = \omicron(x^{m+n})$
      -  $\omicron(x^m) = k \cdot \omicron(x^m), k\not=0$

-  常用的等价无穷小($x \to 0$)
   -  $\sin x \text{\textasciitilde} x$
   -  $\tan x \text{\textasciitilde} x$
   -  $\arcsin x \text{\textasciitilde} x$
   -  $\arctan x \text{\textasciitilde} x$
   -  $\ln(1 + x) \text{\textasciitilde} x$
   -  $e^x - 1 \text{\textasciitilde} x$
   -  $a^x - 1 \text{\textasciitilde} x\ln a$
   -  $1 - \cos x \text{\textasciitilde} \frac{1}{2} x^2$
   -  $(1+x)^\alpha - 1 \text{\textasciitilde} \alpha x$

#### 2.1.3 极限的计算

-  四则运算法则

   -  $\lim \limits_{x \to x_0} [f(x) \pm g(x)] = \lim \limits_{x \to x_0} f(x) \pm \lim \limits_{x \to x_0} g(x)$
   -  $\lim \limits_{x \to x_0} [f(x) \cdot g(x)] = \lim \limits_{x \to x_0} f(x) \cdot \lim \limits_{x \to x_0} g(x)$
   -  $\lim \limits_{x \to x_0} \frac{f(x)}{g(x)} = \frac{\lim \limits_{x \to x_0} f(x)}{\lim \limits_{x \to x_0} g(x)}, \lim \limits_{x \to x_0} g(x) \not= 0$

-  复合函数极限的运算
   $f(x) = g(h(x)) = g(t)$ ，那么 $\lim \limits_{x \to x_0} f(x) = \lim \limits_{t \to h(x_0)} g(t)$

-  重要极限

   -  $\lim \limits_{x \to 0} \frac{\sin x}{x} = 1$
   -  $\lim \limits_{x \to \infty} (1 + \frac{1}{x})^x = e$
      > 一个误区
      > 又把四则运算与复合函数这俩简单的法则加上了，至于原因嘛，当然是因为这里出问题了，什么时候可以直接求 $x \to 0$ 时的 $\cos x$ ，貌似很简单的问题，但是为什么 $\lim \limits_{x \to 0} (\frac{1}{\sin^2 x} + \frac{\cos^2 x}{x^2})$ 里的 $\cos x$ 不是 1？我们可以试着用四则运算拆拆试试，很明显，由于分母是 0 ，我们不能用四则运算直接得出
      >
      > 类似的，出在复合函数上的一个问题，我们知道第二个重要极限，我们可是为什么这样可以呢？我们看一下：$\lim \limits_{x \to \infty} (1 + \frac{1}{x})^x = \lim \limits_{x \to \infty} e^{x \ln (1 + \frac{1}{x})} = e^{\lim \limits_{x \to \infty} x \ln (1 + \frac{1}{x})}$ ，咦，这步为啥，极限四则运算没有它呀，我们还有复合函数运算法则呀，也就是将上一步看成 $e^t$，很容易就得到上面的式子啦

-  函数极限存在准则——夹逼准则
   如果函数 $f(x), g(x)$ 及 $h(x)$ 满足下列条件：

   -  $g(x) \leq f(x) \leq h(x)$
   -  $\lim g(x) = A， \lim h(x) = A$

   则 $\lim f(x)$ 存在，且 $\lim f(x) = A$

-  洛必达法则

-  海涅定理
   设 $f(x)$ 在 $\mathring{U}(x, \delta)$ 内有定义，则 $\lim\limits_{x \to x_0} f(x) = A$ 存在 $\iff$ 对任何以 $x_0$ 为极限的数列 $\{x_n\}(x_n \not= x_0)$ ，极限 $\lim\limits_{n \to \infty} f(x_n) = A$ 存在

   > 例：
   > 试证明 $\lim\limits_{x \to 0} \frac{1}{x} \sin \frac{1}{x}$ 不存在
   >
   > -  若取 $x_n = \frac{1}{n\pi} \to 0, n \to \infty$ ，则有 $f(x_n) = 0$
   > -  若取 $x'_n = \frac{1}{(2n+\frac{1}{2})\pi \to 0, n \to \infty}$ ，则有 $f(x'_n) = (2n + \frac{1}{2})\pi \to \infty$
   >
   > 根据海涅定理可知极限不存在

#### 2.1.4 函数的连续与间断

-  连续的定义

   -  定义方法一：设 $f(x)$ 在点 $x_0$ 的某邻域内有定义，若 $\lim\limits_{\Delta x \to 0} \Delta y = \lim\limits_{\Delta x \to 0}[f(x_0 + \Delta x) - f(x_0)] = 0$ ，则称函数在点 $x_0$ 连续，点 $x_0$ 称为 $f(x)$ 的连续点
   -  定义方法二：设函数 $f(x)$ 在点 $x_0$ 的某邻域内有定义，且有 ==$\lim\limits_{x \to x_0} f(x) = f(x_0)$== ，则称函数 $f(x)$ 在点 $x_0$ 处连续

-  间断点的定义
   -  第一类间断点
      -  可去间断点
      -  跳跃间断点
   -  第二类间断点
      -  无穷间断点
      -  振荡间断点

# Amendant Record

1. 190227 #1 Finished

# Reference

1. 《张宇高等数学 18 讲》
