---
title: Cmder
date: 2018-10-01
categories:
   - 百家·集
tags:
   - Tool
   - Windows
---

## 1 Start

果然是一折腾就停不下来呀，刚重装了系统，又打起了原来没用明白的 cmder 的主意

### 1.1 Merge

重装系统后装机的话，第一个想到的就是 Git 呀，往回迁移资源的时候因为 U 盘挂掉了，所以不少项目文件没了，不过还好有不少在 GitHub 上有备份。

不过这次我在安装 Gitbash 前想到了 cmder，之前用 GitBash、cmd、Powershell 的时候总是忙于三者的切换，曾经试过 cmder 但没用明白，就搁置了下来，但是这次我可不会傻下去了

### 1.2 PATH

将 Cmder 加入环境变量 PATH 中，这个就不赘述了

### 1.3 Context menu

加入右键菜单，要在管理员权限下输入`Cmder.exe /REGISTER ALL`

### 1.4 alias

自定义短命令，在 Environment 里添加

```
set PATH=%ConEmuBaseDir%\Scripts;%PATH%
set LANG=zh_CN.UTF-8
ls=ls --show-control-chars -F
alias ll=ls -al --show-control-chars --color $*
alias gs=git status
alias gl=git log
alias ga=git add
alias gc=git commit
pwd=cd
clear=cls
```

## 2 VS code & Cmder

最近迷上了 VS code，所以开始对 VS code 进行了简单的配置，但是怎么直接从 VS code 里面的终端使用 cmder 呢，经过简单的搜索找到了答案

### 2.1 Creat a bat

创建一个批处理文件，内容如下：

```batch
@echo off
SET CMDER_ROOT=<CmderPath>
"%CMDER_ROOT%\vendor\init.bat"
```

嗯，随便起个名字就好，扩展名'.bat'
::: tip
将`<CmderPath>`替换成你的 cmder.exe 所在目录
:::

### 2.2 Change the settings

使用快捷键`Ctrl + Shift + P`，在弹出的命令框内输入`settings`，找到 User Settings，然后在 settings.json 里面编辑它，在右侧替换框内添加：

```json
"terminal.integrated.shell.windows": "cmd.exe",
"terminal.integrated.shellArgs.windows": [
       "/k",
        "<ScriptPath>"
    ],
```

::: tip
将`<ScriptPath>`替换成你的.bat 文件的具体路径，注意路径中对某些字符的转义
:::

# Reference

1. [Windows 命令行增强 cmder chocolatey 配置指南](https://www.jianshu.com/p/479d974078a7)
2. [超爽的 Windows 终端 Cmder](http://www.360doc.com/content/17/1122/07/1353678_706036759.shtml)
3. [win10 下的 VSCode 用 cmder 作默认的命令终端(shell)](https://www.jianshu.com/p/c3b162df3b57)
