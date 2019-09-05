module.exports = {
  title: "Notev",
  description: "一个小透明的透明世界🌌",
  head: [
    [
      "meta",
      {
        name: "viewport",
        content: "width=device-width,initial-scale=1,user-scalable=no"
      }
    ],
    ["link", { rel: "icon", href: "/sigure_mo.png" }],
    [
      "link",
      {
        rel: "stylesheet",
        href: "https://cdn.jsdelivr.net/npm/katex@0.10.0/dist/katex.min.css"
      }
    ]
  ],

  markdown: {
    // markdown-it-anchor 的选项
    anchor: { permalink: true },
    // markdown-it-toc 的选项
    toc: { includeLevel: [1, 2, 3] },
    // markdown 插件
    extendMarkdown: md => {
      md.set({ html: true });
      md.use(require("@iktakahiro/markdown-it-katex"), {
        throwOnError: false,
        errorColor: " #cc0000"
      });
      md.use(require("markdown-it-mark"));
    }
  },

  // 插件
  plugins: [
    // 页面滚动时自动激活侧边栏链接
    "@vuepress/active-header-links"
  ],

  // 主题配置
  theme: "reco",
  themeConfig: {
    // 博客配置
    type: "blog",
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
    author: "SigureMo",
    // 备案号
    record: "辽ICP备19014250号-1",
    // 项目开始时间，只填写年份
    startYear: "2018",
    nav: [
      { text: "Home", link: "/", icon: "reco-home" },
      { text: "TimeLine", link: "/TimeLine/", icon: "reco-date" },
      { text: "About", link: "/About.html", icon: "reco-account" },
      {
        text: "Conntect",
        icon: "reco-message",
        items: [
          {
            text: "Github",
            link: "https://github.com/SigureMo",
            icon: "reco-github"
          },
          {
            text: "Email",
            link: "mailto:sigure_mo@163.com",
            icon: "reco-message"
          },
          {
            text: "QQ",
            link:
              "http://qr.topscan.com/api.php?text=http://qm.qq.com/cgi-bin/qm/qr?k=1PbIl8QPOkF0ErJKX-GmjA-E8e53djl4",
            icon: "reco-qq"
          },
          {
            text: "Wechat",
            link:
              "http://qr.topscan.com/api.php?text=https://u.wechat.com/EPDjgRrQutXUU-K1XzT9X_0",
            icon: "reco-wechat"
          },
          {
            text: "CSDN",
            link: "https://blog.csdn.net/qq_41819321",
            icon: "reco-csdn"
          }
        ]
      }
    ],
    sidebarDepth: 1,
    sidebar: "auto",
    serviceWorker: {
      updatePopup: true // Boolean | Object, 默认值是 undefined.
    },
    valineConfig: {
      appId: "E0ei2XbovnHMSlL4tQM2mVDo-gzGzoHsz",
      appKey: "zSYs7qvWjLlEvF9tMcVMUUUr"
    },

    lastUpdated: "Last Updated", // string | boolean

    // 假定是 GitHub. 同时也可以是一个完整的 GitLab URL
    repo: "SigureMo/notev",
    // 自定义仓库链接文字。默认从 `themeConfig.repo` 中自动推断为
    // "GitHub"/"GitLab"/"Bitbucket" 其中之一，或是 "Source"。
    repoLabel: "Repo",

    // 以下为可选的编辑链接选项

    // 假如你的文档仓库和项目本身不在一个仓库：
    docsRepo: "SigureMo/notev",
    // 假如文档不是放在仓库的根目录下：
    docsDir: "docs",
    // 假如文档放在一个特定的分支下：
    docsBranch: "master",
    // 默认是 false, 设置为 true 来启用
    editLinks: true,
    // 默认为 "Edit this page"
    editLinkText: "在GitHub上编辑此页！",
    // Service Worker 的配置
    serviceWorker: {
      updatePopup: true
    }
  }
};
