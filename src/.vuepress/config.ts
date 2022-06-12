import { defineConfig4CustomTheme } from 'vuepress/config'
import markdowniItMark from 'markdown-it-mark'
import markdownItTaskLists from 'markdown-it-task-lists'

export default defineConfig4CustomTheme<any>({
  title: 'Notev',
  description: '一个小透明的透明世界',
  port: 1127,
  evergreen: true,
  locales: {
    '/': {
      lang: 'zh-CN',
      title: 'Notev',
      description: '一个小透明的透明世界',
    },
  },
  head: [
    [
      'meta',
      {
        name: 'viewport',
        content: 'width=device-width,initial-scale=1,user-scalable=no',
      },
    ],
    ['meta', { property: 'og:url', content: 'https://nyakku.moe' }],
    ['meta', { property: 'og:site_name', content: 'Notev' }],
    ['meta', { property: 'og:image', content: '/bg.webp' }],
    ['meta', { property: 'og:description', content: '一个小透明的透明世界' }],
    ['meta', { property: 'og:title', content: 'Notev' }],
    ['link', { rel: 'manifest', href: '/manifest.json' }],
    ['meta', { name: 'theme-color', content: '#222222' }],
    ['meta', { name: 'apple-mobile-web-app-capable', content: 'yes' }],
    ['meta', { name: 'apple-mobile-web-app-status-bar-style', content: 'black' }],
    ['link', { rel: 'apple-touch-icon', href: '/icons/favicon152.png' }],
    ['link', { rel: 'mask-icon', href: '/icons/favicon152.png', color: '#3eaf7c' }],
    ['meta', { name: 'msapplication-TileImage', content: '/icons/favicon144.png' }],
    ['meta', { name: 'msapplication-TileColor', content: '#000000' }],
  ],

  markdown: {
    // 代码显示行号
    lineNumbers: true,
    // markdown-it-anchor 的选项
    anchor: { permalink: true },
    // markdown-it-toc 的选项
    toc: { includeLevel: [1, 2, 3] },
    // markdown 插件
    extendMarkdown: (md) => {
      md.set({ html: true })
      md.use(markdowniItMark)
      md.use(markdownItTaskLists)
    },
  },

  // 插件
  // @ts-ignore
  plugins: [
    // 开启 PWA
    [
      '@vuepress/pwa',
      {
        serviceWorker: true,
        updatePopup: true,
      },
    ],
    // 彩带背景
    [
      'ribbon',
      {
        size: 90,
        opacity: 0.8,
        zIndex: -1,
      },
    ],
    // 鼠标特效插件
    [
      'cursor-effects',
      {
        size: 1.75,
        shape: 'star',
      },
    ],
    // 离开页面标题变化
    [
      'dynamic-title',
      {
        showIcon: '/favicon.ico',
        showText: '(ฅ>ω<*ฅ)欢迎回来！',
        hideIcon: '/failure.ico',
        hideText: '( ๑ˊ•̥▵•)੭₎₎不要走呀！',
        recoverTime: 2000,
      },
    ],
    // 悬挂小猫返回顶部
    ['go-top'],
    // RSS 插件
    [
      'feed',
      {
        canonical_base: 'https://nyakku.moe',
      },
    ],
    // Meting 插件
    [
      'meting',
      {
        meting: {
          server: 'netease',
          type: 'playlist',
          mid: '6838211960',
        },
        aplayer: {
          lrcType: 3,
          preload: 'metadata',
        },
      },
    ],
    // KaTeX 插件
    ['@maginapp/vuepress-plugin-katex'],
    // zoom 插件配置（覆盖主题内原配置）
    [
      'zooming',
      {
        selector: '.content :not(a) > img',
      },
    ],
    // 图片懒加载
    ['img-lazy'],
  ],

  // 主题配置
  theme: 'meteorlxy',
  themeConfig: {
    // @ts-ignore
    lang: {
      home: '一个小透明的透明世界',
      posts: 'Posts',
      category: 'Category',
      categories: 'Categories',
      tag: 'Tag',
      tags: 'Tags',

      // post filter
      allCategories: '全部',
      search: '搜索',
      searchHint: '查找标题和摘要',
      noRelatedPosts: '木有找到相关的文章呀～',

      // post meta
      top: '置顶',
      createdAt: '发布时间',
      updatedAt: '最后修改',
      prevPost: '上一篇',
      nextPost: '下一篇',

      // post nav
      toc: '文章目录',
      comments: '评论',

      // hints
      notFound: '哎呀！这里什么都没有哇～',
    },
    personalInfo: {
      // 昵称
      nickname: '喵ック',
      // 个人简介 (支持 HTML)
      description: '可爱是第一驱动力～',
      // 电子邮箱
      email: 'sigure.qaq@gmail.com',
      // 所在地
      location: 'DLC, China',
      // 组织
      organization: 'Dalian University of Technology',
      // 头像
      avatar: '/avatar.jpg',
      // 社交平台帐号信息
      sns: {
        // GitHub 帐号和链接
        github: {
          account: 'SigureMo',
          link: 'https://github.com/SigureMo',
        },
      },
    },

    // 上方 header 的相关设置 (可选)
    header: {
      // header 的背景，可以使用图片，或者随机变化的图案（geopattern）
      background: {
        // 使用图片的 URL，如果设置了图片 URL，则不会生成随机变化的图案，下面的 useGeo 将失效
        url: '/bg.webp',
      },
      // 是否在 header 显示标题
      showTitle: true,
    },

    // 底部 footer 的相关设置 (可选)
    footer: {
      // 是否显示 Powered by VuePress
      poweredBy: true,
      // 是否显示使用的主题
      poweredByTheme: true,
      // 添加自定义 footer (支持 HTML)
      custom: `Copyright 2018-present <a href="https://github.com/SigureMo" target="_blank">Nyakku</a> | <a href="https://creativecommons.org/licenses/by-nc-sa/4.0/">CC BY-NC-SA-4.0</a>`,
    },

    // 个人信息卡片相关设置 (可选)
    infoCard: {
      // 卡片 header 的背景，可以使用图片，或者随机变化的图案（geopattern）
      headerBackground: {
        // 使用图片的 URL，如果设置了图片 URL，则不会生成随机变化的图案，下面的 useGeo 将失效
        url: '/info-bg.webp',
      },
    },

    // 是否显示文章的最近更新时间
    lastUpdated: true,

    // 顶部导航栏内容
    nav: [
      { text: 'Home', link: '/', exact: true },
      { text: 'Posts', link: '/posts/', exact: false },
      { text: 'Friends', link: '/friends.html', exact: false },
      { text: 'About', link: '/about.html', exact: false },
      { text: 'GitHub', link: 'https://github.com/SigureMo/notev' },
    ],

    // 评论配置，参考下方 [页面评论] 章节
    comments: false,

    // 分页配置 (可选)
    pagination: {
      perPage: 7,
    },

    // 默认页面（可选，默认全为 true）
    defaultPages: {
      // 是否允许主题自动添加 Home 页面 (url: /)
      home: true,
      // 是否允许主题自动添加 Posts 页面 (url: /posts/)
      posts: true,
    },
    sidebarDepth: 1,
    sidebar: 'auto',
    // Service Worker 的配置
    serviceWorker: {
      updatePopup: true,
    },

    // 友链配置
    friends: [
      {
        name: 'ClariS',
        url: 'https://silkyheart.moe/',
        desc: 'Querying for a variable and seizing the time',
        avatar:
          'https://cdn.jsdelivr.net/gh/heavenly-zy/heavenly-zy.github.io@latest/images/avatar.jpg',
      },
    ],
  },
})
