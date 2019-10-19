---
title: Diskpart 的简单使用
date: 2018-10-01
categories:
   - 雁影·留
tags:
   - OS
   - Windows
---

::: tip

前段时间装了 SSD 后使用软件直接迁移的系统，之后出现了很多问题（比如经常莫名其妙音频服务未运行），所以昨晚一回到家就把硬盘通过局域网备份到另外一台电脑上，开始重装（emmm 我是想把 HHD 的混乱分区也弄一下的）。

做完系统 U 盘并设为启动盘后就进入了熟悉的界面啦，但是这次选择分区不顺利呀，“Windows 无法安装到 GPT 分区形式磁盘”，这要怎么办呀？搜了下，了解到了 diskpart 这个小工具。下面就介绍下简单的使用方法啦

:::

<!-- more -->

## 如何使用？

1. 在那一步按住“shift + F10”，便出现了 CMD 命令行
2. 输入`diskpart`，进入 diskpart
3. 输入`list disk`，列出所有硬盘，这些是物理上的啦
4. 输入`select disk <DiskNum>`，选择上面那些硬盘中的一个，选中那个需要格式化的就好
5. 输入`clean`，删除磁盘分区
6. 输入`convert mbr`，将当前磁盘分区设置为 Mbr 形式
7. 输入`create partition primary size=<Size>`，创建主分区大小（MB）
8. 输入`format fs=ntfs quick`，格式化磁盘为 ntfs
9. 输入`exit`，退出 diskpart
10.   输入`exit`，退出 cmd

## 关于 4K 对齐

emmm，上面都摘自 Reference，因为之前稍稍了解到 4K 对齐，所以我对这个还是有执念的，经过一番搜索，发现只需要加`align=4096`参数就好，而且 size 参数也可以省略的，也就是，Step7 使用`create partition primary align=4096`替换

剩下的不用说啦，一步一步照着做就好啦，但是后来我把备份往回迁移时候局域网没弄好，用 U 盘传的时候把 U 盘废掉了，低格都救不了了 o(╥﹏╥)o

# Reference

1. [Windows 无法安装到 GPT 分区形式磁盘，怎么办？](https://jingyan.baidu.com/article/08b6a591c82df414a8092224.html)
