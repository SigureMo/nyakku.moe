---
title: Re：从零开始的 CSS 的学习之旅
date: 2020-07-08
category: 迹
tags:
   - front end
---

::: tip

虽然此前已经无数次尝试接触前端项目，却从未认真学习 CSS 等前端知识，导致连个样式都不会添加，因此最近下定决心（但愿）抽空系统地学习下前端的知识～

:::

<!-- more -->

## CSS 基础

### 选择器

-  元素选择器 用元素名标记，如 `p`
-  class 选择器 用 `.<class>` 来标记，如 `.cat`
-  id 选择器 用 `#<id>` 来标记，如 `#cat`（优先级更高）
-  属性选择器 用 `[<attr>=‘<value>’]`来标记，如 `[name=‘cat’]`

### 文本

-  颜色 `color`
   -  名称方式，如 `red`
   -  十六进制，如 `#FF0000`
   -  十六进制缩写，如 `#F00`
   -  rgb(rgba)，如 `rgb(255, 0, 0)` 以及 `rgba(255, 0, 0, 1)`
   -  hsl(hsla)，如 `hsl(0, 100, 50)` 以及 `rgba(0, 100, 50, 1)`
-  字体 `font-family`
-  字体大小 `font-size`

### 图片

-  大小（`width` 和 `height`）
   -  绝对单位
      -  英寸 `in`
      -  毫米 `mm`
   -  相对单位
      -  像素 `px`
      -  百分比 `%`
      -  元素
         -  相对于设置了大小的父级元素 `em`
         -  相对于根元素 `rem`
      -  视窗
         -  视窗宽度 `vw`
         -  视窗高度 `vh`
         -  视窗宽高中较小值 `vmin`
         -  视窗宽高中较大值 `vmmax`

### 边框

基本用法

```css
.thin-red-border {
   border-color: red;
   border-width: 5px;
   border-style: solid;
}
```

加个圆角 `border-radius: 15px`，进一步，设置值为 `50%` 的话，就是个圆咯～

### 盒模型

-  内容 `content`
-  内边距 `padding` 也即边框到内容之间填充的距离
-  边框 `border`
-  外边距 `margin` 也即边框到相邻元素或者父容器之间的距离，还可以设置为负值以达到灵活的定位效果～

---

-  （内/外）边距的设置

   -  分别设置

      ```css
      div {
         margin-top: 10px;
         margin-right: 20px;
         margin-bottom: 30px;
         margin-left: 40px;
      }
      ```

   -  按照顺时针设置

      -  写 1 个自然四周都一样
      -  写 4 个将会按顺时针（上右下左）来分配

         ```css
         div {
            margin: 10px 20px 30px 40px;
         }
         ```

      -  写 2 个分别表示上下和左右
      -  写 3 个分别表示上、左右、下

### 样式优先级

-  important 声明
-  内联样式
-  ID 选择器
-  Class 选择器
-  继承样式

### 变量

```css
.theme {
   /* 该类的元素才可以使用，为了保证变量全局有效，
   常在 :root 下创建全局变量 */
   --accent-color: #3eaf7c;
}
.logo {
   background-color: var(--accent-color);
}
```

## 应用视觉设计

-  文本对齐方式 `text-align`
-  宽度高度调整 `width` 和 `height`
-  文本修饰
   -  加粗 `strong`
   -  下划线 `u`（underline）
   -  强调 `em`（emphasis）
   -  删除线 `s`（strikethrough）
-  水平线 `hr`
-  元素阴影 `box-shadow`
   -  `offset-x` 水平偏移量
   -  `offset-y` 竖直偏移量
   -  `blur-radius` 模糊半径
   -  `spread-radius` 延伸半径
   -  颜色
-  透明度 `opactiy`
-  悬停伪类 `:hover`
-  定位 `position`，具体类型如下

   -  相对定位 `relative`，相对于该元素原本的位置，其占位空间并不会变
   -  绝对定位 `absolute`，相对于最近的已定位父级元素，元素从文档流移除，不再占位
   -  固定定位 `fixed`，不随文档流滚动
   -  粘性定位 `sticky`，未超过阈值为 `relative`，当超过阈值后，转变为 `fixed`

   > 它们都使用额外的属性 `top` 等四属性描述位置

