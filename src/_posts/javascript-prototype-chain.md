---
title: JavaScript 中的“类”与原型链
date: 2021-01-31
category: 墨
tags:
   - JavaScript
   - OOC
---

::: tip

虽然早有耳闻 ECMAScript 的“类”并不是真正的类，但此前我一直都是直接按其他面向对象语言的用法直接用来着，不过也没发现什么不同（毕竟其实也没怎么用过 JS 的说 2333）。

唔，这两天刚好看到了《JavaScript 高级程序设计（第四版）》中的“对象”这一章，就简单整理一下啦～

:::

<!-- more -->

## 实例、构造函数与原型对象

大多数面向对象的编程语言，在获取一个新对象时，都是首先定义一个 class，然后用这个 class 来实例化出来一个对象，而 ECMAScript 是没有类这个概念的，**ECMAScript 中只有对象，所谓的类的继承机制也不过是通过 ECMAScript 的原型链机制实现的**。

在 ECMAScript 中，对象是通过构造函数 new 出来的，就像这样：

```js
function Person(name) {
   this.name = name
}

const person = new Person('Nyakku')

console.log(person.name) // Nyakku
```

由于 Person 是一个函数，所以它当然也可以不用 new 直接调用：

```js
function Person(name) {
   this.name = name
}

Person('Nyakku')

console.log(global.name) // Nyakku
```

不使用 new 调用时，this 自然指向了全局对象 Global（视运行时而定，这里的 Node.js 使用的是 global，而 Deno 与众多浏览器中则使用的是 window），而使用 new 时 this 才会指向新对象（也就是前面的 person）。

在使用 new 新建一个对象后，这个对象与其构造函数之间建立了一种奇妙的联系，可以通过几行代码了解一下：

```js
function Person() {}

const person = new Person()

console.log(person instanceof Person)
console.log(person.__proto__ === Person.prototype)
console.log(Person.prototype.__proto__ === Object.prototype)
console.log(Person.prototype.__proto__.constructor === Object)
console.log(Person.prototype.__proto__.__proto__ === null)
```

当然，上面五个语句返回的都是 `true`，第一个语句没什么可说的，之后的 `__proto__` 是什么鬼，嘛，这就是一个对象用来获取其原型对象的一个属性，比如第二个语句表明了 `person` 是以 `Person.prototype` 为原型的。

::: tip 关于 `__proto__`

事实上并没有访问原型对象的标准方式，但某些运行时会将其暴露在 `__proto__` 属性中，比如 Firefox、Safari、Chrome、Node.js。

