# Cmder
## 1 Start
果然是一折腾就停不下来呀，刚重装了系统，又打起了原来没用明白的cmder的主意
### 1.1 Merge
重装系统后装机的话，第一个想到的就是Git呀，往回迁移资源的时候因为U盘挂掉了，所以不少项目文件没了，不过还好有不少在GitHub上有备份。

不过这次我在安装Gitbash前想到了cmder，之前用GitBash、cmd、Powershell的时候总是忙于三者的切换，曾经试过cmder但没用明白，就搁置了下来，但是这次我可不会傻下去了

### 1.2 PATH
将Cmder加入环境变量PATH中，这个就不赘述了

### 1.3 Context menu
加入右键菜单，要在管理员权限下输入`Cmder.exe /REGISTER ALL`

### 1.4 alias
自定义短命令，在Environment里添加
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

# Amendant Record
1. 181001 Add #1

# Reference
1. [Windows 命令行增强 cmder chocolatey 配置指南](https://www.jianshu.com/p/479d974078a7)
2. [超爽的Windows终端Cmder](http://www.360doc.com/content/17/1122/07/1353678_706036759.shtml)