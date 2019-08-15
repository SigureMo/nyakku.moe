---
title: C++
categories:
   - Computer Science
tags:
   - CS
   - C++
---

## 1. C to ++

### 1.1 Aloha World!

```Cpp
#include<iostream>
int main(){
    std::cout << "Aloha World!" << std::endl;
    return 0;
}
```

> namespace
> 类比于 Python 的 import 很好理解，首先`include <pkgname>`大概相当于`import <pkgname>`，之后就可以使用这个包内的内容啦。
> `using namespace <spacename>;` 就相当于`from <pkgname> import *`，直接把所有内容全引入了，而`using <spacename>::<varname>`相当于`from <pkgname> import <varname>`，就避免了多个库之间的冲突。

### 1.2 More than C

#### 1.2.1 Primitive Data Types & Operations

1. Bool expression
   逻辑和关系运算返回 Boolean (true false)
2. Type conversion
   `static_cast<type> value`

```Cpp
cout << static_cast<double>(1) / 2;
cout << 1 / 2;
```

3. Declaring and Initializing Variables

```Cpp
int i = 1;
int i(1); //等价与上面的，但是不可以这样声明类型后初始化
```

#### 1.2.2 Function

1. Scope of Local Variables
   starts from it's definition to the end of the **block**

2. Unary Spore Resolution
   If a local variable name is the same as a global variable using ::globalVariable.
   Example:

```Cpp
#include<iostream>
using namespace std;
int v1 = 10;
int main(){
    int v1 = 5;
    cout << "local variable v1 is " << v1 << endl;
    cout << "local variable v1 is " << ::v1 << endl;
}
```

3. Overloading Functions
   根据参数表的参数匹配函数，但不能出现二义调用
4. Default Arguments
   参数表默认值后置
   A default argument shall not be redefined by a later declaration (not even to the same value)
5. Inline Functions

```Cpp
inline int max(int a, int b){
    return (a > b ? a : b);
}
```

一般函数需要入栈出栈，使得性能花费极大开销，而内联函数是由编译器将代码直接插入调用位置，以减小入栈出栈的开销，但是导致程序变大，以**空间换时间**

-  适用于小函数不适用于大函数
-  只是对编译器的请求，并不是命令，编译器会根据情况而决定是否插入

#### 1.2.3 Reference & Dynamic Memory

1. Reference

-  A **reference** is an alias for another variable.
-  Any chanages made through the reference variable are actually performed on the original variable.

```Cpp
int X;
int& rx = x;
// (っ•̀ω•́)っ✎⁾⁾
int x, &rx = x;
```

> C++ printers and references should have their reference symbol next to the **type** rather than to the name.

-  You can use a reference variable as a parameter in s function and pass a regular variable to invoke the function.
-  When you change the value through the reference variable, the original value is actually changed.
   > 哭了，这是个什么鬼嘛，怎么只改个参数表就可以用其值了，连类型都不用换的，emmmmm 暂且当作是像 Python、Java 等语言传对象时候传 manager 好了

2. Dynamic Memory

-  malloc -> `new <typeName>(initvalue)` or `new <typeName>[CONSTANT]`
-  free -> `delete <pointerName>` or `delete []<pointerName>`

#### 1.2.4 Simlified Memory Model for C/C++

1. Simplified Memory Model
   1. Stack
   2. Heap
   3. Global/Static
   4. Constant

![C++01](../Images/C++01.png?raw=true)

#### 1.2.5 Const

1. Named Constants
   `const dataType CONSTANTNAME = VALUE;`
   Example:

```Cpp
const double PI = 3.14159;
const int SIZE = 3;
int const X = 5;
```

> const in C and C++

    * in C (C89), const means "ReadOnly Variable"
    * in C++, const means "Constant"

```Cpp
const int ARRAY_SIZE = 10;
int arr[ARRAY_SIZE]; // OK in C++, Error in C
```

