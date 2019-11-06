---
title: Git 协作模式
date: 2019-10-26
categories:
   - 倏尔·论
tags:
   - Git
---

::: tip

虽然用 Git 也有一年多了，但是平时只用那些简单的常用命令(`add`、`commit`、`push`)，导致我平时连个 `merge` 都需要再去网上查，效率极低

这两天在 `vuepress-reco` 下修复了几个 bug ，经过多次的练习，我大概知道一般 Git 团队协作模式了，为了防止以后忘记，还是在这里简单记录下

:::

<!-- more -->

-  预备知识
   -  Git 基本命令
-  开发环境
   -  `Git`

## 单人的工作模式

首先从最基本的简单单人工作模式，渐进地增加一些指令

### 暂存文件

```bash
git add *
```

### 提交文件

```bash
git commit
```

### 推送到远程

```bash
git push
```

### 使用 dev 分支

如果有一个需要做很久的功能，应当新建一个分支，以保证 `master` 的稳定性

```bash
git checkout -b dev
```

### 合并其余分支内容

当在 `dev` 分支上的工作完成后，回到 `master` 并合并

```bash
git checkout master
git merge --no-ff dev            # 将 dev 合并回 master
git branch -d dev                # 移除无用的 dev 分支
```

::: tip 参数 --no-ff 的作用

如果你想保留下来临时分支的信息，可以增加 `--no-ff` 参数，这将把临时分支的信息作为一次 commit 合并到目标分支，但同时也会保留临时分支的过程，下面的图一目了然

![24_Git01.png](../Images/24_Git01.png)

:::

## 如何对待一个 fork 后的仓库

对于一个 fork 后的仓库，个人建议是**不要在原来已经存在的分支上进行修改**，除非你并不想合并回原分支

### 首先 clone 下来你的 repo

```bash
git clone git@github.com:SigureMo/vuepress-theme-reco.git
```

当然，该 `repo` 已经绑定在远程仓库 `origin` 上了

### 将原分支绑定在 upstream

```bash
git remote add upstream git@github.com:vuepress-reco/vuepress-theme-reco.git
```

这样，你的 `upstream` 就代表了原作者的远程分支，而 `origin` 就代表了你 fork 后的远程分支

### 新建一个自己的分支

比如你想修改 `master` 分支，那么直接以此为基础新建分支就好

```bash
git checkout master              # 如果已经在 master 则跳过
git checkout -b feature/sigure   # 新建一个分支，名称随意
```

现在再 `git branch` 一下就可以发现新建了一个 `feature/sigure` 分支，并且已经切换到该分支了

### 改动提交并推送

在你的 `feature/sigure` 上进行修改，并 `commit` 以及推送，推送的时候最好指定分支

```bash
git push origin feature/sigure   # 将 feature/sigure 推送到 origin （也就是你 fork 后的 repo）
```

### 在 GitHub 发起 PR

如果你的修改想要合并回原作者分支，那么就发起 PR 吧，如果原作者 merge 了，你的 `feature/sigure` 也可以删除了，后续从原作者那里重新获取 `master` 就能拥有你的改动了

```bash
git branch -d feature/sigure              # 如果该分支已经没有作用了，可以直接删除
git push origin --delete feature/sigure   # 同时删除远程分支
```

### 同步原作者更改

除了你的新分支，其余分支尽可能不要进行改动，这样保证了可以不需手动合并地同步原作者后续修改

```bash
git checkout master              # 切换到 master
git fetch upstream               # 将原作者分支下载到本地
git merge upstream/master        # 将原作者 master 分支最新内容合并到本地 master
```

## 如何合并 PR

既然你能发起一个 PR ，那么你也有可能收到一个 PR ，如果发起 PR 的人能够按照上面的规范来做，并且能规范书写代码、规范提交 commit 的话，你可以很容易地在 GitHub 上判断是 close 还是直接 merge ，但如果对方的代码很不规范，则需要你手动对代码进行 merge

### 拉取并放在新的分支

比如有这样的一个 PR `https://github.com/SigureMo/course-crawler/pull/6` ，我们可以看到它的 PR id 为 6

那么我们就可以

```bash
git fetch origin pull/6/head:dev
```

这样就创建了一个新的分支 `dev` 用以保存新的 PR 分支， `checkout` 过去就可以看到该分支下的具体内容了，修改好后返回 `master` 并 `merge` 即可

### 使用一个 commit 合并所有内容

如果想要只使用一个 commit 提交所有内容，可以在回到 `master` 后 `merge` 的时候加一个参数 `squash` ，之后再提交

```bash
git merge dev --squash
git commit
```

::: tip 注意

该方式可能导致发起 PR 的人的提交信息丢失，谨慎操作

:::

## 团队协作模式

团队协作应当不止建立 `master` 与 `dev`，抛开额外的功能分支，每个人都应当从 `dev` 建立自己的分支

`master` 应当是一个相当稳定的分支，只有在 `dev` 新功能基本稳定后，才合并回 `master` 发版，团队各成员平时只允许向 `dev` merge

### 建立你自己的分支

```bash
git checkout dev
git checkout -b feature/sigure     # 新建一个你自己的分支
```

### 完成你的工作，并发起 PR

```bash
git commit
git push origin feature/sigure
```

之后在 GitHub 上向 `dev` 发起 PR 即可

### 同步更改

由于你的 `master` 与 `dev` 都是相当干净（自己没做过改动）的，你可以和前面一样 `fetch` 并 `merge` 即可

# Reference

1. [Git 常用命令和 Git Flow 梳理](https://www.cnblogs.com/ldy-blogs/p/10529946.html#4416607)
