---
title: C to ++
date: 2019-10-04
categories:
   - 雁影·留
tags:
   - C
   - C++
---

::: tip

什么是 C++ ？顾名思义，它是在 C 语言的基础上进行了语法的扩展，但同时保留了对 C 语法的兼容性，这就使得 C++ 上能 OOP ，下能精准分配内存，正因为“无所不能”，所以想要一次性全掌握也是难上加难，但由于我们往往并不需要掌握的面面俱到（除非真的要坚持使用 C++ 开发），比如说只是用来刷刷题的话，我们只掌握部分语法即可，本篇也主要面对有着 C 语言基础而苦于入门 C++ 的初学者，让我们将 C++ 学成 C-- 吧~

> 学习中，会持续修改与更新，如有错误与疏漏，欢迎改正~

:::

<!-- more -->

## :sparkles: 基础篇

基础篇主要针对从 C 语言过渡到 C++ 的新手，适合作为刷算法时的查阅资料，如果想了解面向对象等高级特性，请看进阶篇

## 与 C 的兼容性

不严谨地说， C++ 是完全兼容 C 代码的，你完全可以在 C++ 代码中使用任何 C 语言的语法，之后使用 C++ 的编译器进行编译即可

既然是从 C 过渡到 C++ ，我们便要先尝试在 C++ 里写 C 的代码，然后尝试使用 C++ 的特有语法进行替换，以写出 C++ 风格的代码

### Hello, World!

首先，我们如何在 C 语言中打印 `"Hello, World!"` 呢？

```c
#include <stdio.h>

int main(){
   printf("Hello, World!\n");
   return 0;
}
```

我们可以在 C++ 文件中试着编译运行一下上面的代码，当然是可以运行的，但是 C++ 风格的一般会怎么写呢？

```cpp
#include <iostream>

using namespace std;

int main(){
   cout << "Hello, World!" << endl;
   return 0;
}
```

整体上还是差不多啦，但是有几个细节变了

-  导入的头文件由 `<stdio.h>` 变成了 `<iostream>` ，这个很好说，因为原来我们需要 C 的标准输入输出，而现在需要的是 C++ 的输入输出头文件，所以自然要换个头文件了
-  多了 `using namespace std;` ，这是一个命名空间，这里选择了 `std` 这个命名空间，这样，在之后使用 `std` 空间下的变量 `std::cout` 以及 `std::endl` 就可以省略代表命名空间的 `std` 和后面的作用域符号 `::` 啦
-  输出函数使用了 `cout` ，而且输出方式也不是使用函数了，这个是使用流插入的方式进行输出，可以方便的输出一些内容，具体的后面说

很明显，C++ 主体的语法还是沿用 C 的风格，只不过在此基础上进行了部分的改动，下面我们了解下都有什么改动吧

::: tip 如何在终端编译运行

如果你有着趁手的 IDE （比如 Dev-C++、Visual Studio）的话，可以跳过这里了，如果你喜欢使用编辑器编辑并手动编译的话，也可以跳过这里了，我猜你肯定会自己编译了 :joy:

选一个你喜欢的编译器，并添加到环境变量，比如 `gcc` 或者 `clang`

```bash
g++ <source_code> -o a.out    # 编译
a.out                         # 运行
```

:::

### C++ 的命名空间 `namespace`

因为各个头文件中都有着自己命名的变量，我们不能保证引入的各个头文件没有冲突的变量名，正是为了避免这一问题， C++ 中增加了 `namespace` 这一概念，在某一命名空间下变量，便需要通过 `<space>::<var>` 来访问，这样避免了不同空间下明明冲突的问题，但是使用起来也变麻烦了

如果某个命名空间使用的特别频繁的话，我们可以使用 `using namespace <space>;` 来解决这一问题，在代码中添加这一句之后，我们之后再使用该空间下的变量便不必再写完整的 `<space>::<var>` 了，只需要 `<var>` 即可

当然，这么用的弊端之前也说了，一般情况下，并不推荐使用 `using namespace <space>;` ，但是如果只是刷题的场合下，用用 `std` 还是没有问题的，所以放心用就好啦~

### C++ 中的头文件

与 C 语言所不同的是，C++ 标准化的头文件并不带 `.h`

而 C 语言原有的标准头文件由 `<xxx.h>` 变成了 `<cxxx>` ，比如 `<stdio.h>` 变成了 `<cstdio>` ，`<string.h>` 变成了 `<cstring>`

## 输入与输出

### C 语言的 scanf 与 printf

首先看一个简单的例子，如果你想将下面的输入转换为一个人的姓名、学号、成绩、成绩等级，然后再依次输出，应该怎么做呢？

```
tom 201600001 96 A
```

如果是 C 语言，自然是

```c
#include <stdio.h>

int main(){
  char name[10];
  long id;
  int score;
  char level;
  scanf("%s %ld %d %c", name, &id, &score, &level);
  printf("%s %ld %d %c\n", name, id, score, level);
  return 0;
}
```

这里我们使用==模板字符串==将所需数据匹配出来，并按照模板字符串进行输出

### C++ 中的 cin 与 cout

`cin` 与 `cout` 分别被称作标准输入流和标准输出流，它可以配合流插入符 `>>` 和 `<<` 进行很好的工作，还是刚刚那个例子，在 C++ 中有什么比较好的写法呢？

