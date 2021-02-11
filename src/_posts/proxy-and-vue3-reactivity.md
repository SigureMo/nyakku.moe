---
title: Proxy 以及 Vue3 中的响应式
date: 2021-02-10
category: 游
tags:
   - JavaScript
   - Vuejs
   - VCA
---

::: tip

呜，前两天看完对象那一章之后就开始看 Proxy 那一章了，虽然不难，但总觉得没啥用，难道会有人拿着代理去操作一番嘛？直接操作源数据不香嘛？所以我看了一半就溜了……结果这两天就发现 Vue3 的响应式就是通过 Proxy 实现的……

:::

<!-- more -->

## Proxy 与 Reflect

### Proxy 是个什么鬼

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

### 默认行为：Reflect

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

## Vue3 响应式原理浅析

### 响应式基础 API —— reactive

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
      const res = Reflect.set(target, property, value, receiver)
      trigger(target, 'SET', property)
      return res
   },

   deleteProperty(target, property) {
      const res = Reflect.deleteProperty(target, property)
      trigger(target, 'DELETE', property)
      return res
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
      const res = Reflect.set(target, property, value, receiver)
      trigger(target, 'SET', property)
      return res
   },

   deleteProperty(target, property) {
      const res = Reflect.deleteProperty(target, property)
      trigger(target, 'DELETE', property)
      return res
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
      const res = Reflect.set(target, property, value, receiver)
      trigger(target, 'SET', property)
      return res
   },

   deleteProperty(target, property) {
      const res = Reflect.deleteProperty(target, property)
      trigger(target, 'DELETE', property)
      return res
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

```ts{5-8}
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

### ref API

reactive API 主要是将对象转化为响应式对象，因此，即便是基本数据类型的数据，我们也完全可以通过封装成对象后再使用 reactive API 形成响应式数据。

```vue
<template>
   <button type="button" @click="onClick">count: {{ count.value }}</button>
</template>

<script lang="ts">
import { reactive, defineComponent } from 'vue'
export default defineComponent({
   setup() {
      const count = reactive({
         value: 0,
      })

      const onClick = function() {
         count.value++
      }

      return {
         count,
         onClick,
      }
   },
})
</script>
```

这样当然可以实现响应式啦，不过在使用的时候手动地封装对象总觉得比较麻烦，毕竟我们明明在操作一个基本数据类型，却不得不使用对象的方式来操作。

为了解决这一问题，ref API 应运而生，先看下使用方法：

```vue {2,6,9}
<template>
   <button type="button" @click="onClick">count: {{ count }}</button>
</template>

<script lang="ts">
import { ref, defineComponent } from 'vue'
export default defineComponent({
   setup() {
      const count = ref(0)

      const onClick = function() {
         count.value++
      }

      return {
         count,
         onClick,
      }
   },
})
</script>
```

其实只是初始化数据时候不需要自己定义新的对象与模板中不必使用 .value 而已，在 JS 代码中操作 Ref 仍然需要通过 .value 来访问。那么这个 .value 到底能不能去掉呢？答案是不可能，因为一个基本数据类型在传参时是只传值的，因此为了响应式就必然封装成对象，既然封装成了对象，那么就不可能直接访问这个数据，只能通过一个属性来间接访问数据。当然，如果有朝一日你 JS 支持指针、引用的话，也许这是可以做到的。

既然基本使用方法已经了解了，其实其实现也能够猜个差不多了，除了再次封装为一个对象交由 reactive 处理外，我们还可以封装成对象后，重写 getter 和 setter 来实现；

```ts
interface Ref<T = any> {
   _value: T
   value: T
}

function ref<T>(initValue: T): Ref<T> {
   return {
      _value: initValue,
      get value() {
         track(this, 'GET', 'value')
         return this._value
      },
      set value(newVal) {
         this._value = newVal
         trigger(this, 'SET', 'value')
      },
   }
}

const count = ref(0)
// [Track] 执行了 GET 操作，目标属性为 value
// [Trigger] 执行了 SET 操作，目标属性为 value
console.log(++count.value) // 1
```

当然，在 get 和 set 中不要忘记 track 和 trigger。这样我们在调用 `++count.value` 时便成功地调用了 GET 与 SET 方法咯～～～

不过这样写的话，由于所有方法都是定义在对象其本身上的，所有在创建大量这样的对象时就会造成大量的空间浪费。这个问题的解决方案嘛，当然是通过原型链解决啦，不过我们既然会用语法糖 class 了当然就直接使用 class 咯。

```ts
interface Ref<T = any> {
   value: T
}

class RefImpl<T> {
   private _value: T

   constructor(initValue: T) {
      this._value = initValue
   }

   get value() {
      track(this, 'GET', 'value')
      return this._value
   }

   set value(newVal) {
      this._value = newVal
      trigger(this, 'SET', 'value')
   }
}

function ref<T>(value: T): Ref<T> {
   return new RefImpl(value)
}
```

效果呢？测试结果和刚刚完全一致，不必担心～

### track、trigger 以及 effect

哼，这三个东西我起初是不打算了解的，直接看源码也确实没看懂要做些什么，随手搜了一下，就全都在说 track 在收集依赖，trigger 则是触发所有依赖于此的 effect，可是 effect 是个啥啊，什么时候用啊，基本没有一篇文章说清楚的……

因此，起初我其实写完 reactive 就停手了的，但是之后实在是没忍住就又去查了一下，算是大概了解了他们的作用了吧？

为了更好地理解 track、trigger 以及 effect，我基于一定的猜想对整个模型进行绘制，所以不保证模型的准确性啦～

![vue3_reactivity_01](../img/proxy-and-vue3-reactivity/vue3_reactivity_01.png)

我们不妨认为整个视图是一个大拼图，其中不同部分依赖着不同的数据，这里 piece2、piece4、piece8 都依赖着数据 `data[key]`，当然，这可能是数据插槽：

```vue
<template>
   <div>{{ data[key] }}</div>
</template>
```

也可能是 v-bind 等指令绑定的数据：

```vue
<template>
   <div :class="data[key]"></div>
</template>
```

等等等等……

在这里，我们不妨先简单地认为首次渲染时分别执行了以下操作：

```js
View.render = () => {
   View.piece2.render(data[key] + 1)
   View.piece4.render(data[key])
   View.piece8.render(data[key] - 1)
}
```

嗯，很好，我们可以完成数据的首次渲染了，但……响应式呢？？？下次我们如何才能在 `data[key]` 更新时重新渲染这三块拼图呢？

首先，我们先要知道数据 `data[key]` 都被哪几块拼图依赖了，我们要如何追踪这个依赖呢？其实不难发现，依赖 `data[key]` 的拼图是要将 `data[key]` 渲染到 View 上，那么就必然要获取 `data[key]` 的值，也就是必定会执行 GET 操作，因此我们应该在 handler 的 get 中执行相关依赖收集操作，而这个过程则被封装成了 track 函数。

那么 track 函数如何实现对依赖进行收集呢？很简单，我们建立一个 map，用来存储这个依赖与 `data[key]` 之间的依赖关系就好了。

这里先建立全局的 `targetMap: WeakMap`，`targetMap[data]` 就是这个 `data` 的相关依赖。由于不同 `key` 也是拥有不同的依赖，所以再建立一层 `depsMap: Map`，`targetMap[data][key]` 存的就是全部依赖。由于依赖可能不止一条，所以它需要是个 Set。

不过，Set 里要存的依赖是什么呀？emmm，先不用管，我们先只需要知道要存的是 `activeEffect` 就好。那么就简单实现下吧：

```ts
type Dep = Set<Function>
type KeyToDepMap = Map<any, Dep>
const targetMap = new WeakMap<any, KeyToDepMap>()

function track(target: object, type: string, key: unknown) {
   console.log(`[Track] 执行了 ${type} 操作，目标属性为 ${key}`)
   let depsMap = targetMap.get(target)
   if (!depsMap) {
      targetMap.set(target, (depsMap = new Map()))
   }
   let dep = depsMap.get(key)
   if (!dep) {
      depsMap.set(key, (dep = new Set()))
   }
   if (!dep.has(activeEffect)) {
      dep.add(activeEffect)
   }
}
```

代码很简单，就是普通的建立两层 map 和一层 set 而已。

但是 `activeEffect` 是什么？

其实不难理解，在渲染数据时，piece4 对应的渲染语句 `View.piece4.render(data[key])` 其实就是下次数据发生变化时需要重新执行的语句，也就是说该语句依赖于 `data[key]`，那么我们就把该语句存到 `targetMap[data][key]` 中即可。也就是说，`activeEffect` 中存的就是刚刚执行的那条渲染语句。

由于依赖关系是在首次渲染时建立的，因此我们应当把首次渲染伪代码稍微修改下：

```js
View.render = () => {
   effect(() => View.piece2.render(data[key] + 1))
   effect(() => View.piece4.render(data[key]))
   effect(() => View.piece8.render(data[key] - 1))
}
```

那么 effect 中执行了什么呢？

```ts
let activeEffect: Function | undefined
function effect(fn: Function) {
   const _effect = () => {
      activeEffect = fn
      fn() // 执行渲染语句，如果该语句依赖于某个 data[key]，那么将会由于 get 而触发 track
      // track 中则会将 activeEffect 也就是 fn 存储到 data[key] 的依赖中
   }
   _effect()
}
```

其实很简单啦，无非就是将这个函数记录到全局变量 `activeEffect`，并且执行一次（初次渲染）。

在初次渲染时，如果该渲染项依赖于某个 `data[key]`，那么在 get 时就会触发 track 函数，将 `activeEffect` 存入 `data[key]` 的依赖中，而 `activeEffect` 这个全局变量刚刚被替换成了这条渲染语句，这样这条渲染语句就被存起来了。

呼，总算存进去了，不过现在有一个问题就是，即便不是 effect 包裹的语句中只要使用 get 都会触发 track 中的依赖收集，为了避免这一问题，我们再稍微改造一下 track 与 effect 函数。

```ts{7,27,30}
type Dep = Set<Function>
type KeyToDepMap = Map<any, Dep>
const targetMap = new WeakMap<any, KeyToDepMap>()

function track(target: object, type: string, key: unknown) {
   console.log(`[Track] 执行了 ${type} 操作，目标属性为 ${key}`)
   if (shouldTrack) {
      let depsMap = targetMap.get(target)
      if (!depsMap) {
         targetMap.set(target, (depsMap = new Map()))
      }
      let dep = depsMap.get(key)
      if (!dep) {
         depsMap.set(key, (dep = new Set()))
      }
      if (!dep.has(activeEffect)) {
         dep.add(activeEffect)
      }
   }
}

let activeEffect: Function | undefined
let shouldTrack: boolean = false

function effect(fn: Function) {
   const _effect = () => {
      shouldTrack = true
      activeEffect = fn
      fn() // 只有 effect 中的语句才能进入 track 的依赖收集逻辑
      shouldTrack = false
   }
   _effect()
}
```

嗯，再加一个全局变量来限制非 effect 中的 get 方法就好了。

现在依赖应当是被正常收集了～

那么，就差在 trigger 时把依赖都触发了，不过 trigger 中分为 DELETE、SET 和 ADD 方法，比较复杂，这里就只实现最简单的 SET 方法。

```ts
function trigger(target: object, type: string, key: unknown) {
   console.log(`[Trigger] 执行了 ${type} 操作，目标属性为 ${key}`)
   const depsMap = targetMap.get(target)
   if (!depsMap) {
      return
   }
   switch (type) {
      case 'SET':
         if (!depsMap.has(key)) {
            return
         }
         // 遍历 targetMap[data][key]，重新执行所有依赖于 data[key] 的语句
         for (const effect of depsMap.get(key)) {
            effect()
         }
         break
   }
}
```

这里自然是不难理解啦，最后我们测试一下～

```ts
const count = ref(0)

effect(() => {
   console.log(`render: ${count.value}`)
})
count.value++
count.value++
```

输出结果如下：

```
[Track] 执行了 GET 操作，目标属性为 value
render: 0
[Track] 执行了 GET 操作，目标属性为 value
[Trigger] 执行了 SET 操作，目标属性为 value
[Track] 执行了 GET 操作，目标属性为 value
render: 1
[Track] 执行了 GET 操作，目标属性为 value
[Trigger] 执行了 SET 操作，目标属性为 value
[Track] 执行了 GET 操作，目标属性为 value
render: 2
```

前两行自然就是首次渲染，渲染结果是 0。

3、4 行是 count++ 触发的 GET 与 SET，在 SET 里又触发了语句的重新渲染。

5、6 行便是重新渲染时的结果，重新渲染中触发了 GET，渲染结果为 1。

最后四行和 3、4、5、6 行完全一样，就不再赘述了……

嘻嘻，完成啦～源码就先整理到[这里](https://github.com/SigureMo/vue-reactivity)好了。

呼，总算完事了，本来这次探索只是初学 Proxy 的一个延伸罢了，原来就想看看 reactive 的源码就算了，但实在是觉得探索了一半有点可惜，才把 track 等的作用也给分析了下。唔，不过分析的很浅啦，可能还有不少错误的地方，而且很多细节暂且都没有考虑……嗯，以后有机会再深度研读下 Vue3 源码吧，这次就到这里好了～

## References

1. 《JavaScript 高级程序设计（第四版）》 Matt Frisbie
2. [Vue3 源码 reactivity 部分](https://github.com/vuejs/vue-next/tree/master/packages/reactivity)
3. [Vue3 文档](https://v3.cn.vuejs.org/api/basic-reactivity.html#reactive)
