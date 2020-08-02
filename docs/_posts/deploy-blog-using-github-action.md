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

关于自动化部署，起初我接触的是 Travis CI，配置很简单，使用起来非常简单

后来 GitHub Action 完全开放，我就完全转 GitHub Action 这个自定义更加方便的 CI 系统了，起初我的自动化部署脚本也是自己写的 Shell 脚本，因为那时候相关的部署 Action 尚不完善，不支持直接 Push 到根地址，不过前段时间支持了之后我就放弃自己写的脚本咯

那么如何使用 GitHub Action 呢？只需要在项目根目录新建 `.github/workflows/` 文件夹，再在其中新建相应的 YAML 配置文件即可，比如 `hello-github-action.yml`，名字随意啦，只是为了区分

文件内写入相应的内容

```yaml
# action 名字
name: Hello GitHub Action

on:
   # 触发条件，比如 push pull_request 等
   push:
      branches:
         - master

jobs:
   build-and-deploy:
      # 运行环境
      runs-on: ubuntu-latest
      steps:
         # 各步的任务
         - name: Hello GitHub Action
           run: echo 'Hello GitHub Action'
```

这样我们就完成了一个简单的 GitHub Action，它会在我们每次 push 到 master 分支时触发，之后就会打印 `Hello GitHub Action`，虽然看不见……

## 自动化部署到 GitHub Pages

我们对上面的配置稍作修改，目标就是在源仓库 Push 时触发，此时将博客源码构建成静态文件，并将它们 Push 到 GitHub Pages 仓库即可

```yaml
name: Vuepress Deploy

on:
   push:
      branches:
         - master

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
              publish_branch: master
              cname: sigure.xyz
              user_name: "github-actions[bot]"
              user_email: "github-actions[bot]@users.noreply.github.com"
```

