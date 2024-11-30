---
title: Git 协作模式
date: 2019-10-26
category: 想点没谱的
tags:
   - Git
---

::: tip

虽然平时写个笔记都会使用 Git 来保存，但常用的也就只有 `add`、`commit`、`push` 等等简单的命令啦，偶尔出点问题都需要去现查，为了提高效率，我在这里整理一下简单的 Git 协作命令，以备不时之需ヽ(✿ ﾟ ▽ ﾟ)ノ

:::

<!-- more -->

- 预备知识
   - Git 基本命令
- 开发环境
   - `Git`

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

如果有一个需要做很久的功能，应当新建一个分支，以保证 `main` 的稳定性

```bash
git checkout -b dev
```

### 合并其余分支内容

当在 `dev` 分支上的工作完成后，回到 `main` 并合并

```bash
git checkout main
git merge --no-ff dev            # 将 dev 合并回 main
git branch -d dev                # 移除无用的 dev 分支
```

::: tip 参数 --no-ff 的作用

如果你想保留下来临时分支的信息，可以增加 `--no-ff` 参数，这将把临时分支的信息作为一次 commit 合并到目标分支，但同时也会保留临时分支的过程，下面的图一目了然

![](../img/git-collaboration/git-collaboration01.png)

:::

## 如何提交 PR

提交 PR 的最佳实践是现将原仓库 fork 到自己的账户下，然后**新建一个分支**进行修改

### 首先 clone 下来你 fork 的 repo

```bash
git clone git@github.com:SigureMo/vuepress.git
```

当然，该 `repo` 已经绑定在远程仓库 `origin` 上了

### 将原仓库绑定在 upstream

```bash
git remote add upstream git@github.com:vuejs/vuepress.git
```

这样，你的 `upstream` 就代表了原作者的远程分支，而 `origin` 就代表了你 fork 后的远程分支

### 新建一个自己的分支

比如你想修改 `main` 分支，那么直接以此为基础新建分支就好

```bash
git checkout main                # 如果已经在 main 则跳过
git checkout -b feature-xxx      # 新建一个分支，名称随意
```

现在再 `git branch` 一下就可以发现新建了一个 `feature-xxx` 分支，并且已经切换到该分支了

### 改动提交并推送

在你的 `feature-xxx` 上进行修改，并 `commit` 以及推送，推送的时候最好指定分支

```bash
git push origin feature-xxx   # 将 feature-xxx 推送到 origin（也就是你 fork 后的 repo）
```

### 在 GitHub 发起 PR

如果你的修改想要合并回原作者分支，那么就发起 PR 吧，如果原作者 merge 了，你的 `feature-xxx` 也可以删除了，后续从原作者那里重新获取 `main` 就能拥有你的改动了

```bash
git branch -d feature-xxx              # 如果该分支已经没有作用了，可以直接删除
git push origin --delete feature-xxx   # 同时删除远程分支
```

### 解决冲突

如果你的 PR 与原作者的默认分支修改发生了冲突，那么最佳实践是我们基于原作者最新修改 rebase 一下。

```bash
git fetch upstream
git rebase upstream/main
```

此时应当会提示有冲突，我们手动将所有冲突解决后，add 它们，比如这里发生冲突的是 `conflicted.md`

```bash
git add conflicted.md
```

然后我们让 rebase 继续下去

```bash
git rebase --continue
```

现在，我们的修改就会变成基于原作者最新进度的修改了。我们 push 一下，当然，由于我们本次改动对历史有影响，因此需要 force 一下

```bash
git push --force-with-lease
```

### 同步原作者更改

如果原作者更新了原来的分支，总不能每次都重新 fork 一下仓库吧，如果之前没有在原有分支上进行修改的话，现在就可以在避免手动合并的情况下同步原作者后续修改了

```bash
git checkout main                # 切换到 main
git fetch upstream               # 将原作者分支下载到本地
git merge upstream/main          # 将原作者 main 分支最新内容合并到本地 main
```

## 如何合并 PR

既然你能发起一个 PR ，那么你也有可能收到一个 PR ，如果发起 PR 的人能够按照上面的规范来做，并且能规范书写代码、规范提交 commit 的话，你可以很容易地在 GitHub 上判断是 close 还是直接 merge ，但如果对方的代码稍有欠缺，就需要手动对代码进行 merge

### 拉取目标用户分支

比如有这样的一个 PR <https://github.com/SigureMo/bilili/pull/89> ，它是由用户 @vx13 创建的，为了能够在 GitHub 直接进行后续 Review 等操作，我们需要直接对该用户的该分支进行修改

为了实现这一点，我们可以这样做

```bash
git remote add vx13 https://github.com/vx13/bilili.git
git fetch vx13
git checkout -b feature-with-section vx13/feature-with-section
```

这样就将该用户的 PR 分支保存到 `feature-with-section` 分支了，之后进行各种修改后 push 即可

```bash
git push vx16 HEAD:feature-with-section
```

值得注意的是，这需要该用户在提交 PR 时勾选 `Allow edits from maintainers`，该选项默认是勾选的，当然也不排除该用户取消勾选的可能

### 在 GitHub 交互式合并

GitHub 可以轻松对代码进行 Review，在整个 PR 完成之后，我们可以直接点击绿色的合并按钮右侧的下拉菜单，选择 `Squash and merge` 来对整个 PR 进行合并，这样就可以将多个 commit 合并成一条 `main` 分支的 commit 了，保证了主线清爽的线性结构，也保证了主线的一个 commit 对应一个完整的功能（一次 PR）

## 团队协作模式

团队协作应当不止建立 `main` 与 `dev`，抛开额外的功能分支，每个人都应当从 `dev` 建立自己的分支

`main` 应当是一个相当稳定的分支，只有在 `dev` 新功能基本稳定后，才合并回 `main` 发版，团队各成员平时只允许向 `dev` merge

### 建立你自己的分支

```bash
git checkout dev
git checkout -b feature-xxx     # 新建一个你自己的分支
```

### 完成你的工作，并发起 PR

```bash
git commit
git push origin feature-xxx
```

之后在 GitHub 上向 `dev` 发起 PR 即可

### 同步更改

由于你的 `main` 与 `dev` 都是相当干净（自己没做过改动）的，你可以和前面一样 `fetch` 并 `merge` 即可

## References

1. [Git 常用命令和 Git Flow 梳理](https://www.cnblogs.com/ldy-blogs/p/10529946.html#4416607)
2. [git merge squash 和 rebase 区别](https://www.jianshu.com/p/684a8ae9dcf1)
3. [优雅地修改他人贡献的 Pull Request](https://liuyib.github.io/2020/09/19/add-commits-to-others-pr)
