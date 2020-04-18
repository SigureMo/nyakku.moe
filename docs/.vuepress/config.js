module.exports = {
  title: "Notev",
  description: "一个小透明的透明世界",
  evergreen: true,
  locales: {
    "/": {
      lang: "zh-CN",
    },
  },
  head: [
    [
      "meta",
      {
        name: "viewport",
        content: "width=device-width,initial-scale=1,user-scalable=no",
      },
    ],
    [
      "link",
      {
        rel: "stylesheet",
        href: "https://cdn.jsdelivr.net/npm/katex@0.11.1/dist/katex.min.css",
      },
    ],
    ["meta", { property: "og:image", content: "/sigure_mo.png" }],
    ["link", { rel: "manifest", href: "/manifest.json" }],
    ["meta", { name: "theme-color", content: "#222222" }],
    ["meta", { name: "apple-mobile-web-app-capable", content: "yes" }],
    [
      "meta",
      { name: "apple-mobile-web-app-status-bar-style", content: "black" },
    ],
    ["link", { rel: "apple-touch-icon", href: "/icons/favicon152.png" }],
    [
      "link",
      { rel: "mask-icon", href: "/icons/favicon152.png", color: "#3eaf7c" },
    ],
    [
      "meta",
      { name: "msapplication-TileImage", content: "/icons/favicon144.png" },
    ],
    ["meta", { name: "msapplication-TileColor", content: "#000000" }],
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
      md.set({ html: true });
      md.use(require("@iktakahiro/markdown-it-katex"));
      md.use(require("markdown-it-mark"));
      md.use(require("markdown-it-task-lists"));
      md.use(require("markdown-it-vuepress-code-snippet-enhanced"));
    },
  },

  // 插件
  plugins: [
    // 开启 PWA
    [
      "@vuepress/pwa",
      {
        serviceWorker: true,
        updatePopup: true,
      },
    ],
    // 彩带背景
    [
      "ribbon",
      {
        size: 90,
        opacity: 0.8,
        zIndex: -1,
      },
    ],
    // 鼠标特效插件
    [
      "cursor-effects",
      {
        shape: "star",
      },
    ],
    // 离开页面标题变化
    [
      "dynamic-title",
      {
        showIcon: "/favicon.ico",
        showText: "(ฅ>ω<*ฅ)欢迎回来！",
        hideIcon: "/failure.ico",
        hideText: "( ๑ˊ•̥▵•)੭₎₎不要走呀！",
        recoverTime: 2000,
      },
    ],
    // 悬挂小猫返回顶部
    ["go-top"],
    // 流程图
    ["flowchart"],
    // RSS 插件
    [
      "feed",
      {
        canonical_base: "https://www.sigure.xyz",
      },
    ],
    // sitemap 插件
    [
      "sitemap",
      {
        hostname: "https://www.sigure.xyz",
      },
    ],
  ],

  // 主题配置
  theme: "meteorlxy",
  themeConfig: {
    lang: Object.assign(require("vuepress-theme-meteorlxy/lib/langs/en-US"), {
      home: "一个小透明的透明世界",
    }),
    personalInfo: {
      // 昵称
      nickname: "SigureMo",
      // 个人简介 (支持 HTML)
      description: "喵喵喵？",
      // 电子邮箱
      email: "sigure@163.com",
      // 所在地
      location: "DLC, China",
      // 组织
      organization: "Dalian University of Technology",
      // 头像
      avatar: "/sigure_mo.png",
      // 社交平台帐号信息
      sns: {
        // Github 帐号和链接
        github: {
          account: "SigureMo",
          link: "https://github.com/SigureMo",
        },
      },
    },

    // 上方 header 的相关设置 (可选)
    header: {
      // header 的背景，可以使用图片，或者随机变化的图案（geopattern）
      background: {
        // 使用图片的 URL，如果设置了图片 URL，则不会生成随机变化的图案，下面的 useGeo 将失效
        url: "/bg.jpg",
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
      custom:
        'Copyright 2018-present <a href="https://github.com/SigureMo" target="_blank">SigureMo</a> | MIT License',
    },

    // 个人信息卡片相关设置 (可选)
    infoCard: {
      // 卡片 header 的背景，可以使用图片，或者随机变化的图案（geopattern）
      headerBackground: {
        // 使用图片的 URL，如果设置了图片 URL，则不会生成随机变化的图案，下面的 useGeo 将失效
        url: "/info_bg.jpg",
      },
    },

    // 是否显示文章的最近更新时间
    lastUpdated: true,

    // 顶部导航栏内容
    nav: [
      { text: "Home", link: "/", exact: true },
      { text: "Posts", link: "/posts/", exact: false },
      { text: "About", link: "/About.html", exact: false },
      { text: "Github", link: "https://github.com/SigureMo/notev" },
    ],

    // 评论配置，参考下方 [页面评论] 章节
    comments: {
      owner: "SigureMo",
      repo: "notev",
      clientId: "02c64bbb4f2a3b0ec621",
      clientSecret: "fb5ea1b5e6117ae25abb0459489f6a0359048d7f",
    },

    // 分页配置 (可选)
    pagination: {
      perPage: 5,
    },

    // 默认页面（可选，默认全为 true）
    defaultPages: {
      // 是否允许主题自动添加 Home 页面 (url: /)
      home: true,
      // 是否允许主题自动添加 Posts 页面 (url: /posts/)
      posts: true,
    },
    sidebarDepth: 1,
    sidebar: "auto",
    // Service Worker 的配置
    serviceWorker: {
      updatePopup: true,
    },
  },
};
