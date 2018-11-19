# Termux and ssh
## 1 初设置
### 1.1 juicessh

1. 由termux接触juicessh，稍作了解与学习
2. 使用Git创建windows公钥并上传GitHub
    1. 打开git bash
    2. 执行生成公钥和私钥的命令：ssh-keygen -t rsa 并按回车3下（为什么按三下，是因为有提示你是否需要设置密码，如果设置了每次使用Git都会用到密码，一般都是直接不写为空，直接回车就好了）。会在一个文件夹里面生成一个私钥 id_rsa和一个公钥id_rsa.pub。（可执行start ~ 命令，生成的公私钥在 .ssh的文件夹里面）
    3. 执行查看公钥的命令：cat ~/.ssh/id_rsa.pub  
    4. 生成在~/.ssh下的.pub是公钥，另一个同名文件是私钥
3.	使用juice连接windows
安装powershell server 用上述生成的公钥认证，并修改编码为utf-8/简体中文
4.	使用juice连接termux
私钥 -> 更新私钥 -> 生成 -> 密钥格式RSA -> 长度1024bit
长按认证列表里的termux -> 导出公钥，追加到authorized_keys，在termux内执行下列code：
```Bash
 cat >> ~/.ssh/authorized_keys << EOF
#公钥
EOF
```

### 1.2 启用外部存储

在termux内执行下列code获得外部存储（会在home下生成手机文件目录）：
```Bash
termux-setup-storage
```
执行下列code建立软连接方便与qq tim WeChat互传信息
```Bash
ln –s /data/data/com.termux/files/home/storage/shared/tencent/QQfile_recv qq
ln –s /data/data/com.termux/files/home/storage/shared/tencent/ TIMfile_recv TIM
ln –s /data/data/com.termux/files/home/storage/shared/tencent/MicroMsg/Download Wechat
```

# Reference

[Termux初设置参考](https://www.cnblogs.com/learnpy/p/7350905.html)

[Termux初设置参考2](https://www.sfantree.com/termux_01/)

# Amendant Record
1. 180421 Add #1

[goto S_Note;](../README.md)

[return 0;](#termux-and-ssh)
