# Git Handbook

## 合并 PR

比如有这样的一个 PR `https://github.com/SigureMo/course-crawler/pull/6` ，我们可以看到它的 PRid 为 6

那么我们就可以

```bash
git fetch origin pull/6/head:dev
```

这样就创建了一个新的分支 `dev` 用以保存新的 PR 分支， `checkout` 过去就可以看到该分支下的具体内容了，修改好后返回 `master` 并 `merge` 即可

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

1. [拉取 Github PR 代码到本地分支](https://www.huangyunkun.com/2018/06/15/pull-github-pr-to-local-branch/)
2. [github 同步原作者代码](https://blog.csdn.net/lym152898/article/details/80505406)