```cpp {10,11}
#include <iostream>

using namespace std;

int main() {
  string name;
  long id;
  int score;
  char level;
  cin >> name >> id >> score >> level;
  cout << name << " " << id << " " << score << " " << level << endl;
  return 0;
}
```

-  `line10`: 将标准输入流中的值从左到右依次存入各个变量中
-  `line11`: 从左到右依次将各个变量对应的字符串插入到标准输出流中，其中 `std::endl` 相当于换行符

我们可以很**方便**的获取**输入**的数据，而且可以**快速**对某个变量进行**输出**

但是其弱势也很明显，格式化输出很麻烦，所以需要格式化输出的时候并不建议使用 `cout` ，直接使用 `printf` 就好，另外，`cin` 与 `cout` 的使用会引起性能的少许降低，所以如果需要频繁输出输出建议使用 C 语言中的 `scanf` 和 `printf`

事实上 `cout` 只适合在某些需要 debug 的位置进行临时输出（我喜欢使用 print 作为 debug 方式，不喜欢 gdb），而 `cin` 配合 C++ 的 string 有着很好的效果，就比如

-  `cin` 按行获取输入

   ```cpp
   getline(cin, s);
   ```

::: tip 如何选用？

一般刷题的时候能用 `scanf` 与 `printf` 就用它们，如果 `cin` 更方便的话，则可以使用 `cin` 和 `cout`，但尽量不要混用

:::

## 原生支持的 C99 语法

很多 C 语言在 C99 中才得到支持的语法在 C++ 中是原生支持的，这就使得 C++ 相比于 C 语言有着很强的易用性

### 变量可以随时声明

C++ 中的变量的声明并不一定需要在最前面，我们在写代码的时候，在需要新的变量的时候再进行声明也是可以的，这样也可以增加可读性

### 原生支持的 bool 类型

C99 下，需要引入 `stdbool.h` 才直接使用 `bool` 类型，而 C++ 直接将其作为标准类型，这样我们可以更加方便的使用更加易读的 `true` 和 `false` 而不是 `1` 和 `0` 了

### 原生支持的块级作用域

在块内声明的变量便可以作为一个块级变量存在，块内对该变量的操作无法影响到块外同名变量，而且出块会自动释放，避免同名变量的管理问题

比如我们现在的 `for` 循环可以直接简写成这样，变量 `i` 是在块内声明的，并不会影响到块外的 `i`

```cpp
int i = 9;
for (int i = 0; i < 10; i++) {
   cout << i << endl;
}
```

## 一些易用的特性

### 能够提高性能的 inline 函数

某个小功能如果经常出现在代码里怎么办？很明显，我们会将其写成一个函数，这样代码会简洁很多，但是函数的调用本身是会大大降低性能的，函数的调用需要入栈出栈操作，频繁的调用会大幅降低效率，有没有两全之法呢？

在 C++ 里是有的，就是马上要介绍的 `inline` 关键字，使用了 `inline` 关键字的行内函数会被插入到被调用的位置，比如如下的代码

```cpp
inline int Max(int a, int b) {
   return a > b ? a : b;
}

int main(){
   int a = 0, b = 1, c, d, e;
   c = Max(a, b);
   d = Max(b, c);
   e = Max(c, d);
   return 0;
}
```

实际上它是转化成下面的代码进一步进行编译的

```cpp
int main(){
   int a = 0, b = 1, c, d, e;
   c = a > b ? a : b;
   d = b > c ? b : c;
   e = c > d ? c : d;
   return 0;
}
```

函数的代码被直接插入在了调用它的位置，这样就不会有调用函数时候性能下降的问题了？

但是这也带来一个问题，就是程序长度的增加，所以这并不适合比较大的函数，而且即便你使用了 `inline` 关键字，是否将其作为行内函数直接插入也是要看编译器的，编译器会根据程序的长度判断是否转换

### 传引用与传值的区别

C++ 中最不习惯的便是新增了一种传引用的操作，我们只需要在参数表上增加一个 `&` ，就可以对该变量进行写操作，也就是传引用之后，传过去的真的是这个变量，而不仅仅是它的值

比如我们想利用函数（无返回值）对一个数值进行修改，直接传值是不行的

```cpp
void inc(int i) {
   i++;
}

int main(){
   int i = 0;
   inc(i);
   return 0;
}
```

为了解决这一问题，我们可以通过传指针解决

```cpp
void inc(int *ptri) {
   (*ptri)++;
}

int main(){
   int i = 0;
   inc(&i);
   return 0;
}
```

函数内部拿到 `i` 的指针后，对指针所指的值进行修改，这样也便修改了 `i` 的值

但如果你觉得这样很麻烦的话，C++ 中只需要加一个符号就能满足你的需求

```cpp
void inc(int &i) {
   i++;
}

int main(){
   int i = 0;
   inc(i);
   return 0;
}
```

真的是只多了一个符号 `&` ，这样实际上传的是 `i` 的引用，你可以通过引用直接修改这个变量的值，而不需要解引用等操作

::: tip 简单地说

传值相当于直接将原变量的值传给了函数内的局部变量，而局部变量的修改是不会影响到原变量的