2. const and pointer
   1. Pointer to Constant(常量指针) `const int* p1;`
   2. Pointer Constant(指针常量) `int* const p1;`

-  数组名就是一个指针常量
   > const 在谁前面谁就不可变

## 2 Objects and Classes

### 2.1 Concepts of Class

#### 2.1.1 Features of OO

1. Abstraction
2. Polymorphism
3. Inheritance
4. Encapsulation

#### 2.1.2 Classes - an example

```Cpp
class Circle
{
public:
    // The radius of this circle
    double radius;

    // Construct a circle object
    Circle()
    {
        radius = 1;
    }

    // Construct a circle object
    Circle(double nuwRadius)
    {
        radius = newRadius;
    }

    // Return the area of tis circle
    double getArea()
    {
        return radius * radius * 3.14159;
    }
};
```

#### 2.1.3 C++ Data Types

![C++02](../Images/C++02.png?raw=true)

### 2.2 Create Objects and Access the members

#### 2.2.1 Construcing Objects

1. `ClassName objectName;`
2. `ClassName objectName(arguments);`

#### 2.2.2 Object Member Acccess Operator

-  To access the data & functions of an object
   `objectName.dataField`
   `objectName.function(arguments)`

### 2.3 More on Creating Objects

#### 2.3.1 Memberwise Copy

'='

> 喵喵喵？C++果然是不一样呀，'='赋值并不是把指针交予另一个变量的

#### 2.3.2 Anonymous Object

1. `ClassName();`
2. `ClassName(arguements);`

#### 2.3.3 Class Replaces struct

用 class 取代 struct，struct 相当于 public 的 class

### 2.4 Separating Declaration fromImplementation

#### 2.4.1 Separating Declaration fromImplementation

-  .h 类声明
-  .cpp 类实现
   `FunctionType ClassName :: FunctionName(Arguments){//...}`

#### 2.4.2 Inline Declaration & Inline Function

-  When a function is implemented inside a class declaration, it automatically becomes an inline function.

### 2.5 Object Pointer & Dynamic Object

#### 2.5.1 Accessing Object Members via Pointers

'->'

#### 2.5.2 Creating Dynamic Objects on Heap

-  Object declared in a function is created in the stack. When the function returns, the object is destroyed.
-  To retain the object, you may create it dynamically on the heap using the **new** operator.

```Cpp
ClassName *pObject = new ClassName();
ClassName *pObject = new ClassName(arguments);
// (っ•̀ω•́)っ✎⁾⁾
delete pObject;
```

### 2.6 The C++ string Class

#### 2.6.1 Constructing a Sting

-  `string newString;`
-  `string message("Aloha World!");`
-

```Cpp
char charArray[] = {'H', 'e', 'l', 'l', 'o', '\0'};
string message1(charArray);
```

#### 2.6.2 Appending a String

`append(arguments)`

#### 2.6.3 Assigning a String

`assign(arguments)`

#### 2.6.4 Function at, clear, erase, and empty

-  `at(index)` 返回当前字符串中 index 位置的字符
-  `clear()` 清空字符串
-  `erase(index, n)` 删除字符串从 index 开始的 n 个字符
-  `empty()` 检测字符串是否为空

#### 2.6.5 Comparing String

`compare()`

#### 2.6.6 Obtaining Substrings

`substr()`

#### 2.6.7 Searching in a String

`find()`

#### 2.6.8 Inserting and Replacing String

`insert()`
`replace()` 如果替换成"blabla"，那么由于其后必然有一个'\0'，所以其后字符串必然隐藏

#### 2.6.7 String Operators

| Operator                   | Description                                      |
| -------------------------- | ------------------------------------------------ |
| []                         | 用数组下标运算符访问字符串中的字符               |
| =                          | 将一个字符串的内容复制到另一个字符串             |
| +                          | 连接两个字符串得到一个新串                       |
| +=                         | 将一个字符串追加到另一个字符串末尾               |
| <<                         | 将一个字符串插入一个流                           |
| >>                         | 从一个流提取一个字符串，分界符为空格或者空结束符 |
| ==, !=, <, &nbsp;<=, >, >= | 用于字符串比较                                   |