这里第一步是使用你的源代码 repo，其中 uses 是指使用了某个现成的 Action，比如这个 `actions/checkout` 就是 [`github.com/actions/checkout`](https://github.com/actions/checkout) 的 `v2` 版本，如果需要 submodule 或者 lfs 可以通过 `with` 选项来修改参数

第二步是将博客源码构建成静态文件，不同的框架的构建方法自然不同，我这里是以 Vuepress 作为示例

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

这样，该 action 在 `secrets.PERSONAL_TOKEN` 处就可以获得刚刚生成的拥有读写 repo 权限的 token，然后传入该 action 的 ACCESS_TOKEN 参数，进而完成整个部署过程

这样就完成了权限的配置啦，该 Action 还提供了很多比较实用的参数，比如 `cname`，更多详情去看它的文档吧

完成这些，就可以重新 push 一下源代码 repo 试一下啦，还可以在源 repo 的 Actions 中可以看到相关进度

## 同步到 Coding Pages

虽然 GitHub Pages 非常方便，但是国内访问实在是太慢，加载太久的话就木有人愿意继续访问的说，虽然想尝试下 CDN，但貌似 CDN 有着更新不及时的缺点，强迫症表示无法接受

Coding 是国内的软件开发平台，国内访问速度还不错，因此利用 Coding 作为国内的访问镜像也许是个不错的选择，只需要将国内域名解析到 Coding Pages，国外解析到 GitHub Pages 就可以啦

我们首先在 Coding 新建一个项目，选择项目模板时记得选择 `DevOps 项目`

进入项目，在`持续部署 -> 静态网站` 中开启该功能，记得勾选自动部署功能，之后就可以获得访问地址啦，而且还可以配置自己的域名

为了能够自动将 GitHub Pages 的静态文件同步过来，我们需要配置一个 Action

```yaml
- name: Sync to Coding 🔀
  uses: wearerequired/git-mirror-action@v1
  env:
     SSH_PRIVATE_KEY: ${{ secrets.SSH_PRIVATE_KEY }}
  with:
     source-repo: "git@github.com:SigureMo/SigureMo.github.io.git"
     destination-repo: "git@e.coding.net:sigure/notev/notev.git"
```

`source-repo` 和 `destination-repo` 自然分别对应 GitHub Pages Repo 和 Coding Pages Repo 的 ssh 地址，后者在 `代码仓库 -> 设置 -> 仓库设置` 下的 `仓库设置` 即可获得

当然，我们需要拥有 GitHub Pages Repo 的读权限和 Coding Pages Repo 的写权限，该 Action 才能进行，这里需要配置下 ssh 公钥与私钥，公钥配置在 GitHub Pages Repo 和 Coding Pages Repo，而负责执行 Action 的源代码 Repo 则存储私钥

为了安全起见，不要使用现有的 ssh 密钥，创建一个临时的 ssh 密钥对即可

私钥直接保存在 GitHub 源代码 Repo 的 `Settings -> secrets` 中，而公钥则要保存在两个目标 repo 中

对于 GitHub，直接在该目标 repo 中的 `Settings -> Deploy keys` 中添加该公钥即可

对于 Coding，也是在 `代码仓库 -> 设置 -> 仓库设置` 的 `部署公钥` 配置即可，记得勾选写入权限

此时再次触发 Action 就可以同步到 Coding Pages 啦

## 同步到 Gitee Pages

那么，为什么之前没有选择 Gitee 呢？因为 Gitee 的自动部署以及自定义域名都是 Gitee Pages Pro 的服务，前者可以通过 GitHub Action 来完成，但后者就没有办法了，如果你没有绑定域名的需求的话，Gitee 会是更好的选择

我们在 Gitee 创建一个 GitHub 目标 repo 对应的 repo，在创建时的 `Import` 选项中填写 GitHub 目标 repo 的地址

之后在新的 Gitee repo 下中的 `Services -> Gitee Pages` 开启该服务，emmm，此时就可以注意到该服务的更新需要手动更新，并不能像 GitHub Pages 那样自动更新

为了完成 GitHub 目标 repo 到 Gitee 目标 repo 的同步，以及 Gitee Pages 的自动更新，我们还需要配置新的 Action

```yaml
# 同步到 Gitee repo
- name: Sync to Gitee 🔀
  uses: wearerequired/git-mirror-action@v1
  env:
     SSH_PRIVATE_KEY: ${{ secrets.SSH_PRIVATE_KEY }}
  with:
     source-repo: "git@github.com:SigureMo/SigureMo.github.io.git"
     destination-repo: "git@gitee.com:siguremo/SigureMo.git"

# 更新 Gitee Pages
- name: Build Gitee Pages 👷
  uses: yanglbme/gitee-pages-action@master
  with:
     gitee-username: SigureMo
     gitee-password: ${{ secrets.GITEE_PASSWORD }}
     gitee-repo: SigureMo/SigureMo
```

首先我们需要将 GitHub 的静态文件存储 repo 的代码同步到 Gitee，它需要配置下 `SSH_PRIVATE_KEY`，也就是能够同时访问两个 repo 的私钥，这个和前面 Coding 的配置方法都一样啦，私钥放 GitHub 源 Repo，公钥放两个目标 Repo，值得注意的是，Gitee 的公钥不能直接在该 Repo 下的 `Settings -> Deploy keys` 进行配置，因为在这里配置的公钥并不能拥有对该 repo 的写权限，所以我们需要在个人 `Settings -> SSH keys` 中添加该公钥

第二步就是更新 Gitee Pages 了，这一步很简单，将 Gitee 的密码配置到 `Settings -> secrets` 即可

现在再重新 Push，你会发现 Gitee Pages 也会立刻重新构建，不过 Gitee 可能会弹出在非常用地登陆的消息，因为更新过程使用你的密码进行了登陆

# References

1. [actions-gh-pages](https://github.com/peaceiris/actions-gh-pages)
2. [gitee-pages-action](https://github.com/yanglbme/gitee-pages-action)
3. [利用 GitHub 和 Coding 为 Hexo 博客开启 Https](https://zhuanlan.zhihu.com/p/111786790)