而传引用时是将原变量的别名传给了局部变量，虽然也是创建了一个新的局部变量，但是该局部变量实际存储的是原变量的地址，所有操作会被处理成间接寻址

至于具体操作的时候，如果在函数内不需要对原变量值进行修改的话，我们直接传值就好了，而在需要修改的时候，我们在对应参数表的位置加上一个 `&` 就好了

:::

### C++ 中的 const

C （C89） 中也是有 `const` 的，但是它的 `const` 实际上是只读的变量而并不是常量，所以使用上有着很大的限制，比如下面的语句，在 C 语言语法下就会报错

```cpp
const int ARRAY_SIZE = 10;
int arr[ARRAY_SIZE];
```

而 C++ 中的 `const` 是真正的常量，可以通过如下方法定义一个常量

```Cpp
const double PI = 3.14159;
const int SIZE = 3;
int const X = 5;
```

这里要注意的是，指针常量与常量指针的区别

-  常量指针 `const int* p1;`
-  指针常量 `int* const p1;`
   -  数组名就是一个指针常量
      > `const` 在谁前面谁就不可变

### 不断发展的新特性……

C++ 以 98 年的标准为最初的标准，但是之后其特性不断发展，自 11 年以来，每 3 年都会产生一个新的标准，也就是说现在在基础的标准上又出现了 `C++11` 、 `C++14` 、`C++17` 三个标准， `C++20` 也即将出世，每一个新的标准都会增加新的特性，使得我们使用 C++ 更加容易

那么我们如何能够使用这些新的特性呢？

如果是终端的话，在编译的时候添加参数 `-std` 即可，比如想使用 C++11 的特性，按如下方式编译运行即可

```bash
g++ <source_code> -std=c++11 -o a.out
a.out
```

如果是一些 IDE 的话，随便找找设置就能找到的

## 字符串 string

C 语言诞生的时代，计算机主要处理的是数据，而随着互联网的兴起等原因，计算机处理字符串的需求越来越大，但是 C 语言自带的字符数组用起来并不方便，因此 C++ 中增加了 string 类型，方便对字符串的操作

首先看下 C 中的“字符串”

```c
char str[] = "123456";
```

它会创建一个 7 位的字符的数组，各位分别为 `{'1', '2', '3', '4', '5', '6', '\0'}` ，对于字符串的操作需要依赖于 `string.h` 中的一些函数来实现，但是这仍然很不方便，能否让字符串和数字一样可以“加加减减”呢？

C++ 中的 string 实际上是一个类，它内置了很多常用的方法，并对其很多运算符进行重载，使得 C++ 中的字符串非常好用

### 重载的运算符

#### `+` 字符串的拼接

我们可以很容易地通过 `+` 完成字符串的拼接

```cpp
string a = "111";
string b = "222";
cout << a + b << endl;
```

#### `[]` 像操作数组一样操作字符串

我们还可以利用 `[]` ，像操作 C 语言中的字符数组一样操作字符串

```cpp
string a = "111";
char c = a[0];
```

#### `+=` 字符串的追加

`+=` 可以将一个字符串追加到另一个字符串末尾

```cpp
string a = "111";
string b = "222";
a += b;
cout << a << endl;
```

#### `==` 字符串判等

对字符串内容进行判等，如果两字符串内容完全相同则返回 `true`

### 寻找子串

```cpp
position = s.find("b", 5);
```

意为从位置 `5` 开始寻找子串（缺省为 `0`），返回第一个找到的位置，若未找到，则返回 `string::npos` （使用 `-1` 即可），可据此判断子串是否在串中

### 截取子串

```cpp
string substr = s.substr(pos, n);
```

从原串 `s` 的 `pos` 位开始，截取长度为 `n` 的子串

### 替换子串

```cpp
s.replace(pos, n, substr);
```

将原串位置 `pos` 开始的 `n` 位子串替换为 `substr` 的内容

### C++ 中的 string 与 char\* 的转换

由于有时需要在 C++ 中调用 C 的接口函数，但是往往接口要求的是 `char*` 而不是 `string` （当然， C 也没有），所以就需要对 `string` 进行转化

-  `const char *p = str.data();`
-  `const char *p = str.c_str();`

### 流操作

举个例子即可

```cpp
stringstream namestream;
string name;
namestream << "a.txt";
name = string(namestream.str());
```

## 数据转换

### 数字与字符串的相互转换

#### 利用 `stringstream`

> 需 `#include <sstream>`

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

#### 利用 `sscanf` 和 `sprintf`

> 需 `#include <string>`

常用于格式化转换

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

#### 利用 `atoi` 和 `itoa`

`atoi` 需要使用 `char *` 的参数，所以 `string` 的话，需要调用 `c_str()` 转化为字符指针，比如

```cpp
string s = "123";
cout << atoi(s.c_str()) << endl;
```

相应地，我们也可以使用 `itoa` 反向转换，但是要注意， `itoa` 并不支持跨平台，所以尽量不要使用它

```cpp
int i = 123;
cout << string(itoa(i)) << endl;
```

#### 利用 `stoi` 和 `to_string` <Badge text="C++11" type="tip"/>

`stoi` 是 C++11 才引入的，所以它当然可以完美的支持字符串，除此之外，它还对输入字符串进行范围校验，一旦不在限定的范围内，就会抛出错误，这使得它更加安全

