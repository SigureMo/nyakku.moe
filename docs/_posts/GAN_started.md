---
title: 初尝 GAN
date: 2020-05-25
category: 迹
tags:
   - DL
   - GAN
---

::: tip

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

## Unsupervised Conditional Generation

CGAN 的数据是有明确的标签的，每张图片都有相应的文本一一对应，而 Unsupervised CGAN 所处理的任务则是两个没有任何关系的 domain，它们之间没有给出任何对应关系，比如一个是真实世界人物图片，一个是二次元人物图片，Unsupervised CGAN 能做到在没有任何对应关系的前提下学出来给出一个真实人物图片输出这个人的二次元形象（有点像神经网络风格转换）

那么如何做到？一般有以下两种方法

### Direct Transformation

所谓直接转换，是指直接 train 一个从 Domain X 到 Domain Y 的 Generator $G_{X \to Y}$，当然结果需要一个 Discriminator $D_Y$ 来评判，就像下面这样

![Unsupervised-CGAN-01](../img/GAN_started/Unsupervised-CGAN-01.png)

不过这样虽然能够保证生成的图片是接近于 Domain Y 的，但如何保证能够保留原图的语义信息呢？

最简单的方法就是，什么都不管，当 $G_{x \to Y}$ 足够 Shallow 的情况下，那么原图并不会改变太多的

但……我们如果需要一个足够 Deep 的 $G_{X \to Y}$ 才能 work 的时候要怎么办呢？

方式一（添加约束项）：

