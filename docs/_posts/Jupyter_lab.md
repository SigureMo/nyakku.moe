---
title: 使用 JupyterLab 开启全新的炼丹之旅
date: 2020-03-06
category: 迹
tags:
   - DL
---

::: tip

本地设备的配置大大限制了炼丹的效率，如果有一个合适的服务器的话，如何配置能最方便地进行炼丹呢？

:::

<!-- more -->

## 1 什么是 JupyterLab？

什么工具更适合在云端炼丹呢？基于在本地使用 VS-Code 的流畅体验，我最初尝试的便是 VS-Code 的 Remote-SSH 扩展，经过一段时间的体验之后，发现 VS-Code 的远程连接很不稳定（也可能是 VPN 不稳定的原因），而且对 Jupyter 支持并不是很好。而直接使用 Jupyter Notebook 的话，多个文件以及终端之间的切换与管理又非常不方便。JupyterLab 刚好结合了两者的优点，将多 Tab 标签页、终端以及 Jupyter 集成起来，最重要的是它还支持丰富的扩展~

## 2 如何使用

### 2.1 安装

直接使用 pip 就可以安装啦~

```bash
pip install jupyterlab
```

### 2.2 基本配置

为了安全考虑，先配置下密码，这里使用 Ipython 生成密钥

```bash
ipython
```

执行命令生成密钥

```python
from notebook.auth import passwd
passwd()
```

之后按照提示输入密码即可，将最终的输出序列（`sha1:????????`） copy 下来

下面首先生成配置文件

```bash
jupyter lab --generate-config
```

修改配置文件

```bash
vim ~/.jupyter/jupyter_notebook_config.py
```

添加以下配置信息

```
# 将 IP 设置为 *，意味允许任何 IP 访问
c.NotebookApp.ip = '*'
# 这里的密码就是前面生成的那一串序列
c.NotebookApp.password = 'sha1:????????'
# 服务器上没有浏览器供 Jupyter 打开
c.NotebookApp.open_browser = False
# 监听端口设置为 8888 或其他自己喜欢的端口
c.NotebookApp.port = 8888
# 允许远程访问
c.NotebookApp.allow_remote_access = True
```

接下来就可以运行啦~

### 2.2 使用

```bash
jupyter lab --ip=0.0.0.0
```

此时输入刚刚的密码，在本地浏览器输入 `http://<服务器IP>:8888` 即可打开 JupyterLab，不过打开可能需要花点时间，要稍稍等待一下~

::: tip

如果需要长期练一颗丹的话，可以使用 `nohup` 命令防止退出终端后也自动终止，另外配合 `&` 可以将其转为后台运行

```bash
nohup jupyter lab --ip=0.0.0.0 &
# nohup jupyter lab --ip=0.0.0.0 >/dev/null 2>log & # 只输出错误信息到日志文件
# nohup jupyter lab --ip=0.0.0.0 >/dev/null 2>&1 & # 什么信息也不要
```

关于 `nohup` 的更多使用方法可见 Ref3

:::

## 3 丰富的扩展

暂未深入体验，可参见 Ref4

# Reference

1. [部署自己的交互式 Python 开发环境 JupyterLab](https://tf.wiki/zh/appendix/jupyterlab.html)
2. [JupyterLab 远程访问配置方法（CentOS7）](https://www.cnblogs.com/ratels/p/11387740.html)
3. [Linux nohup 实现后台运行程序及查看（nohup 与 &）](https://www.jb51.net/article/169783.htm)
4. [15 个好用到爆炸的 Jupyter Lab 插件](https://zhuanlan.zhihu.com/p/101070029)
5. [Nohup 过大的清理](https://blog.csdn.net/crisschan/article/details/72967027)
