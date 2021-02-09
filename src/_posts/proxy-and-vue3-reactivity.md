---
title: Proxy 以及 Vue3 中的响应式
date: 2021-02-10
category: 游
tags:
   - JavaScript
   - Vuejs
---

::: tip

呜，前两天看完对象那一章之后就开始看 Proxy 那一章了，虽然不难，但总觉得没啥用，难道会有人拿着代理去操作一番嘛？直接操作源数据不香嘛？所以我看了一半就溜了……结果这两天就发现 Vue3 的响应式就是通过 Proxy 实现的……

:::

<!-- more -->

## Proxy 是个什么鬼

Proxy 就是代理啦，我们可以为一个对象创建一个代理对象，之后通过这个代理对象也可以访问目标对象了。

```js
const target = {
   name: 'foo',
   age: 10,
   friend: {
      name: 'bar',
      age: 11,
   },
}

const proxy = new Proxy(target, {})
console.log(proxy.name) // 'foo'
```

这里的 proxy 是以 target 为目标对象创建出来的代理对象，因此访问 proxy 就相当于访问 target 了，但……这有什么用嘛……别急，有用的在第二个参数。

Proxy 构造函数第二个位置接受的是一个 ProxyHandler，以此修改通过 proxy 访问时的行为。

那么就简单举个例子吧～

```js
const handler = {
   get(target, property, receiver) {
      console.log(`有个坏人想访问 ${property} 但被我拒绝了～`)
      return '哼！才不告诉你！'
   },
}

const proxy = new Proxy(target, handler)
// 有个坏人想访问 name 但被我拒绝了～
console.log(proxy.name) // '哼！才不告诉你！'
// 有个坏人想访问 age 但被我拒绝了～
console.log(proxy.age) // '哼！才不告诉你！'
console.log(target.name) // 'foo'
```

这里定义了一个拥有 get 方法的 handler，也就是说我们如果通过 proxy 来访问 target 并且执行的是 GET 操作的话，那么便会执行该函数。很明显，我这样定义后通过 proxy 无论访问任何属性都只能返回「哼！才不告诉你！」。当然，target 对象本身并没有改变，我们仍然可以通过直接访问到任何属性。

此时代理的功能就显而易见了，它相当于为我们增加了一个操作目标对象的方式，通过该方式操作对象会被 ProxyHandler 所接管，提高了对象的扩展性。另外由于 handler 是定义在 proxy 上的，所以对目标对象是没有任何「污染」的。

![proxy_01](../img/proxy-and-vue3-reactivity/proxy_01.png)

嘛，这么看其实和网络代理也很像嘛，当我们开启代理时就是经由代理获取网络数据，而关闭代理则是直连目的主机～

## 默认行为：Reflect

唔，不过我们要如何还原 get 时的行为呢？当然不定义 get 方法就好了……那如果定义了呢？ECMAScript 中还定义了一系列 Reflect API，它们可以看作是在我们不定义时的默认行为，比如下面这样：

```js
const handler = {
   get(target, property, receiver) {
      return Reflect.get(target, property, receiver)
   },
}

const proxy = new Proxy(target, handler)
console.log(proxy.name) // 'foo'
```

此时再使用 get 就相当于默认行为啦，当然我们也可以这样：

```js
const handler = {
   get: Reflect.get,
}
```

由于 Reflect 定义了全部默认的 Handler，所以我们甚至可以像下面这样将全部 handler 都设为默认反射行为：

```js
const proxy = new Proxy(target, Reflect)
```

当然，效果和之前是一样的。

有了 Reflect API 我们就可以做更多有趣的事情了，比如像下面这样在不影响结果的情况下监听 get 事件：

```js
const handler = {
   get(target, property, receiver) {
      console.log(`[GET] ${property} 被访问`)
      return Reflect.get(target, property, receiver)
   },
}

const proxy = new Proxy(target, handler)
// [GET] name 被访问
console.log(proxy.name) // 'foo'
```

## Vue3 中 reactive 的响应式

