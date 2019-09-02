---
title: C++ Handbook
date: 2019-04-27
categories:
   - 雁影·留
tags:
   - C++
---

由于对 C++ 的使用大多限于刷算法，所以对很多语法的了解并不是很深，而且对于很多好用的接口函数都需要现查现用，为了方便查阅，根据局部性原理，就在自己这里做个 $Cache$ 吧 :joy:

<!-- more -->

## String

### C++ 中的 string 与 char\* 的转换

由于有时需要在 C++ 中调用 C 的接口函数，但是往往接口要求的是 `char*` 而不是 `string` （当然， C 也没有），所以就需要对 `string` 进行转化

-  `const char* p = str.data();`
-  `const char *p = str.c_str();`

### 流操作

举个例子即可

```cpp
stringstream namestream;
string name;
namestream << "a.txt";
name = string(namestream.str());
```

### 数字与字符串的相互转换

-  利用 `stringstream` （需 `#include <sstream>`）

   -  字符串转浮点型

      ```cpp
      double a ;
      string res= "123.32";
      stringstream ss;
      ss << res;
      ss >> a;
      ```

   -  浮点型转字符串

      ```cpp
      double a = 123.32;
      string res;
      stringstream ss;
      ss << a;
      ss >> res;
      ```

-  利用 `sscanf` 和 `sprintf` （需 `#include <string>`）

   -  字符串转浮点型

      ```cpp
      char str1[]="123.321";
      double b;
      sscanf(str1, "%lf", &b);
      ```

   -  浮点型转字符串

      ```cpp
      char str1[10];
      double b=123.321;
      sprintf(str1, "%.3lf", b);
      ```

### 如何按行获取输入？

```cpp
getline(cin, s);
```

### 寻找子串

```cpp
position = s.find("b", 5);
```

意为从位置 `5` 开始寻找子串（缺省为 `0`），返回第一个找到的位置，若未找到，则返回 `string::npos` ，可据此判断子串是否在子串中

## 排序算法

### Sort

```cpp
Sort(start, end, 排序方法)
```

第三个参数缺省为从小到大排列，比如有一个 `int a[10]`

```cpp
sort(a, a+10);
```

便可对其进行排序

那么如何自定义排序方法呢？

比如我们定义

```cpp
bool compare(int a, int b)
{
  return a > b;
}
```

之后调用

```cpp
sort(a, a+10, compare);
```

即可获得从大到小的序列

## 随机数的生成

> 头文件 `stdlib.h`

`rand()` 会生成一个随机整型数，我们可以通过定义宏来实现对上限的限制

```cpp
#define random(x) (rand()%x)
#define randint(start, end) (rand()%(end-start) + start)
```

另外 `void srand(unsigned int seed)` 可以对喂一个随机种子

# Reference

1. [C++中 string、char \*、char[]的转换](https://www.cnblogs.com/Pillar/p/4206452.html)
2. [sort 函数的用法(C++排序库函数的调用)](https://www.cnblogs.com/jjzzx/p/5122381.html)
3. [C++ string 中的 find()函数](https://www.cnblogs.com/wkfvawl/p/9429128.html)
4. [c++数字和字符串的转换](https://www.cnblogs.com/houchen/p/8984164.html)
