<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/KaTeX/0.9.0/katex.min.css">

# Template <Badge text="alpha" type="warn"/>

[[TOC]]

## QuickStart!

本笔记使用了一些规范，为方便查阅，特在这里进行记录

[vuepress 官方文档](https://vuepress.vuejs.org/)

## 插入图片

1. 使用相对路径

```md
![<noteName><imgCnt>](../Images/<noteName><imgCnt>.<ext>)
```

2. 使用外部路径

```md
![<noteName><imgCnt>](https://github.com/SigureMo/notev/blob/master/docs/Images/<noteName><imgCnt>.<ext>?raw=true)
```

## 引用代码

1. 引用外部代码

```md
![<codename>.<ext>](https://github.com/SigureMo/notev/blob/Codes/<noteName>/.../<codename>.<ext>)
```

2. 引用外部代码目录

```md
![<codename>.<ext>](https://github.com/SigureMo/notev/master/Codes/<noteName>/.../)
```

3. 导入代码块

暂无

## 数学公式($\KaTeX$)

我们可以渲染公式例如：$x_i + y_i = z_i$和$\sum_{i=1}^n a_i=0$
我们也可以单行渲染

$$
\begin{aligned}
\sum_{i=1}^n a_i & = 0 \\
\sum_{j=1}^n b_j & = 1000
\end{aligned}
$$

具体可参照[katex 文档](http://www.intmath.com/cg5/katex-mathjax-comparison.php)和[katex 支持的函数](https://github.com/Khan/KaTeX/wiki/Function-Support-in-KaTeX)以及[latex 文档](https://math.meta.stackexchange.com/questions/5020/mathjax-basic-tutorial-and-quick-reference)

::: tip
不过有个前提就是在使用 KaTeX 的 markdown 的首行添加下面的 css 链接：

```html
<link
   rel="stylesheet"
   href="https://cdnjs.cloudflare.com/ajax/libs/KaTeX/0.9.0/katex.min.css"
/>
```

该问题尚待解决……
:::

## Emoji:smiley:

使用 emoji 使文档更加生动~

比如在哪里需要提到 bug，不妨在两边加上:，就像`:bug:`这样，然后就成了:bug:这样子~

当然，我们还可以使用 Emoji 作为 git 的 commit 说明，可以参考[Gitmoji](./Discovery/05_Gitmoji.md)

更多请查看[Gitmoji 官网](http://gitmoji.carloscuesta.me/)和[Emoji 官网](https://emojipedia.org/)

## Badge <Badge text="beta" type="warn"/> <Badge text="0.10.1+"/>

这是 Vuepress 中的内置组件，可以通过这种方式使用：

```md
## Badge <Badge text="beta" type="warn"/> <Badge text="0.10.1+"/>
```

渲染出来的效果当然就是标题这种啦~

更多选项参考[Vuepress 文档](https://vuepress.vuejs.org/zh/guide/using-vue.html#badge)

::: tip
今后将使用其作为笔记状态标记，暂定以下规则：

1. <Badge text="alpha" type="warn"/> <Badge text="0.10.1"/>为**studying**类（正在编写与学习中）的标记
2. <Badge text="beta" type="tip"/> <Badge text="1.10.1"/>为**debugging**类（基本框架完成，待补充完善）的标记
3. <Badge text="beta" type="error"/> <Badge text="1.10.1"/>为**discarded**类（中途停止继续记录，可能使用新框架重写）的标记
   :::

## Prettier

使用 Prettier 对文档进行优化，使用 husky 配合 pretty-quick 钩子，详情请见[Prettier 官网](https://prettier.io/)

::: warning

优化工作进行中

:::

# Amendant Record

1. 18xxxx Init
2. 18xxxx Add #0 #1

# Reference

1. XXX 老师课程
2. [url](/)
