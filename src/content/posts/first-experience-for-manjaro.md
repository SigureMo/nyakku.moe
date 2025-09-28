---
title: Manjaro 初体验
published: 2020-04-06
category: 找点好玩的
tags:
   - Linux
   - Manjaro
---

:::tip

虽然此前也接触 Linux 很久了，但平时也只是作为备用系统偶尔用用罢了，之前也用过一段时间 deepin，但是有很多细节上有 bug，一段时间后还是将 Windows 作为我的主力系统了。

前段时间了解到了 Manjaro 这个 Linux 发行版，可以非常方便地安装软件，所以决定尝试一下下～

:::

<!-- more -->

```

 ██████████████████  ████████     nyakku@shigure-yuu
 ██████████████████  ████████     OS: Manjaro 21.3.5 Ruah
 ██████████████████  ████████     Kernel: x86_64 Linux 5.15.55-1-MANJARO
 ██████████████████  ████████     Uptime: 4m
 ████████            ████████     Packages: 1175
 ████████  ████████  ████████     Shell: zsh 5.9
 ████████  ████████  ████████     Disk: 13G / 94G (14%)
 ████████  ████████  ████████     CPU: Intel Core i5-7500 @ 4x 3.8GHz [35.0°C]
 ████████  ████████  ████████     GPU: NVIDIA GeForce GTX 1050
 ████████  ████████  ████████     RAM: 964MiB / 7913MiB
 ████████  ████████  ████████
 ████████  ████████  ████████
 ████████  ████████  ████████
 ████████  ████████  ████████

```

## Manjaro 的安装