-  浮动 `float`，值为 `left` 或 `right`，此时内容不再是沿着文档流自上而下排列，而是优先自左向右（或反之）排列，最后不要忘记在容器上加上清除浮动，以免对外部元素造成影响
-  线性渐变
   -  `linear-gradient()`
      -  `background: linear-gradient(方向, 颜色 1, 颜色 2, 颜色 3, ...);`，如 `background: linear-gradient(90deg, red, yellow, rgb(204, 204, 255));`
   -  `repeating-linear-gradient()`
-  变换 `transform`
   -  放缩 `transform: scale(2);` 即可放大两倍
   -  倾斜 `transform: skewX(-32deg)` 即沿 x 轴翻转 -32 度
-  `:before` 和 `:after` 伪类，记得要设置 `content` 属性，即便为空字符串
-  动画（在元素上设置 `animation-name` 等属性，并设定各个关键帧）

   ```css
   #anim {
      animation-name: colorful;
      animation-duration: 3s;
      animation-iteration-count: infinite;
      animation-timing-function: cubic-bezier(0, 0, 0.58, 1);
   }
   @keyframes colorful {
      0% {
         background-color: blue;
      }
      100% {
         background-color: yellow;
      }
   }
   ```

## 响应式设计

### 媒体查询

```css
img {
   width: 100px;
}

@media (min-width: 500px) {
   img {
      width: 300px;
   }
}

@media (min-width: 300px) {
   img {
      width: 200px;
   }
}
```

### 自适应大小

```css
img {
   max-width: 100%;
   display: block;
   height: auto;
}
```

### 使用相对视窗大小单位（`vw` 等）

```css
img {
   width: 80vw;
}
```

## 弹性盒子布局

### 容器属性

想要使用弹性布局很简单，只需要修改 `display` 属性即可

```css
#box-container {
   display: flex;
}
```

当然，我们是将一个容器设为了一个弹性盒子，这样其中的各个元素就能乖乖按照我们的设计来啦

但是布局必然需要方向，这只需要设定 `flex-direction` 即可，比如 `row` 和 `column`，如果想反着来，就加个 `reverse`

```css
#box-container {
   display: flex;
   flex-direction: column-reverse;
}
```

但是各个元素要如何排列？居中还是分开在两端呢？

```css
#box-container {
   display: flex;
   justify-content: center;
}
```

还有其余可选值

-  `flex-start` 都挤在开始那一侧
-  `flex-end` 与上面相反
-  `space-between` 分散排列，中间留空隙，两侧不留
-  `space-around` 两侧也留空隙

另外，与排列方向的垂直方向也没有指定具体的方式

```css
#box-container {
   display: flex;
   align-items: center;
}
```

此外还有

-  `flex-start`
-  `flex-end`
-  `stretch` 充满
-  `baseline` 基线对齐

> 当然每个元素也可以单独设置该属性，属性名为 `align-self`，可选值同上

如果所有元素都挤在一行并不利于响应式变换，如果当屏幕变小时可以自动换行就好了

```css
#box-container {
   display: flex;
   flex-wrap: wrap;
}
```

另外，默认值是 `nowrap` 不换行，此外还可以使用 `wrap-reverse` 反序排列换行

### 子元素属性

至今为止都是设定的容器元素的属性，这样子元素的“个性”还没有彰显，那么子元素有什么特性呢？比如在容器收缩的时候，可以设定两者各自的收缩比，反之在容器拉伸时，可以设定两者各自的生长比，另外还可以设定在伸缩之前的初始大小

```css
#box-container {
   display: flex;
}

#box-1 {
   flex-grow: 2;
   flex-shrink: 2;
   flex-basis: 150px;
}

#box-2 {
   flex-grow: 1;
   flex-shrink: 1;
   flex-basis: 150px;
}
```

还可以将这三个属性简写在一起