随便打印一个 Vue3 中的 reactive 返回的对象便可以发现是一个代理，既然如此，Vue3 的响应式的实现方式其实已经很容易猜到了。

从 Vue3 源码可以得知，reactive 返回的代理对象代理了 get、set、deleteProperty、has、ownKeys 五种行为。很容易写出代理的方法：

```ts
const handler: ProxyHandler<any> = {
   get(target, property, receiver) {
      return Reflect.get(target, property, receiver)
   },

   set(target, property, value, receiver) {
      return Reflect.set(target, property, value, receiver)
   },

   deleteProperty(target, property) {
      return Reflect.deleteProperty(target, property)
   },

   has(target, property) {
      return Reflect.has(target, property)
   },

   ownKeys(target) {
      return Reflect.ownKeys(target)
   },
}

function reactive<T extends object>(target: T): T
function reactive(target: object) {
   return new Proxy(target, handler)
}
```

当然现在这只是默认行为，我们完全可以根据需要在其中添加代码。在 Vue3 源码中，我们可以发现在 get、has、ownKeys 这种不会对数据进行改变的 handler 中都会调用 track 这个方法，而 set、deleteProperty 这种明显会改变数据的方法中则会调用 trigger 方法。我们先不理会它们的作用，先尝试实现一下。

```ts
function trigger(target: object, type: string, key: unknown) {
   console.log(`[Trigger] 执行了 ${type} 操作，目标属性为 ${key}`)
}

function track(target: object, type: string, key: unknown) {
   console.log(`[Track] 执行了 ${type} 操作，目标属性为 ${key}`)
}

const handler: ProxyHandler<any> = {
   get(target, property, receiver) {
      track(target, 'GET', property)
      return Reflect.get(target, property, receiver)
   },

   set(target, property, value, receiver) {
      trigger(target, 'SET', property)
      return Reflect.set(target, property, value, receiver)
   },

   deleteProperty(target, property) {
      trigger(target, 'DELETE', property)
      return Reflect.deleteProperty(target, property)
   },

   has(target, property) {
      track(target, 'HAS', property)
      return Reflect.has(target, property)
   },

   ownKeys(target) {
      track(target, 'OWN_KEYS', '')
      return Reflect.ownKeys(target)
   },
}

function reactive<T extends object>(target: T): T
function reactive(target: object) {
   return new Proxy(target, handler)
}
```

我们测试一下是否能够正确触发相关函数：

```ts
const target = {
   name: 'foo',
   age: 10,
   friend: {
      name: 'bar',
      age: 11,
   },
}

const proxy = reactive(target)
console.log(proxy) // { name: "foo", age: 10, friend: { name: "bar", age: 11 } }
proxy.friend.name = 'baz'
// [Track] 执行了 GET 操作，目标属性为 friend
console.log(proxy) // { name: "foo", age: 10, friend: { name: "baz", age: 11 } }
```

这里 `proxy.friend` 成功地触发了 get 里的 track，但 `friend.name = 'baz'` 却没有触发 set 里的 trigger，归根结底，是因为 `friend` 并不是一个 proxy，自然也就不会被经过 handler 里的 set 方法。也就是说我们现在只实现了一个浅层的响应式，也就是 shallowReactive。

那么如何让深层对象也能经过代理访问呢？一种方法就是在初始化时将目标对象中所有的对象修改为代理，另外如果新 set 的值是对象的话，也需要修改为代理，以保证我们的对象中只存在对象的代理，而不存在对象本身。

```ts
const isObject = (val: unknown): val is Record<any, any> => val !== null && typeof val === 'object'

const handler: ProxyHandler<any> = {
   get(target, property, receiver) {
      track(target, 'GET', property)
      return Reflect.get(target, property, receiver)
   },

   set(target, property, value, receiver) {
      // 如果新值为 object，则获取其代理再存入
      if (isObject(value)) {
         value = reactive(value)
      }
      trigger(target, 'SET', property)
      return Reflect.set(target, property, value, receiver)
   },

   deleteProperty(target, property) {
      trigger(target, 'DELETE', property)
      return Reflect.deleteProperty(target, property)
   },

   has(target, property) {
      track(target, 'HAS', property)
      return Reflect.has(target, property)
   },

   ownKeys(target) {
      track(target, 'OWN_KEYS', '')
      return Reflect.ownKeys(target)
   },
}

function reactive<T extends object, U extends keyof T>(target: T): T {
   for (const [key, value] of Object.entries(target)) {
      // 将所有为对象的 value 转化为其代理后存入
      if (isObject(value)) {
         target[key as U] = reactive(value) as T[U]
      }
   }
   return new Proxy(target, handler)
}
```

