---
title: Git Handbook
date: 2018-09-16
categories:
   - 雁影·留
tags:
   - Git
---

## Git Commit 规范

### Gitmoji

| view                        | code                          | mean                                         | translate                            |
| --------------------------- | ----------------------------- | -------------------------------------------- | ------------------------------------ |
| :art:                       | `:art:`                       | Improving structure / format of the code.    | 改良结构和代码格式                   |
| :zap:                       | `:zap:`                       | Improving performance.                       | 优化性能                             |
| :fire:                      | `:fire:`                      | Removing code or files.                      | 移除代码或文件                       |
| :bug:                       | `:bug:`                       | Fixing a bug.                                | 修复 bug                             |
| :ambulance:                 | `:ambulance:`                 | Critical hotfix.                             | 修复关键程序                         |
| :sparkles:                  | `:sparkles:`                  | Introducing new features.                    | 引入新功能                           |
| :memo:                      | `:memo:`                      | Writing docs.                                | 写文档                               |
| :rocket:                    | `:rocket:`                    | Deploying stuff.                             | 部署新功能                           |
| :lipstick:                  | `:lipstick:`                  | Updating the UI and style files.             | 升级 UI 和样式文件                   |
| :tada:                      | `:tada:`                      | Initial commit.                              | 初次提交                             |
| :white_check_mark:          | `:white_check_mark:`          | Adding tests.                                | 添加测试用例                         |
| :lock:                      | `:lock:`                      | Fixing security issues.                      | 修复安全问题                         |
| :apple:                     | `:apple:`                     | Fixing something on macOS.                   | 修复 MacOS 下的问题                  |
| :penguin:                   | `:penguin:`                   | Fixing something on Linux.                   | 修复 Linux 下的问题                  |
| :checkered_flag:            | `:checkered_flag:`            | Fixing something on Windows.                 | 修复 Windows 下的问题                |
| :robot:                     | `:robot:`                     | Fixing something on Android.                 | 修复 Android 下的问题                |
| :green_apple:               | `:green_apple:`               | Fixing something on iOS.                     | 修复 iOS 下的问题                    |
| :bookmark:                  | `:bookmark:`                  | Releasing / Version tags.                    | 发版/版本标签                        |
| :rotating_light:            | `:rotating_light:`            | Removing linter warning.                     | 移除 linter 的警告                   |
| :construction:              | `:construction:`              | Work in progress.                            | 工作在进行中                         |
| :green_heart:               | `:green_heart:`               | Fixing CI Build.                             | 修复 CI 构建问题                     |
| :arrow_down:                | `:arrow_down:`                | Downgrading dependencies.                    | 降级依赖库                           |
| :arrow_up:                  | `:arrow_up:`                  | Upgrading dependencies.                      | 升级依赖库                           |
| :pushpin:                   | `:pushpin:`                   | Pinning dependencies to specific versions.   | 将依赖库固定到特定版本               |
| :construction_worker:       | `:construction_worker:`       | Adding CI build system.                      | 添加 CI 构建系统                     |
| :chart_with_upwards_trend:  | `:chart_with_upwards_trend:`  | Adding analytics or tracking code.           | 添加分析或跟踪代码。                 |
| :recycle:                   | `:recycle:`                   | Refactoring code.                            | 重构代码                             |
| :whale:                     | `:whale:`                     | Work about Docker.                           | Docker 相关工作                      |
| :heavy_plus_sign:           | `:heavy_plus_sign:`           | Adding a dependency.                         | 添加一个依赖项                       |
| :heavy_minus_sign:          | `:heavy_minus_sign:`          | Removing a dependency.                       | 删除一个依赖项                       |
| :wrench:                    | `:wrench:`                    | Changing configuraton files.                 | 改变配置文件                         |
| :globe_with_meridians:      | `:globe_with_meridians:`      | Internationalization and localization.       | 国际化和本地化                       |
| :pencil2:                   | `:pencil2:`                   | Fixing typos.                                | 修复拼写错误                         |
| :hankey:                    | `:hankey:`                    | Writing bad code that needs to be improved.  | 需要改进的代码                       |
| :rewind:                    | `:rewind:`                    | Reverting changes.                           | 恢复更改                             |
| :twisted_rightwards_arrows: | `:twisted_rightwards_arrows:` | Merging branches.                            | 合并分支                             |
| :package:                   | `:package:`                   | Updating compiled files or packages.         | 更新编译的文件或包                   |
| :alien:                     | `:alien:`                     | Updating code due to external API changes.   | 由于外部 API 更改而更新代码          |
| :truck:                     | `:truck:`                     | Moving or renaming files.                    | 移动或重命名文件                     |
| :page_facing_up:            | `:page_facing_up:`            | Adding or updating license.                  | 添加或更新许可证                     |
| :boom:                      | `:boom:`                      | Introducing breaking changes.                | 介绍突破性变化                       |
| :bento:                     | `:bento:`                     | Adding or updating assets.                   | 添加或更新静态资源                   |
| :ok_hand:                   | `:ok_hand:`                   | Updating code due to code review changes.    | 由于代码审阅更改而更新代码           |
| :wheelchair:                | `:wheelchair:`                | Improving accessibility.                     | 提升可访问性                         |
| :bulb:                      | `:bulb:`                      | Documenting source code.                     | 记录源代码                           |
| :beers:                     | `:beers:`                     | Writing code drunkenly.                      | 醉醺醺地编写代码                     |
| :speech_balloon:            | `:speech_balloon:`            | Updating text and literals.                  | 更新文本或字面量                     |
| :card_file_box:             | `:card_file_box:`             | Performing database related changes.         | 执行与数据库相关的更改               |
| :loud_sound:                | `:loud_sound:`                | Adding logs.                                 | 添加日志                             |
| :mute:                      | `:mute:`                      | Removing logs.                               | 删除日志                             |
| :busts_in_silhouette:       | `:busts_in_silhouette:`       | Adding contributor(s).                       | 添加贡献者                           |
| :children_crossing:         | `:children_crossing:`         | Improving user experience / usability.       | 改善用户体验/可用性                  |
| :building_construction:     | `:building_construction:`     | Making architectural changes.                | 改变架构                             |
| :iphone:                    | `:iphone:`                    | Working on responsive design.                | 进行响应式设计                       |
| :clown_face:                | `:clown_face:`                | Mocking things.                              | 可笑的事情                           |
| :egg:                       | `:egg:`                       | Adding an easter egg.                        | 加入一个彩蛋                         |
| :see_no_evil:               | `:see_no_evil:`               | Adding or updating a .gitignore file         | 添加或更新.gitignore 文件            |
| :camera_flash:              | `:camera_flash:`              | Adding or updating snapshots                 | 添加或更新快照                       |
| :alembic:                   | `:alembic:`                   | Experimenting new things                     | 尝试新事物                           |
| :mag:                       | `:mag:`                       | Improving SEO                                | 搜索优化                             |
| :wheel_of_dharma:           | `:wheel_of_dharma:`           | Work about Kubernetes                        | Kubernetes 相关工作                  |
| :label:                     | `:label:`                     | Adding or updating types (Flow, TypesScript) | 添加或更新类型声明(Flow、TypeScript) |

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

   -  ==feat==：新功能（feature）
   -  ==fix==：修补 bug
   -  ==docs==：文档（documentation）
   -  ==style==： 格式（不影响代码运行的变动）
   -  ==refactor==：重构（即不是新增功能，也不是修改 bug 的代码变动）
   -  ==test==：增加测试
   -  ==chore==：构建过程或辅助工具的变动

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