```cpp
string s = "123";
cout << stoi(s) << endl;
```

> 相应地，还有转化为 `float` 和 `double` 的 `stof` 、 `stod`

`to_string` 可以将很多类型都转化为字符串，整型变量自然也不在话下

```cpp
int i = 123;
cout << to_string(i) << endl;
```

## STL 的使用 :heart:

STL(Standard Template Library) 是什么？它对某些常用的数据结构进行了封装，比如 `Stack` 、 `Queue` 等

我们在学习数据结构的时候，会遇到在一个数据结构中用到了另一个数据结构，比如二叉树非递归遍历的实现，就是需要使用 `Stack` 的，如果在 C 语言中，我们不得不再自己去实现一遍 `Stack` 了

如果在 C++ 中，我们就不必每次都自己去实现 `Stack` 了，直接 `#include <stack>` ，就可以使用 STL 中内置的 `Stack` 啦

### 动态数组 vector

> 需 `#include <vector>`

C 与 C++ 中的数组都是一经声明大小便不可变的，STL 中的 `vector` 是一种大小可变的数组，可以随着数组元素的增加而增加长度

STL 中的类都是支持保存各种数据的，我们只需要在创建它的时候声明一下具体要保存哪种数据（其具体实现可以参考·进阶篇·中的·模板类·）

```cpp
vector<int> v;
```

这样就创建了一个可以存放 `int` 的动态数组啦，那么怎么用呢？

#### push_back() 在数组尾部追加元素

可以通过 `void push_back(T value)` 在数组的尾部追加元素

```cpp
for (int i = 0; i < 10; i++) {
   v.push_back(i);
}
```

相应地，我们可以使用 `void pop_back()` 弹出尾部的元素，但是需要注意的是，它并不返回尾部元素的值

#### 按照索引进行读写

可以像数组一样直接使用 `[]` 获取对应索引下的元素

```cpp
for (int i = 0; i < 10; i++) {
   v[i]++;
}
```

#### size() 获取数组的大小

`int size()` 可以获取数组的大小，可据此对数组进行迭代

```cpp
for (int i = 0; i < v.size(); i++) {
   cout << v[i] << endl;
}
```

#### resize() 调整数组的大小

`void resize(int new_size, T value)` ，第一个参数为新的·数组大小·，第二个参数为**扩充部分**所填充的值（比如原来有 10 个值，resize 到 100 ，以 5 为填充值的话，那么后 90 个新的空位都将会被填充为 5），可省略

```cpp
v.resize(100);
v.resize(100, 5);
```

#### empty() 判空

`bool empty()` 用于判断数组是否为空

#### clear() 清空

`void clear()` 用于清空数组

### STL 的公共方法

STL 虽然各不相同，但是还是有很多相同的方法的哦~

-  empty() 判空
-  size() 获取元素个数
-  insert(postion, elem) 在指定位置插入元素
-  erase(begin, end) 删除一段元素，从 begin 到 end-1
-  clear() 删除所有元素
-  `=` 拷贝元素
-  `==` 元素判等

### 如何对 STL 进行迭代

#### 像数组一样进行迭代

比如 `vector` 这样可以直接用下标索引并且索引值是从 `0` 到 `size - 1` 我们可以直接使用数组那种遍历方法逐个遍历

```cpp
for (int i = 0; i < v.size(); i++) {
   cout << v[i] << endl;
}
```

#### 使用 STL 的迭代器

如果一个容器并不能像数组那样使用顺序的索引直接获取值怎么办呢？我们还有 STL 提供的迭代器

迭代器的类型是容器类型下的 `iterator` 类型，我们可以通过 `begin()` 方法和 `end()` 方法分别获得**指向第一个元素的迭代器**和**指向最后一个元素后面的迭代器**，而对迭代器解引用 `*` 便可完成对该位置元素的读写，我们将根据这个完成一次对 STL 的遍历操作

```cpp
for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
   cout << *it << endl;
}
```

#### 使用 auto 关键字简化迭代 <Badge text="C++11" type="tip"/>

C++11 中新的关键字 auto 可以自动帮助我们判断类型，这并不是说变成了动态语言，只是可以帮助我们推断某个类型已经确定的变量的类型，该过程由编译器完成，并不会修改编译结果

比如这里，我们的迭代器类型写起来太麻烦啦，这里我们完全可以使用 `auto` 关键字自动推断出来它的类型，而不需要我们每次都写那么长一串类型名

```cpp
for (auto it = v.begin(); it != v.end(); it++) {
   cout << *it << endl;
}
```

这样就好看多啦~

#### C++11 中 for 循环的新用法 <Badge text="C++11" type="tip"/>

C++11 标准中增加了新的 `for` 循环使用方法，可以很方便地对某一个可迭代对象进行迭代，这当然包括 STL

```cpp
for (auto i: v) {
   cout << i << endl;
}
```

如果想对元素进行修改，声明为引用类型即可

```cpp
for (auto &i: v) {
   cout << ++i << endl;
}
```

### 栈 stack

> 需 `#include <stack>`

-  `void push(T value)` 向栈顶插入一个元素
-  `void pop()` 弹出栈顶元素
-  `T top()` 查看栈顶元素

### 队列 queue

> 需 `#include <queue>`

