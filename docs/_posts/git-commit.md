---
title: Git 提交说明
date: 2018-09-16
category: 迹
tags:
   - Git
---

::: tip

Git Commit Message 虽然可以随意描述，但是应当使用对当前更改最合适的描述才有意义，而且在 review 代码的时候能够最快地找到相关位置，Commit Message 的规范有助于提高其意义，下面会分别介绍通用的规范以及可爱的 Gitmoji 规范

:::

<!-- more -->

## Git Commit 规范

### Gitmoji

| view                        | code                          | mean                                          | translate                                      |
| --------------------------- | ----------------------------- | --------------------------------------------- | ---------------------------------------------- |
| :art:                       | `:art:`                       | Improve structure / format of the code.       | 改良结构和代码格式                             |
| :zap:                       | `:zap:`                       | Improve performance.                          | 优化性能                                       |
| :fire:                      | `:fire:`                      | Remove code or files.                         | 移除代码或文件                                 |
| :bug:                       | `:bug:`                       | Fix a bug.                                    | 修复 bug                                       |
| :ambulance:                 | `:ambulance:`                 | Critical hotfix.                              | 修复关键程序                                   |
| :sparkles:                  | `:sparkles:`                  | Introduce new features.                       | 引入新功能                                     |
| :pencil:                    | `:pencil:`                    | Write docs.                                   | 写文档                                         |
| :rocket:                    | `:rocket:`                    | Deploy stuff.                                 | 部署任务                                       |
| :lipstick:                  | `:lipstick:`                  | Add or update the UI and style files.         | 添加或更新 UI 和样式文件                       |
| :tada:                      | `:tada:`                      | Begin a project.                              | 开始一个项目                                   |
| :white_check_mark:          | `:white_check_mark:`          | Add or update tests.                          | 添加或更新测试用例                             |
| :lock:                      | `:lock:`                      | Fix security issues.                          | 修复安全问题                                   |
| :bookmark:                  | `:bookmark:`                  | Release / Version tags.                       | 发版/版本标签                                  |
| :rotating_light:            | `:rotating_light:`            | Remove linter warning.                        | 移除 linter 的警告                             |
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
| :hammer:                    | `:hammer:`                    | Add or update build scripts.                  | 添加或更新构建脚本                             |
| :globe_with_meridians:      | `:globe_with_meridians:`      | Internationalization and localization.        | 国际化和本地化（i18n）                         |
| :pencil2:                   | `:pencil2:`                   | Fix typos.                                    | 修复拼写错误                                   |
| :poop:                      | `:poop:`                      | Write bad code that needs to be improved.     | 需要改进的代码                                 |
| :rewind:                    | `:rewind:`                    | Revert changes.                               | 恢复更改                                       |
| :twisted_rightwards_arrows: | `:twisted_rightwards_arrows:` | Merge branches.                               | 合并分支                                       |
| :package:                   | `:package:`                   | Add or update compiled files or packages.     | 添加或更新编译的文件或包                       |
| :alien:                     | `:alien:`                     | Update code due to external API changes.      | 由于外部 API 更改而更新代码                    |
| :truck:                     | `:truck:`                     | Move or rename files.                         | 移动或重命名文件                               |
| :page_facing_up:            | `:page_facing_up:`            | Add or update license.                        | 添加或更新许可证                               |
| :boom:                      | `:boom:`                      | Introduce breaking changes.                   | 引入不兼容的变动                               |
| :bento:                     | `:bento:`                     | Add or update assets.                         | 添加或更新静态资源                             |
| :wheelchair:                | `:wheelchair:`                | Improve accessibility.                        | 提高可访问性                                   |
| :bulb:                      | `:bulb:`                      | Add or update comments in source code.        | 在源代码中添加或更新注释                       |
| :beers:                     | `:beers:`                     | Write code drunkenly.                         | 醉醺醺地编写代码                               |
| :speech_balloon:            | `:speech_balloon:`            | Add or update text and literals.              | 添加或更新用于文本、对话框等文本内容相关的更改 |
| :card_file_box:             | `:card_file_box:`             | Perform database related changes.             | 执行与数据库相关的更改                         |
| :loud_sound:                | `:loud_sound:`                | Add or update logs.                           | 添加或更新日志                                 |
| :mute:                      | `:mute:`                      | Remove logs.                                  | 删除日志                                       |
| :busts_in_silhouette:       | `:busts_in_silhouette:`       | Add or update contributor(s).                 | 添加或更新贡献者                               |
| :children_crossing:         | `:children_crossing:`         | Improve user experience / usability.          | 改善用户体验/可用性                            |
| :building_construction:     | `:building_construction:`     | Make architectural changes.                   | 改变架构                                       |
| :iphone:                    | `:iphone:`                    | Work on responsive design.                    | 进行响应式设计                                 |
| :clown_face:                | `:clown_face:`                | Mock things.                                  | 可笑的事情                                     |
| :egg:                       | `:egg:`                       | Add or update an easter egg.                  | 添加或更新彩蛋内容                             |
| :see_no_evil:               | `:see_no_evil:`               | Add or update a .gitignore file.              | 添加或更新.gitignore 文件                      |
| :camera_flash:              | `:camera_flash:`              | Add or updatesnapshots.                       | 添加或更新快照                                 |
| :alembic:                   | `:alembic:`                   | Experiment new things.                        | 实验性内容                                     |
| :mag:                       | `:mag:`                       | Improve SEO.                                  | SEO 优化                                       |
| :label:                     | `:label:`                     | Add or update types (Flow, TypesScript).      | 添加或更新类型声明(Flow、TypeScript)           |
| :seedling:                  | `:seedling:`                  | Add or update seed files.                     | 添加或更新种子文件                             |
| :triangular_flag_on_post:   | `:triangular_flag_on_post:`   | Add, update, or remove feature flags.         | 添加、更新或删除功能标志                       |
| :goal_net:                  | `:goal_net:`                  | Catch errors.                                 | 发现错误                                       |
| :dizzy:                     | `:dizzy:`                     | Add or update animations and transitions.     | 添加或更新动画和过渡                           |
| :wastebasket:               | `:wastebasket:`               | Deprecating code that needs to be cleaned up. | 清理冗余代码                                   |

