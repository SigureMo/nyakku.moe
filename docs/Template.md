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
![<codename>.<ext>](https://github.com/SigureMo/notev/blob/master/Codes/<noteName>/.../<codename>.<ext>)
```

2. 引用外部代码目录

```md
![<codename>.<ext>](https://github.com/SigureMo/notev/tree/master/Codes/<noteName>/.../)
```

3. 导入代码块

暂无

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
plt.savefig("Images/example.png")
```

![example](./Images/example.png)

# Change Log

1. 18xxxx Init
2. 18xxxx Add #0 #1

# Reference

1. XXX 老师课程
2. [url](/)
