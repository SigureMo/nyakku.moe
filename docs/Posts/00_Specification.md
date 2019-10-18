---
title: 本 Repo 规范
date: 2018-09-01
categories:
   - 此间·语
tags:
   - Vuepress
---

::: tip

> 不规矩无以成方圆

一个规范是任何建设的基础，有了规范才能作出更好的上层建筑，本篇主要介绍本 Repo 的使用规范，当然，是给自己看的

:::

<!-- more -->

## 为什么需要规范？

任何事物都有着规范，不按照规范行事吃亏的总归是自己，本规范的存在是让自己在日常就养成按照规范行事的习惯，这样回头再看的时候，就可以“随心所欲不逾矩”了

当然，随着学习的不断深入，本规范会随之不断更新

## 这个 Repo 到底是个什么存在？

18 年 9 月，开始正式学习数据结构等 CS 专业课，为了方便记录与留存笔记，我使用有道云笔记使用 Markdown （不熟，边写边学）对课程笔记进行记录，开了本 Repo 作为代码和笔记图片存储库，但是使用了半个月，我发现有道云笔记经常会吞掉我的笔记，不过所幸能够在后台恢复，不过体验实在不佳，不久后我就弃坑了

之后我萌生了使用 Git 存储笔记的想法，但是并没能找到比较友好的前端（那时候我也不咋会搭建静态博客，随手按教程弄了个，但是没试过 Hexo）

偶然间发现了 Vuepress ，不过该框架是在当年 4 月刚刚诞生（搜尤大微博就能看到啦），此时 1.0.0 还仅仅是 alpha 阶段，我试着按照文档搭建了一个，效果非常满意，虽然只是文档格式，但是其实我根本就没想过搭建博客啦，我只想写写笔记什么的

不过新也挺好的啊，我能和它一起成长嘛（学会了查阅技术文档，也认识到了项目文档的重要性）~之后就是各种折腾咯~

后来我又用 Vuepress 写了好几个项目文档，用起来非常顺手~

19 年 8 月，偶然间发现了 reco 这个博客主题，看着还不错，继而又是折腾一番，当然这对我来说已经没啥难度了，自此本笔记 repo 正式转为博客 repo

不过 reco 也是个比较新的主题呀，我又见证了一个项目的一步一步成长 :joy: ，也略微尝试了些前端的东西

## 从文档开始