```css
#box-container {
   display: flex;
}

#box-1 {
   flex: 2 2 150px;
}

#box-2 {
   flex: 1 1 150px;
}
```

此外，我们还可以通过 `order` 属性自由地调整各个元素的顺序

```css
#box-container {
   display: flex;
}

#box-1 {
   order: 2;
}

#box-2 {
   order: 1;
}
```

## 网格布局

### 容器属性

与弹性盒子布局一样，只需要将容器的 `display` 属性修改即可启用该布局模式

```css
#grid-container {
   display: grid;
}
```

而一个网格，应当明确其行数、列数以及行宽、列宽

```css
#grid-container {
   display: grid;
   grid-template-rows: auto 50px 10% 2fr 1fr;
   grid-template-columns: 50px 50px;
}
```

这将创建 5 行 2 列的网格容器，两列都是 50px，而五行分别占据

-  auto 自动等于其内容的高度
-  50px
-  10% 容器高度
-  剩余高度的 2/3
-  剩余高度的 1/3

此外还可以通过 `minmax` 函数来限制项目的大小

```css
#grid-container {
   display: grid;
   grid-template-columns: 100px minmax(50px, 200px);
}
```

这样第二列的宽度就被限制在 `50px` 和 `200px` 之间了

如果要创建的列数太多，也可以通过 `repeat` 函数来解决

```css
#grid-container {
   display: grid;
   grid-template-columns: repeat(2, 1fr 50px) 20px;
   /* 等同于下面这个 */
   grid-template-columns: 1fr 50px 1fr 50px 20px;
}
```

如果不想明确指定行数或者列数以达到弹性布局的效果，也是可以的

```css
#grid-container {
   display: grid;
   grid-template-columns: repeat(auto-fill, minmax(60px, 1fr));
}
```

但是这样在容器的大小大于各网格项之和时，会在一端持续放入空行或空列，只需稍稍调整就可以解决该问题

```css
#grid-container {
   display: grid;
   grid-template-columns: repeat(auto-fit, minmax(60px, 1fr));
}
```

另外，各个各自之间的间距也应当明确指定

```css
#grid-container {
   display: grid;
   grid-template-rows: repeat(3, 20px);
   grid-template-columns: repeat(3, 20px);
   grid-row-gap: 5px;
   grid-column-gap: 10px;
}
```

当然也可以一起指定

```css
#grid-container {
   display: grid;
   grid-template-rows: repeat(3, 20px);
   grid-template-columns: repeat(3, 20px);
   grid-gap: 5px 10px;
}
```

另外，指定全部元素的对齐方式也很简单

```css
#grid-container {
   display: grid;
   grid-template-rows: repeat(4, 20px);
   grid-template-columns: repeat(4, 20px);
   justify-items: center;
   align-items: center;
}
```

> 当然元素也可以分别指定，使用属性 `justify-self` 和 `align-self`

### 子元素属性

当然，各个元素的个性我们还没有提

如果一个元素比较蛮横，想要占据两个或者更多格子呢？

```css
#grid-container {
   display: grid;
   grid-template-rows: repeat(3, 20px);
   grid-template-columns: repeat(3, 20px);
}

#item5 {
   grid-row: 2 / 4;
   grid-column: 2 / 4;
}
```

这样 item5 就顺利占据了 `(2, 2)-(4, 4)` 这个 2 \* 2 的大格子

此外，我们还可以对格子的各个区域进行命名，然后为各个元素分配自己占据的区域

```css
#grid-container {
   display: grid;
   grid-template-rows: repeat(3, 1fr);
   grid-template-columns: repeat(3, 1fr);
   grid-template-areas:
      "header header header"
      "advert content content"
      "footer footer footer";
}

#item1 {
   grid-area: header;
}
```

这样 item1 就成功占据了上面三个格子

我们还可以利用这个特性结合媒体查询创建响应式布局