-  `void push(T value)` 元素入队
-  `void pop()` 队首元素出队
-  `T front()` 获取队首元素
-  `T back()` 获取队尾元素

### 映射 map

> 需 `#include <map>`

map 主要表示的是一种离散的映射关系，它表现为一个个的键值对

比如，有这样一个 map `m` ，当键为 `1` 时对应的值为 `"5"` ，键为 `3` 时对应的值为 `"7"` ，我们可以通过插入键值对 `{ {1, "5"}, {3, "7"} }` 完成

```cpp
map<int, string> m = {
   {1, "one"},
   {2, "two"}
};
```

#### 创建时需要分别指明键和值的类型

由于键和值的类型并不一定是相同的，我们在声明一个 map 的时候需要分别声明键和值的类型

```cpp
map<int, string> m;
```

#### 像数组一样通过键读写值

```cpp
m[1] = "5";
m[3] = "7";
```

以键为索引就可以轻松地获取对应的值，而且能对值进行修改

#### find() 查找是否存在某个键

如何查看一个键是否已经在 map 中了呢？

`find(T key)` ，它将返回键 `key` 对应的迭代器，如果没有键 `key` ，则返回 `m.end()` ，该方法通常用于查找某个键是否在 map 中，就像这样

```cpp
if (m.find(key) != m.end()) {
   m[key] = "5";
}
```

#### C++17 中更加优雅的遍历方法 <Badge text="C++17" type="tip"/>

在 C++11 中我们如何遍历一个 map 呢？

```cpp
for (auto &it : m) {
   cout << it.first << ": " << it.second << endl;
}
```

虽然已经很简洁了，但是语义并不是很明了，需要 `first` 与 `second` 分别取键与值，C++17 标准中的结构化绑定可以帮助我们直接将键与值取出来

```cpp
for (auto &[key, value] : m) {
   cout << key << ": " << value << endl;
}
```

能够直接将每个迭代结果中的值赋给对应位置的变量咯，事实上是返回的 `pair<int, string>` 键值对中的两个值分别被赋给了 `key` 和 `value`

### 集合 set

> 需 `#include <set>`

我们如何表示一个没有重复元素的集合呢？毫无疑问，set 是最好的方法啦，至于操作方法，我们可以将 set 理解为一个只有键没有值的 map ，那么我想，下面两个方法的使用方法也不必赘述了

-  `void insert(T value)` 插入一个元素
-  `find(T value)` 查找一个元素

#### 取并、交、差集

> 需 `#include <algorithm>`

-  取并集 `set_union`

   比如取集合 `a` 和 集合 `b` 的并集，并将值存入 `c` 中，我们可以通过以下操作完成

   ```cpp
   set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.begin()));
   ```

-  取交集 `set_intersection`
-  取差集 `set_difference` （将 b 中属于 a 的元素去掉）

### unordered_map 和 unordered_set <Badge text="C++11" type="tip"/>

> 分别需 `#include <unordered_map>` 和 `#include <unordered_set>`

按名字来看，它们并不对元素进行排序了……这其实是与 `map` 与 `set` 进行对比，`map` 与 `set` 底层采用的是红黑树结构，但是如果需要更高的性能的话，你可能需要底层使用 `hash` 的 `unordered` 系列，不用说也能知道为啥它性能更高啦~

### 位运算 bitset

> 需 `#include <bitset>`

`bitset` 每一位真的只占一位，是不是瞬间感觉很好玩的样子

#### bitset 的构造

我们可以通过只含 `0` 和 `1` 的字符串对其进行构造，或者通过整型数进行构造

```cpp
bitset<4> bitset1;　　//无参构造，长度为４，默认每一位为 0
bitset<8> bitset2(12);　　//长度为８，二进制保存，前面用 0 补充

string s = "100101";
bitset<10> bitset3(s);　　//长度为10，前面用 0 补充

char s2[] = "10101";
bitset<13> bitset4(s2);　　//长度为13，前面用 0 补充

cout << bitset1 << endl;　　//0000
cout << bitset2 << endl;　　//00001100
cout << bitset3 << endl;　　//0000100101
cout << bitset4 << endl;　　//0000000010101
```

#### 重载的运算符

-  `^` 按位异或
-  `&` 按位与
-  `|` 按位或
-  `~` 按位取反
-  `<<` 左移
-  `>>` 右移

#### 更多方法

-  `bool test(int idx)` 检查 `idx` 处的元素是否为 `1`
-  `int count()` 返回 `1` 的个数
-  `int size()` 返回集合的大小
-  `bool any()` 检查是否存在 `1`
-  `bool none()` 检查是否不存在 `1`
-  `bool all()` 检查是否全为 `1`
-  `void flip(int idx)` 对 `idx` 处的元素取反，如果未指定 `idx` ，则每一位都取反
-  `set(int idx, int value)` 将 `idx` 处的值置 `value` ，如果不指定 `value` 则置 `1` ，如果不指定 `idx` 则每一位都修改
-  `reset(int idx)` 将 `idx` 处的值置 `0` ，如果不指定 `idx` ，则每一位都置 `0`

### 堆 heap

> 需 `#include <algorithm>`

STL 中封装了四个有关堆的函数，分别是

