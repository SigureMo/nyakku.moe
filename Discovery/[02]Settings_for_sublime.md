# Settings for sublime
## 1 sublime初配置
### 1.1 安装repl
1. Cmd+Shift+P调出快捷命令窗口，输入install，选择Package Control:Install Package；
2. 输入sublimerepl，点击选中，然后它就会在后台安装；
3. 安装完之后，查看 Tools->SublimeREPL。
4. 添加自定义快捷键，点击菜单Preferences->Key Bindings，在右侧添加如下json代码：
```JSON
[
	{ "keys": ["f5"], "caption": "SublimeREPL:Python","command": "run_existing_window_command", "args":
		{
			"id": "repl_python_run","file": "config/Python/Main.sublime-menu"
		}
	}
	, 
]
```
5. Alt+shift+2 分屏

# Reference

[sublime设置参考](https://www.cnblogs.com/zhaof/p/8126306.html)

[linux 配置python3](https://www.cnblogs.com/unflynaomi/p/5704293.html)

# Amendant Record
1. 180421 Add #1

[goto S_Note;](../README.md)

[return 0;](#settings-for-sublime)