本 Repo 的 Markdown 等语法基于 [Vuepress 文档](https://vuepress.vuejs.org/) 、 [vuepress-theme-reco 文档](https://vuepress-theme-reco.recoluan.com/) ，查文档是一种最基础的能力

## 如何书写文章

表述能力是一种很重要的能力，一个好的文字描述可以使得用户更快地抓住重点，如果有必要，可以加上 `==`（高亮） 或者 `**`（加粗），尽量使用加粗而不是高亮，因为高亮并非 Markdown 原生语法

在一些需要图形描述时，可以添加图片，图片等二进制文件默认以 LFS 形式存储，如果没有加入 LFS 不得提交，图片应尽量少

## 图片路径怎么使用

## 插入图片

1. 使用相对路径

```md
![<noteName><imgCnt>](../Images/<noteName><imgCnt>.<ext>)
```

2. 使用外部路径

```md
![<noteName><imgCnt>](https://github.com/SigureMo/notev/blob/master/docs/Images/<noteName><imgCnt>.<ext>?raw=true)

<!-- or -->

![<noteName><imgCnt>](https://raw.githubusercontent.com/SigureMo/notev/master/docs/Images/<noteName><imgCnt>.<ext>)
```

使用 `git-lfs` 时

```md
![<noteName><imgCnt>](https://media.githubusercontent.com/media/SigureMo/notev/master/docs/Images/<noteName><imgCnt>.<ext>)
```

::: warning

当前使用 `git-lfs` 上传图片文件，所以后者才是有效链接

:::

## 引用代码

1. 引用外部代码

```md
![<codename>.<ext>](https://github.com/SigureMo/notev/blob/master/Codes/<notename>/.../<codename>.<ext>)
```

2. 引用外部代码目录

```md
![<codename>.<ext>](https://github.com/SigureMo/notev/tree/master/Codes/<notename>/.../)
```

3. 导入代码块

```md
<<< @/Codes/<noteName>/.../<codename>{<hightlight_line1>,<hightlight_line2>}
```

4. 代码高亮

[Vuepress 支持高亮的语言](https://prismjs.com/#languages-list)

## 数学公式($\KaTeX$)

我们可以渲染公式例如：$x_i + y_i = z_i$和$\sum_{i=1}^n a_i=0$
我们也可以单行渲染

$$
\begin{aligned}
\sum_{i=1}^n a_i & = 0 \\
\sum_{j=1}^n b_j & = 1000
\end{aligned}
$$

具体可参照[$\KaTeX$ 支持的公式](https://katex.org/docs/supported.html)以及[$\LaTeX$ 支持的公式](https://math.meta.stackexchange.com/questions/5020/mathjax-basic-tutorial-and-quick-reference)

::: tip

过长的公式请不要使用单行渲染！否则在手机浏览器会产生部分空屏的效果！

:::

## Emoji:smiley:

使用 emoji 使文档更加生动~

比如在哪里需要提到 bug，不妨在两边加上:，就像`:bug:`这样，然后就成了:bug:这样子~

当然，我们还可以使用 Emoji 作为 git 的 commit 说明，可以参考[Gitmoji](./Discovery/05_Git_Commit.md)

更多请查看[Gitmoji 官网](http://gitmoji.carloscuesta.me/)和[Emoji 官网](https://emojipedia.org/)

## Badge <Badge text="beta" type="warn"/> <Badge text="0.10.1+"/>

这是 Vuepress 中的内置组件，可以通过这种方式使用：

```md
## Badge <Badge text="beta" type="warn"/> <Badge text="0.10.1+"/>
```

渲染出来的效果当然就是标题这种啦~

更多选项参考[Vuepress 文档](https://vuepress.vuejs.org/zh/guide/using-vue.html)

::: tip

今后将使用其作为笔记状态标记，暂定以下规则：

1. <Badge text="alpha" type="warn"/> <Badge text="0.10.1"/>为 Studying 类（正在编写与学习中）的标记
2. <Badge text="beta" type="tip"/> <Badge text="1.10.1"/>为 Debugging 类（基本框架完成，待补充完善）的标记
3. <Badge text="2.10.1" type="error" />为 Discarded 类（中途停止继续记录，可能使用新框架重写）的标记

:::

## ==Mark==

使用 `markdown-it` 扩展中的 `markdown-it-mark` 扩展，只需要在需要==高亮==的文本两侧加`==`，便可实现 `<mark>` 效果，增加笔记的可读性

## Prettier

使用 Prettier 对文档进行优化，使用 husky 配合 pretty-quick 钩子，详情请见[Prettier 官网](https://prettier.io/)

## Matplotlib

使用 `Python` 库 `matplotlib` 愉快地生成函数等图像！

基于`VS Code` 插件 [Markdown Preview Enhanced](https://shd101wyy.github.io/markdown-preview-enhanced/#/zh-cn/code-chunk) ，首先打开 `VS Code` 设置中的 `enableScriptExecution` ，之后便可以通过快捷键 `shift-enter` 运行当前代码块、快捷键 `ctrl-shift-enter` 运行全部代码块

使用 `plt.show()` 可在预览文档中快速预览生成的图片，但无法保存到云端文档，故可配合 `plt.savefig('../Images/filename.png')` 将图片保存至 `Images` 文件夹内，之后添加`![filename](../Images/filename.png)` 即可

示例：

```python {cmd=true matplotlib=true hide=true}
import matplotlib.pyplot as plt
plt.plot([1, 2, 3, 4])
plt.show()
plt.savefig("../Images/example.png")
```

![example](../Images/example.png)

# Change Log

1. 18xxxx Init
2. 18xxxx Add #0 #1

# Reference

1. XXX 老师课程
2. [url](/)