-  `make_heap(first, last, comp);` 建立一个空堆
-  `push_heap(first, last, comp);` 向堆中插入一个新元素
-  `pop_heap(first, last, comp);` 移除当前堆顶元素的值（到堆底之后）
-  `sort_heap(first, last, comp);` 对当前堆进行排序

我们可以利用它对数组进行操作

> 注意这里的数组不需要将第一位空出来

```cpp
const int MaxSize = 10;
int size = 5;
int a[MaxSize] = {1, 5, 6, 2, 9};
// 建堆（使用仿函数 greater 快速建立最小堆，默认为最大堆）
make_heap(a, a+size, greater<int>());
// 添加元素（先添加，后使用堆的函数调整）
a[size++] = 7;
push_heap(a, a+size, greater<int>());
// 移除元素（先使用堆的函数将堆顶元素移到堆底，然后取走并移除）
pop_heap(a, a+size, greater<int>());
cout << a[--size] << endl;
```

另外，我们可以使用 `vector` 获得更好的效果（更加动态，不需要考虑堆是否会满等等问题）

```cpp
int a[] = {1, 5, 6, 2, 9};
vector<int> v(a, a+5);
// 建堆（使用仿函数 greater 快速建立最小堆，默认为最大堆）
make_heap(v.begin(), v.end(), greater<int>());
// 添加元素（先添加，后使用堆的函数调整）
v.push_back(7);
push_heap(v.begin(), v.end(), greater<int>());
// 移除元素（先使用堆的函数将堆顶元素移到堆底，然后取走并移除）
pop_heap(v.begin(), v.end(), greater<int>());
cout << v.back() << endl;
v.pop_back();
```

### 排序 sort

> 需 `#include <algorithm>`

STL 中不仅包含了一些好用的容器类，而且还有一些常用的算法，比如最常用的排序

```cpp
sort(start, end, cmp)
```

第三个参数缺省为从小到大排列，比如有一个 `int a[10]`

```cpp
sort(a, a+10);
```

便可对其进行排序

#### 自定义排序方式

那么如何自定义排序方法 `cmp` 呢？

比如我们定义

```cpp
bool cmp(int a, int b)
{
  return a > b;
}
```

之后调用

```cpp
sort(a, a+10, cmp);
```

即可获得从大到小的序列

#### 利用 C++11 中的 Lambda 表达式自定义排序 <Badge text="C++11" type="tip"/>

```cpp
auto cmp = [](int a, int b) -> bool {
   return a > b;
};
sort(a, a+10, cmp);
```

使用 Lambda 表达式可以避免额外在函数体外新建函数，增加了代码的可读性

#### 使用仿函数

如果只是简单的比较大小的话，有没有更加简单的方法呢？

当然有啦， STL 中可不止容器和算法，还有很多新奇玩意呢，比如说这个仿函数，当然我们现在不需要了解太多，只需要知道我们可以使用仿函数 `greater<int>()` 以及 `less<int>()` 这样简单的函数进行排序就好了

现在我们想要进行从大到小排序，只需要

```cpp
sort(a, a+10, greater<int>());
```

比 Lambda 还优雅呢~当然，这仅限于简单函数，复杂函数建议使用 Lambda 表达式

---

## :sparkles: 进阶篇

## 从结构体到类 :boom:

### 始于 C

我们如何在 C++ 中写一个结构体呢？

```cpp
struct Stack_struct {
  int data[MaxSize];
  int top;
};
```

和 C 里的一毛一样~稍微需要注意的一点是，C++ 的结构体在后面作为类型进行声明的时候，不必加上 `struct` ，比如说 `Stack_struct ss;` 就是合法的声明语法

我们创建一个等价的类

```cpp
class Stack_class {
  int data[MaxSize];
  int top;
};
```

嗯，只需要将关键字 `struct` 换成 `class` 就行了，这样的 `Stack_class` 可以像之前的 `Stack_struct`. 一样进行声明与赋值了，可是仅仅是如此的话，C 语言中的 `struct` 也是能做到的呀，所以 C++ 中的 `class` 到底有什么用呢？

### 超越 C

下面我们考虑下如果用 C 语言我们会怎么完成 `Stack` 这个 ADT

```cpp
struct Stack_struct {
  int data[MaxSize];
  int top;
};

void Push(Stack_struct *s, int value) {
  s->data[++(s->top)] = value;
}

int Pop(Stack_struct *s) {
  return s->data[s->top--];
}

bool IsEmpty(Stack_struct *s) {
  return s->top == -1;
}

int main() {
  Stack_struct *ss = (Stack_struct*)malloc(sizeof(Stack_struct));
  ss->top = -1;
  for (int i = 0; i < 10; i++) {
    Push(ss, i);
  }
  while (!IsEmpty(ss)) {
    cout << Pop(ss) << endl;
  }
  return 0;
}
```

我们需要将各个方法实现出来，而且在声明变量之后还要对其逐个成员进行初始化（如果需要的话），有没有什么方法将这些集成在一起呢？当然， C++ 的类便做到了这一点

```cpp {2,5}
class Stack_class {
  private:
    int data[MaxSize];
    int top;
  public:
    Stack_class () {
      top = -1;
    }
    void Push(int value) {
      data[++top] = value;
    }
    int Pop() {
      return data[top--];
    }
    bool isEmpty() {
      return top == -1;
    }
};

int main() {
  Stack_class sc;
  for (int i = 0; i < 10; i++) {
    sc.Push(i);
  }
  while (!sc.IsEmpty()) {
    cout << sc.Pop() << endl;
  }
  return 0;
}
```

