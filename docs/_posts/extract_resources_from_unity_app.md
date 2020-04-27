---
title: 记一次从 apk 中提取音乐资源的尝试
date: 2020-04-26
category: 游
tags:
   - Android
---

::: tip

最近非常喜欢某款游戏的音乐，但是尚未发布音乐集，所以就想试着自行提取一下

以下尝试仅是一个特例，不是通用的哦

:::

<!-- more -->

## 解压 apk

这个 apk 将扩展名改为 zip 直接解压就可以了，第一步完成的很顺利

## 找想要的资源

解压后的目录层次很清晰，我在 `assets/sound` 下找到了我想要的音乐，但是这些文件都是 `.dat` 的，尝试直接修改 `.wav`、`.m4a`、`.mp3` 均无效，所以开始尝试查看其二进制格式

使用 VSCode 插件 `hexdump` 查看其二进制内容，发现开头的关键字是 `UnityFS`，便知道该文件是使用 Unity 打包的文件，因此寻找解包方法

## 解包 Unity 文件

经过搜索找到了[AssetStudio](https://github.com/Perfare/AssetStudio)，直接在 releases 里下载就好，因为有 GUI，操作起来很方便，可以轻松将需要的内容解包出来，之后就可以愉快地享受音乐啦 (ฅ>ω<\*ฅ)
