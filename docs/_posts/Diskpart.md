---
title: Diskpart 的简单使用
date: 2018-10-01
category: 迹
tags:
   - OS
   - Windows
---

::: tip

前段时间装了 SSD 后使用软件直接迁移的系统，之后出现了很多问题（比如经常莫名其妙音频服务未运行），所以昨晚一回到家就把硬盘通过局域网备份到另外一台电脑上，开始重装（emmm 我是想把 HDD 的混乱分区也弄一下的）

做完系统 U 盘并设为启动盘后就进入了熟悉的界面啦，但是这次选择分区并不是很顺利，粗现了“Windows 无法安装到 GPT 分区形式磁盘”的问题，为了解决该问题我了解到了 diskpark 这个小工具……

:::

<!-- more -->

## 使用方法

在分区时按下 `Shift + F10`，便出现了 CMD 命令行，此时输入 `diskpart` 即可进入 diskpart

```
lisk disk               # 列出全部硬盘，找到需要修改的硬盘号
select disk <DiskNum>   # 选择该硬盘
clean                   # 清空磁盘分区
convert mbr             # 将当前磁盘分区设置为 Mbr 形式，当然已经是的不需要了
create partition primary size=<Size> align=1024
                        # 建立主分区，可设置分区大小，如果不设置则默认对剩余全部空间进行分区
select partition 1      # 现在应该也就这么一个分区，不放心可以 list partition 看一下嘛
format fs=ntfs unit=4096 quick
                        # 快速格式化，系统为 ntfs，并进行 4K 对齐
exit                    # 退出 diskpart
exit                    # 退出 cmd
```

剩下的不用说啦，一步一步照着做就好啦，但是后来我把备份往回迁移时候局域网没弄好，用 U 盘传的时候把 U 盘废掉了，低格都救不了了 o(╥﹏╥)o

# Reference

1. [Windows 无法安装到 GPT 分区形式磁盘，怎么办？](https://jingyan.baidu.com/article/08b6a591c82df414a8092224.html)
2. [SSD 固态硬盘 4K 怎么对齐 SSD 固态硬盘 4K 对齐方法](https://zhuanlan.zhihu.com/p/71386318)