是不是感觉瞬间就高级了很多？如果你使用过其它面向对象的语言的话（除了 C ，大多都支持），上面的语法你应该是很熟悉的

首先，它多了一堆函数，这个在 C 语言的结构体中是不支持的（但是 C++ 的结构体还是支持的），这些函数称为这个类的方法，我们可以通过 `<obj>.<method>` 来调用一个方法

但是，方法并不是类最重要的特性，其最重要的特性是，能够对数据进行封装，在 C++ 的类中还多了两个关键字 `private` 和 `public` ，这两个关键字有什么用呢？简单地说，`private` 下的方法或者属性是不能在类外通过 `.` 运算符操作的，比如这里的 `top` 属性，在类外我们是不能通过 `sc.top` 进行获取的，但是我们可以通过 `public` 的方法安全地对其值进行修改，比如调用 `sc.Pop()`

封装有什么好处呢？很明显，这样更加安全，原本我们不仅能通过一些专用方法对某些值进行修改，还能直接对数据的值进行修改，比如我们随手 `ss.top--` ，显然这是很危险的，因为栈顶的值并没有取出来，下次 `ss.Pop()` 必然会跳过一个值，如果没有进行“补救”的话，这个值就永远失去了

如果使用封装，我们将数据域作为私有数据，仅仅通过公有的方法进行修改、获取，那么就会安全很多

当然，将数据域放在 `private` 将方法放在 `public` 只是一种比较常用的方法，你也可以将某些方法作为私有方法，将某些数据作为公有数据，具体怎么处理需要视情况而定，另外还有其它的关键字（比如 `protect`）会在你后续的学习中逐步了解，这里不进行赘述

面向对象还有还有其他的特性，比如继承、多态等等，由于初步学习的话并不会涉及到这么多，所以这里不进行展开了

## C++ 中的模板

### 模板函数

我们在书写数据结构的时候，由于不知道最终存储的数据到底是什么类型的，所以一般会使用 `ElemType` 作为数据的类型，在使用具体类型的时候，对 `ElemType` 进行替换，比如下面这样

```cpp {1,2}
typedef int ElemType;
ElemType Max(ElemType a, ElemType b) {
  return a > b ? a : b;
}
int main() {
  cout << Max(1, 2) << endl;
  return 0;
}
```

但是这样有一个很明显弊端就是，需要对 `typedef <type> ElemType;` 才能对新的类型进行支持，有没有什么方法能够使得一个函数参数支持任意的类型呢？C++ 中的模板函数就是为了这一特性进行设计的，我们只需要在函数前面加上 `template<typename T>` ，之后我们的函数类型中就可以使用通用的类型 `T` 了，无论之后传入 `int` 型还是 `char` 型等等都是可以调用这个函数的，但是要注意的一点是，`T` 类型是一种类型，不能同时作为不同的类型进行使用

```cpp {1,2}
template<typename T>
T Max(T a, T b) {
  return a > b ? a : b;
}

int main() {
  cout << Max(1, 2) << endl;
  cout << Max('a', 'b') << endl;
  return 0;
}
```

### 模板类

既然模板函数内的可以使用模板类型，那么是否有办法让整个类也能使用某个模板类型呢？

```cpp {1,22}
template<typename T>
class Stack_class {
  private:
    T data[MaxSize];
    int top;
  public:
    Stack_class () {
      top = -1;
    }
    void Push(T value) {
      data[++top] = value;
    }
    T Pop() {
      return data[top--];
    }
    bool IsEmpty() {
      return top == -1;
    }
};

int main() {
  Stack_class<int> sc;
  for (int i = 0; i < 10; i++) {
    sc.Push(i);
  }
  while (!sc.IsEmpty()) {
    cout << sc.Pop() << endl;
  }
  return 0;
}
```

没有过多地修饰，直接在类前声明一下模板即可，另外值得注意的是，在类的声明的时候，需要加上模板类的具体类型

### 多模板声明

如果要用多个类型参数的话，直接在模板声明处使用 `template <typename T, typename S, ...>` 就好啦

## 文件读写

通过 `ifstream` 和 `ofstream` 可打开文件，之后利用流插入符就可以像标准输入输出一样对文件进行读写，不过读写完毕记得关闭文件

### 读文件

> 需 `#include <fstream>`

```cpp
ifstream input;
input.open("scores.txt");

char firstName[80];
char mi;
char lastName[80];
int score;
while (!input.eof()){
   input >> firstName >> mi >> lastName >> score;
}

input.close();
```

### 写文件

> 需 `#include <fstream>`

```cpp
ofstream output;
output.open("scores.txt");

output << "John" << " " << "T" << " " << "Smith"
<< " " << 90 << endl;
output << "Eric" << " " << "K" << " " << "Jones"
<< " " << 85;

output.close();
```

## 多返回值的使用 <Badge text="C++17" type="tip"/>

C 中想要返回多个值，一种方法是将指针作为参数传入，这使得参数表变长，真正的输入和输出难以分辨，另一种方法是返回一个结构体，但是难道要每个函数为它创建一个新的结构体？不现实啊

