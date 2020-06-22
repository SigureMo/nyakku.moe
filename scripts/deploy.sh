#!/usr/bin/env sh

ACCESS_TOKEN=$1
USERNAME=SigureMo       # 你的用户名
REPO=""                 # 如果不指定，将发布在 <username>.github.io
BRANCH=""               # 如果不指定，将发布在 master 分支
CNAME=sigure.xyz    # 你想发布到的域名

if [ $ACCESS_TOKEN ]
then TOKEN_PREFIX="${ACCESS_TOKEN}@"
else TOKEN_PREFIX=""
fi

if [ $BRANCH ]
then BRANCH_POSTFIX=":${BRANCH}"
else BRANCH_POSTFIX=""
fi

if [ $REPO ]
then REMOTE=https://${TOKEN_PREFIX}github.com/${USERNAME}/${REPO}.git
else REMOTE=https://${TOKEN_PREFIX}github.com/${USERNAME}/${USERNAME}.github.io.git
fi

# 确保脚本抛出遇到的错误
set -e

# 生成静态文件
npm run docs:build

# 进入生成的文件夹
cd docs/.vuepress/dist

# 如果是发布到自定义域名
if [ $CNAME ]
then echo $CNAME > CNAME
fi

# 初始化仓库并提交发布
git init
git config user.name "GitHub Actions"
git config user.email "support@github.com"
git add -A
time=$(date "+%Y-%m-%d %H:%M:%S")
git commit -m "rebuild @${time}"
git push -f $REMOTE master${BRANCH_POSTFIX}

cd -
