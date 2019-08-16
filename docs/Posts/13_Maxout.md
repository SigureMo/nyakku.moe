---
title: Maxout 的简单理解与实现
date: 2019-07-01
categories:
   - 倏尔·论
tags:
   - DL
---

::: tip
Maxout 是 Goodfellow 在 2013 年提出的一个新的激活函数，相比于其它的激活函数，Maxout 本身是需要参数的，参数可以通过网络的反向传播得到学习，相应地，它比其它激活函数有着更好的性能，理论上可以拟合任意凸函数，进而使得网络取得更好的性能
:::

<!-- more -->

## 1 什么是 Maxout

Maxout 可以说是一个激活函数，但与其他激活函数所不同的是，它本身是拥有参数的，正因为此，它可以拟合任意的凸函数，那么它是如何实现的呢？

首先我们弄清一个问题，卷积层在通道阶上和全连接层并没有任何区别，只是额外在图像的两个阶增加了卷积核的稀疏连接，但这往往是很小的（$3 \times 3$ ，$5 \times 5$ 这样），所以说我们只考虑卷积网络的最后一个阶的话，它与全连接并无区别，这里就直接使用全连接网络作为例子，当然，卷积网络也是适用的

我们网络前层进行 $WX + b$ 的线性变换后，是需要增加激活函数进行非线性变换的，但是具体怎么选择激活函数呢？我们可不可以让网络自己学习这个呢？

![DL00](../Images/DL00.png)

上图便是最基本的 $Maxout$ 连接示意图，前面与普通的全连接并无区别，之后每两个单元“连接”到一个单元上，当然，这里不是真的连接，因为该条线上并不涉及参数，那么如何从两个单元得到一个单元的值呢？其实只需要比较两个单元的值即可，大的值便可以通过~也便是 $Max\ Out$

![DL01](../Images/DL01.png)

结果便如上图所示，每两个单元中较大的值会被激活

![DL02](../Images/DL02.png)

我们知道每个单元都是前层特征的线性组合，那么比如上图中第一个单元学习到了 $y = 0$ ，而第二个单元学习到了 $y = x$ ，那么这两个单元学习到的激活函数便是 $ReLU$ 激活函数

更一般地，我们使每 $k$ （前面的例子 $k = 2$）个单元“连接”到一个单元上，那么 $Maxout$ 可以学习到更多段的分段函数作为激活函数，当 $k$ 足够大时，理论上可以拟合任何凸函数

## 2 如何实现 Maxout

首先令前层单元数为 $d$，后层单元数为 $m$，$Maxout$ 单元扩增倍数为 $k$ （即每 $k$ 个单元“连接”到一个单元）

那么我们要怎么实现这样的 $Maxout$ 激活呢？

### 2.1 构建网络层时直接使用新的结构

一种方式是对整个网络层进行重构，原来，即原本 $d \times m$ 个参数改为 $d \times m \times k$ 个参数，之后从中挑选出最大的即可，比如下面的代码

```Python
import tensorflow as tf


x = tf.random_normal([1,3])
m = 3
k = 2

d = x.get_shape().as_list()[-1]

W = tf.Variable(tf.random_normal(shape=[d, m, k]))
b = tf.Variable(tf.random_normal(shape = [m, k]))
dot_z = tf.tensordot(x, W, axes=1) + b
z = tf.reduce_max(dot_z, axis=2)

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    print(sess.run([x, dot_z, z]))
```

### 2.2 将 Maxout 作为一个激活函数进行使用

另一种方式是按照 $Maxout$ 为一个激活函数，搭建完线性变换部分（$d$ 个单元连接到 $k \times m$ 个单元）后，再进行 $Reshape$ 分为 $k$ 组，之后每组挑选出最大的即可，参考 `tf.contrib.layers.maxout` ，实现如下

```python
def maxout(inputs, num_units, axis=None):
    """ 将前层部分参数作为 maxout 的参数进行处理 """
    shape = inputs.get_shape().as_list()
    if axis is None:
        # Assume that channel is the last dimension
        axis = -1
    num_channels = shape[axis]
    if num_channels % num_units:
        raise ValueError('number of features({}) is not a multiple of num_units({})'
             .format(num_channels, num_units))
    shape[axis] = num_units
    shape += [num_channels // num_units]
    for i in range(len(shape)):
        if shape[i] is None:
            shape[i] = -1
    outputs = tf.reduce_max(tf.reshape(inputs, shape), -1, keepdims=False)
    return outputs

# X.shape = (..., d)
X = tf.layers.conv2d(inputs=X, filters=k * m, kernel_size, strides, padding)
# X.shape = (..., m*k)
X = maxout(inputs=X, num_units=m)
# X.shape = (..., m)
```

相比于前一种方式，这种方式操作起来更加方便，可以不对原有网络结构进行改变便可实现 $Maxout$ 激活，但是要注意的一点是，前面的线性变换输出单元数是 $m \times k$ 而不是 $m$ ，经过 $Maxout$ 激活后输出单元数才是 $m$

# Reference

1. [Tensorflow 文档 Maxout](https://tensorflow.google.cn/api_docs/python/tf/contrib/layers/maxout?hl=en)
2. [Paper: Maxout Networks](https://arxiv.org/abs/1302.4389)
3. [Maxout 激活函数原理及实现](https://www.jianshu.com/p/710fd5d6d640)
