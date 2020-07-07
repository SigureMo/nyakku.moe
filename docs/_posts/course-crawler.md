---
title: 如何轻松下载各种慕课课程
date: 2019-08-25
category: 游
tags:
   - Python
   - Crawler
---

::: tip
虽然网上有很多 MOOC 课程，但是大多不支持下载，在线播放总会出现各种各样的问题

-  卡顿，看一会加载一会
-  播放器出问题，明明关闭了还有声音，甚至出现“二重奏”（说的就是你，中国大学 MOOC）
-  反复看同一个视频，每次都要重新加载
-  ...

为了克服以上困难，这里介绍一个非常好用的 MOOC 课程下载程序，支持各大主流 MOOC 平台并支持下载各种资源（视频、文档、附件等等）
:::

<!-- more -->

-  预备知识
   -  零基础
-  开发环境
   -  `python 3.6`
      -  `requests`
      -  `BeautifulSoup4`
      -  `lxml`
      -  `pycryptodome`
   -  `Chrome`
-  [项目地址](https://github.com/SigureMo/course-crawler)
-  [项目文档](https://sigure.xyz/course-crawler/)

## 支持的课程

-  [中国大学 MOOC](https://www.icourse163.org/)
-  [网易云课堂](http://study.163.com/)
   -  [普通课程](http://study.163.com/)
   -  [MOOC 课程](http://mooc.study.163.com/)
-  [网易公开课](https://open.163.com/)
-  [好大学在线](https://www.cnmooc.org/)
-  [爱课程](http://www.icourses.cn/)
   -  [视频公开课](http://www.icourses.cn/cuoc/)
   -  [资源共享课](http://www.icourses.cn/mooc/)
-  [学堂在线](http://www.xuetangx.com/)
-  [北京高校优质课程研究会](http://www.livedu.com.cn/)

## 快速开始

### 准备工作

在下载之前，你需要保证你已经安装 `python3.5` 及其以上版本，并且安装完成依赖

需要的依赖如下

-  `requests`
-  `BeautifulSoup4`
-  `lxml`
-  `pycryptodome`

```bash
pip install requests BeautifulSoup4 lxml pycryptodome
```

### 下载程序源码

前往项目主页下载程序，或者直接点击[这里](https://github.com/SigureMo/course-crawler/archive/master.zip)，之后解压

当然，已经安装 `git` 的同学可以直接 `clone`

```bash
git clone https://github.com/SigureMo/course-crawler.git
```

### 运行程序

在刚刚下载的项目根目录下打开命令行（“终端”、“命令提示符”、“PowerShell”都行，`Win10` 在项目根目录按住 `shift` 右键就有相应的选项，后面统称命令行）

在命令行中输入 `python mooc.py <url>` ，即可将课程课件下载到当前文件夹

比如，中国大学 MOOC 课程 `《高等数学（一）》 - 同济大学`

```bash
python mooc.py https://www.icourse163.org/course/TONGJI-53004
```

::: tip
这里的 `<url>` 为课程主页的地址，网址的具体要求及课程下载的额外要求详见[分类](https://sigure.xyz/course-crawler/courses/icourse163.html)
:::

### 身份验证

很多课程并不是直接就能下载的，需要验证下你的身份，这大多都可以通过输入 Cookies 解决

当你下载的课程需要输入 Cookies 时，用浏览器打开课程主页，然后按下 `F12` 打开开发者工具

切换到 `Network` 选项卡，刷新页面，在左侧选择第一个抓到的包，在右侧 `Headers` 中找到 `cookie` （也可能是 `Cookie`），复制粘贴到程序命令行中

![get_cookies.png](https://raw.githubusercontent.com/SigureMo/course-crawler/docs/images/get_cookies.png)

::: tip
如果你和我一样懒的话，可以直接三击 cookies 快速将整个 cookies 及前面的 `cookie:` 一起选中，直接复制粘贴到程序中，也是可以的，反正我是懒得从左上滑到右下啦，所以特意做了这个小“优化”~
:::

### 等待 ...

等待程序运行，程序首先会从课程主页获取课件列表及解析所需相关信息，之后逐个课件进行解析下载

### 下载视频

特别地，由于视频资源相对来说花费时间较多，所以视频资源并不是在解析时直接进行下载，而是解析出 `url` 至 `<course>/Videos/Videos.txt` ，之后需要你自行使用下载工具进行下载（比如 `aria2` ，或者迅雷等）

::: tip
这里的 `<course>` 指课程根目录
:::

下载后将视频移动到 `<course>/Videos/` 内，之后运行 `Rename.bat` 或者 `Rename.sh` 即可修正视频名

### 视频的播放

使用 `PotPlayer` 打开 `Playlist.dpl` 即可播放视频

## 进阶使用

### 直接下载视频

增加参数 `--download-video` 即可

示例

```bash
python mooc.py --download-video https://www.icourse163.org/course/TONGJI-53004
```

### 修改存储目录

使用参数 `-d` 指定存储目录，默认存储为当前目录

示例

```bash
python mooc.py https://www.icourse163.org/course/TONGJI-53004 -d "G:\MOOCs"
```

> 更多参数请参见[项目文档](https://sigure.xyz/course-crawler/)

## 推荐

-  [mooc-dl](https://github.com/SigureMo/mooc-dl) 使用手机端接口的中国大学 MOOC 课件爬虫
-  [bilili](https://github.com/SigureMo/bilili) B 站视频爬虫
