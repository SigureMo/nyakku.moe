---
title: 用可爱的插件装饰你的 VuePress~
date: 2019-10-21
category: 做点有趣的
tags:
   - front end
   - blog
   - VuePress
---

::: tip

早在一年多以前我就喜欢上了 `hexo-theme-sagiri` 这个主题（效果可以参见 [diygod.me](https://diygod.me/)），不过当时还什么都不懂啦，不会用 GitHub ，更不知道这居然是静态博客做出来的效果（如果当时知道那么简单的话，我也许现在用的就是 hexo 了 :joy:）

前些日子因为机缘巧合发现了 `sagiri` 中的彩带背景的开源实现，原来其出自若干年前 Evan 的个人主页背景，之后我试着简单阅读 `vuepress-plugin-nest` 插件源码，照喵画虎地摹了个 `vuepress-plugin-ribbon` 插件，居然真的成功了！这使我萌生了把 `sagiri` 中一些小组件作为 VuePress 插件实现的想法，之后的几天……

废话说太多了，还是说说怎么用吧 :joy:

:warning: 本文章仅针对 VuePress V1，对于 VuePress V2 及 VitePress 没有太多参考意义

:::

<!-- more -->

## 在背景添加一条彩带

[vuepress-plugin-ribbon](https://github.com/moefyit/vuepress-plugin-ribbon)

只需要简单的配置就可以在你的 VuePress 中添加一条背景彩带~

首先使用 yarn 安装~

```bash
yarn add vuepress-plugin-ribbon -D
```

然后在 `config.js` 中添加以下配置~

```js
module.exports = {
   plugins: [
      [
         'ribbon',
         {
            size: 90, // 彩带的宽度，默认为 90
            opacity: 0.8, // 彩带的不透明度，默认为 0.3
            zIndex: -1, // 彩带的 z-index 属性，默认值为 -1
         },
      ],
   ],
}
```

然后再次 `dev` 你就可以发现你的背景多一条彩带啦~

::: tip

如果你的彩带会把博客文字覆盖掉，请先尝试调整 `z-index` 属性，如果无论如何调整都不能有合适的效果，请使用 CSS 为你的主题添加样式覆盖，最简单的方法就是为不想显示彩带的位置添加背景，因为博客主题样式大多不一致，这里就不贴具体修改方式了

:::

## 添加一个动态的标题

[vuepress-plugin-dynamic-title](https://github.com/moefyit/vuepress-plugin-dynamic-title)

如果你现在使用的是 PC 端的话，试着切换浏览器到其它标签页~

唔，欢迎回来，你应该已经看到效果了~这就是 `dynamic-title` 的效果~

想要把它装到你的 VuePress 的话，就 yarn 一下吧~

```bash
yarn add vuepress-plugin-dynamic-title -D
```

配置稍微有点麻烦，需要提供图标以及相应的文字，不提供时默认是不显示图标的，图标放在 `.vuepress/public/` 下就好

```js
module.exports = {
   plugins: [
      [
         'dynamic-title',
         {
            showIcon: '/favicon.ico',
            showText: '(/≧▽≦/)咦！又好了！',
            hideIcon: '/failure.ico',
            hideText: '(●—●)喔哟，崩溃啦！',
            recoverTime: 2000,
         },
      ],
   ],
}
```

## 增加鼠标点击动效

[vuepress-plugin-cursor-effects](https://github.com/moefyit/vuepress-plugin-cursor-effects)

只需要简单的安装就可以在你的 VuePress 添加鼠标点击后散落彩色粒子的效果~

插件名是 `vuepress-plugin-cursor-effects`，安装方法应该不用说了吧，配置也很简单，按照下面配置就好

```js
module.exports = {
   plugins: [
      [
         'cursor-effects',
         {
            size: 2, // 粒子大小
            shape: 'star', // 粒子形状（可选 'star' 和 'circle'）
            zIndex: 999999999,
         },
      ],
   ],
}
```

## 修改你的鼠标为更可爱的样式

这个就不用插件实现了，自己配置下 `style/index.styl` 就可以了

```stylus
body {
  cursor: url('/cursor.ico'), auto;
}
```

找一个你喜欢的鼠标指针放在 `public` 下就好，当然图片名也记得修改

## 使用悬挂喵作为返回顶部按钮

[vuepress-plugin-go-top](https://github.com/moefyit/vuepress-plugin-go-top)

相信你看到这个位置应该已经能看到它啦，点一下就可以返回顶部哦~

安装方法就不必说了，由于没什么配置项，直接像下面这样就行

```js
module.exports = {
   plugins: ['go-top'],
}
```

值得注意的是，由于猫猫在窄屏设备上很容易遮挡内容，因此设计了两个响应式变化点，当屏幕变窄时会依次显示“猫猫” -> 显示“猫爪爪” -> 不显示，具体的响应式变化点你可以在 `.vuepress/styles/palette.styl` 中自行修改

```stylus
// 显示猫猫
$MQWide ?= 1440px
// 显示猫爪爪
$MQMobile ?= 768px
// 啥都不显示
```

## 添加一个萌萌哒看板娘

[vuepress-plugin-live2d](https://github.com/yanjun0501/vuepress-plugin-live2d) [Author 聆歌](https://github.com/yanjun0501/vuepress-plugin-live2d)

```js
plugins: [
   [
      'vuepress-plugin-live2d',
      {
         modelName: '', // 模型名称，可传入一个字符串或者数组
         mobileShow: false, // 是否在移动设备上显示
         position: 'right', // 显示在左下角还是右下角
      },
   ],
]
```

配置详情请在[项目主页](https://github.com/yanjun0501/vuepress-plugin-live2d)查看

感谢聆歌提供本插件，感觉效果不错的可以给他一个 Star 哟~

## 添加一个漂亮的音乐播放器

[vuepress-plugin-meting](https://github.com/moefyit/vuepress-plugin-meting)

这个插件是利用 Meting 接口来获取音乐资源，传入 Vue-APlayer，解决 APlayer 的音源问题，当然如果你有合适的音源也可以直接用 Vue-APlayer 哒~

如果你想添加一个全局的吸底播放器，直接在 `config.js` 中配置即可

```js
module.exports = {
   plugins: [
      'meting',
      {
         meting: {
            server: 'netease', // 音乐源
            type: 'playlist', // 资源类型
            mid: '2539599584', // 资源 id
         },
         aplayer: {
            lrcType: 3,
         },
      },
   ],
}
```

另外，它也支持在任何页面单独引入播放器，当然你需要首先在 `config.js` 启用它（但不必填写配置项，配置项只与全局吸底播放器有关，不配置便不会出现该播放器）

```markdown
<!-- my-music.md -->

<Meting server="netease"
        type="playlist"
        mid="2539599584"
        :lrc-type="3"/>

<!-- 这样就可以在 my-music.html 页面单独引入一个播放器咯～ -->
```

## 最后

再次感谢 [DIYGod](https://github.com/DIYgod)~
