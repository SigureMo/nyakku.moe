---
title: 初尝 GAN
date: 2020-05-25
category: 迹
tags:
   - DL
   - GAN
---

::: warning

最近在 DL 的学习方向上稍有迷茫，毕竟有那么多学习的方向嘛。“开学”那几天初尝 RL 做了个 AlphaZero 五子棋，但理论什么的尚需补足，而且暂时没有什么别的想做的也没继续深入。毕设这段时间主要是学习一些机器学习领域的知识啦，大多是一些浅层神经网络及其优化算法，比如 AutoEncoder 和遗传算法等等，唔，本来兴趣就寥寥，然后毕设凉了就更没动力了……

前两天突然翻出来一张猫猫十年前的照片，但分辨率实在太低啦（240 \* 320），就想尝试一下超分辨率相关模型，发现最近超分辨率也在用 GAN 啦，所以，就尝试学一下～

:::

<!-- more -->

## 何为 GAN？

GAN 是 Generative Adversarial Network 的缩写，也即生成对抗网络，那么……生成对抗是指？

首先，它是一个生成网络，目标是生成数据，所以它首先要有一个 Generator（简称 G），但是如何评判这个 G 的优劣？emmm 貌似不太容易啊，毕竟生成的数据大多比较复杂……

因此，引入了 Discriminator（简称 D），D 的作用就是用来判别一张图片是否是真实图片，也就是当 D 的输入是 G 生成的图片时就输出 0，当 D 的输入是真实图片时输出就是 1，最小化这个误差即可

嗯，D 知道怎么训练了，那么 G？嘛，也很简单啦，就是把 G 的输出喂给 D，然后让 D 尽可能输出较大的值就好啦，也就是 G 在这个过程中尽可能地骗过 D

但是，两者同时训练还是不可取的，我们要交替地训练，具体迭代如下

-  在每个迭代过程中：
   -  下面训练 D，锁定 G 的 Weights
   -  从真实数据集随便选 m 个数据 $\{x^1, x^2, \cdots, x^m\}$
   -  再从某一个分布中选取 m 个噪声数据 $\{z^1, z^2, \cdots, z^m\}$ 并喂给 G 生成 $\{\tilde{x}^1, \tilde{x}^2, \cdots, \tilde{x}^m\}$（也即 $\tilde{x}^i = G(z^i)$）
   -  更新 D 咯，也就是让 D 判断更准确
      -  $\tilde{V} = \frac{1}{m} \sum \limits_{i=1}^m \log D(x^i) + \frac{1}{m} \sum \limits_{i=1}^m \log (1 - D(\tilde{x}^i))$
      -  $\theta_d \leftarrow \theta + \eta \nabla \tilde{V}(\theta_d)$
   -  修炼完毕，可以更精准地分辨真实图片与 G 生成的图片
   ***
   -  下面训练 G，锁定 D 的 Weights
   -  从某一个分布中选取 m 个噪声数据 $\{z^1, z^2, \cdots, z^m\}$，然后喂给 G，再将 G 的结果喂给 D，G 是想让 D 觉得它们都是 1 咯
   -  那么我们更新 G 吧
      -  $\tilde{V} = \frac{1}{m} \sum \limits_{i=1}^m \log D(G(z^i))$
      -  $\theta_g \leftarrow \theta_g - \eta \nabla \tilde{V}(\theta_g)$
   -  修炼完毕，可以更容易骗过 D

两者在不停地“对抗”过程中完成了进化，两者的模型最后都有着较好的效果

## GAN 与 AutoEncoder

简单地看，GAN 就是个倒过来的 AE 嘛，AE 是 encoder $\to$ decoder，而 GAN 则是 decoder(G) $to$ encoder(D)，当然细节略有区别

而效果，AE 自然是远不如 GAN，AE 的要求是 encoder 输入与 decoder 输出尽可能相似，而相似性的比较大多使用的是像素级比较，但这往往并不合适，生成的图像大多比较模糊（类似于多个图片的叠加）

## Conditional GAN

emmmm，虽然 GAN 能够生成图片，但并不能根据我们的要求准确地输出我们想要的东西，Conditional GAN（简称 CGAN） 就是用来解决该问题的

CGAN 的 G 是同时需要词语 c 和噪声 z 的，词语 c 自然就是我们想要的东西咯

那么 D 也需要改一下咯，它不仅需要一张图片，还需要词语 c，也就是一方面判别这张图片是否是真实图片，另一方面判别这张图片与 c 描述是否相符

至于训练过程嘛，D 的训练过程数据由

-  正样本真实图片正确标签
-  负样本 G 生成图片对应标签
-  负样本真实图片错误标签

三部分组成，G 的不必说了，还是想骗过 D

另外，D 的结构如何设计比较好呢？比较多的用法像下面这样，直接吞掉 x 和 c 给出 0 或 1

![CGAN-01](../img/GAN_started/CGAN-01.png)

如果使用上面的结构的话，我们并不知道 0 的情况是因为图片生成的不好还是图片生成错了，为此，我们可以稍微改一下网络结构，就像下面这样，这样看起来会更合理一点

![CGAN-02](../img/GAN_started/CGAN-02.png)

# References

1. [Hung-yi Lee MLDS18](http://speech.ee.ntu.edu.tw/~tlkagk/courses_MLDS18.html)