### Commit Message 规范

组成： header 、 body 、 footer

即

```
<type>(<scope>): <subject>
<BLANK LINE>
<body>
<BLANK LINE>
<footer>
```

#### Header

-  type

   -  ==feat==: 添加新功能
   -  ==fix==: 修复 bug
   -  ==docs==: 仅对文档进行修改
   -  ==style==: 对代码语义无影响的格式修改（如去除无用空格、格式化等等修改）
   -  ==refactor==: 代码重构（即不是新增功能，也不是修改 bug 的代码变动）
   -  ==perf==: 提高性能的代码修改
   -  ==test==: 测试用例添加及修改
   -  ==build==: 影响构建系统或外部依赖关系的更改
   -  ==ci==: 更改 CI 配置文件和脚本
   -  ==chore==: 其它不涉及源码以及测试的修改
   -  ==revert==: 回退到某一个历史版本，下面详述

-  scope

   scope 用于说明 commit 影响的范围，如果你的修改影响了不止一个 scope ，你可以使用 `*` 代替

-  subject

   subject 是 commit 目的的简短描述，不超过 50 个字符

   -  以动词开头，使用第一人称现在时，比如 change，而不是 changed 或 changes
   -  第一个字母小写
   -  结尾不加句号（.）

#### Body

Body 是详细描述

#### Footer

-  不兼容变动（BREAKING CHANGE）
-  关闭 Issue 如 `Closes #234`

#### Revert

用于撤销之前的某次 commit ，以 `revert` 开头，后面跟着被撤销 Commit 的 Header ，如

```
revert: feat(pencil): add 'graphiteWidth' option

This reverts commit 667ecc1654a317a13331b17617d973392f415f02.
```

# References

1. [conventional-commit-types @d1fb9cc](https://github.com/commitizen/conventional-commit-types)
2. [gitmoji @5f15232](http://gitmoji.carloscuesta.me/)
3. [程序员提交代码的 emoji 指南——原来表情文字不能乱用](https://www.h5jun.com/post/gitmoji.html)
4. [用 gitmoji 来提交你的 git commit 吧](https://github.com/mytac/blogs/issues/2)
5. [git commit 规范指南](https://segmentfault.com/a/1190000009048911?utm_source=tag-newest)
6. [优雅地提交你的 Git Commit Message](https://juejin.im/post/5afc5242f265da0b7f44bee4)
