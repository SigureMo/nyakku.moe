module.exports = {
  title: "Notev",
  description: "一个小萌新的笔记，基本每天都会更新~",
  base: "/notev/",
  head: [["link", { rel: "icon", href: "/sigure_mo.png" }]],
  configureWebpack: {
    resolve: {
      alias: {
        "@codes": "https://github.com/SigureMo/notev/tree/master/Codes"
      }
    }
  },

  markdown: {
    // markdown-it-anchor 的选项
    anchor: { permalink: false },
    // markdown-it-toc 的选项
    toc: { includeLevel: [1, 2, 3] },
    // markdown 插件
    extendMarkdown: md => {
      md.set({ breaks: true });
      md.use(require("@iktakahiro/markdown-it-katex"), {
        throwOnError: false,
        errorColor: " #cc0000"
      });
      md.use(require("markdown-it-mark"));
    }
  },

  // 插件
  plugins: [
    // 自动返回顶部
    "@vuepress/back-to-top",
    // 页面滚动时自动激活侧边栏链接
    "@vuepress/active-header-links"
  ],

  // 主题配置
  themeConfig: {
    nav: [
      { text: "Home", link: "/" },
      { text: "Notes", link: "/Notes/" },
      { text: "Discovery", link: "/Discovery/" },
      { text: "About", link: "/About.html" }
    ],
    sidebarDepth: 1,
    sidebar: {
      "/Notes/": [
        "",
        "Principle_of_Metal_Plastic_Working",
        "Solid-state_Phase_Transformation",
        "Mathematical_Modeling",
        "Deep_Learning",
        "Cpp",
        "PIC",
        "Computer_Network",
        "Principles_of_Computer_Composition",
        "Data_Structures"
      ],
      "/Discovery/": [
        "",
        "07_Cmder",
        "06_Harddisk",
        "05_Gitmoji",
        "04_Hardware",
        "03_C_and_pointer",
        "01_Everything_is_object"
      ],
      "/": ["", "Template", "About"]
    },

    serviceWorker: {
      updatePopup: true // Boolean | Object, 默认值是 undefined.
    },

    lastUpdated: "Last Updated", // string | boolean

    // 假定是 GitHub. 同时也可以是一个完整的 GitLab URL
    repo: "SigureMo/notev",
    // 自定义仓库链接文字。默认从 `themeConfig.repo` 中自动推断为
    // "GitHub"/"GitLab"/"Bitbucket" 其中之一，或是 "Source"。
    repoLabel: "Github",

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
    editLinkText: "在GitHub上编辑此页！"
  }
};