首先在[官网下载](https://manjaro.org/download/)镜像，我选择的桌面环境是 KDE Plasma。使用 [Ventoy](https://github.com/ventoy/Ventoy) 制作一个启动盘，然后用 U 盘启动即可。

U 盘启动后会有时区、键盘、语言的配置，之后的 Boot 不是配置项，在选择它之前先修改下前几项

```
tz = Asia/Shanghai
keytable = us
lang = zh_CN
```

由于深度学习的显卡加速需要闭源驱动，因此选择 `Boot with proprietary drivers` 来启动

之后会进入桌面环境，会有些配置选项，这些简单配置下就好，其中分区需要注意一下，最好手动分区一下

- `/` 15-20GB 根目录，由于包含 `/usr` 所以会有安装的各种软件，不能太小
- `/boot` 512MB
- `/var` 8-12GB，主要是缓存，读写频繁
- `swap` 4GB，交换分区
- `/home` 剩余全部

再之后直接安装就好啦～静待片刻，Manjaro 之旅就正式开始啦～

## 换源

二话不说，先换个源

```bash
sudo pacman-mirrors -i -c China -m rank   # 更新镜像排名
sudo pacman -Syy                          # 更新数据源
```

添加 `archlinuxcn` 镜像，在 `/etc/pacman.conf` 中添加以下内容

```
[archlinuxcn]
Server = https://mirrors.ustc.edu.cn/archlinuxcn/$arch
```

> 更多镜像见 [mirrorlist-repo](https://github.com/archlinuxcn/mirrorlist-repo)

## 安装软件

### 使用 pacman 安装

`pacman` 是 Manjaro 下的软件包管理器，有点类似于 Ubuntu 下的 `apt`，只不过参数稍稍不一样，安装软件需要这样

```bash
sudo pacman -S <package_names>
```

### 使用 yay 安装

`yay` 是 AUR 仓库的包管理器，那么什么是 AUR 呢？AUR 是 Arch 的社区维护软件仓库，而不是官方的，所以如果 `pacman` 有下不到的软件可以使用 `yay` 试一下

用 `yay` 之前先开启 AUR，软件包管理器 -> 首选项 -> 第三方 -> 启用 AUR 支持

之后需要安装 `yay`

```bash
sudo pacman -S yay
```

然后就可以使用 `yay` 愉快地安装各种软件啦

```bash
yay -S <package_name>
```

### 安装 deb 包

有些软件只提供 debian 系的包，但我们可以使用 debtap 将其转换为 Arch package（debtap 是 DEB To Arch (Linux) Package 的缩写），然后再进行安装

```bash
# 安装 debtap
yay -S debtap
# 更新 debtap
sudo debtap -u
# 使用 debtap 进行转换（Licence 可以填 GPL）
sudo debtap <package_name>.deb
# 使用 pacman 安装
sudo pacman -U <package_name>.tar.xz
```

### 一些常用软件及安装方式

- vim

   ```
   sudo pacman -S vim
   ```

- Sunpinyin

   听说 Linux 版搜狗输入法有点问题，之前在 Deepin 下确实遇到些 Bug，所以就不选了，这里用 `Sunpinyin` 配合 `Cloudpinyin`，在那之前需要先安装输入法管理器 `fcitx`

   ```
   sudo pacman -S fcitx-im
   sudo pacman -S fcitx-configtool
   sudo pacman -S fcitx-sunpinyin
   sudo pacman -S fcitx-cloudpinyin
   ```

   并将以下内容添加到 `/etc/profile`

   ```
   export GTK_IM_MODULE=fcitx
   export QT_IM_MODULE=fcitx
   export XMODIFIERS="@im=fcitx"
   ```

   之后在 fcitx 将 `Sunpinyin` 调整为第二输入法并移除多余输入法即可

- chrome

   ```
   yay -S google-chrome
   ```

- spotify

   ```bash
   yay -S spotify
   ```

- vscode

   ```bash
   yay -S visual-studio-code-bin
   ```

- WPS

   ```bash
   yay -S wps-office
   yay -S ttf-wps-fonts
   ```

- flameshot

   ```bash
   yay -S flameshot
   ```

- simplescreenrecorder

   ```bash
   yay -S simplescreenrecorder
   ```

## 美化

### Shell 美化

zsh 相对于 bash 拥有更强的功能，而且也更加美观

参考 [`os-my-zsh` 官网](https://ohmyz.sh/)，输入下面的命令就可以美化优化 zsh 了

```
sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
```

然后编辑 `~/.zshrc`，修改下主题就能拥有更加美观的 zsh 了（暂时使用的是 `agnoster`）

:::tip

有些主题在 VS Code 里不能正确显示，需要修改下 Terminal 的字体，我改成了 `Menlo for Powerline`，如果没有该字体，下载并安装下即可

```bash
git clone https://github.com/abertsch/Menlo-for-Powerline.git  # 下载字体
cd Menlo-for-Powerline
sudo cp *.ttf* /usr/share/fonts/TTF/                           # 手动安装到字体文件夹
sudo fc-cache -f -v                                            # 刷新字体
```

之后修改 VS Code Settings 中 Terminal 的 Font Family 即可

:::

### Dock

首先安装一个 `Dock`

```bash
sudo pacman -S latte-dock
```

略作配置即可

现在底部的面板就有点多余了，移到上面去～然后将无用的部件也都去掉

### 主题更换

KDE 的主题更换都超简单，直接在设置里就能完成

设置 -> 系统设置 -> 外观 -> 全局主题

在这里不仅可以修改主题，还可以在主题库中搜索主题哦，更重要的是，不止全局主题可以，鼠标样式、图标样式等等都可以在丰富的库中寻找资源，一键即可美化系统～

## 一些小问题

### 双系统时间差问题

由于 Windows 与 Linux 显示时间的方式不太一样，所以每次切换系统总是需要改一下时间，如果让这两个系统任意一个妥协使用对方的计时标准即可，这里因为 Manjaro 操作方便，就在 Manjaro 修改了

```bash
sudo timedatectl set-local-rtc true
```

### 卡在开机界面

emmmm，刚折腾一天把所有基本该折腾的折腾完了，我突然想把 Krunner 给卸了，然后居然把整个 KDE 给卸了，结果再开机我就卡在登陆界面了

为了能够重新安装 KDE，首先需要进入终端，在卡住的界面按 <kbd>Ctrl</kbd> + <kbd>Alt</kbd> + <kbd>F4</kbd> 进入 tty4，然后输入用户名和密码登陆

为了能够联网下载，需要使用 `ifconfig` 开启无线网卡，但如果 `ifconfig` 也没有安装怎么办……一种解决方法是通过数据线将 Android 手机与电脑相连接，在手机上开启 USB 共享网络即可

之后重装 KDE 并重启就又看到了熟悉的开机界面了

## References

1. [Manjaro 美化与调优](https://juejin.im/post/5c6d0a1051882561ad329255)
2. [Manjaro-KDE 美化](https://www.bilibili.com/video/BV1pJ411N75i)
3. [manjaro 安装 deb 包](https://zhuanlan.zhihu.com/p/83335242)
4. [如何解决 Windows 和 Manjaro 双系统时间差 8 小时的问题](https://www.itdaan.com/blog/2017/12/02/2be8e9eaf332561e7ed94c35ba57e757.html)
5. [安装 Manjaro Linux 的详细步骤](https://ywnz.com/linuxaz/3504.html)
6. [记 manjaro 图形驱动删除后的一次补救](https://www.cnblogs.com/comixH/p/12232252.html)
7. [manjaro 安装分区以及配置方案](https://blog.csdn.net/lj402159806/article/details/80218360)
8. [调教你的 manjaro，配合微信、TIM 食用，让它比 windows 还好用！](https://www.bilibili.com/video/av60476406/)
9. [Manjaro 下 vscode 中 zsh 乱码](https://www.jianshu.com/p/c2f8bc4e19c0)
