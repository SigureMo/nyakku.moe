# C++ Handbook

由于对 C++ 的使用大多限于刷算法，所以对很多语法的了解并不是很深，而且对于很多好用的接口函数都需要现查现用，为了方便查阅，根据局部性原理，就在自己这里做个 $Cache$ 吧 :joy:

## String

### C++ 中的 string 与 char\* 的转换

由于有时需要在 C++ 中调用 C 的接口函数，但是往往接口要求的是 `char*` 而不是 `string` （当然， C 也没有），所以就需要对 `string` 进行转化

-  `const char* p = str.data();`
-  `const char *p = str.c_str();`

# Reference

1. [C++中 string、char \*、char[]的转换](https://www.cnblogs.com/Pillar/p/4206452.html)
