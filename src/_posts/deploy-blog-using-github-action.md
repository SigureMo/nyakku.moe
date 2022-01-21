---
title: 采用 GitHub Action 自动化部署博客
date: 2020-06-22
category: 迹
tags:
   - CI
   - GitHub
---

::: tip

博客的部署往往只需要一行命令，但却需要花费我几分钟在本地的构建时间，完成博客内容后本应该放松放松心情，这几分钟的等待显得尤为惹人生厌

那么如何解决这个问题呐？当然是自动化部署啦，这样我们每次只需要将写完的博客 Push 到 GitHub 上，就可以触发相应的 CI 以完成博客的自动部署咯，所以这里就介绍如何使用 GitHub Action 来自动化部署博客

:::

<!-- more -->

## GitHub Action 的使用

关于自动化部署，起初我接触的是 Travis CI，配置起来非常简单～

后来 GitHub Action 完全开放，我就完全转 GitHub Action 这个自定义更加方便的 CI 系统了，起初我的自动化部署脚本也是自己写的 Shell 脚本，因为那时候相关的部署 Action 尚不完善，不支持直接 Push 到根地址，不过前段时间支持了之后我就放弃自己写的脚本咯 (๑˃◡˂๑)

GitHub Action 的使用方法也非常简单～只需要在项目根目录新建 `.github/workflows/` 文件夹，再在其中新建相应的 YAML 配置文件即可，比如 `hello-github-action.yml`，名字随意啦，只是为了区分而已～

文件内写入相应的内容

```yaml
# action 名字
name: Hello GitHub Action

on:
   # 触发条件，比如 push pull_request 等
   push:
      branches:
         - main

jobs:
   build-and-deploy:
      # 运行环境
      runs-on: ubuntu-latest
      steps:
         # 各步的任务
         - name: Hello GitHub Action
           run: echo 'Hello GitHub Action'
```

这样我们就完成了一个简单的 GitHub Action，它会在我们每次 push 到 main 分支时触发，之后就会打印 `Hello GitHub Action`，虽然看不见……

## 自动化部署到 GitHub Pages

我们对上面的配置稍作修改，目标就是在源仓库 Push 时触发，此时将博客源码构建成静态文件，并将它们 Push 到 GitHub Pages 仓库即可

```yaml
name: VuePress Deploy

on:
   push:
      branches:
         - main

jobs:
   build-and-deploy:
      runs-on: ubuntu-latest
      steps:
         # 使用某个 Repo
         - name: Checkout 🛎️
           uses: actions/checkout@v2

         # 构建静态文件
         - name: Install and Build 🔧
           run: |
              npm install yarn
              yarn
              yarn docs:build

         # 部署到 GitHub Pages
         - name: Deploy 🚀
           uses: peaceiris/actions-gh-pages@v3
           with:
              personal_token: ${{ secrets.PERSONAL_TOKEN }}
              publish_dir: docs/.vuepress/dist
              external_repository: SigureMo/SigureMo.github.io
              publish_branch: main
              cname: nyakku.moe
              user_name: 'github-actions[bot]'
              user_email: 'github-actions[bot]@users.noreply.github.com'
```

这里第一步是使用你的源代码 repo，其中 uses 是指使用了某个现成的 Action，比如这个 `actions/checkout` 就是 [`github.com/actions/checkout`](https://github.com/actions/checkout) 的 `v2` 版本，如果需要 submodule 或者 lfs 可以通过 `with` 选项来修改参数

第二步是将博客源码构建成静态文件，不同的框架的构建方法自然不同，我这里是以 VuePress 作为示例

第三步就是将构建好的静态文件 Push 到目标的 GitHub Pages 对应的 Repo 了，这里使用的是 [`peaceiris/actions-gh-pages`](https://github.com/peaceiris/actions-gh-pages)，如果你只需要部署到当前 Repo 的 `gh-pages` 分支上的话，你只需要配置以下内容即可

```yaml
- name: Deploy 🚀
  uses: peaceiris/actions-gh-pages@v3
  with:
     github_token: ${{ secrets.GITHUB_TOKEN }}
     publish_dir: docs/.vuepress/dist
```

这里的 `secrets.GITHUB_TOKEN` 不需要配置，GitHub 会自动提供

但是如果你和我一样想部署到 `<username>.github.io` 的话，就需要稍微改动一下啦，该 Action 提供了非常丰富的参数以供配置

由于目标 Repo 和目标分支都变了，就需要分别设置下 `external_repository` 和 `publish_branch` 这两个参数咯

另外，由于 Push 到外部 Repo 的话 `GITHUB_TOKEN` 的权限不足，因此需要提供其它的验证方式，比如 `personal_token` 和 `deploy_key`，这里提一下 `personal_token` 的生成与配置方式，该方法相比于后者也更方便一些

依次进入`个人 Settings -> Developer settings -> Personal access tokens` 点击 `Generate new token`，随便填写个名字，然后下面勾选 `repo`（权限） 后确认 `Generate token`

由于生成的 token 只能看一次，请确定复制后再关闭页面

之后依次进入 `源 repo -> Settings -> Secrets`，点击 `New secret`，Name 字段填写 `PERSONAL_TOKEN`，Value 字段粘贴刚刚生成的 token 即可

这样，该 action 在 `secrets.PERSONAL_TOKEN` 处就可以获得刚刚生成的拥有读写 repo 权限的 token，然后传入该 action 的 `personal_token` 参数，进而完成整个部署过程

这样就完成了权限的配置啦，该 Action 还提供了很多比较实用的参数，比如 `cname`，更多详情去看它的文档吧

完成这些，就可以重新 push 一下源代码 repo 试一下啦，还可以在源 repo 的 Actions 中可以看到相关进度

## References

1. [actions-gh-pages](https://github.com/peaceiris/actions-gh-pages)