但是实践证明这种方式可能会导致一系列安全问题，Deno 和 Node.js 也分别在 [#4324](https://github.com/denoland/deno/issues/4324) 和 [#31951](https://github.com/nodejs/node/issues/31951) 展开了讨论，前者直接删掉了 `__proto__` 这一属性，而后者（v15.6.0）则是默认开启，通过 [`--disable-proto=mode` 选项](https://nodejs.org/dist/latest-v15.x/docs/api/cli.html#cli_disable_proto_mode)可以设置在何种程度上禁用 `__proto__` 属性。

虽说现在各种运行时上的行为不一致，但为了方便，本文就直接使用 `__proto__` 属性来获取原型对象啦。

:::

这么多语句看起来有点复杂呢，我们画个图来整理一下吧～

![prototype01](../img/javascript-prototype-chain/prototype_01.png)

根据刚刚的关系可以轻松画出来这张图，我们可以看到 person 是以 Person.prototype 为原型，而 Person.prototype 则是以 Object.Prototype 为原型，形成了一条原型链，而原型链的终点就是 null。

虽说这张图已经可以将实例、构造函数、原型对象之间的关系大致表示出来，但是细心的小伙伴一定已经发现了一个非常令人疑惑的点：person 是以 Person.prototype 为原型自然不难理解，毕竟 person 是用 Person new 出来的，但 Object.prototype 凭什么可以是 Person.prototype 的原型呢？

稍安勿躁，我们继续往下看。

这次考虑一个稍微复杂的例子：

```js
function SuperType() {}
function SubType() {}

SubType.prototype = new SuperType()
SubType.prototype.constructor = SubType // 保证 constructor 属性正确
const sub = new SubType()

console.log(SubType.prototype.__proto__ === SuperType.prototype)
console.log(sub.__proto__ === SubType.prototype)
```

毋庸置疑，这次返回的也是 ture，毕竟 SubType.prototype 是由 SuperType 所 new 出来的，所以 SuperType.prototype 自然是 SubType.prototype 的 原型。

值得注意的是，SubType.prototype 是由 SuperType new 出来的，也就是说前者是后者的实例，而 sub 则是 SubType.prototype 的实例，由此形成一条非常清晰的原型链，我们依此将刚刚的图进行补足。

![prototype02](../img/javascript-prototype-chain/prototype_02.png)

在刚刚图的结构上稍加修整，不难画出这样的图，在这张图上我们可以清晰地看出 SuperType.prototype 是 SubType.prototype 的原型的原因是后者是前者构造函数 new 出来的，这也与刚刚在代码中所分析的一致。那么 SuperType.prototype 为何是 Object.prototype 的实例此时想必已经呼之欲出了。由于我们并没有明确指定 SuperType 的 prototype，此时其默认原型就是一个 Object 的实例，也就相当于 `SuperType.prototype = new Object()`。

与此同时，我们也不难发现，**对于任何一个构造函数 F，使用这个构造函数 new 出来的实例会以 F.prototype 为原型，这就是它们三者之间的关系**。

## 原型链机制

下面我们忽略掉构造函数，只看我们关心的对象：

![prototype03](../img/javascript-prototype-chain/prototype_03.png)

很明显，一个原型是可以创造多个实例（如 super1、super2、super3、super4）的，但是有时一个实例（如 super4）会突然不想只做一个平平淡淡的实例啦，然后就自己做起了一个原型，并创造起了自己的实例。

而对于任何一个实例，都有唯一的一条路径向上寻找自己的原型，甚至原型的原型，这条路径就是专属于它的原型链。

那么这么一条路径有什么用呢？

ECMAScript 有一个机制就是，如果访问自身某个属性访问不到时，会去尝试访问其原型的属性，当然，其原型如果还有原型的话还会按照这条规则查找，这就是原型链的作用。

下面举个例子：

```js
function SuperType() {}
function SubType() {}

SubType.prototype = new SuperType()
SubType.prototype.constructor = SuperType
const sub = new SubType()

SuperType.prototype.name = 'SuperPrototype'
console.log(sub.name) //  SuperPrototype
```

这里 sub 明明没有 name 属性的，所以会向上查找 SubType.prototype，不过也是没有 name 属性诶～那就继续找 SuperType.prototype 吧，嗯，找到了呢～

但一个实例应当拥有自己的属性的呀，那要怎么做呢？

接着上面的代码，在后面添加下面几行：

```js
sub.name = 'sub'

console.log(sub.name) // sub
console.log(SubType.prototype.name) // SuperPrototype
console.log(SuperType.prototype.name) // SuperPrototype
```

一个实例想要自己的属性的话，直接在自己对象上添加属性就好了，此时在对象上已经查找到这个属性值了，所以不会向上查找。当然 SubType.prototype 还是会向上查找的。

有没有发现，通过原型链机制可以很方便地实现继承？新的实例可以直接到定义在原型上的属性，而且也可以方便地对已有属性进行修改。

但是，原型链还有一个最大的弊端，就是如果原型上属性的数据类型不是原始类型，而是引用类型时，对该属性的修改会直接影响到原型的属性，下面举个例子：

```js
function Person() {}

Person.prototype.devices = ['Phone']

const person1 = new Person()
const person2 = new Person()

person1.devices.push('PC')
console.log(person1.devices) // [ 'Phone', 'PC' ]
console.log(person2.devices) // [ 'Phone', 'PC' ]
console.log(Person.prototype.devices) // [ 'Phone', 'PC' ]
```

上面最终运行的结果是每个人的 devices 都变成了 `[ 'Phone', 'PC' ]`，究其根本，是直接调用原型上的引用类型属性的方法，改变了其值，这导致所有以其为原型的对象都会受到影响。

但这个问题还是无法解决的，毕竟原型链与引用类型就是这样的机制，所以说仅仅简单使用原型链机制还是无法实现完美的继承的。

那么，怎么才能实现我们心目中的继承呢？

## 使用原型链实现继承

我们下面一步步修改上面的例子，让它能够实现我们想要的继承。

为了避免上面的原型链上引用类型数据带来的问题，属性最好不要定义在原型上，如果能定义在每个实例上最好不过了。

emmm，想要定义在实例上的话，只需要把定义属性这一过程放到构造函数中就好。

```js
function Person() {
   this.devices = ['Phone']
   this.sayName = function() {
      console.log('Person')
   }
}

const person1 = new Person()
const person2 = new Person()
person1.devices.push('PC')
console.log(person1.devices) // [ 'Phone', 'PC' ]
console.log(person2.devices) // [ 'Phone' ]
```

此时，person1 和 person2 在实例对象上就有了各自的属性，因此不需要查找原型上的属性了。

不过要如何实现继承呢？

```js
function SuperType() {
   this.name = 'SuperType'
   this.sayName = function() {
      console.log(this.name)
   }
}

function SubType() {
   SuperType.call(this) // 继承 SuperType
}

SubType.prototype = new SuperType()
SubType.prototype.constructor = SubType
const sub = new SubType()

console.log(sub.name) // SuperType
sub.sayName() // SuperType
sub.name = 'sub'
sub.sayName() // sub
console.log(SubType.prototype.name) // SuperType
```

在 SubType 中将 SuperType 函数作用于自身，就可以将属性和方法继承起来了，这种方式被称作“盗用构造函数”。

很好，此时已经完成了继承的效果了，但是仍有两处不足：

-  方法在每个实例中都定义了一份，然而很明显我们方法只需要共用同一个就行了，这造成了极大的空间浪费。
-  明明每个实例上都有各自的属性了，但原型上还是定义了一份属性，这也造成了空间的浪费。

下面一一解决这两个问题。

首先，既然方法只需要一份，那么我们就不在构造函数中定义方法，而在原型上定义。

```js
function SuperType() {
   this.name = 'SuperType'
}

SuperType.prototype.sayName = function() {
   console.log(this.name) // 通过构造函数继承 SuperType 的属性
}

function SubType() {
   SuperType.call(this)
}

SubType.prototype = new SuperType() // 通过原型链继承 SuperType 的方法
SubType.prototype.constructor = SubType
const sub = new SubType()

console.log(sub.name) // SuperType
sub.sayName() // SuperType
sub.name = 'sub'
sub.sayName() // sub
console.log(SubType.prototype.name) // SuperType
```

这样，定义在原型上的方法就可以被实例通过原型链获取到，实例本身是没有这个方法的。

好了，方法的问题解决了，那么在原型对象上的冗余属性要怎么解决呢？

首先看问题在哪？原型对象的冗余属性就是在构造该原型对象时添加的：

```js
SubType.prototype = new SuperType()
```

这条语句不仅仅实现了搭建了原型链，还让在该原型对象上执行了一遍构造函数，这才使得该原型对象上有着冗余的属性。

那么有没有办法可以既保留原型链，又能不执行这个构造函数呢？

当然是有滴～我们这回构造 SubType.prototype 不用 SuperType 就好啦，临时创建一个空的函数 F，并将其 prototype 绑定在 SuperType.prototype 上，不就可以曲线地构造这条原型链了嘛～

```js
function F() {}
F.prototype = SuperType.prototype
SubType.prototype = new F()
```

把上面那行代码换成这段就可以解决属性的冗余问题啦，由于现在 SubType.prototype 不再是 SuperType 直接构造出来的，之前那张“实例、构造函数、原型对象关系”图也需要更新一下下啦～

![prototype04](../img/javascript-prototype-chain/prototype_04.png)

此时继承时所使用的 prototype 都应当是使用一个临时的构造函数 F new 出来的，这个过程封装成函数就好，出函数后 F 应当就会被自动回收了。

## 语法糖 class

虽然我们可以通过原型链机制与亿点点改动实现继承的效果，但每次写个继承都需要一大堆代码，属实令人难以接受。

好在 ES6 添加了 class 语法糖，让我们能够像写其他语言的类一样写继承啦，不过 class 毕竟只是语法糖，究其根本还是通过原型链实现的。

```js
class SuperType {
   constructor() {
      this.name = 'SuperType'
   }

   sayName() {
      console.log(this.name)
   }
}

class SubType extends SuperType {
   constructor() {
      super()
   }
}

const sub = new SubType()

console.log(sub.name) // SuperType
sub.sayName() // SuperType
sub.name = 'sub'
sub.sayName() // sub
console.log(SubType.prototype.name) // SuperType
```

喏，上面的代码就实现了之前的功能，代码还更加简洁，再也不用头疼什么 prototype 啦原型链什么的了，而且还支持 static 关键字定义类静态方法，比原来的 prototype 方便多啦嘻嘻～

## References

1. 《JavaScript 高级程序设计（第四版）》 Matt Frisbie
