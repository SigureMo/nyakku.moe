---
title: 用可爱的插件装饰你的 Vuepress~
date: 2019-10-21
categories:
   - 趣笔·书
tags:
   - front end
   - blog
   - Vuepress
---

::: tip

早在一年多以前我就喜欢上了 `hexo-theme-sagiri` 这个主题（效果可以参见 [diygod.me](https://diygod.me/)），不过当时还什么都不懂啦，不会用 GitHub ，更不知道这居然是静态博客做出来的效果（如果当时知道那么简单的话，我也许现在用的就是 hexo 了 :joy:）

前些日子因为机缘巧合有了写一个 `ribbon` 背景插件的想法，这其实就是 `sagiri` 中的背景，其原型出自若干年前尤大的个人主页背景，之后我试着简单阅读 `vuepress-plugin-nest` 插件源码，照喵画虎地摹了个 `vuepress-plugin-ribbon` 插件，居然成功了！这使我萌生了把 `sagiri` 中一些小组件作为 Vuepress 插件实现的想法，之后的几天……

废话说太多了，还是说说怎么用吧 :joy:

:::

<!-- more -->

-  预备知识
   -  会简单配置 Vuepress ，不会的话请先行阅读 [使用 Vuepress 搭建个人静态 Blog](16_build_blog_by_vuepress.md)
-  开发环境
   -  `nodejs 8+` 及 `npm` or `yarn`
-  文档 [vuepress-lovely-plugins](https://www.sigure.xyz/vuepress-lovely-plugins/)

## 在背景添加一条彩带

[vuepress-plugin-ribbon](https://github.com/SigureMo/vuepress-plugin-ribbon)

只需要简单的配置就可以在你的 Vuepress 中添加一条背景彩带~

首先使用 yarn 安装~

```bash
yarn add vuepress-plugin-ribbon -D
```

然后在 `config.js` 中添加以下配置~

```js
module.exports = {
   plugins: [
      [
         "ribbon",
         {
            size: 90, // 彩带的宽度，默认为 90
            opacity: 0.8, // 彩带的不透明度，默认为 0.3
            zIndex: -1 // 彩带的 z-index 属性，默认值为 -1
         }
      ]
   ]
};
```

然后再次 `dev` 你就可以发现你的背景多一条彩带啦~

::: tip

如果你的彩带会把博客文字覆盖掉，请先尝试调整 `z-index` 属性，如果无论如何调整都不能有合适的效果，请使用 CSS 为你的主题添加样式覆盖，最简单的方法就是为不想显示彩带的位置添加背景，因为博客主题样式大多不一致，这里就不贴具体修改方式了

:::

## 添加一个动态的标题

[vuepress-plugin-dynamic-title](https://github.com/SigureMo/vuepress-plugin-dynamic-title)

如果你现在使用的是电脑的话，试着切换浏览器到其它标签页~

唔，欢迎回来，你应该已经看到效果了~这就是 `dynamic-title` 的效果~

想要把它装到你的 Vuepress 的话，就 yarn 一下吧~

```bash
yarn add vuepress-plugin-dynamic-title -D
```

配置稍微有点麻烦，需要提供图标以及相应的文字，不提供时默认是不显示图标的，图表放在 `.vuepress/public/` 下就好

```js
module.exports = {
   plugins: [
      [
         "dynamic-title",
         {
            showIcon: "/favicon.ico",
            showText: "(/≧▽≦/)咦！又好了！",
            hideIcon: "/failure.ico",
            hideText: "(●—●)喔哟，崩溃啦！",
            recoverTime: 2000
         }
      ]
   ]
};
```

## 增加鼠标点击动效

[vuepress-plugin-cursor-effects](https://github.com/SigureMo/vuepress-plugin-cursor-effects)

只需要简单的安装就可以在你的 Vuepress 添加鼠标点击后散落彩色粒子的效果~

插件名是 `vuepress-plugin-cursor-effects`，安装方法应该不用说了吧，配置的话，也没有额外的配置项，直接如下便好

```js
module.exports = {
   plugins: ["cursor-effects"]
};
```

## 使用悬挂喵作为返回顶部按钮

[vuepress-plugin-go-top](https://github.com/SigureMo/vuepress-plugin-go-top)

相信你看到这个位置应该已经能看到它啦，点一下就可以返回顶部哦~

都到现在了，应该不需要我说怎么安装了吧？也是没有额外的配置项的，也许以后会添加~

## 添加音乐播放插件 <Badge text="alpha" type="error"/>

[@vuepress-reco/vuepress-plugin-music](https://github.com/vuepress-reco/vuepress-plugin-music)

[reco 主题](https://github.com/vuepress-reco)成员[橘子](https://github.com/smallsunnyfox)正在开发中，请期待……

## 添加一个萌萌哒看板娘

[vuepress-plugin-live2d](https://github.com/yanjun0501/vuepress-plugin-live2d) [Author 聆歌](https://github.com/yanjun0501/vuepress-plugin-live2d)

```js
plugins: [
   [
      "vuepress-plugin-live2d",
      {
         modelName: "", // 模型名称，可传入一个字符串或者数组
         mobileShow: false, // 是否在移动设备上显示
         position: "right" // 显示在左下角还是右下角
      }
   ]
];
```

配置详情请在[项目主页](https://github.com/yanjun0501/vuepress-plugin-live2d)查看

感谢聆歌提供本插件，感觉效果不错的可以给他一个 Star 哟~

## 修改你的鼠标为更可爱的样式

这个就不用插件实现了，自己配置下 `style/index.styl` 就可以了

```stylus
body {
  cursor: url('/cursor.ico'), auto;
}
```

找一个你喜欢的鼠标指针放在 `public` 下就好，当然图片名也记得修改

## 最后

再次感谢 [DIYGod](https://github.com/DIYgod)~
