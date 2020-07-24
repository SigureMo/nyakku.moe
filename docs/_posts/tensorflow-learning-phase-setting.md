---
title: TensorFlow 踩坑记：训练状态的设置
date: 2020-04-08
category: 迹
tags:
   - TensorFlow
   - Python
   - DL
---

::: tip

虽然说 TensorFlow2.x 比 1.x 易用了很多，但杂乱的 API 还是让人抓狂，特别是 Keras 中有着多种多样的模型实现方式（最简单的 Sequential、最灵活的 Functional、最规整的 SubClass）以及训练方式（fit 和自己写训练循环），fit 过于封装，有时候想加点东西都挺麻烦，而自己写循环又怕效率较低，也可能会忽略点什么，果不其然，最近又发现了训练状态的设置问题，于是它差点又把我推向了 Pytorch 的怀抱

:::

<!-- more -->

## 为什么要设定训练状态

由于某些层在训练时会使用与测试时不一致的行为（主要指 BN 层与 Dropout 层），所以自己写训练 Loop 时候需要设定一下训练状态，但要如何改变这个状态？？？嗯由于 TensorFlow 文档基本都用的 fit 方式，所以……基本没有看到与状态设定有关的 API

之后我看到了 [1] 这篇文章才了解到训练状态的指定方式，但原文中涵盖不太全面，我稍微进一步进行了测试（由于基本不用 fit 方式，而且 fit 方式也没这方面的问题，所以仅针对自写循环方式进行测试）

## 三种模型定义方式

对于三种模型定义方式，并没有什么不同，并不需要修改 SubClass 的定义方式

```python
# Sequential
model = tf.keras.Sequential([
    tf.keras.layers.Conv2D(16, 3),
    tf.keras.layers.BatchNormalization()
])

# Functional
inputs = tf.keras.Input(shape=data.shape[1: ])
x = inputs
x = tf.keras.layers.Conv2D(16, 3)(x)
x = tf.keras.layers.BatchNormalization()(x)
outputs = x
model = tf.keras.Model(inputs=inputs, outputs=outputs)

# SubClass
class Model(tf.keras.Model):
    def __init__(self):
        super().__init__()
        self.conv = tf.keras.layers.Conv2D(16, 3)
        self.bn = tf.keras.layers.BatchNormalization()

    def call(self, input):
        x = input
        x = self.conv(x)
        x = self.bn(x)
        output = x
        return output
model = Model()
```

模型在训练时候需要指定 `training=True`（默认值是 `None`）

```python
model(data, training=True)
```

这样，训练时 BN 才能更新 `moving_mean` 和 `moving_variance`，相应地，如果是 Dropout，这样才会 dropout 掉部分 neurons

## tf.keras.backend.set_learning_phase

那么，另外一种改变状态的方式 `tf.keras.backend.set_learning_phase` 是否有效呢？经过测试也是可以的，但是要注意一个问题，当在 `model` 中指定训练状态时，会忽略掉这个设置

也就是说即便之前指定了 `tf.keras.backend.set_learning_phase(True)`，但使用了 `model(data, training=False)` 的话，实际执行的仍然是非训练状态

也就是说，当 `training` 没有指定（`None`）的时候，会使用 `tf.keras.backend.set_learning_phase` 的值，而指定后则忽略 `tf.keras.backend.set_learning_phase` 的值

## 所以要怎么训练？

还是有两种方式耶，喜欢哪种就用哪种吧

```python
# training
tf.keras.backend.set_learning_phase(True)
model(data)

# testing
tf.keras.backend.set_learning_phase(False)
model(data)
```

```python
# training
model(data, training=True)

# testing
model(data)
```

由于后者更方便一些，所以我一般选用后者

## References

1. [TensorFlow 2.0+Keras 防坑指南](https://zhuanlan.zhihu.com/p/64310188)
