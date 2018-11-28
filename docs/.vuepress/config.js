const timeago = require("timeago.js");

module.exports = {
    title: 'Notev',
    description: '一个个人总结性的笔记，基本每天都会更新',
    base: "/notev/",
    head: [
        ['link', { rel: 'icon', href: '/sigure_mo.png'}]
    ],
    configureWebpack: {
        resolve: {
            alias: {
                '@codes': 'https://github.com/SigureMo/S_Note/tree/master/Codes'
            }
        }
    },

    // markdown插件
    extendMarkdown: md => {
        md.set({ breaks: true })
        // md.use(require('markdown-it-katex'))
        md.use(require('@iktakahiro/markdown-it-katex'),
        {"throwOnError" : false, "errorColor" : " #cc0000"})
    },
    markdown: {
        // markdown-it-anchor 的选项
        anchor: { permalink: false },
        // markdown-it-toc 的选项
        toc: { includeLevel: [1, 2, 3] },
    },

    // 插件 
    plugins: [
        // 自动返回顶部
        '@vuepress/back-to-top',
        // 最近更新时间
        [
            '@vuepress/last-updated',
            { transformer: timeago.format },
        ],
    ],

    // 主题配置
    themeConfig: {
        nav: [
            { text: 'Home', link: '/' },
            { text: 'Notes', link: '/Notes/' },
            { text: 'Opinions', link: '/Opinions/' },
            { text: 'Projects', link: '/Projects/' },
            { text: 'Discovery', link: '/Discovery/' },
            { text: 'About', link: '/About.html' },
        ],
        sidebarDepth: 1,
        sidebar: {
            '/Opinions/': [
                '',
                '01_Everything_is_object',
                '02_Encoding',
                '03_C_and_pointer',
                '04_Hardware',
            ],
            '/Notes/': [
                '',
                'Data_Structures',
                'Principles_of_Computer_Composition',
                'Computer_Network',
                'Basis_of_Mechanical_Designing',
                'PIC',
                'Cpp',
                'Deep_Learning',
                'Mathematical_Modeling',
                'Principle_and_Application_of_Solid_Phase_Transition',
                'Principle_of_Metal_Plastic_Working',
            ],
            '/Projects/': [
                '',
                '01_MOOC_Downloading',
                '02_open_163',
                '03_Baidu_Indexation',
            ],
            '/Discovery/': [
                '',
                '01_Termux_and_ssh',
                '02_Settings_for_sublime',
                '03_Pip3',
                '04_Chrome_headless',
                '05_Gitmoji',
                '06_Harddisk',
                '07_Cmder',
            ],
            '/': [
                '',
                'Start',
                'Template',
                'About',
                'Disclaimer',
            ]
        },

        // 假定是 GitHub. 同时也可以是一个完整的 GitLab URL
        repo: 'SigureMo/notev',
        // 自定义仓库链接文字。默认从 `themeConfig.repo` 中自动推断为
        // "GitHub"/"GitLab"/"Bitbucket" 其中之一，或是 "Source"。
        repoLabel: 'Github',

        // 以下为可选的编辑链接选项

        // 假如你的文档仓库和项目本身不在一个仓库：
        docsRepo: 'SigureMo/notev',
        // 假如文档不是放在仓库的根目录下：
        docsDir: 'docs',
        // 假如文档放在一个特定的分支下：
        docsBranch: 'master',
        // 默认是 false, 设置为 true 来启用
        editLinks: true,
        // 默认为 "Edit this page"
        editLinkText: '欢迎提出建议！',
    },
}