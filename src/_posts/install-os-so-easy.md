---
title: 我与 OS 的时间之旅
date: 2020-07-06
category: 游
tags:
   - OS
   - Windows
   - diskpart
---

::: tip

近日 @Ainavo 找我加装固态，不过时间有限，没对他的 HDD 进行备份以及格式化，结果果然出大问题了……Windows 直接用了原来 HDD 上的 EFI 引导，SSD 上就只有个系统分区……经过查阅各种资料，只得重新在 SSD 上建立了一个新的 EFI 启动分区，这才解决了该问题

:::

<!-- more -->

## 装操作系统如此简单

### 装 Windows 如此简单

第一次自己装操作系统大概是<span title="2018-01-21">两年半以前</span>自己组装了家里的第一台台式机（万恶之源，没有它的话我现在大概率还在学材料），硬件的组装只花了两小时，系统安装花掉我六个多小时……按照网上各种各样花里胡哨的教程进行安装，结果都没成功，大多数的时间都花在了镜像的下载与写入上……

那么……最终成功的那次到底是怎么安装上的呢？当然是直接去[官网](https://www.microsoft.com/zh-cn/software-download/windows10ISO)下载啦……然后直接写入 U 盘，之后重新启动，在启动开始时按“某个按键”进入 BIOS 界面（不同主板按键不同……一般是 `F1~F12` 以及 `Delete` 键，有些笔记本的 `F?` 需要同时按住 `Fn` 键才可以），将 U 盘启动项调整到最上面并保存就好啦；或者直接进入启动项界面，从 U 盘启动

启动之后呐……就直接一步一步往下走就好啦～超容易的说

### 装 Deepin 如此简单

有了装 Windows 的经验，再装什么都感觉很简单了嘛，也就是

-  做启动 U 盘
-  重启使用 U 盘启动
-  按照引导一步一步来

就……OK 啦，deepin 的安装可以说基本上借鉴了 Windows 的流程，事实上 Deepin 为了让 Windows 用户能够轻松过渡到自己的操作系统，在用户接口上做了太多的优化，使得用 Deepin 就像直接用 Windows 似的……不过这也比较适合初次接触 Linux 的人啦

装过 Windows 之后一段时间，喜欢折腾的我便在自己的笔记本上装了个 Deepin，不过由于 Deepin 笔记本耗电更高一些，而我又习惯在熄灯后码代码到没电，因此 Deepin 一直失宠，此后我还装了个 Ubuntu，不过是同样的下场

### 装 Manjaro 如此简单

装 Manjaro 已经是前几个月的事情啦，疫情期间不能返校，在家可就没熄灯这回事咯，Manjaro 顺势变成了我的主操作系统，至于[安装](./first_experience_for_Manjaro.md)嘛……我也是重装过好几次了，在此期间也就简单了解了 Linux 各目录的挂载问题（当然也可以自动分区啦）

先简单了解下各个目录分别用来做什么

-  /root

   该目录为系统管理员，也称作超级权限者的用户主目录。

-  /home

   用户的主目录，在 Linux 中，每个用户都有一个自己的目录，一般该目录名是以用户的账号命名的。

-  /boot

   这里存放的是启动 Linux 时使用的一些核心文件，包括一些连接文件以及镜像文件。

-  /media

   linux 系统会自动识别一些设备，例如 U 盘、光驱等等，当识别后，linux 会把识别的设备挂载到这个目录下。

-  /mnt

   系统提供该目录是为了让用户临时挂载别的文件系统的，我们可以将光驱挂载在 `/mnt/` 上，然后进入该目录就可以查看光驱里的内容了。

-  /opt

   这是给主机额外安装软件所摆放的目录。比如你安装一个 ORACLE 数据库则就可以放到这个目录下。默认是空的。

-  /bin

   bin 是 Binary 的缩写, 这个目录存放着最经常使用的命令。

-  /var

   这个目录中存放着在不断扩充着的东西，我们习惯将那些经常被修改的目录放在这个目录下。包括各种日志文件。

-  /tmp

   这个目录是用来存放一些临时文件的。

-  /dev

   dev 是 Device(设备) 的缩写, 该目录下存放的是 Linux 的外部设备，在 Linux 中访问设备的方式和访问文件的方式是相同的。

-  /etc

   这个目录用来存放所有的系统管理所需要的配置文件和子目录。

-  /lib

   这个目录里存放着系统最基本的动态连接共享库，其作用类似于 Windows 里的 DLL 文件。几乎所有的应用程序都需要用到这些共享库。

-  /lost+found

   这个目录一般情况下是空的，当系统非法关机后，这里就存放了一些文件。

-  /proc

   这个目录是一个虚拟的目录，它是系统内存的映射，我们可以通过直接访问这个目录来获取系统信息。

   这个目录的内容不在硬盘上而是在内存里，我们也可以直接修改里面的某些文件，比如可以通过下面的命令来屏蔽主机的 ping 命令，使别人无法 ping 你的机器：

   ```bash
   echo 1 > /proc/sys/net/ipv4/icmp_echo_ignore_all
   ```

-  /sbin

   s 就是 Super User 的意思，这里存放的是系统管理员使用的系统管理程序。

-  /selinux

   这个目录是 Redhat/CentOS 所特有的目录，Selinux 是一个安全机制，类似于 Windows 的防火墙，但是这套机制比较复杂，这个目录就是存放 selinux 相关的文件的。

-  /srv

   该目录存放一些服务启动之后需要提取的数据。

-  /sys

   这是 linux2.6 内核的一个很大的变化。该目录下安装了 2.6 内核中新出现的一个文件系统 sysfs 。

   sysfs 文件系统集成了下面 3 种文件系统的信息：针对进程信息的 proc 文件系统、针对设备的 devfs 文件系统以及针对伪终端的 devpts 文件系统。

   该文件系统是内核设备树的一个直观反映。

   当一个内核对象被创建的时候，对应的文件和目录也在内核对象子系统中被创建。

-  /usr

   这是一个非常重要的目录，用户的很多应用程序和文件都放在这个目录下，类似于 Windows 下的`program files` 目录。

-  /usr/bin

   系统用户使用的应用程序。

-  /usr/sbin

   超级用户使用的比较高级的管理程序和系统守护程序。

-  /usr/src

   内核源代码默认的放置目录。

-  /run

   是一个临时文件系统，存储系统启动以来的信息。当系统重启时，这个目录下的文件应该被删掉或清除。如果你的系统上有 /var/run 目录，应该让它指向 run。

大多数看名字还是能猜到是用来干嘛的，那么，在装 Manjaro 进行分区时，我们可以为几个目录单独设置分区，以保证重装系统时不影响这些目录

-  /boot - 512MB
-  /var - 8-12GB

   存储变量以及日志，读写频繁，但只是缓存而已，可放心清理

-  swap - 4-8GB

   linuxswap 文件系统，也就类似于 Windows 的虚拟内存

-  / - 15-20GB

   也就是挂载其他部分咯

-  /home - 剩余空间

   个人目录，多大都可以咯

另外可以直接将 Windows 的 EFI 分区挂载到 `/boot/efi`，这样新的引导将直接建立在 Windows 原有的引导分区内

## 系统迁移到固态上的两三事

### 直接使用软件迁移

emmm，非常不建议，<span title="2018-08-30">两年前</span>我给自己笔记本装完固态后直接使用软件迁移的 Windows，此后出现了很多莫名其妙的问题，之后我<span title="2018-09-30">回家</span>的第一件事就是重装系统

### 分区格式不对

大概是当初我没有开启 UEFI 启动，导致无法在 GPT 分区的 SSD 上直接装操作系统，因此我不得不了解了下 Diskpart 这个命令行工具，首先了解下为什么不开启 UEFI 无法在 GPT 上装操作系统

传统硬盘采用 MBR（Master Boot Record，主引导记录）分区方式引导操作系统，与之配套使用的是 BIOS（Basic Input Output System，基本输入输出系统）主板，随着技术和需求的不断发展，GPT（GUID Partition Table，全局唯一标识分区表）硬盘及 UEFI（Unified Extensible Firmware Interface，统一可扩展固件接口）主板逐渐流行，后者现已常见并将成为今后的主流方向。BIOS 只支持 MBR 格式的分区，而 UEFI 则同时支持 GPT 和 MBR 格式的分区

那么如果格式不对的话，转换一下就好啦，可以回到 Windows 在磁盘管理里进行转换，或者直接使用管理员模式打开命令行，在命令行中输入 `diskpart` 进行分区管理，但……如果已经回不到原来的 Windows 的话，直接在系统安装引导界面按下 `Shift + F10` 也能进入命令行，输入 `diskpart` 即可

```powershell
diskpart
DISKPART> lisk disk              # 列出全部硬盘，找到需要修改的硬盘号
DISKPART> select disk <SSD_ID>   # 选择该硬盘
DISKPART> clean                  # 清空磁盘分区
DISKPART> convert mbr            # 将当前磁盘分区设置为 MBR 形式
DISKPART> create partition primary size=<Size> align=1024
                                 # 建立主分区，可设置分区大小，如果不设置则默认对剩余全部空间进行分区
DISKPART> select partition 1     # 现在应该也就这么一个分区，不放心可以 list partition 看一下嘛
DISKPART> format fs=ntfs unit=4096 quick
                                 # 快速格式化，系统为 ntfs，并进行 4K 对齐
DISKPART> exit                   # 退出 diskpart
exit                             # 退出 cmd
```

这样就使用 diskpart 进行了简单的分区操作啦

不过在这次装系统的过程中我是直接把整个 HDD 全格掉了，当然数据做了备份，备份时使用的是局域网，而传回去的时候没配置好局域网就直接使用 U 盘了，结果 U 盘坏掉了……数据还损失了不少……

### 新的硬盘没有 EFI 引导

两年过去了，也并非一帆风顺，去年开学前两周做的课设答辩的前一天我的系统崩了……然后不得不重做了下系统，在此过程中又废了一个 U 盘……结果桌面上的文件忘记了备份（没错就是答辩需要的文件……），答辩自然是很惨，从那以后我的桌面再也不放文件了（那次真的是个意外，那之前我也不常放的，只不过那时候还没想好放在哪里就先丢在桌面了）……

时间线回到今天，给 @Ainavo 装的时候来不及像我那样给 HDD 进行备份了，结果没有清除 HDD 的引导，Windows 居然直接用了 HDD 上的引导了，这导致每次开机都会出现“你的电脑/设备需要恢复”，经过一番检查发现 SSD 上根本没有新的 EFI 引导分区，BIOS 并没出现新的引导项

emmm，也不想重装系统，而且他回家也没 U 盘能够重装，要怎么办呢？不如，我们自己新建个引导项吧～

```powershell
diskpart
DISKPART> select disk <SSD_ID>            # 选择 SSD
DISKPART> select partition <PART_ID>      # 选择要压缩的分区，将从该分区中分出一部分作为 EFI 分区
DISKPART> shrink desired=300              # 分出 300MB 作为 EFI 分区
DISKPART> create partition efi size=300   # 创建 EFI 分区，当然如果只有这 300 MB 空闲空间的话不需指定 size
DISKPART> format fs=fat32 quick           # 格式化
DISKPART> assign letter=s                 # 分配卷标为 S，当然可以随便改
DISKPART> exit                            # 退出 diskpart
bcdboot C:\windows /s S:                  # 建立新的引导，从 S 卷的 EFI 分区引导到 C 盘下的系统文件夹
exit                                      # 退出 cmd
```

大功告成～重启就可以发现 BIOS 有新的引导了，将新的引导移到第一位即可默认启动在 SSD 上的 Windows 咯～

## References

1. [Linux 系统目录结构](https://www.runoob.com/linux/linux-system-contents.html)
2. [硬盘分区、挂载及 Ubuntu 系统安装](https://blog.csdn.net/hurry0808/article/details/78882111)
3. [U 盘安装 WIN10 时显示 windows 无法安装到这个磁盘 选中的磁盘采用 GPT 分区形式](https://answers.microsoft.com/zh-hans/windows/forum/windows_10-update/u%E7%9B%98%E5%AE%89%E8%A3%85win10%E6%97%B6/f6c8e140-2a36-4859-afee-ca7abfb796c7)
4. [manjaro 安装分区以及配置方案](https://blog.csdn.net/lj402159806/article/details/80218360)
5. [Windows 无法安装到 GPT 分区形式磁盘，怎么办？](https://jingyan.baidu.com/article/08b6a591c82df414a8092224.html)
6. [SSD 固态硬盘 4K 怎么对齐 SSD 固态硬盘 4K 对齐方法](https://zhuanlan.zhihu.com/p/71386318)
7. [迁移 win10 的 efi 引导分区到系统固态硬盘](https://blog.csdn.net/Sebastien23/article/details/99691881)
8. [新加装的硬盘，装上系统后发现 EFI 分区没有被创建，还是用旧硬盘的 EFI 分区](https://blog.csdn.net/u013580080/article/details/51754486)
9. [电脑基础知识普及：BIOS、EFI 与 UEFI 详解！](https://zhuanlan.zhihu.com/p/54108702)
