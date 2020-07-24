module.exports = {
  title: "Notev",
  description: "一个小透明的透明世界",
  port: 1127,
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
    ["meta", { property: "og:url", content: "https://sigure.xyz" }],
    ["meta", { property: "og:site_name", content: "Notev" }],
    ["meta", { property: "og:image", content: "/avatar.jpg" }],
    ["meta", { property: "og:description", content: "一个小透明的透明世界" }],
    ["meta", { property: "og:title", content: "Notev" }],
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
        size: 1.75,
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
        canonical_base: "https://sigure.xyz",
      },
    ],
    // GA 插件
    [
      "@vuepress/google-analytics",
      {
        ga: "UA-164960376-1",
      },
    ],
    // Meting 插件
    [
      "meting",
      {
        meting: {
          server: "netease",
          type: "playlist",
          mid: "2539599584",
        },
        aplayer: {
          lrcType: 3,
        },
      },
    ],
    // KaTeX 插件
    ["@maginapp/vuepress-plugin-katex"],
    // zoom 插件配置（覆盖主题内原配置）
    [
      "zooming",
      {
        selector: ".content :not(a) > img",
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
      description: "私にとって、本物とはなんですか。",
      // 电子邮箱
      email: "sigure.qaq@gmail.com",
      // 所在地
      location: "DLC, China",
      // 组织
      organization: "Dalian University of Technology",
      // 头像
      avatar: "/avatar.jpg",
      // 社交平台帐号信息
      sns: {
        // GitHub 帐号和链接
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
      custom: `Copyright 2018-present <a href="https://github.com/SigureMo" target="_blank">SigureMo</a> | <a href="https://creativecommons.org/licenses/by-sa/4.0/">CC 4.0 BY-SA</a><br/>
        <a href="http://www.beian.miit.gov.cn/" target="_blank">辽ICP备19014250号</a>`,
    },

    // 个人信息卡片相关设置 (可选)
    infoCard: {
      // 卡片 header 的背景，可以使用图片，或者随机变化的图案（geopattern）
      headerBackground: {
        // 使用图片的 URL，如果设置了图片 URL，则不会生成随机变化的图案，下面的 useGeo 将失效
        url: "/info-bg.jpg",
      },
    },

    // 是否显示文章的最近更新时间
    lastUpdated: true,

    // 顶部导航栏内容
    nav: [
      { text: "Home", link: "/", exact: true },
      { text: "Posts", link: "/posts/", exact: false },
      { text: "Friends", link: "/friends.html", exact: false },
      { text: "About", link: "/about.html", exact: false },
      { text: "GitHub", link: "https://github.com/SigureMo/notev" },
    ],

    // 评论配置，参考下方 [页面评论] 章节
    comments: {
      owner: "SigureMo",
      repo: "notev",
      clientId: "02c64bbb4f2a3b0ec621",
      clientSecret: "fb5ea1b5e6117ae25abb0459489f6a0359048d7f",
      prefix: "💬 ",
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

    // 友链配置
    friends: [
      {
        name: "ClariS",
        url: "https://wryyy.life/",
        description: "Querying for a variable and seizing the time",
        avatar: "https://wryyy.life/avatar.png",
      },
    ],
  },
};