-  不兼容变动
-  关闭 Issue 如 `Closes #234`

#### Revert

用于撤销之前的某次 commit ，以 `revert` 开头，后面跟着被撤销 Commit 的 Header ，如

```
revert: feat(pencil): add 'graphiteWidth' option

This reverts commit 667ecc1654a317a13331b17617d973392f415f02.
```

## 合并 PR

### 放在新的分支

比如有这样的一个 PR `https://github.com/SigureMo/course-crawler/pull/6` ，我们可以看到它的 PR id 为 6

那么我们就可以

```bash
git fetch origin pull/6/head:dev
```

这样就创建了一个新的分支 `dev` 用以保存新的 PR 分支， `checkout` 过去就可以看到该分支下的具体内容了，修改好后返回 `master` 并 `merge` 即可

### 使用一个 commit 合并所有内容

如果想要只使用一个 commit 提交所有内容，可以在回到 `master` 后 `merge` 的时候加一个参数 `squash` ，之后再提交

```bash
git merge dev --squash
git commit
```

## 同步原作者代码

### 添加 upstream remote

-  使用 git remote -v 查看远程状态

   ```bash
   git remote -v
   ```

-  添加原作者的远程仓库到 `remote` （本例使用 `upstream` 作为远程仓库名）

   ```bash
   git remote add upstream <原作者远程仓库地址>
   ```

### 同步 fork

-  从上游仓库 fetch 分支和提交点，传送到本地，并会被存储在一个本地分支 upstream/master

   ```bash
   git fetch upstream
   ```

-  切换到本地主分支

   ```bash
   git checkout master
   ```

-  把 `upstream/master` 分支合并到本地 `master`
   ```bash
   git merge upstream/master
   ```
-  push 到远程仓库
   ```bash
   git push origin master
   ```

### 解决冲突

直接编辑冲突文件，然后提交更改重新 `push` 即可

### 如何删除已经添加的远程仓库

```bash
git remote rm <remoteRep>
```

# Reference

1. [程序员提交代码的 emoji 指南——原来表情文字不能乱用](https://www.h5jun.com/post/gitmoji.html)
2. [Gitmoji](http://gitmoji.carloscuesta.me/)
3. [用 gitmoji 来提交你的 git commit 吧](https://github.com/mytac/blogs/issues/2)
4. [git commit 规范指南](https://segmentfault.com/a/1190000009048911?utm_source=tag-newest)
5. [拉取 Github PR 代码到本地分支](https://www.huangyunkun.com/2018/06/15/pull-github-pr-to-local-branch/)
6. [github 同步原作者代码](https://blog.csdn.net/lym152898/article/details/80505406)