```css
#grid-container {
   display: grid;
   grid-template-columns: 1fr;
   grid-template-rows: 50px auto 1fr auto;
   grid-gap: 10px;
   grid-template-areas:
      "header"
      "advert"
      "content"
      "footer";
}

@media (min-width: 300px) {
   #grid-container {
      grid-template-columns: auto 1fr;
      grid-template-rows: auto 1fr auto;
      grid-template-areas:
         "advert header"
         "advert content"
         "advert footer";
   }
}

@media (min-width: 400px) {
   #grid-container {
      grid-template-areas:
         "header header"
         "advert content"
         "footer footer";
   }
}
```

最后，grid 是可以嵌套的哦，一个格子也可以成为一个新的容器～

## Sass 预处理器

Sass 是一个 CSS 的预处理器，我们可以在 Sass 里写更加方便的语法（变量、嵌套以及逻辑语句），而 Sass 会帮助我们将这些语法编译为纯 CSS，以供浏览器渲染

### 变量

变量是各种 CSS 预处理器的核心，Sass 的变量使用 `$` 来标记，定义与使用都远比 CSS 内置的变量方便地多

```scss
$text-color: red;

.blog-post,
h2 {
   color: $text-color;
}
```

### 嵌套

CSS 语法并不支持嵌套结构，这就使得大型项目 CSS 规则需要写很多重复的选择器，Sass 的嵌套语法可以极大简化代码

```css
nav {
   background-color: red;
}

nav ul {
   list-style: none;
}

nav ul li {
   display: inline-block;
}
```

上面的代码用 Sass 来改写只需要

```scss
nav {
   background-color: red;

   ul {
      list-style: none;

      li {
         display: inline-block;
      }
   }
}
```

### Mixins

Mixin 类似于函数

```css
div {
   -webkit-box-shadow: 0px 0px 4px #fff;
   -moz-box-shadow: 0px 0px 4px #fff;
   -ms-box-shadow: 0px 0px 4px #fff;
   box-shadow: 0px 0px 4px #fff;
}
```

上面的代码可以简单得替换为下面的代码，当然如果只使用这一次是看不出来优势的，但如果要反复调用其优势不言而喻

```scss
@mixin box-shadow($x, $y, $blur, $c) {
   -webkit-box-shadow: $x, $y, $blur, $c;
   -moz-box-shadow: $x, $y, $blur, $c;
   -ms-box-shadow: $x, $y, $blur, $c;
   box-shadow: $x, $y, $blur, $c;
}

div {
   @include box-shadow(0px, 0px, 4px, #fff);
}
```

### if / else

简单的示例就可以知道怎么用啦

```scss
@mixin text-effect($val) {
   @if $val == danger {
      color: red;
   } @else if $val == alert {
      color: yellow;
   } @else if $val == success {
      color: green;
   } @else {
      color: black;
   }
}
```

### for 循环

理解起来也很容易，注意在选择器中使用变量的方式

```scss
@for $i from 1 through 12 {
   .col-#{$i} {
      width: 100%/12 * $i;
   }
}
```

除了 `from through` 还有 `from to`，前者包含最后的数字，后者不包含

### each 循环

for 循环的劣势在于只能遍历数字，而 each 循环可以遍历一个列表

```scss
@each $color in blue, red, green {
   .#{$color}-text {
      color: $color;
   }
}
```

也可以将列表单独设为一个变量

```scss
$colors: (
   color1: blue,
   color2: red,
   color3: green,
);

@each $key, $color in $colors {
   .#{$color}-text {
      color: $color;
   }
}
```

### while 循环

while 循环也即如我们熟知的那个 while 循环，如果不注意很容易写成死循环

```scss
$x: 1;
@while $x< 13 {
   .col-#{$x} {
      width: 100%/12 * $x;
   }
   $x: $x + 1;
}
```

### 样式扩展

如果有一个样式与已存在的某个样式基本相同，可以通过 `extend` 来复用已经写好的样式

```scss
.panel {
   background-color: red;
   height: 70px;
   border: 2px solid green;
}

.big-panel {
   @extend .panel;
   width: 150px;
   font-size: 2em;
}
```

## References

1. [freecodecamp 中文社区](https://www.freecodecamp.one/)