### 2.7 Data Field Encapsulation

#### 2.7.1 Data Field Encapsulation

`private`

#### 2.7.2 Accessor and Mutator

### 2.8 The Scope of Variables & "this" pointer

#### 2.8.1 The Scope of Data Fields in Class

#### 2.8.2 Hidden by same name

#### 2.8.3 The this Pointer

> this 只是**指针指针指针**！

#### 2.8.4 Simple way to avoid name hidden

私有变量名增加下划线后缀

### 2.9 Passing Objects to Functions

#### 2.9.1 PassObjectByValue

> 直接 Copy 过去，生成一个新的 Object

#### 2.9.2 PassObjectByReference

> 把 Reference 传过去，是同一个 Object

#### 2.9.3 PassObjectToPointer

> 把 Pointer 传过去，解引用(\*)后自然也是原 Object

### 2.10 Array of Objects

#### 2.10.1 Array of Objects

```Cpp
Circle circleArray[10];
// (っ•̀ω•́)っ✎⁾⁾
Circle circleArray[3] = {
    Circle(3),
    Circle(4),
    Circle(5)
}
```

### 2.11 Class Abstration and Encapsulation

#### 2.11.1 Class astraction

1. to separate class implementation from the use of te class.
2. The creator provides a class description
3. The user of the class does not need to know how the class is implemented.

#### 2.11.2 Class encapsulation

-  The detail of implementation is encapsulated and hidden from the use.

#### 2.12 Constructor Initializer Lists

#### 2.12.1 Constructor Initializer

```Cpp
ClassName (parameterList)
    : dataField1(value1), dataField2(value2)
{
    // (っ•̀ω•́)っ✎⁾⁾
}
```

#### 2.12.2 The Role of Default Constructor

1. If a data field is an object type (Object in Object)
   -  the default constructor is automatically invoked to construct an object for the data field.
   -  If a default constructo does not exist, a compilation error will be reported.
2. You can use the Constructor Initalizer to construct the object manually.

## 3 More on Objects and Classes

### 3.1 Immutable Objects and Classes; Preventing Multiple Declaration

#### 3.1.1 Immutable Objects and Classes

-  immutable object: The contents of an object cannot be changed (except through memberwise copy) once the object is created.
-  immutable class: The class of immutable object

1. Mark all data fields private
2. No mutetor functions (　  ´-ω ･)▄︻┻┳══━ 一
3. No accessor that would return a reference/pointer to a mutable data field object.

#### 3.1.2 Preventing Multiple Declaration

1. Put `#pragma once` in te first line of .h file
2. Use `#infdef` preprocessing instructions in .h file

### 3.2 Instance and Static Members

> 使用 ClassName::StaticVar 引用静态变量

### 3.3 Destructor and Friend

#### 3.3.1 Destructors

> 就相当于 Python 里的**del**啦，C++要写成~ClassName()

#### 3.3.2 Friend

> friend 的对象和函数可以直接访问该对象的 private

#### 3.4 CopyConstructor

`ClassName(ClassName&);`

> 使用时仅限于对象的声明时，已经声明的对象无法再通过赋值进行 copy

1. Shallow copy
2. Deep copy（需要自己写的）

### 3.5 Case Study

