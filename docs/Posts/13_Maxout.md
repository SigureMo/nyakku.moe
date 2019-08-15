---
title: Maxout
date: 2019-07-01
categories:
   - Discovery
tags:
   - DL
---

Maxout 是 Goodfellow 在 2013 年提出的一个新的激活函数，相比于其它的激活函数，Maxout 本身是需要参数的，参数可以通过网络的反向传播得到学习，相应地，它比其它激活函数有着更好的性能，理论上可以拟合任意凸函数，使得网络取得更好的性能

<!-- more -->

## 1 什么是 Maxout

Maxout 可以说是一个激活函数，但与其他激活函数所不同的是，它本身是拥有参数的，正因为此，它可以拟合任意的凸函数，那么它是如何实现的呢？

首先我们弄清一个问题，卷积层在通道阶上和全连接层并没有任何区别，只是额外在图像的两个阶增加了卷积核的稀疏连接，但这往往是很小的（$3 \times 3$ ，$5 \times 5$ 这样），所以说我们只考虑卷积网络的最后一个阶的话，它与全连接并无区别，这里就直接使用全连接网络作为例子，当然，卷积网络也是适用的

我们网络前层进行 $WX + b$ 的线性变换后，是需要增加激活函数进行非线性变换的，但是具体怎么选择激活函数呢？我们可不可以让网络自己学习这个呢？

![DL00](../Images/DL00.png)
![DL01](../Images/DL01.png)

我们看卷积层或者说全连接层的输出部分，单独看每个单元，将它连接到 $k$ （这里 $k = 2$）个单元上，也就是 $k$ 个参数，然后看这 $k$ 个单元中哪个的激活值最大，我们取最大的那个即可，每个单元都进行如此操作，这样激活前后的单元数的没有变的

## 1 如何实现 Maxout

那么我们要怎么实现这样的 $Maxout$ 激活呢？很明显，这需要使用新的参数，要在不同通道之间分别进行全连接，当然这会很麻烦

![DL02](../Images/DL02.png)

我们看前面的全连接部分，是很复杂的连接，但是前两层的线性变换可以看成一层线性变换，也就是

![DL03](../Images/DL03.png)

如果我们将其中一部分连接使用 $Maxout$ 的方式去掉，也就相当于实现了 $Maxout$ 层

![DL05](../Images/DL05.png)
![DL04](../Images/DL04.png)

可以看到，这里激活后的连接方式与前面的完全相同，那么如何实现它呢？

可以参考 `tf.contrib.layers.maxout` 的实现方式，将前层的部分参数作为 $Maxout$ 的激活参数，这样省去了新建 $Maxout$ 层的麻烦，但是经过这样的 $Maxout$ 层单元数会减少，所以要注意连接方式

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
```

# Reference

1. [Tensorflow 文档 Maxout](https://tensorflow.google.cn/api_docs/python/tf/contrib/layers/maxout?hl=en)
2. [Paper: Maxout Networks](https://arxiv.org/abs/1302.4389)