[Yaniv Taigman, et al. Unsupervised Cross-Domain Image Generation, ICLR, 2017](https://arxiv.org/pdf/1611.02200.pdf)

![Unsupervised-CGAN-02](../img/GAN_started/Unsupervised-CGAN-02.png)

我们用一个 PreTrain 的 CNN backbone 来提取图片中的表示，然后让原图与生成图在表示空间内尽可能地一致

方式二（Circle GAN）：

[Jun-Yan Zhu, et al. Unpaired Image-to-Image Translation using Cycle-Consistent Adversarial Network, ICCV, 2017](https://arxiv.org/pdf/1703.10593.pdf)

![Unsupervised-CGAN-03](../img/GAN_started/Unsupervised-CGAN-03.png)

也就是，除去 $G_{X \to Y}$，再加一个 $G_{Y \to X}$，原图 $x$ 与 $G_{Y \to X}(G_{X \to Y}(x))$ 尽可能相同，以保证这个图片能顺利还原回来

另外，我们可以同时 train $Y \to X$ 的过程，构成一个 Circle

![Unsupervised-CGAN-04](../img/GAN_started/Unsupervised-CGAN-04.png)

大功告成，完美～

但是 Circle GAN 虽然能够成功将 Domain X 变成 Domain Y，并再解回来，但 Domian Y 的结果可能并不一定能够保证是那么地接近与原图，因为神经网络可能在 Domain Y 图中“隐藏”某些肉眼看不到的信息再解回去，该问题尚待解决

### Projection to Common Space

那么我们能不能直接在表示空间中进行操作呢？将前面的 $G_{X \to Y}$ 拆开变成一个 $Encoder_X$ 和一个 $Decoder_Y$，那么中间的 embedding 就暴露出来了

![Unsupervised-CGAN-05](../img/GAN_started/Unsupervised-CGAN-05.png)

可是，这个怎么 train？emmm，分成两个 auto-encoder（$Encoder_X \to Decoder_X$ 和 $Encoder_Y \to Decoder_Y$），各自在自己的 Domain 里 train……但 auto-encoder 的结果非常模糊呀，要如何解决？emmm，我们可以在这里加个 Discriminator

![Unsupervised-CGAN-06](../img/GAN_started/Unsupervised-CGAN-06.png)

我们在最后加一个 Discriminator，这样就可以让图片足够清晰啦（这个结构和 VAE-GAN 一样）

emmmm，还有他们 train 出来的 embedding 完全没有关系啊，语义不一致啊，这要如何解决呢？

方式一（共享接近于表示那几层的参数）：

![Unsupervised-CGAN-07](../img/GAN_started/Unsupervised-CGAN-07.png)

比较容易理解啦，这个 trick 在 Couple GAN（CoGAN） 中有使用，不过原论文图中 G（Decoder）在左面，D（Encoder）在右面，看起来就像是两侧的参数进行共享，但其实都一样啦，都是在接近特征空间进行 share

方式二（加一个对 embedding 的 Discirminator）：

![Unsupervised-CGAN-08](../img/GAN_started/Unsupervised-CGAN-08.png)

在 embedding 加一个 Domain Discriminator，用于判断该 embedding 来自 Domain X 还是 Domain Y，而 $Encoder_X$ 和 $Encoder_Y$ 则致力于骗过 Domain Discriminator，让其分不清原图到底来自哪个 Domain

方式三（能够转一圈再回来的就是好 GAN）：

![Unsupervised-CGAN-09](../img/GAN_started/Unsupervised-CGAN-09.png)

一个小 $x$ 的旅途：$x \to Encoder_X(x) \to Decoder_Y(Encoder_X(x)) \to Encoder_Y(Decoder_Y(Encoder_X(x))) \to Decoder_X(Encoder_Y(Decoder_Y(Encoder_X(x))))$ 然后我还要尽可能和我原来的样子一样……该方法被用于 ComboGAN

方式三（这次少跑一点就好）：

![Unsupervised-CGAN-10](../img/GAN_started/Unsupervised-CGAN-10.png)

转 3/4 圈，然后要求在特征空间尽可能不变，有被用在 DTN 和 XGAN

## GAN 背后的理论

那么 GAN 为什么是真的可行的呢？GAN 并不是简单的启发式算法，它也是有理论依据的哟

### Generator

如果我们将已有数据看作一个 distribution 的，并将其记为 $P_{data}(x)$，那么我们所 train 的 G 生成的数据应当尽可能都在 $P_{data}$ 中，或者说 G 映射的目标 distribution $P_G$ 应当尽可能地贴近 $P_{data}$

![GAN-Theory-01](../img/GAN_started/GAN-Theory-01.png)

如何让它们尽可能贴近？最大化 Likelihood，也即从 $P_{data}$ 里 sample 出来一些数据 $\{x^1, x^2, \cdots, x^m\}$，既然它们 Likelihood 相似，那么 $L = \prod \limits_{i=1}^m P_G(x_i; \theta)$ 也应当取得最大值，那么我们就要找到使得这个 Likelihood 最大的参数 $\theta^*$，也即

$$
\theta^* = arg\max\limits_\theta \prod\limits_{i=1}^m P_G(x^i; \theta)
$$

经过一点点推导，我们发现最大化这个 Likelihood 等价于最小化两个分布之间的 KL Divergence（还是蛮直觉的）

$$
\theta^* = arg\min\limits_\theta KL(P_{data} || P_G)
$$

也即

$$
G^* = arg\min\limits_G KL(P_{data} || P_G)
$$

那么如何计算这个 Divergence，我们的 G 是一个复杂的 network，它的分布并不能直接衡量，当然 $P_{data}$ 也不能直接衡量，emmm，那么第二个主角就该登场了

### Discriminator

我们训练一个 D 来告诉我们 Divergence 有多大，之前已经知道训练它是使用二分类的方法，此时相当于最大化下式

$V(G, D) = E_{x~P_{data}}[\log D(x)] + E_{x~P_G}[\log (1 - D(x))]$

其中 G 是 fixed 住的

也就是说

$$
D^* = arg\max\limits_{D} V(G, D)
$$

那么……为什么这样是可以的？

经过亿点推算，我们可以得到

$$
\max\limits_D V(G, D) = -2\log 2 + 2JSD(P_{data} || P_G)
$$

其中，$JSD(P_{data}||P_G)$ 是指 $P_{data}$ 和 $P_G$ 之间的 JS Divergence，那么……我们是不是可以用 JS Divergence 替换之前的 KL Divergence？emmm，其实不能直接替换，JS Divergence 和 KL Divergence 是不同的衡量标准，但……它们确实也都是衡量标准，先换上试试看

$$
G^* = arg\min\limits_G\max\limits_D V(G, D)
$$

也就是说，在每个 G 中，我们先找到 V(G, D) 的最大值 $V(G_i, D^*)$，然后从这些 G 中挑选出使得各自 $V(G_i, D^*)$最小的 $G^*$

![GAN-Theory-02](../img/GAN_started/GAN-Theory-02.png)

从上图而言，就是各个 G 先找出最大值，然后再取这些值之中的最小值对应的 G

### Algorithm

那么为什么我们的 GAN 是用最开始那种算法的呢？我们的算法过程是在解 $G^* = arg\min\limits_G\max\limits_D V(G, D)$，也就是首先训练一个能够表征 JS Divergence 的 D，D 需要越精确越好，因此这个过程需要重复多次，尽可能收敛

-  在每个迭代中，更新 D，重复以下过程 k 次
   -  从 $P_{data}$ 中选取 $\{x^1, x^2, \cdots, x^m\}$
   -  从 $P_{prior}(z)$ 中选取 $\{z^1, z^2, \cdots, z^m\}$，喂给 $G$ 获得 $\{\tilde{x}^1, \tilde{x}^2, \cdots, \tilde{x}^m\}$，其中 $\tilde{x}^i = G(z^i)$
   -  更新 D 的参数 $\theta_d$
      -  $\tilde{V} = \frac{1}{m} \sum\limits_{i=1}^m \log D(x^i) + \frac{1}{m} \log (1 - D(\tilde{x}^i))$
      -  $\theta_d \leftarrow \theta_d + \eta \nabla \tilde{V}(\theta_d)$

那么，我们就认为这个 D 能够代表 JS Divergence，更新一下 G，但不能更新太多，当 G 过度更新时，$V(G, D)$ 也被更新，而 JS Divergence 是 $\max V(G, D)$，可能此时的 D 已经不能代表 JS Divergence 了，因此 G 的更新比较少，可能只有一次

-  在每个迭代中，更新 G，重复以下过程 1 次
   -  从 $P_{prior}(z)$ 中选取 $\{z^1, z^2, \cdots, z^m\}$
   -  更新 G 的参数 $\theta_g$
      -  $\tilde{V} = \sout{\frac{1}{m} \sum\limits_{i=1}^m \log D(x^i) +} \frac{1}{m} \log (1 - D(G(z^i)))$
      -  $\theta_g \leftarrow \theta_g - \eta \nabla \tilde{V}(\theta_g)$

Ian Goodfellow 在 G 的更新中使用 $\tilde{V} = \frac{1}{m} (- \log (D(x)))$ 替换了原式的 $\tilde{V} = \frac{1}{m} \log (1 - D(x))$，这样……在实际操作时就变得更加简单了，训练 G 时只需要将 G 生成的标签翻转改为 1 即可，G 和 D 可以直接使用同一个 Loss 函数

为了区分两者，Ian Goodfellow 将原始的式子 $\tilde{V} = \frac{1}{m} \log (1 - D(x))$ 称为 Minimax GAN（MMGAN），将修改后的 $\tilde{V} = \frac{1}{m} (- \log (D(x)))$ 称为 Non-saturating GAN（NSGAN）

## 算法改进

通常，JS Divergence 并不是特别合适，因为它对两个无重叠的两个分布的测度永远为 $\log 2$，因此梯度永远为 0，G 无法得到更新

换言之，它并不能评估两个无重叠分布之间的“距离”，然而 G 生成分布和真实分布在训练之初基本上不可能重叠，这就导致了当 D 训练地太好时，G 将会没有梯度，训练无法进行下去

![Improving-GAN-01](../img/GAN_started/Improving-GAN-01.png)

为了使 GAN 能够正常训练，就需要一些算法上的一些技巧以及理论改进

### LSGAN（Least Square GAN）

LSGAN 从 D 的分类器角度来进行改进，它认为 D 最终使用的是 Sigmoid 进行激活，会导致两侧梯度较小，进而发生梯度消失的现象，因此……就直接改成线性的了

![Improving-GAN-02](../img/GAN_started/Improving-GAN-02.png)

### fgan: General Framework of GAN

如果不想使用 JS Divergence 的话，fGAN 从理论上给出了其它各种 Divergence 在 GAN 中的使用方法

### WGAN（Wasserstein GAN）

WGAN 用了一种新的评估距离方式——Wasserstein 距离，由于它并不是 Divergence，因此 fGAN 中并没有该方式

该方式可以理解为将其中一个分布变成另一个分布所需最少移动次数，它能够表征两个无重叠分布之间的距离

那么，Wasserstein 距离到底要如何计算呢？emm，就像这样

$
V(G, D) = \max\limits_{D \in 1-Lipschitz} \{ E_{x \sim P_{data}} [D(x)] - E_{x \sim P_G} [D(x)]\}
$

这里 $1-Lipschitz$ 是约束 D 为一个光滑的函数，它不能变化地太快，那么……如何约束它呢

一是 WGAN 中提出的方法，Weight Clipping，也就是将 weights 截断在某个范围内，防止 weights 太大，从而保证函数不会变化太快

另一个是 WGAN-GP 中提出的方法，是从梯度的角度进行约束，因为 $1-Lipschitz$ 函数满足任意位置导数不大于 1，因此我们可以通过一点约束以使得 D 的导数不大于 1 即可

$
V(G, D) = \max\limits_{D \in 1-Lipschitz} \{ E_{x \sim P_{data}} [D(x)] - E_{x \sim P_G} [D(x)] - \lambda \int_x \max(0, || \nabla_x D(x) || - 1) dx \}
$

最后一项的补偿能够保证 D 不大于 1，但……最后一项的要求是对于全部 x 都满足才可以，事实上这也是不可能的，WGAN-GP 中提出只需要使得 $P_{penalty}$ 全部满足就好了，并将从 $P_{data}$ 和 $P_G$ 中 Sample 出来的样本之间连线上随机取样作为 $P_{penalty}$

$
V(G, D) = \max\limits_{D \in 1-Lipschitz} \{ E_{x \sim P_{data}} [D(x)] - E_{x \sim P_G} [D(x)] - \lambda E_{x \sim P_{penalty}} \max(0, || \nabla_x D(x) || - 1) \}
$

![Improving-GAN-02](../img/GAN_started/Improving-GAN-03.png)

WGAN-GP 在实际应用中使用的是

$
V(G, D) = \max\limits_{D \in 1-Lipschitz} \{ E_{x \sim P_{data}} [D(x)] - E_{x \sim P_G} [D(x)] - \lambda E_{x \sim P_{penalty}} (|| \nabla_x D(x) || - 1)^2 \}
$

因为效果更好一些

算法：

-  在每个迭代

   -  更新 D，重复以下过程 k 次
      -  从 $P_{data}$ 中选取 $\{x^1, x^2, \cdots, x^m\}$
      -  从 $P_{prior}(z)$ 中选取 $\{z^1, z^2, \cdots, z^m\}$，喂给 $G$ 获得 $\{\tilde{x}^1, \tilde{x}^2, \cdots, \tilde{x}^m\}$，其中 $\tilde{x}^i = G(z^i)$
      -  更新 D 的参数 $\theta_d$
         -  $\tilde{V} = \frac{1}{m} \sum\limits_{i=1}^m D(x^i) - \frac{1}{m} D(\tilde{x}^i)$
         -  $\theta_d \leftarrow \theta_d + \eta \nabla \tilde{V}(\theta_d)$

   ***

   -  更新 G，重复以下过程 1 次

      -  从 $P_{prior}(z)$ 中选取 $\{z^1, z^2, \cdots, z^m\}$
      -  更新 G 的参数 $\theta_g$
         -  $\tilde{V} = -\frac{1}{m} D(G(z^i))$
         -  $\theta_g \leftarrow \theta_g - \eta \nabla \tilde{V}(\theta_g)$

   > D 最后不要用 Sigmoid，直接输出即可
   > 另外，记得使用 Weight clipping 或者 Gradient Penalty

## More GANs

### Stack GAN

[Han Zhang, Tao Xu, Hongsheng Li, et al. StackGAN: Text to Photo-realistic Image Synthesis with Stacked Generative Adversarial Networks”, ICCV, 2017](http://openaccess.thecvf.com/content_ICCV_2017/papers/Zhang_StackGAN_Text_to_ICCV_2017_paper.pdf)

直接 Generate 一个较为大的图往往是不容易的，StackGAN 将该过程分解为多步，先让 $G_1$ 生成一个较为小的图，然后再将这个小的图喂给 $G_2$，让 $G_2$ 据此生成一个较为大的图

### Patch GAN

D 有时不太容易直接判别图片是否为真实，但我们可以让 D 每次只判断图片的某一块

### EBGAN（Energy-based GAN）

使用 Auto Encoder 作为 D，这样使得 D 可以 pretrain，所以在训练之初就可以获得比较好的 G

### Info GAN

使 GAN 的输入 code 各个维度更加正交，将输入 code 分为两部分，一部分带有分类信息 $c$，这个分类信息要求后续 Classifier 能够还原出来，另外一部分就是噪声 $z'$

![InfoGAN](../img/GAN_started/InfoGAN.png)

### VAE-GAN

VAE 与 GAN 的结合，D 需要能够分辨

-  从真实图片经过 VAE 重构后的图片
-  从噪声经过 G 生成的图片
-  真实图片

三者

![VAE-GAN](../img/GAN_started/VAE-GAN.png)

### BiGAN

有一个 Encoder，输入图片，输出 code

有一个 Decoder，输入 code，输出图片

有一个 D，输入一对图片与 code，然后判断它们是经由 Encoder 生成还是经由 Decoder 生成

![BiGAN](../img/GAN_started/BiGAN.png)

至于为什么有效，D 使得 Encoder 对应的 distribution $P(x, z)$ 与 Decoder 的 distribution $Q(x, z)$ 尽可能地接近

BiGAN 的训练类似于同时训练一个 Decoder $\to$ Encoder，与一个反向的 Encoder $\to$ Decoder，而 BiGAN 的效果会更好些

# References

1. [Hung-yi Lee MLDS18](http://speech.ee.ntu.edu.tw/~tlkagk/courses_MLDS18.html)
2. [基于 GAN 的动漫头像生成](https://zhuanlan.zhihu.com/p/76340704)
3. [KL 散度、JS 散度、Wasserstein 距离](https://zxth93.github.io/2017/09/27/KL%E6%95%A3%E5%BA%A6JS%E6%95%A3%E5%BA%A6Wasserstein%E8%B7%9D%E7%A6%BB/index.html)
