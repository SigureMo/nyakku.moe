---
title: 使用 Python 爬取 B 站视频
date: 2019-08-18
categories:
   - 趣笔·书
tags:
   - Python
   - Crawler
---

::: tip
好歹也是玩过挺久资源型爬虫的，但是却一篇文章都没有写，也许时间久了就忘了的说，这里将 B 站爬虫程序单独拿出来重新写一遍，并且记录一下探索流程

注：仅限个人学习和研究使用，切勿用于其他用途
:::

<!-- more -->

-  预备知识
   -  Python 基本语法
   -  requests 库的基本使用
-  开发环境
   -  `python 3.6`
      -  `requests`
   -  `ffmpeg`
   -  `Chrome`
-  [项目地址](https://github.com/SigureMo/bilili-dl)

## 探索

> 如果仅仅是使用的话，请跳到[使用方法](#使用方法)

### 查看 Robots 协议

遵守业界规范，首先查看[其 robots 协议](https://www.bilibili.com/robots.txt)

可以发现仅有几个 api 是限制使用的，这里先记着，后面看是否会用到它们（并没有）

### 普通视频的爬取

仔细分析我们可以发现 B 站视频主页主要有两种，一种是普通视频，另一种是番剧，下面分别对这两种视频进行分析爬取

普通视频的 url 如

```
https://www.bilibili.com/video/av6538245
```

在该页面下的`视频选集`一栏中可以看到视频列表

首先 `F12` 打开开发者模式，切换到 `Network` 栏下并刷新页面（最好右键刷新按钮`选择清空缓存并影星重新加载`），在抓到的包中分别搜索 `.mp4` 与 `.flv` ，可以搜到类似于如下的 `url`

```
http://upos-hz-mirrorks3u.acgvideo.com/upgcxcode/97/67/10636797/10636797-1-32.flv?e=ig8euxZM... ...
```

搜索其来源，可以得到一个视频 url 获取接口

```
https://api.bilibili.com/x/player/playurl?avid={avid}&cid={cid}&qn={sp}&type=&otype=json
```

也就是说只要有 `avid` 、 `cid` 以及 `sp` 就可以获取视频，通过分析可以得知 `avid` 即为主页 url 中尾部数字，而 `sp` 代表了清晰度，代码对应情况如下

-  80: 高清 1080P
-  64: 高清 720P
-  32: 清晰 480P
-  16: 流畅 360P

所以一个视频只需要字段 `cid` 就可以解析其地址了，可以很容易找到 `cid` 等信息的解析接口

```
https://api.bilibili.com/x/player/pagelist?aid={avid}&jsonp=jsonp
```

这个接口可以得到所有视频的 `cid` 以及标题信息，值得注意的是，每个视频其实是分为多个片段的，所以我们需要分别下载各个视频片段，之后使用 `ffmpeg` 进行合并

### 番剧的下载

番剧的 url 如

```
https://www.bilibili.com/bangumi/media/md1733
```

同样地，可以搜到视频 url 解析接口为

```
https://api.bilibili.com/pgc/player/web/playurl?avid={avid}&cid={cid}&qn={sp}&ep_id={ep_id}
```

而 `aid` 与 `cid` 的解析接口为（这里 `aid` 并不是主页 url 尾部数字，每个视频的 `aid` 与 `cid` 都是不同的，所以都需要重新解析）

```
https://api.bilibili.com/pgc/web/season/section?season_id={season_id}
```

### 爬虫请求的模拟

值得注意的是，B 站视频主页直接爬取是不能获得 HTML 的（返回 403），通过对抓到的 Headers 进行筛选，可以发现以下字段是必须的

```python
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.167 Safari/537.36',
    'Referer': 'https://www.bilibili.com',
}
```

## 使用方法

### 项目下载

项目主页下载或者直接[点击链接](https://github.com/SigureMo/bilili-dl/archive/master.zip)

### 快速开始

`bilili-dl` 可以从以下两种视频主页获取视频

-  普通视频： `https://www.bilibili.com/video/avxxxxxx`
-  番剧视频： `https://www.bilibili.com/bangumi/media/mdxxxx`

在下视频之前，首先要配置好 `ffmpeg` ，随便在网上下一个就好，存放在 `/ffmpeg/ffmpeg.exe` （也可以存放在其他路径，之后在参数中指定路径即可）

下载的方式很简单，只需要在终端中运行如下命令即可

```bash
python bilili-dl.py <url>
```

需要将 `<url>` 替换为前面的视频主页 url

### 更多参数

`bilili-dl` 还支持很多参数，具体如下

-  `-d` 指定存储目录，默认为根目录
-  `-r` 指定清晰度，默认为 80，对应关系如下
   -  80 # 高清 1080P
   -  64 # 高清 720P
   -  32 # 清晰 480P
   -  16 # 流畅 360P
-  `-t` 指定最大下载线程数，默认为 10
-  `--playlist-type` 指定播放列表类型，支持 dpl 和 m3u ，默认为 dpl
-  `--path-type` 指定播放列表路径的类型（rp：相对路径，ap：绝对路径），默认为相对路径
-  `--ffmpeg` 指定 `ffmpeg` 存放路径，默认为 `ffmpeg/ffmpeg.exe`

# Reference

1. [Bilibili 视频爬取](https://github.com/1033020837/Bilibili)