在 C++ 中，最开始想到的无非也是传入引用，和输出类这两种方法，和 C 语言中大同小异，呃，有没有什么优雅的方法？

当然有！在 C++17 中，我们可以方便的对结构体进行绑定和解绑，比如

```cpp
struct Person {
  string name;
  int age;
  int height;
};

int main() {
  Person p{"tom", 20, 175};
  auto [name, age, height] = p;
  cout << name << " " << age << " " << height << endl;
  return 0;
}
```

就像这样，我们就可以从结构体中获取它的三个成员变量，我们试着使用 `tuple` 简化一下上面的代码

```cpp
#include <tuple>

int main() {
  auto p = make_tuple("tom", 20, 175);
  auto [name, age, height] = p;
  cout << name << " " << age << " " << height << endl;
  return 0;
}
```

如果把第一条语句换成函数返回值呢？

```cpp
#include <tuple>

auto get_record() {
  return make_tuple("tom", 20, 175);
}

int main() {
  auto [name, age, height] = get_record();
  cout << name << " " << age << " " << height << endl;
  return 0;
}
```

这样我们就可以获得一个可以返回多个值的函数啦~

## `extern "C"` 回归 C

C++ 编译的时候会使用 `name mangling` 机制，就比如函数 `void Test(void);` 就可能被 C++ 编译为 `vTest_v` ，C++ 的很多语法特性（比如命名空间、重载）是通过该方法得来的

而 `extern "C"` 可以告诉 C++ 编译器抑制 `name mangling` 机制，以 `C Linkage` 方式编译，比如像这样 `extern "C" void Test(void)`，那么我们最终得到的函数名和 C 编译器得到的一样为 `Test` ，这就保证了函数名不会“面目全非”，当然这在 C++ 中并不会有太大的用处，但是如果别的语言想要调用 C++ 编译得到的函数（比如 dll）时，杂乱的函数名并不是可读的，所以我们需要使用 `extern "C"` 为需要导出的函数封装一下，保证它们函数名称可读

## 更多技巧

### 常用函数

#### 判断一个数是否为素数

```cpp
bool isPrime(int n) {
   if (n == 0 || n == 1) return false;
   for (int i = 2; i * i <= n; i++) {
      if (n % i == 0) return false;
   }
   return true;
}
```

#### 求两个数的最大公因数

辗转相除法，很容易就能写出来~

```cpp
int gcd(int a,int b) {
  return (b>0) ? gcd(b, a%b) : a;
}
```

### 数组置零

#### 初始化时置零

我们经常需要对一个数组进行置零操作，在初始化的时候，我们可以使用一个 0 ，对整个数组进行置零

```cpp
int a[MAX_SIZE] = {0};
```

::: tip

只有置零效果是针对整个数组的，置其他数值只针对第一位

:::

#### 使用 memset

> 需 `#include <cstring>`

如果无法在初始化时置零，或者需要在其他时候置零，可以使用 `memset`

```cpp
memset(a, 0, sizeof(a));
```

### 字符处理库 cctyte

> 需 `#include <cctype>`

-  字符测试
   -  `isalnum()` 如果参数是字母数字，即字母或者数字，函数返回 true
   -  `isalpha()` 如果参数是字母，函数返回 true
   -  `iscntrl()` 如果参数是控制字符，函数返回 true
   -  `isdigit()` 如果参数是数字（0－9），函数返回 true
   -  `isgraph()` 如果参数是除空格之外的打印字符，函数返回 true
   -  `islower()` 如果参数是小写字母，函数返回 true
   -  `isprint()` 如果参数是打印字符（包括空格），函数返回 true
   -  `ispunct()` 如果参数是标点符号，函数返回 true
   -  `isspace()` 如果参数是标准空白字符，如空格、换行符、水平或垂直制表符，函数返回 true
   -  `isupper()` 如果参数是大写字母，函数返回 true
   -  `isxdigit()` 如果参数是十六进制数字，即 0－9、a－f、A－F，函数返回 true
-  字符映射
   -  `tolower()` 如果参数是大写字符，返回其小写，否则返回该参数
   -  `toupper()` 如果参数是小写字符，返回其大写，否则返回该参数

### 随机数的生成

> 需 `#include <cstdlib>`

`rand()` 会生成一个随机整型数，我们可以通过定义宏来实现对上限的限制

```cpp
#define random(x) (rand()%x)
#define randint(start, end) (rand()%(end-start) + start)
```

另外 `void srand(unsigned int seed)` 可以对喂一个随机种子

### 获取极限值

> 需 `#include <climits>`

有的时候需要获得某个最大值或者最小值，如果只是刷题我们可能会给它取某个 99999 这样的值，但是这样显得就很不优雅，有没有什么比较优雅的方法呢？

`climits` 中为我们提供了 `INT_MAX` 以及 `INT_MIN` ，这样我们就不用再纠结取哪个值啦

# Reference

> 初学阶段，需要查阅的太多，不对参考链接进行一一列出

1. [从 C 语言转 C++简明教程 v5.0+ の 目录](https://www.liuchuo.net/333-3)
2. [网易云课堂 C++程序设计入门（上）](https://mooc.study.163.com/course/1000003015)
3. [网易云课堂 C++程序设计入门（下）](https://mooc.study.163.com/course/1000005002)