[Stack](https://github.com/SigureMo/notev/tree/master/Codes/Data_Structures/Chapter_3_Stack/Stack.cpp)

### 3.6 The C++ vector Class

-  Limitation of using array to store values: the array size is fixed in the class declaration.
-  The vector object can increase its size if needed.

```
+vector<dataType>()
+push_back(element: dataType): void
+pop_back(): void
+size(): unsigned int
+at(index: int): dataType
+empty(): bool
+clear(): void
+swap(v2: vector): void
```

[Vector](https://github.com/SigureMo/notev/tree/master/Codes/C++/3.6_Vector.cpp)

### 3.7 More Programming Style Guidelines

1. 运算符前后应有空格
2. C++保留字后边应有空格
3. 逗号后面跟空格
4. 冒号前后有空格
5. for 语句的分号后有空格

## 4 Inheritance and Polymorphism

### 4.1 Inheritance

```Cpp
class Circle : public GeometricObject
{
    // (っ•̀ω•́)っ✎⁾⁾
}
```

### 4.2 Constructor and Destructor

> 派生类不继承的特殊函数：

    1. 构造函数（C++11已允许继承）
    2. 析构函数
    3. 作为特权地位的友元函数
    4. 赋值运算符函数

#### 4.2.1 Calling Base Class Constructors

-  Ctors of base class can only be invoked from the constructors of the derived classes.
-  The syntax to invoke it is as follows:

```Cpp
DerivedClass(parameterList) : BaseClass(){
    // (っ•̀ω•́)っ✎⁾⁾
}
// Or
DerivedClass(parameterList) : BaseClass(argumentList){
    // (っ•̀ω•́)っ✎⁾⁾
}
```

#### 4.2.2 Constructor and Destructor Chaining

> 构造函数沿着构造函数链调用所有的基类 ctor，而且基类有限，而析构恰恰相反

#### 4.2.3 no-arg constructor

If a class is designed to be extended, provide a no-arg constructor.

### 4.3 Redefining Functions

> 派生类里重定义函数覆盖掉基类里的函数

### 4.4 Polymorphism and Virtual Functions

Binding：确定具有多态性的语句调用哪个函数的过程

-  Static Binding
-  Dynamic Binding

*  通过派生类对象访问同名函数 -> 静态联编
*  通过基类对象的指针访问同名函数 -> 静态联编
*  通过基类对象的指针访问同名虚函数 -> 动态联编

### 4.5 Accessibility(Visibility)

-  Private 私有成员只能在类内的函数访问
-  Public 公有成员可被任何其他类访问
-  Protected 保护属性的数据或函数可被派生类成员访问

继承方式：
基类内所有高于继承方式的访问性将降低到继承方式。
比如，public、protected、private 以 protected 方式继承将分别变为 protected、protected、private

### 4.6 Abstract Class and Pure Virtual Function

#### 4.6.1 Abstract Functions

类中定义纯虚函数，如`virtual double getArea() = 0;`，那么子类必须对这个函数进行重定义

### 4.7 Dynamic Cast

#### 4.7.1 Upcasting and Downcasting

向上转换不必显式声明
向下必显式执行（`c = dynamic_cast<Circle *>(g)`）

#### 4.7.2 typeid operator

```Cpp
string X;
cout << typeid(X).name() << endl;
```

## 5 File Input and Output

### 5.1 Introduction to the Input and Output Classes

![C++03](../Images/C++03.png?raw=true)

### 5.2 Write data to a file

[File_Output.cpp](https://github.com/SigureMo/notev/tree/master/Codes/C++/5.2_File_Output.cpp)

### 5.3 Read data from a file

[File_Input.cpp](https://github.com/SigureMo/notev/tree/master/Codes/C++/5.3_File_Input.cpp)

### 5.4 Formating Output

#### 5.4.1 Format output to the console

[Formating_Output.cpp](https://github.com/SigureMo/notev/tree/master/Codes/C++/5.4.1_Formating_Output.cpp)

#### 5.4.2 getline

[getline.cpp](https://github.com/SigureMo/notev/tree/master/Codes/C++/5.4.2_getline.cpp)

#### 5.4.3 get and put

get 读入一个字符，put 写入一个字符

### 5.5 File Open Mode & Testing File State

#### 5.5.1 Combining Modes

[Combining_Modes.cpp](https://github.com/SigureMo/notev/tree/master/Codes/C++/5.5.1_Combining_Modes.cpp)

#### 5.5.2 Stream State Bit

| Function | Description                   |
| -------- | ----------------------------- |
| eof()    | ios::eofbit                   |
| fail()   | ios::failbit or ios::hardfail |
| bad()    | ios::badbit                   |
| good()   | ios::goodbit                  |
| clear()  | Clears all flags.             |

### 5.6 Binary IO

#### 5.6.1 The write Function

[File_Output_Binary.cpp](https://github.com/SigureMo/notev/tree/master/Codes/C++/5.6.1_File_Output_Binary.cpp)

#### 5.6.2 Write Any Type

[File_Output_Binary2.cpp](https://github.com/SigureMo/notev/tree/master/Codes/C++/5.6.2_File_Output_Binary2.cpp)

#### 5.6.3 The read Function

[File_Input_Binary.cpp](https://github.com/SigureMo/notev/tree/master/Codes/C++/5.6.3_File_Input_Binary.cpp)

#### 5.6.4 Read Any Type

[File_Input_Binary2.cpp](https://github.com/SigureMo/notev/tree/master/Codes/C++/5.6.4_File_Input_Binary2.cpp)

### 5.7 More on Binar IO

Array and Object
和前面都一样，只需要加个类型转换就行，要注意的是，Object 只保存数据域的数据，不会保存方法（因为方法本来就不在 Object 指针那里）

### 5.8 Random Access File

seek：移动文件指针
tell：获取文件指针位置

---

p：put，表示操作输出文件中的指针
g：get，表示操作输入文件中的指针

---

ios::beg，从文件开始处偏移
ios::end，从文件结束处开始偏移
ios::cur，从当前位置开始偏移

---

Example：

```Cpp
seekg(-100L, ios::end); // 读模式，将指针移到末尾前100字节的位置
```

## 6 Operator Overloading

### 6.1 Behind What We Have Learned

#### 6.1.1 The string, vector class

```Cpp
string s1("Hello"), s2("World!");
cout << s1 + s2 << endl;
```

```Cpp
vector<char> v(3, 'a'); // 'a', 'a', 'a'
v[1] = 'b';
```

#### 6.1.2 An Example

[Operator_Overloading_example.cpp](https://github.com/SigureMo/notev/tree/master/Codes/C++/6.1_Operator_Overloading_example.cpp)

#### 6.1.2 The operator vs function

-  运算符可以看做是函数
-  函数是前缀式的
-  不能自定义新的运算符，只能重载，比如 C++就不能用 Python 里的\*\*
-  C++原始数据的运算符可不能重载，后定义的对象是可以的

### 6.2 Rational Class

#### 6.2.1 What is a rational number?

-  有理数 -> 成比例的数

#### 6.2.2 How do to we describe a rational number in C++ ?

-  Data fields
   -  分子
   -  分母
-  Operations
   -  加减乘除
   -  比较
   -  转换为各种类型
-  Zero(0) and default value
-  Lowest term
-  Negative

#### 6.2.3 Test Rational Class

[6.2_Rational.cpp](https://github.com/SigureMo/notev/tree/master/Codes/C++/6.2_Rational.cpp)

### 6.3 Operator Function and Shorthand Operators Overloading

#### 6.3.1 Operator Function

```Cpp
bool Rational::operator<(Rational &secondRational){
    return (this->compareTo(secondRational) < 0);
}
```

#### 6.3.2 Operator: Which can overload

-  Overloadable
   ```
   +   -   *   /   %   ^   &   |   ~   !   =
   <   >   +=  -=  *=  /=  %=  ^=  &=  |=  <<
   >>  >>= <<= ==  !=  <=  >=  &&  ||  ++  --
   ->* ,   ->  []  ()  new delete
   ```
-  Operators That Cannot Be Overloaded
   ```
   .  .*  ::  ?:  #   sizeof()
   ```

#### 6.3.3 Restrictions for operator overloading

-  Precedence and Associativity are unchangeable
-  NOT allowing to create new operator

### 6.4 Overloading [] Operator

> 既需要作为访问器，又需要作为修改器，所以应当返回一个 reference

```Cpp
long& Rational::operator[](const int &index){
    if (index == 0)
        return numrator_;
    else if (index == 0)
        return denominator_;
    else{
        cout << "subscript error" << endl;
        exit(0);
    }
}
```

### 6.5 Overloading the Unary Operator

#### 6.5.1 prepositive unary operators

当编译器遇到@obj;时

-  若 operator@ 是在 obj 的类中的成员，则调用 obj,operator@();
-  若 operator@是 obj 的类的 friend 函数，则调用 operator@(obj);

#### 6.5.2 Overloading the - Operators

```Cpp
Rational Rational::operator-(){
    numerator *= -1;
    return *this;
}
```

#### 6.5.3 Overloading the ++ and -- Operators

-  prefix

```Cpp
Rational Rational::operator++(){
    numerator += denominator;
    return *this;
}
```

-  postfix

```Cpp
Rational Rational::operator++(int dummy){
    Rational temp(numerator, denominator);
    numerator += denominator;
    return temp;
}
```

### 6.6 Overloading << / >> Operator and Object Converting Operator

#### 6.6.1 Overloading << and << as friend

```Cpp
class Rational {
    public:
        ostream &operator<<(ostream &stream);
        istream &operator>>(istream &stream);
};
```

```Cpp
class Rational {
    public:
        friend ostream &operator<<(ostraem &stream, Rational &rational);
        friend ostream &operator>>(istream &stream, Rational &rational);
};
```

#### 6.6.2 Example

```Cpp
ostream &operator<<(ostream &str, Rational &rational){
    str << rational.numerator << " / " << retional.denominator;
    return str; // 因为连续使用流插入运算是顺序执行的，后面的会插入到前面的返回值中，故需要return一个ostream
}
```

```Cpp
istream &operator>>(istream &str, Rational &rational){
    cout << "Enter numerator: ";
    str >> rational.numerator;
    cout << "Enter denominator: ";
    str >> rational[1];
    return str;
}
```

#### 6.6.3 Object Conversion

```Cpp
Rational::operator double(){
    return doubleValue();
}
Rational r1(1, 4);
double d = r1 + 5.1;
cout << "r1 + 5.1 is " << d << endl;
```

### 6.7 The New Rational Class

略略略~ヽ(ﾟ ∀ ﾟ)ﾒ(ﾟ ∀ ﾟ)ﾉ

### 6.8 Overloading the = Operaor

```Cpp
const Person operator=(const Person& person);
```

> 和拷贝构造函数相类似，只不过它是在对象已经创建之后使用的

> 函数声明的后面加上 const 关键字可让编译器知道该函数不会其内的值

### 6.9 More on Operator Overloading

#### 6.9.1 Can you overload operators for basic data types ?

重载的运算符必须和用户定义的 class 类型一起使用

#### 6.9.2 Function Type, Parameter Type, const

```Cpp
Rational Rational::operator+=(const Rational &secondRational){
    // (っ•̀ω•́)っ✎⁾⁾
}
```

#### 6.9.3 friend (which & how)

blabla

## 7 Exception-Handling

### 7.1 Overview of Exception-Handling

```Cpp
int main(){
    // Read two intergers
    cout << "Enter two integers: ";
    int number1, number2;
    cin >> number1 >> number2;

    try {
        if (number2 == 0)
            throw number1;

        cout << number1 << " / " << number2 <<
                " is " << (number1 / number2) << endl;
    }
    catch (int e) {
        cout << "Exception: an integer " << e <<
                " cannot be divided by zero" << endl;
    }
    cout << "Exception continues ..." << endl;
}
```

### 7.2 Exception-Handling Advantages

-  throw 可以直接放到函数中哦，调用函数体的位置也可以 catch 住的哦
-  正是这种特性，我们不需要考虑这个异常发生后如何向上传递，我们只需要写一个 throw，它保证了异常可以向上传递
-  不过，在本地处理的掉的事情就不要抛出去使用异常处理

### 7.3 Exception Classes

-  emmmm 就是 C++有些内建异常类，继承于 exception……
-  比如我们可以`throw runtime_error("Runtime error in quotient");`，然后用`catch (exception &e)`接住，并且用`e.what()`和`typeid(e).name()`获取信息，另外别忘了`#include <stdexcept>`

### 7.4 Custom Exception Classes

![C++04](../Images/C++04.png?raw=true)

### 7.5 Multiple Catches

try - catch - catch

### 7.6 Exception Propagation

沿着调用链反向查找

### 7.7 Rethrowing Exception and Exception Specification

catch 之后再`throw;`

## 8 Templates

### 8.1 Templates Basics

我们期望得到利用这样的函数解决类似的问题：

```Cpp
GenericType maxValue (const GenericType &x,
                      const GenericType &y) {
    if (x > y)
        return x;
    else
        return y;
}

int main(){
    cout << maxValue(1, 3);
    cout << maxValue(1.0, 3.0);
    cout << maxValue('a', 'x');
    return 0;
}
```

### 8.2 Function Templates

对上面的进行实现：

```Cpp
template<typename T>
T maxValue(T x, T y) {
    if (x > y)
        return x;
    else
        return y;
}
```

如果要用多个类型参数的话，直接`template <typename T, typename S>`

### 8.3 Class Template

```Cpp
template<typename T>
class Stack(){
    // (っ•̀ω•́)っ✎⁾⁾
    public:
        Stack();
        // (っ•̀ω•́)っ✎⁾⁾
};

int main(){
    Stack<int> intStack;
    // (っ•̀ω•́)っ✎⁾⁾
}
```

## 9 Standard Template Library

### 9.1 STL Basics

#### 9.1.1 What is STL

-  Containers
-  Iterators
-  Algorithms
-  Function Objects
-  Memory Allocation

#### 9.1.2 Categories of Containers

-  Sequence containers
   -  vector
   -  list
   -  deque
-  Associative containers
   -  set
   -  multiset
   -  map
   -  multimap
-  Container adapters
   -  stack
   -  queue
   -  priority_queue

#### 9.1.3 Iterators

Iterators are a generalization of pointers.

#### 9.1.4 Algorithm

-  Search
-  Sort
-  compare
-  replace

### 9.2 STL Containers

### 9.3 STL Iterator

-  处理一级容器
-  begin()指向首元素，end()指向尾元素之后那个元素
-  Example：

```Cpp
vector<int>::iterator p1;
for (p1 = intVector.begin(); p1 != intVector.end(); p1++){
    cout << *p1 << " ";
}
```

### 9.4 More on Containers

-  vector 动态数组
-  deque 双端动态数组
-  list 双向链表

-  set
-  multiset
-  map
-  multimap

-  stack
   -  push
   -  pop
   -  top
   -  size
   -  empty
-  queue
   -  push
   -  pop
   -  front
   -  back
   -  size
   -  empty
-  priority_queue
   -  push
   -  pop
   -  top
   -  size
   -  empty

# Change Log

180917 #1 Finished
180919 #2 Finished
181005 #3 Finished
181006 #4 #5 Finished
181013 #6 Finished
181015 #7 #8 #9 Finished

# Reference

1. [网易云课堂 C++程序设计入门（上）](https://mooc.study.163.com/course/1000003015)
2. [网易云课堂 C++程序设计入门（下）](https://mooc.study.163.com/course/1000005002)
