---
title: 在个人 Blog 主页中添加各种联络链接
date: 2019-08-17
category: 游
tags:
   - front end
---

::: tip
个人 Blog 难免会添加一些联络方式，最**简洁**的方式就是每个联络方式弄一个链接啦，这样对方点击一下就可以查看/加好友了，当然简书、CSDN 之类都很简单，但是如果是 QQ 、微信就相对来说有点麻烦了，这里总结下如何添加 QQ 和微信的联络链接
:::

<!-- more -->

::: tip
当然，这些也可以直接留个 `ID` 更直接，但是会破坏各个链接的一致性，如果链接的内容只能是一个 `icon` 的话，那么这种方法会显得更加简洁方便
:::

## 点击发送邮件

```
mailto:<email_address>
```

将上面的 `<email_address>` 替换为你自己的邮箱地址即可，效果如下

<a href="mailto:sigure_mo@163.com">点击发送邮件</a>

手机或电脑会调用邮箱软件进行发送

## 点击添加 QQ 好友

```
tencent://AddContact/?fromId=45&fromSubId=1&subcmd=all&uin=<QQID>&website=www.oicqzone.com
```

将上面的 `<QQID>` 替换为你自己的 QQ 号即可，效果如下

<a href="tencent://AddContact/?fromId=45&fromSubId=1&subcmd=all&uin=240377379&website=www.oicqzone.com">点击添加 QQ 好友</a>

> 该方法在手机端测试无效

## 点击显示二维码

如果是手机 QQ 或者是微信的话，就不得不使用二维码了，这里以微信为例， QQ 同理

首先保存自己的二维码，随便搜一个在线二维码解码网址，比如[二维码解码器](https://jiema.wwei.cn/)，上传二维码可以解析得到一个网址，手机浏览器访问这个网址作为链接是无法添加好友的，所以就需要重新生成二维码，同样，找一个生成二维码的接口，比如

```
http://qr.topscan.com/api.php?text=<text>
```

将 `<text>` 替换为之前提取出来的网址即可，这样点击之后便会打开二维码图片，进而使用手机扫描加好友

<a href="http://qr.topscan.com/api.php?text=https://u.wechat.com/EPDjgRrQutXUU-K1XzT9X_0">扫描二维码添加好友</a>

::: tip
也许会有人觉得这是多此一举，直接上传二维码图片不就好了吗，但是二进制数据对于 git 来说就是灾难，使用 git 管理的情况下，我会尽可能使用代码 or 文字进行描述，而且表示同样的数据（一行字符串与一张图片），何必多提交那几十 KB 呢？
:::
