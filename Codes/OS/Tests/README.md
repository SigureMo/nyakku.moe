# 操作系统实验

## 0 上机准备

-  熟悉 Cygwin 环境
-  编译源程序使用 `gcc xxx.c -o xxx.out`
-  学习 Linux (Unix) 的常用命令
-  学习 vi 编辑器的使用
-  C 语言语法

> 不用 Cygwin ，直接装 Linux 的双系统也是可以的，本人将使用 Ubuntu Server 16.04 对实验环境进行模拟

## 1 进程管理（20'）

### 1.1 实验目的

加深对于进程并发执行概念的理解，实践并发进程的创建和控制方法。观察和体验进程的动态特性，进一步理解进程生命期期间创建、变换、撤销状态变换的过程，掌握进程控制的方法，链接父子进程间的控制和协作关系，练习 Linux 系统中进程创建与控制有关的系统调用的编程和调试技术

### 1.2 实验说明

-  与进程创建、执行有关的系统调用说明

   -  进程可以通过系统调用 `fork()` 创建子进程并和其子进程并发执行

   -  子进程初始的执行映像是父进程的一个副本，子进程可以通过 `exec()` 系统调用族装入一个新的执行程序

   -  父进程可以使用 `wait()` 或 `waitpid()` 系统调用等待子进程的结束并负责收集和清理子进程的退出状态

-  `fork()` 系统调用语法

   ```c
   #include <unistd.h>
   pid_t fork(void);
   ```

   `fork` 成功创建子进程后将返回子进程的进程号，不成功会返回 `-1`

-  `exec` 系统调用有一组 6 个函数，其中示例实验中引用了 `execve` 系统调用语法

   ```c
   #include <unistd.h>
   int execve(const char *path, const char *argv[], const char *envp[]);
   ```

   -  `path` 要装入的新的执行文件的绝对路径名字符串
   -  `argv[]` 要传递给新执行程序的完整的命令参数列表（可以为空）
   -  `envp[]` 要传递给新执行程序的完整的环境变量参数列表（可以为空）

   `exec` 执行成功后将用一个新的程序代替原进程，但进程号不变，它绝不会再返回到调用进程了；如果 `exec` 调用失败，它会返回 `-1`

-  `getpid()` 获取进程的 `pid`

> `fork` 调用一次却能返回两次，它可能是

-  父进程中，返回子进程 `pid`
-  子进程中，返回 `0`
-  如果出现一个错误，返回 `-1`

### 1.3 实验内容

1. 实现如下所示关系进程，并且每个进程都执行自己独立的程序，打印自己的 `pid`，每个父进程打印其子进程的 `pid`

   $$
   P \to Sub1 \to Sub2
   $$

   [test1-1.c](test1-1.c)

2. 实现如下所示关系进程，并且每个进程都执行自己独立的程序，打印自己的 `pid`，每个父进程打印其子进程的 `pid`

   $$
   \begin{aligned}
   P & \to Sub1 \\
   & \to Sub2
   \end{aligned}
   $$

   [test1-2.c](test1-2.c)

3. 编写一个命令处理程序，能处理 `max(m, n)`、 `min(m, n)`、 `average(m, n, l)` 这几个命令（使用 `exec` 函数族）

   [test1-3](test1-3/)

## 2 处理器调度（20'）

## 3 存储管理上机作业（20'）

## 4 磁盘移臂调度算法实验（20'）

## 5 文件管理作业（20'）

> 本文档转自杨志豪老师实验题目 PDF 版，添加部分个人笔记

# Refs

1. [c 语言：fork 函数详解](https://www.cnblogs.com/jeakon/archive/2012/05/26/2816828.html)
2. [linux c 之 wait 和 waitpid 函数的用法和总结](https://blog.csdn.net/u011068702/article/details/54409273)
3. [linux c 之 exec 函数族](https://blog.csdn.net/butterfly5211314/article/details/84945108)

Copyright 2019 DUT [杨志豪老师](http://faculty.dlut.edu.cn/zhyang_CS/zh_CN/jxzy/749840/content/1641.htm)
