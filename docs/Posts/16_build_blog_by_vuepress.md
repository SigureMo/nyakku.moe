---
title: 使用 Vuepress 搭建个人静态 Blog
date: 2019-08-17
categories:
   - 游
tags:
   - front end
   - blog
   - Vuepress
---

::: tip

静态博客并不难搭建，但是对前端什么都不懂的我还是走了很多的弯路，而且 `vuepress` 是一个比较新的框架，网上的资源还是较少的，能用的资源基本只有文档，本文跟随源文档，以最简的方式搭建一个简单的文档 demo ，进而搭建一个属于你自己的 blog

:::

<!-- more -->

-  预备知识
   -  基本 Markdown 语法
   -  基本 Github 与 git 操作方式
   -  前端零基础
-  开发环境
   -  `nodejs 8+` 及 `npm` or `yarn`
   -  `git bash`

## 为什么选择 Vuepress

### 什么是静态博客

首先看动态博客的工作流，客户端向博客页面发起 http 请求，服务器根据请求的 url 进行路由，然后做一些事情，最终可能返回一个响应

而静态博客，服务器端只能根据路由返回一个页面，也就是后端基本什么事情都不做，只做了路由这一件事，更别说访问数据库之类的了，所以静态博客是没有数据库的，但是可以在前端使用外部数据库（比如 Valine）

由于不需要后端程序，静态博客可以很容易地部署在 `Github` 等网站上，只需要将静态博客的代码上传到 `Github` 的 `repo` 内即可

### Vuepress 是什么

Vuepress 是一个 Vue 驱动的静态网站生成器，我们使用 Markdown 写好文档后，使用 Vuepress 进行编译便可以生成静态网站了，进而将其 push 到 github repo 便可以在互联网中访问到它了

相比于 Docsify ，Vuepress 是在部署前就将文档编译好了，而 Docsify 是在前端对文章进行编译，当然，如果是简单的文档的话 Docsify 相比于 Vuepress 可能会更加简洁，但是博客之类就不太适合了

相比与 Hexo ，Vuepress 可以方便地在文档中使用 Vue ，但缺陷也很明显， Vuepress 还很年轻，其插件、社区等生态尚不丰富，所以当前静态博客的主流还是 Hexo

## 从头开始搭建文档

### 快速上手

