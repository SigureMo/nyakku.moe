# H 型钢正火冷却过程非稳态温度场的有限差分法计算

## 模型的建立

H 型钢是一种在工业界常用的钢种，它的回火冷却过程是一个涉及相变、热传导、对流换热的三维非稳态传热过程。但当 H 型钢长度远大于其截面尺寸时，可忽略长度方向热传导，这时可用二维模型来描述 H 型钢正火冷却过程的传热过程

![image01](image01.jpg)

在这个模型中采用以下几种假定：

-  工件为无限长 H 型钢
-  材料的热物性参数不随温度变化
-  不考虑相变潜热
-  考虑工件与正火介质的对流换热
-  材料各向同性

## 热传导方程

根据工件的形状，采用直角坐标系，这样材料内部的热传导方程为

$$
\frac{\partial T}{\partial t} = \alpha (\frac{\partial^2 T}{\partial x^2} + \frac{\partial^2 T}{\partial y^2})
$$

式中

-  $\rho$ - 密度，$kg/m^3$
-  $C_p$ - 比热， $J/(kg \cdot ^{\circ}C)$
-  $\lambda$ - 热导率，$W/(m \cdot ^{\circ}C)$
-  $T$ - 温度， $^{\circ}C$
-  $t$ - 时间， $s$

## 边界条件

边界条件为：

$$
-\lambda \frac{\partial T}{\partial n} = h(T - T_n)
$$

式中

-  $T$ - 工件表面温度，$^{\circ}C$
-  $T_a$ - 正火介质温度， $^{\circ}C$
-  $n$ - 其它表面的外法线方向
-  $h$ - 材料表面欲淬火介质的对流换热系数， $W / (m^2 \cdot ^{\circ}C)$

## 初始条件

初始时刻工件整体温度分布均匀， $T|_{t=0} = T_0$ ， $T_0$ 为一常数，取加热炉温， 920 $^{\circ}C$

## 有限差分方程

如图所示，由于对称性，仅对右上角部分进行求解即可

![image02](image02.jpg)

$x$ 方向节点数为 $N_2$ ， $y$ 方向节点数为 $N_4$ ，$x$ 方向的步长为 $\Delta x$ ，$y$ 方向的步长为 $\Delta y$ ，时间步长为 $\Delta t$

内部节点有限差分方程：

$$
\frac{T_{i,j}^{n+1} - T_{i,j}^n}{\Delta t} = \alpha [\frac{T_{i+1, j}^n - 2T_{i,j}^n + T_{i-1, j}^n}{(\Delta x)^2} + \frac{T_{i, j+1}^n - 2T_{i,j}^n + T_{i, j-1}^n}{(\Delta y)^2}]
$$

令 $F_x = \frac{\alpha \Delta t}{\Delta x^2}$， $F_y = \frac{\alpha \Delta t}{\Delta y^2}$ ， $F_1 = 1 - 2F_x - 2F_y$

则

-  内部节点有限差分方程变为

$$
T_{i,j}^{n+1} = F_1 T_{i,j}^n + F_x (T_{i+1,j}^n + T_{i-1,j}^n) + F_y (T_{i,j+1}^n + T_{i,j-1}^n)
$$

-  六条线边界节点的有限差分方程：

（按顺序依次为位置 2、6、11、8、9、5）

$$
\begin{aligned}
T_{i, N_4}^{n+1} =& F_1 T_{i, N_4}^n + F_x (T_{i-1,N_4}^n + T_{i+1,N_4}^n) + 2F_y T_{i,N_4-1}^n + \frac{2 h \Delta t}{\rho C_p \Delta y} (T_a - T_{i,N_4}^n) \\
T_{i, N_3 +1}^{n+1} =& F_1 T_{i, N_3 +1}^n + F_x (T_{i-1,N_3 +1}^n + T_{i+1,N_4}^n) + 2F_y T_{i,N_3 +2}^n + \frac{2 h \Delta t}{\rho C_p \Delta y} (T_a - T_{i,N_3 +1}^n) \\
T_{i, 1}^{n+1} =& F_1 T_{i, 1}^n + F_x (T_{i-1,1}^n + T_{i+1,1}^n) + 2F_y T_{i,2}^n \\
T_{1,j}^{n+1} =& F_1 T_{1,j}^n + 2 F_x T_{2,j}^n + F_y (T_{1,j-1}^n + T_{1,j+1}^n) \\
T_{N_1,j}^{n+1} =& F_1 T_{N_1,j}^n + 2 F_x T_{N_1 -1,j}^n + F_y (T_{N_1,j-1}^n + T_{N_1,j+1}^n) + \frac{2 h \Delta t}{\rho C_p \Delta x} (T_a - T_{N_1,j}^n) \\
T_{N_2,j}^{n+1} =& F_1 T_{N_2,j}^n + 2 F_x T_{N_2 -1,j}^n + F_y (T_{N_2,j-1}^n + T_{N_2,j+1}^n) + \frac{2 h \Delta t}{\rho C_p \Delta x} (T_a - T_{N_2,j}^n) \\
\end{aligned}
$$

-  五个角边界节点的有限差分方程：

（按顺序依次为位置 1、10、12、3、7）

$$
\begin{aligned}
T_{1,N_4}^{n+1} =& F_1 T_{1, N_4}^n + 2 F_x T_{2,N_4}^n + 2 F_y T_{1,N4-1}^n + \frac{2 h \Delta t}{\rho C_p \Delta y} (T_a - T_{i,N_4}^n) \\
T_{1,1}^{n+1} =& F_1 T_{1, 1}^n + 2 F_x T_{2,1}^n + 2 F_y T_{1,2}^n \\
T_{N_1,1}^{n+1} =& F_1 T_{N_1,1}^n + 2 F_x T_{N_1 -1,1}^n + 2 F_y T_{N_1,2}^n + \frac{2 h \Delta t}{\rho C_p \Delta x} (T_a - T_{N_1,1}^n) \\
T_{N_2,N_4}^{n+1} =& F_1 T_{N_2,N_4}^n + 2 F_x T_{N_2 -1,N_4}^n + 2 F_y T_{N_2,N_4 -1}^n + \frac{2 h \Delta t}{\rho C_p} (\frac{1}{\Delta x} + \frac{1}{\Delta y}) (T_a - T_{N_2,N_4}^n) \\
T_{N_2,N_3 +1}^{n+1} =& F_1 T_{N_2,N_3 +1}^n + 2 F_x T_{N_2 -1,N_3 +1}^n + 2 F_y T_{N_2,N_3 +2}^n + \frac{2 h \Delta t}{\rho C_p} (\frac{1}{\Delta x} + \frac{1}{\Delta y}) (T_a - T_{N_2,N_3 +1}^n) \\
\end{aligned}
$$
