---
title: Git 提交信息规范
published: 2018-09-16
category: 找点好玩的
tags:
  - Git
---

:::tip

Git Commit Message 虽然可以随意描述，但使用没有意义的描述对于后续 review 代码以及理解代码用途等方面都会造成巨大的影响。因此 Commit Message 具有意义是最基本的要求，此外，你还应该遵守一定的格式规范，这样能够让大家更快更清晰地了解该 Commit 的详情。这里我主要介绍下常规的 Git Commit 规范和 Gitmoji 规范，最后介绍下我常用的相关配置。

:::

<!-- more -->

## 常规 Commit Message 规范

一个 Commit Message 最基本的组成为： `header`、`body`、`footer`

书写起来就是下面这样

```
<type>(<scope>): <subject>
<BLANK LINE>
<body>
<BLANK LINE>
<footer>
```

当然 `header` 就是第一行的内容，它包含了 `type`、`scope` 和 `subject`

### Header

#### type

根据 [conventional-commit-types](https://github.com/commitizen/conventional-commit-types), `type` 的可选值一般来说是有下面几种，

- feat: 添加新功能
- fix: 修复 bug
- docs: 仅对文档进行修改
- style: 对代码语义无影响的格式修改（如去除无用空格、格式化等等修改）
- refactor: 代码重构（既不是新增功能，也不是修改 bug 的代码变动）
- perf: 提高性能的代码修改
- test: 测试用例添加及修改
- build: 影响构建系统或外部依赖关系的更改
- ci: 更改 CI 配置文件和脚本
- chore: 其它不涉及源码以及测试的修改

#### scope

`scope` 用于说明 commit 影响的范围，如果你的修改影响了不止一个 scope ，你可以使用 `*` 代替，该字段一般可以省略

#### subject

`subject` 是 commit 目的的简短描述，不超过 50 个字符

- 以动词开头，使用第一人称现在时，比如 change，而不是 changed 或 changes
- 第一个字母小写
- 结尾不加句号（.）

### Body

`Body` 是详细描述，在这里可以详细介绍该次改动的具体修改内容

### Footer

`Footer` 一般只包含以下两种情况

- 不兼容变动（BREAKING CHANGE）
- 关闭 Issue 如 `Closes #234`

### Revert

此外，当你使用 `git revert` 撤销之前的某次 commit 时，该次的 Commit Message 应当以 `revert` 开头，后面跟着被撤销 Commit 的 Header ，如

```
revert: feat(pencil): add 'graphiteWidth' option

This reverts commit 667ecc1654a317a13331b17617d973392f415f02.
```

## Gitmoji 规范

[Gitmoji](https://gitmoji.carloscuesta.me/) 规范允许你在 Commit Message 中使用 [Emoji](https://emojipedia.org/)，简单的说，你可以用生动形象的 Emoji 来表示该次 Commit 的 type，Gitmoji 推荐的 `header` 格式是

```
<gitmoji>: <subject>
```

这里的 subject 首字母仍是大写字母，其它倒与常规的规范没什么区别，`gitmoji` 的具体选值如下

<!-- prettier-ignore -->
| view                        | code                          | mean                                          | translate                                      |
| --------------------------- | ----------------------------- | --------------------------------------------- | ---------------------------------------------- |
| :art:                       | `:art:`                       | Improve structure / format of the code.       | 改良结构和代码格式                             |
| :zap:                       | `:zap:`                       | Improve performance.                          | 优化性能                                       |
| :fire:                      | `:fire:`                      | Remove code or files.                         | 移除代码或文件                                 |
| :bug:                       | `:bug:`                       | Fix a bug.                                    | 修复 bug                                       |
| :ambulance:                 | `:ambulance:`                 | Critical hotfix.                              | 紧急的热修复                                   |
| :sparkles:                  | `:sparkles:`                  | Introduce new features.                       | 引入新功能                                     |
| :memo:                      | `:memo:`                      | Add or update documentation.                  | 添加或更新文档                                  |
| :rocket:                    | `:rocket:`                    | Deploy stuff.                                 | 部署                                       |
| :lipstick:                  | `:lipstick:`                  | Add or update the UI and style files.         | 添加或更新 UI 和样式文件                       |
| :tada:                      | `:tada:`                      | Begin a project.                              | 开始一个全新的项目～                                   |
| :white_check_mark:          | `:white_check_mark:`          | Add or update tests.                          | 添加或更新测试用例                             |
| :lock:                      | `:lock:`                      | Fix security issues.                          | 修复安全问题                                   |
| :bookmark:                  | `:bookmark:`                  | Release / Version tags.                       | 发版 / 版本标签                                  |
| :rotating_light:            | `:rotating_light:`            | Fix compiler / linter warnings.               | 修复编译器或者 linter 的 warning                        |
| :construction:              | `:construction:`              | Work in progress.                             | 工作在进行中                                   |
| :green_heart:               | `:green_heart:`               | Fix CI Build.                                 | 修复 CI 构建问题                               |
| :arrow_down:                | `:arrow_down:`                | Downgrade dependencies.                       | 降级依赖库                                     |
| :arrow_up:                  | `:arrow_up:`                  | Upgrade dependencies.                         | 升级依赖库                                     |
| :pushpin:                   | `:pushpin:`                   | Pin dependencies to specific versions.        | 将依赖库固定到特定版本                         |
| :construction_worker:       | `:construction_worker:`       | Add or update CI build system.                | 添加或更新 CI 构建系统                         |
| :chart_with_upwards_trend:  | `:chart_with_upwards_trend:`  | Add or update analytics or track code.        | 添加或更新分析或跟踪代码                       |
| :recycle:                   | `:recycle:`                   | Refactor code.                                | 重构代码                                       |
| :heavy_plus_sign:           | `:heavy_plus_sign:`           | Add a dependency.                             | 添加一个依赖项                                 |
| :heavy_minus_sign:          | `:heavy_minus_sign:`          | Remove a dependency.                          | 删除一个依赖项                                 |
| :wrench:                    | `:wrench:`                    | Add or update configuration files.            | 添加或改变配置文件                             |
| :hammer:                    | `:hammer:`                    | Add or update development scripts.            | 添加或更新构开发脚本                             |
| :globe_with_meridians:      | `:globe_with_meridians:`      | Internationalization and localization.        | 国际化和本地化（i18n）                         |
| :pencil2:                   | `:pencil2:`                   | Fix typos.                                    | 修复拼写错误                                   |
| :poop:                      | `:poop:`                      | Write bad code that needs to be improved.     | 当前代码尚需优化                                 |
| :rewind:                    | `:rewind:`                    | Revert changes.                               | 撤销之前的修改                                  |
| :twisted_rightwards_arrows: | `:twisted_rightwards_arrows:` | Merge branches.                               | 合并分支                                       |
| :package:                   | `:package:`                   | Add or update compiled files or packages.     | 添加或更新编译的文件或包                       |
| :alien:                     | `:alien:`                     | Update code due to external API changes.      | 由于外部 API 更改而更新代码                    |
| :truck:                     | `:truck:`                     | Move or rename resources (e.g.: files, paths, routes).  | 移动或重命名资源（诸如：文件、路径、路由）|
| :page_facing_up:            | `:page_facing_up:`            | Add or update license.                        | 添加或更新 LICENSE                            |
| :boom:                      | `:boom:`                      | Introduce breaking changes.                   | 引入不兼容的变动                               |
| :bento:                     | `:bento:`                     | Add or update assets.                         | 添加或更新静态资源                             |
| :wheelchair:                | `:wheelchair:`                | Improve accessibility.                        | 提高可访问性                                   |
| :bulb:                      | `:bulb:`                      | Add or update comments in source code.        | 在源代码中添加或更新注释                       |
| :beers:                     | `:beers:`                     | Write code drunkenly.                         | 醉醺醺地编写代码                               |
| :speech_balloon:            | `:speech_balloon:`            | Add or update text and literals.              | 添加或更新用于文本、对话框等文本字面量相关的更改    |
| :card_file_box:             | `:card_file_box:`             | Perform database related changes.             | 执行与数据库相关的更改                         |
| :loud_sound:                | `:loud_sound:`                | Add or update logs.                           | 添加或更新日志                                 |
| :mute:                      | `:mute:`                      | Remove logs.                                  | 删除日志                                       |
| :busts_in_silhouette:       | `:busts_in_silhouette:`       | Add or update contributor(s).                 | 添加或更新贡献者                               |
| :children_crossing:         | `:children_crossing:`         | Improve user experience / usability.          | 改善用户体验/可用性                            |
| :building_construction:     | `:building_construction:`     | Make architectural changes.                   | 改变架构                                       |
| :iphone:                    | `:iphone:`                    | Work on responsive design.                    | 进行响应式设计                                 |
| :clown_face:                | `:clown_face:`                | Mock things.                                  | 添加或更改 mock                                |
| :egg:                       | `:egg:`                       | Add or update an easter egg.                  | 添加或更新彩蛋内容                             |
| :see_no_evil:               | `:see_no_evil:`               | Add or update a .gitignore file.              | 添加或更新 .gitignore 文件                     |
| :camera_flash:              | `:camera_flash:`              | Add or updatesnapshots.                       | 添加或更新快照                                 |
| :alembic:                   | `:alembic:`                   | Perform experiments.                          | 实验性内容                                     |
| :mag:                       | `:mag:`                       | Improve SEO.                                  | 提高 SEO                                       |
| :label:                     | `:label:`                     | Add or update types.                          | 添加或更新类型声明                               |
| :seedling:                  | `:seedling:`                  | Add or update seed files.                     | 添加或更新种子文件                             |
| :triangular_flag_on_post:   | `:triangular_flag_on_post:`   | Add, update, or remove feature flags.         | 添加、更新或删除功能标志                       |
| :goal_net:                  | `:goal_net:`                  | Catch errors.                                 | 捕获错误                                     |
| :dizzy:                     | `:dizzy:`                     | Add or update animations and transitions.     | 添加或更新动画和过渡                           |
| :wastebasket:               | `:wastebasket:`               | Deprecate code that needs to be cleaned up.   | 清理冗余代码                                   |
| :passport_control:          | `:passport_control:`          | Work on code related to authorization, roles and permissions. | 处理与授权、账户和权限相关的代码   ｜
| 🩹 <!-- :adhesive_bandage: (need markdown-it-emoji 2.0)--> | `:adhesive_bandage:`          | Simple fix for a non-critical issue.          | 简单修复一个非关键问题                         |
| 🧐 <!-- :monocle_face: (need markdown-it-emoji 2.0)-->   | `:monocle_face:`              | Data exploration/inspection.                  | 数据探索/检查                         |
| :coffin:                    | `:coffin:`                    | Remove dead code.                             | 清除无效代码                                 |
| 🧪 <!-- :test_tube: -->     | `:test_tube:`                  | Add a failing test.                          | 添加一个运行失败的测试用例（TDD 第一步）                                 |
| :necktie:                   | `:necktie:`                   | Add or update business logic.                 | 添加或更新业务逻辑                               |
| 🩺                          | `:stethoscope:`               | Add or update healthcheck.                    | 添加或更新健康检查                               |
| 🧱                          | `:bricks:`                    | Infrastructure related changes.               | 基础设施相关改动                                 |
| 🧑‍💻                          | `:technologist:`              | Improve developer experience.                 | 提升开发体验                                   |
| 🔐                          | `:closed_lock_with_key:`      | Add or update secrets.                        | 添加或更新加密内容                              |
| 💸                          | `:money_with_wings:`          | Add sponsorships or money related infrastructure. | 添加赞助商或者资金支持相关内容                       |
| 🧵                          | `:thread:`                    | Add or update code related to multithreading or concurrency. | 添加或更新多线程或与并发相关的代码                            |

在提交时你可以按照喜好使用其 code 或者直接使用 emoji，因为 GitHub 是能够正确将这些 code 渲染为对应的 emoji 的。

由于 `gitmoji` 有着丰富的类型，因此其可以表达的信息会更多一些，这使得你能在 `<subject>` 中省去一些内容。但相对的，由于类型实在太多，记忆起来也是相当地麻烦，起初我基本每次提交都来查一下表格，所以如果你使用的是 VS Code，建议使用 [gitmoji-vscode](https://github.com/vtrois/gitmoji-vscode) 插件以简化这一过程。

## 我自己常用的规范

虽然 gitmoji 很可爱，但总觉得与常规兼容性太差，因此我平时使用的规范是常规规范前面加上一个 `gitmoji`，也就是

```
<gitmoji> <type>(<scope>): <subject>
<BLANK LINE>
<body>
<BLANK LINE>
<footer>
```

在 `scope` 不太重要的情况，我一般都把 `scope` 省略掉，以免长度过长

## References

1. [gitmoji](http://gitmoji.dev/)
2. [gitmoji 改动追踪](https://github.com/carloscuesta/gitmoji/commits/master/src/data/gitmojis.json)
3. [git commit 规范指南](https://segmentfault.com/a/1190000009048911?utm_source=tag-newest)
