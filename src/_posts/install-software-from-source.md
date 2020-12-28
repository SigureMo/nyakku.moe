---
title: Linux 上使用源码编译程序
date: 2020-03-06
category: 迹
tags:
   - Linux
---

::: tip

虽然 Linux 上的包管理器很方便，但是没有 root 权限时还是很头疼的，这就需要我们自己寻找软件源码自行编译咯~

下面以安装 `node-v12.16.1` 为例

:::

<!-- more -->

## 1 初始化环境

emmmm，因为我们要安装很多软件的嘛，那么首先考虑好把软件都安装到哪里，比如这里就安装在用户目录下的 `software` 下

```bash
mkdir ~/software
```

## 2 获取源码

自己去找需要的源码啦，用 `wget` 下载下来并且解压

```bash
wget https://nodejs.org/dist/v12.16.1/node-v12.16.1.tar.gz
tar -xvf node-v12.16.1.tar.gz -C node-v12.16.1/
```

## 3 配置安装目录

进入刚刚解压好的目录下，配置下安装到哪里

```bash
cd node-v12.16.1/
./configure --prefix=$HOME/software/node/
```

## 4 编译安装

```bash
make
make install
```

## 5 配置环境变量

编辑 `.bashrc`

```bash
vim ~/.bashrc
```

添加以下内容

```
export PATH="/home/username/software/node/bin:$PATH"
```

并重新 `source` 一下

```bash
source ~/.bashrc
```

## References

1. [linux 为某个用户安装程序](https://blog.csdn.net/qq_21280629/article/details/84962505)