emmm，简单测试即可发现深层响应式已经能够实现了：

```ts
const proxy = reactive(target)
console.log(proxy) // { name: "foo", age: 10, friend: { name: "bar", age: 11 } }
proxy.friend.name = 'baz'
// [Track] 执行了 GET 操作，目标属性为 friend
// [Trigger] 执行了 SET 操作，目标属性为 name
console.log(proxy) // { name: "foo", age: 10, friend: { name: "baz", age: 11 } }
```

但……这样真的好吗？很明显，目标对象已经被「污染」了，代理得不够彻底啊～

那……要怎么做呢？我们可以发现在 `proxy.friend` 执行时已经触发了一个 get，此后才是 set 操作，那么……我们能否在 get 上做点手脚呢？其实很简单啦，只要 get 时返回代理就好啦，这样之后的 set 也是通过代理进行操作的。

```ts
const isObject = (val: unknown): val is Record<any, any> => val !== null && typeof val === 'object'

const handler: ProxyHandler<any> = {
   get(target, property, receiver) {
      track(target, 'GET', property)
      const res = Reflect.get(target, property, receiver)
      // 如果值为对象，则返回其代理
      if (isObject(res)) {
         return reactive(res)
      }
      return res
   },

   set(target, property, value, receiver) {
      trigger(target, 'SET', property)
      return Reflect.set(target, property, value, receiver)
   },

   deleteProperty(target, property) {
      trigger(target, 'DELETE', property)
      return Reflect.deleteProperty(target, property)
   },

   has(target, property) {
      track(target, 'HAS', property)
      return Reflect.has(target, property)
   },

   ownKeys(target) {
      track(target, 'OWN_KEYS', '')
      return Reflect.ownKeys(target)
   },
}

function reactive<T extends object>(target: T): T
function reactive(target: object) {
   return new Proxy(target, handler)
}
```

测试结果和上面一样，也解决了刚刚的问题，但是有一个新的小小的问题：这样岂不是每次访问一个值为对象的属性都创建一个新的代理对象？

通过测试发现也确实如此：

```ts
console.log(proxy.friend === proxy.friend) // false
```

当然，Vue3 怎么会没想到这一点？解决方法也很简单，建立一个全局对象来存储已经创建过的 proxy 即可：

```ts
const proxyMap = new WeakMap<any>()

function reactive<T extends object>(target: T): T
function reactive(target: object) {
   const existingProxy = proxyMap.get(target)
   if (existingProxy) {
      return existingProxy
   }
   const proxy = new Proxy(target, handler)
   proxyMap.set(target, proxy)
   return proxy
}
```

这里采用的是 WeakMap，也就是说在运行时执行垃圾回收之前我们都可以复用。那么再来测试一下：

```ts
console.log(proxy.friend === proxy.friend) // true
```

此时便不必再担心产生多余的 proxy 了。

当然 Vue3 源码中细节还有很多很多，比如 track 与 trigger 的作用、以及它们与 effect 之间的关系等等，简单看了下……都还没有搞懂……

不过这次探索只是初学 Proxy 的一个延伸罢了，所以其他的暂且先不管，等以后有兴趣的时候再去看看吧～

## References

1. 《JavaScript 高级程序设计（第四版）》 Matt Frisbie
2. [Vue3 源码 reactivity 部分](https://github.com/vuejs/vue-next/tree/master/packages/reactivity)
3. [Vue3 文档](https://v3.cn.vuejs.org/api/basic-reactivity.html#reactive)