[源文档](https://v1.vuepress.vuejs.org/zh/guide/getting-started.html)

首先创建一个项目文件夹，并且安装 Vuepress

```bash
# 创建项目文件夹并进入
mkdir myblog
cd myblog

# 安装
yarn add -D vuepress # 或者：npm install -D vuepress
```

创建文档文件夹（也可以直接在根目录写作，这里不建议）

```bash
# 创建文档文件夹
mkdir docs
```

开始写作~

```bash
echo '# Hello Vuepress!' > README.md
```

本地调试

```bash
vuepress dev docs
```

之后便可以在浏览器中看到刚刚写的文档啦

为了方便调试，可以在 `package.json` （根目录下，没有就新建）中添加以下 `npm script`

```json
{
   "scripts": {
      "docs:dev": "vuepress dev docs",
      "docs:build": "vuepress build docs"
   }
}
```

现在，使用

```bash
yarn docs:dev # 或者：npm run docs:dev
```

便可调用 `vuepress dev docs` 进行本地调试

同样地，使用

```bash
yarn docs:build # 或者：npm run docs:build
```

便可编译生成静态 HTML 文件

### 目录结构

[源文档](https://v1.vuepress.vuejs.org/zh/guide/directory-structure.html)

基本结构如下

```
.
├── docs
│   ├── .vuepress (可选的)
│   │   ├── public (可选的)
│   │   ├── styles (可选的)
│   │   │   ├── index.styl
│   │   │   └── palette.styl
│   │   └── config.js (可选的)
│   │
│   ├── README.md
│   ├── guide
│   │   ├── README.md
│   │   └── getting_started.md
│   └── config.md
│
└── package.json
```

`docs` 目录下的 Markdown 文件编译后便可生成 HTML 文件，上述文件结构可生成以下结构的 url

```
/                                (对应于 docs/README.md)
/guide/                          (对应于 docs/guide/README.md)
/guide/getting_started.html      (对应于 docs/guide/getting_started.md)
/config.html                     (对应于 docs/config.md)
```

`docs/.vuepress/` 文件夹中保存的是 `vuepress` 的基本配置，具体见下节

### 基本配置

[源文档](https://v1.vuepress.vuejs.org/zh/guide/basic-config.html)

首先的配置文件就是 `docs/.vuepress/config.js` ，它对于 Vuepress 是必不可少的，首先可以通过简单地配置得到一个基本的

```js
module.exports = {
   title: "Hello VuePress",
   description: "Just playing around"
};
```

### 主题配置

> 只搭建博客可以跳至博客配置部分

首先使用默认主题来创建文档，在 `docs/.vuepress/config.js` 中添加来配置标题栏与侧边栏

```js
module.exports = {
   themeConfig: {
      nav: [
         { text: "Home", link: "/" },
         { text: "Guide", link: "/guide/" }
      ],
      sidebar: {
         "/guide/": ["", "getting_started"],
         "/": ["", "config"]
      }
   }
};
```

### 默认首页

没有首页怎么行，首先配置下默认的首页，只需要修改下 `docs/README.md` 就好

```yaml
---
home: true
heroImage: /hero.png
heroText: Hero 标题
tagline: Hero 副标题
actionText: 快速上手 →
actionLink: /zh/guide/
features:
   - title: 简洁至上
     details: 以 Markdown 为中心的项目结构，以最少的配置帮助你专注于写作。
   - title: Vue驱动
     details: 享受 Vue + webpack 的开发体验，在 Markdown 中使用 Vue 组件，同时可以使用 Vue 来开发自定义主题。
   - title: 高性能
     details: VuePress 为每个页面预渲染生成静态的 HTML，同时在页面被加载的时候，将作为 SPA 运行。
footer: MIT Licensed | Copyright © 2018-present Evan You
---

```

其中 `heroImage` 是相对于 `docs/.vuepress/public/` 的子路径

现在调试运行一下，便可以看到一个极简的文档雏形了

## 在文档的基础上搭建博客

这里使用主题 `vuepress-theme-reco` ，文档见 [ref2](#reference)，当然也可以使用其他主题

### 安装主题

```bash
yarn add -D vuepress-theme-reco
# OR npm install -D vuepress-theme-reco
```

### 博客配置

在 `docs/.vuepress/config.js` 中添加主题配置如下

```js
module.exports = {
   theme: "reco"
};
```

并修改主题配置

```js
module.exports = {
   themeConfig: {
      // 博客配置
      blogConfig: {
         category: {
            location: 2, // 在导航栏菜单中所占的位置，默认2
            text: "Category" // 默认文案 “分类”
         },
         tag: {
            location: 3, // 在导航栏菜单中所占的位置，默认3
            text: "Tag" // 默认文案 “标签”
         }
      },
      nav: [
         { text: "Home", link: "/", icon: "reco-home" },
         { text: "Guide", link: "/Guide/", icon: "reco-eye" }
      ],
      sidebar: "auto"
   }
};
```

### 文章前加 front matter

之后只需要在书写的文章中增加分类以及标签即可

```yaml
---
title: 使用 Vuepress 搭建个人静态 Blog
date: 2019-08-17
categories:
   - 游
tags:
   - front_end
   - blog
---

```

这样在对应的标签以及分类内就能找到相应的文章了

### 配置博客首页

默认首页更偏于文档风格，`vuepress-theme-reco` 中内置一种博客风格首页，略作配置便可完成，在 `docs/.vuepress/config.js` 中指定首页类型

```js
module.exports = {
   themeConfig: {
      type: "blog"
   }
};
```

至于首页内容，类似于前面默认首页的配置，只需要修改下 `docs/README.md` 就好

```yaml
---
home: true
bgImage: "/bg.png"
bgImageStyle: { height: "350px" }
faceImage: "/head.png"
---

```

这里两个图片都以 `docs/.vuepress/public/` 为根目录

## 部署

[源文档](https://v1.vuepress.vuejs.org/zh/guide/deploy.html)

这里仅记录 GitHub-pages 的部署方式，其他的详见文档

在根目录新建文件 `deploy.sh` ，内容如下（自行修改注释部分代码）

```bash
#!/usr/bin/env sh

# 确保脚本抛出遇到的错误
set -e

# 生成静态文件
npm run docs:build

# 进入生成的文件夹
cd docs/.vuepress/dist

# 如果是发布到自定义域名
# echo 'www.example.com' > CNAME

git init
git add -A
time=$(date "+%Y-%m-%d %H:%M:%S")
git commit -m "rebuild @${time}"

# 如果发布到 https://<USERNAME>.github.io
# git push -f git@github.com:<USERNAME>/<USERNAME>.github.io.git master

# 如果发布到 https://<USERNAME>.github.io/<REPO>
# git push -f git@github.com:<USERNAME>/<REPO>.git master:gh-pages

cd -
```

之后运行即可

```bash
bash scripts/deploy.sh
```

::: tip
至此，一个基本博客的框架便搭建完成啦，一些更细节的配置详见文档，下面记录一些我自己的进阶配置
:::

## 进阶配置

### 添加插件

[源文档](https://v1.vuepress.vuejs.org/zh/plugin/using-a-plugin.html)

比如说启用页面滚动时自动激活侧边栏，首先安装该插件

```bash
yarn add -D @vuepress/plugin-active-header-links@next
# OR npm install -D @vuepress/plugin-active-header-links@next
```

之后在 `docs/.vuepress/config.js` 中添加

```js
module.exports = {
   plugins: [
      // 页面滚动时自动激活侧边栏链接
      "@vuepress/active-header-links"
   ]
};
```

其他推荐的插件

-  `vuepress-plugin-ribbon` 在背景中加入一条彩带
-  `vuepress-plugin-live2d` 在博客中添加一个看板娘
-  `@vuepress/pwa` 启用 PWA

### Markdown 插件的添加

通过安装并配置 `markdown-it` 插件便可在 Markdown 中使用新的 Mardown 特性

安装

```bash
yarn add markdown-it-xxx # or npm install markdown-it-xxx
```

配置 `docs/.vuepress/config.js`

```bash
module.exports = {
  markdown: {
    extendMarkdown: md => {
      // 使用更多的 markdown-it 插件!
      md.use(require('markdown-it-xxx'))
    }
  }
}
```

下面推荐几个有用的插件

-  `markdown-it-mark` 在词语两侧添加 `==` 即可对其实现 ==高亮== 的效果，非常简单实用
-  `@iktakahiro/markdown-it-katex` 可在 Markdown 内解析 $\KaTeX$，但是其依赖 `CSS`，所以需要额外配置下 `docs/.vuepress/config.js`

```js
module.exports = {
   head: [
      [
         "link",
         {
            rel: "stylesheet",
            href: "https://cdn.jsdelivr.net/npm/katex@0.10.0/dist/katex.min.css"
         }
      ]
   ]
};
```

::: warning
在 `config.js` 中配置的 markdown 配置都是在编译时便解析完成的，所以配置 `markdown-it-katex` 后可能会导致编译时间特别长，但是当前其是一个非常有效的方式

另外也可以使用插件 `vuepress-plugin-mathjax` 进行渲染，但是我在使用的时候发生了一些问题，尚待解决
:::

### 配置主题颜色

通过配置 `docs/.vuepress/styles/palette.styl` 即可修改主题颜色

```stylus
$accentColor = #222222
$textColor = #2c3e50
$borderColor = #eaecef
$codeBgColor = #282c34
```

# Reference

1. [Vuepress 1.x 文档](https://v1.vuepress.vuejs.org/zh/)
2. [vuepress-theme-reco 文档](https://github.com/vuepress-reco/vuepress-theme-reco)
