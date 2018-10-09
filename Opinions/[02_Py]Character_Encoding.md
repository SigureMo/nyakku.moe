# Character Encoding
## 1 初识
任何数据在计算机看来都是二进制01组成的代码，所以，为了能将数据存储，就必须转换成二进制的数据，这其中的规则便是编码。
### 1.1 ASCII -> Unicode -> UTF-8
本文所述均为字符编码，那么……就从字符编码的发展讲起吧。
1. ASCII

在字符编码内首先出现的便是ASCII码了，它存储了128个基本字符，仅需要1byte的数据，基本对应键盘上的大部分字符。

2. 各种标准

很明显，我们在ASCII中找不到我们想要的中文字符，当然，中文也不是128个所能容纳的，那么我们就需要有其他的字符编码。所以就中文而言有了’GB2312’这样的编码，同样地，其他国家也有自己的字符编码。这样问题就来了，因为编码规则不同，所以一个码可能对应多个字符，通过不同编码方式解码出来的文字完全不一样，这样的话就会出现我们常说的乱码问题，而且，同一文章也无法兼容两种文字。

3. Unicode

为了统一这一标准Unicode应运而生。Unicode是在ASCII编码的基础上进行了扩展，对ASCII兼容，也即，ASCII码的字符的Unicode码是在其基础上加1byte的0，（这1byte的0便是’’（空字符）啦，所以ASCII解码时候完全不影响哒），Unicode采用2byte数据存储，完美解决了各国标准不一的问题。

4. UTF-8

但是另一个问题就产生了，就是上面所说的，ASCII码对应的字符是要两倍的数据，造成了资源的极大浪费（毕竟英语还是使用最广泛的语言啊），因此便有了我们现在最常用的UTF-8编码。UTF-8编码采用1-3byte数据存储字符，ASCII对应那些字符依然只需要1byte，中文等字符采用2-3byte的编码，使资源得到了极大的节约。因此我们在文件中在的字符采用utf-8编码以节省空间，但当我们读取他们的时候，就会重新编码为Unicode码存到内存中，当我们保存它的时候又会编码为utf-8码存到硬盘上。

### 1.2 Python Encoding

编码（encode）和解码（decode）的问题困扰了我很久，但把之前学的基础知识梳理一遍后就有了新的发现。首先，任何字符串都一定有一个编码规则，不然这个字符串是不会被计算机所认识的，我们在python中的字符是以Unicode编码存储的，也就是说任何存储在python内存的字符都是以Unicode码形式存储的，每个字符都对应一个Unicode码，就比如说’\u6587’是完全等价于’文’的：
```Python
>>> '\u6587'#后面四位是四个十六进制数，刚好是Unicode码对应的2byte（一个16进制数相当于4个2进制数，也即4bit，2byte需要4个16进制数）
'文'
```
而且，我们也可以用chr(),ord()函数将字符进行与Unicode码的互相转换：
```Python
>>> chr(25991)#十进制的25991对应十六进制数就是6587
'文'
```
当然，python也只是用Unicode码存储str，我们的str还是str，并不是一个bytes，想要将它变成一个bytes就需要调用encode方法：
```Python
>>> '文'.encode('utf-8')
b'\xe6\x96\x87' #bytes类型，编码之后对应的字节流，’\x??’是转义为16进制数，每个1byte，一共3byte
```
encode方法是将一个str按照编码方式转化成bytes，这个bytes是我们所看不懂的，但却是文件传输时候所需要的，当我们想要把它再变回str时候是一定要按原来编码方式进行decode，不然就会乱码甚至引发无法解码的错误：
```Python
b'\xe6\x96\x87'.decode('GB2312')
Traceback (most recent call last):
  File "<pyshell#9>", line 1, in <module>
    b'\xe6\x96\x87'.decode('GB2312')
UnicodeDecodeError: 'gb2312' codec can't decode byte 0xe6 in position 0: illegal multibyte sequence
>>> b'\xe6\x96\x87'.decode('utf8')#这里不区分utf8 utf-8的（大小写也都行）
'文'
```
在spider实战过程中遇到了不少编码问题，刚开始还经常将decode和encode弄混，下面记录下遇到的编码问题：
1.	bs4库：把修改bs4对象encoding属性当做之后会对其进行encode，后来才明白原来只是申明编码方式，事实上还是将HTML页面（bytes）进行decode，这样才得到我们所能看到的页面，如果申明的编码方式错误便会出现乱码甚至无法decode的情况。
2.	emoji的处理问题：当时是直接复制过来的，后来才明白是将无法解码的bytes过滤，这样就不会报错了。
```Python
non_bmp_map = dict.fromkeys(range(0x10000, sys.maxunicode + 1), 0xfffd)
r.text.translate(non_bmp_map)#r.text是待解析的str
```
3.	解析页面时候遇到“不间断空白符&nbsp”无法解码的问题：将HTML中获得的str中的该字符进行替换
s.string.replace(u'\xa0',u' ')#s.string是待替换文本


# Amendant Record
1. 180518 Init
2. 180909 Change #1
# Reference
1. [廖雪峰 Python教程](https://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000/001431664106267f12e9bef7ee14cf6a8776a479bdec9b9000)

[goto S_Note;](../README.md)

[return 0;](#character-encoding)