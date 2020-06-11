---
title: 使用 git-filter-repo 清理 git 历史记录
date: 2020-06-12
category: 迹
tags:
   - Git
---

::: tip

有时候 Git 不小心提交了一些二进制文件，当随着 repo 越来越庞大，二进制文件就会像滚雪球一般越来越多，而且即便删除掉这些二进制文件，仍然会存在于历史之中，为了解决该问题，就需要一些针对二进制文件的处理手段啦～

:::

<!-- more -->

## Git LFS

Git LFS 是 github 推出的大文件存储服务，它是让 git 只保存二进制文件的 hash，而二进制文件将会存在 Git LFS 服务器中，当然，这可以有效防止 Git 历史的增长，但……免费只有 1G 空间，而且每月还限 1G 带宽，虽然看起来挺大的，但有一个月我频繁更新博客，CI 频繁地从 LFS 获取图片，结果居然真的差点就用到了 1 个 G 的带宽……之后我就开始另寻他法……

## 定期清理 Git 历史

定期清理的话，虽然麻烦，但也最实用，在使用 LFS 之前我也定期清理过，是使用的 git-filter-branch，但由于嫌麻烦，就改用 LFS 了，至于为什么不用 BFG，因为懒得装 JDK

弃用 LFS 后，我仍然使用 git-filter-branch，不过实在是麻烦，每次清理我需要运行好多命令，比如清理全部 `*.jpg` 图片，我需要

```bash
git filter-branch --force --index-filter \
'git rm --cached --ignore-unmatch -r *.jpg' \
--prune-empty --tag-name-filter cat -- --all
rm -rf .git/refs/original/
git reflog expire --expire=now --all
git gc --prune=now
git gc --aggressive --prune=now
git push origin master --force
```

emmm，就很麻烦

最近，使用 `git filter-branch` 会提示 `warning`，推荐使用 `git filter-repo`，于是就试着搜了下，这居然是 python 实现的清理器，拥有远比 `git filter-branch` 更加方便的使用方法，所以我在尝试了一下下就果断转 `git filter-repo` 了

在使用之前需要先使用 pip 安装一下

```bash
pip3 install git-filter-repo
```

使用 `git filter-repo` 清理全部 `*.jpg` 只需要

```bash
git filter-repo --path-glob '*.jpg' --invert-paths
```

不仅命令简单，而且速度超快，只不过不能像 `git filter-branch` 一样清楚地了解都清理了哪些文件了

当然，这只是 `git filter-repo` 的一个最简单的应用啦，更多使用技巧还是要看文档的～

# Reference

1. [git-filter-repo GitHub](https://github.com/newren/git-filter-repo)
2. [git-filter-repo Manual Page](https://htmlpreview.github.io/?https://github.com/newren/git-filter-repo/blob/docs/html/git-filter-repo.html#EXAMPLES)
