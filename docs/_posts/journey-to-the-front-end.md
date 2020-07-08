---
title: Re：从零开始的前端之旅
date: 2020-07-08
category: 迹
tags:
   - front end
---

::: warning 持续更新……

之前已经无数次尝试前端项目，却从未认真学习前端知识，未免觉得有些遗憾，最近下定决心（但愿）抽空系统地学习下前端的知识，以免和之前一样只能写写简单的 JS 脚本，连个样式都不会添加，顺便再完善完善博客啥的～

> 主线跟随 [freecodecamp](https://www.freecodecamp.one/)

:::

<!-- more -->

## HTML 基础

-  标题 `h1`~`h6` 没什么可说的
-  段落 `p`（paragraph）
-  html5 的语义化元素（`header`、`footer`、`main`、`nav`、`video`、`article`、`section`）
-  图片 `img`
-  锚点 `a`（anchor）
-  无序列表 `ul`（unordered lists）
-  有序列表 `ol`（ordered lists）
-  输入框 `input`
   -  type 字段
      -  文本输入框 `text`
      -  单选按钮 `radio`
      -  复选框 `checkbox`
   -  设置为必填 添加 `required` 属性
   -  设置为默认勾选 添加 `checked` 属性
-  按钮 `button`（`type=submit`）
-  块级嵌套元素 `div`（division）
-  行内嵌套元素 `span`
-  网页基本结构

   ```html
   <!DOCTYPE html>
   <html>
      <head>
         <!-- metadata elements -->
      </head>
      <body>
         <!-- page contents -->
      </body>
   </html>
   ```

emm 还算比较简单啦，主要是了解了这些标签的英文全称都是些啥

## CSS 设计

### CSS 基础

-  选择器
   -  元素选择器 用元素名标记，如 `p`
   -  class 选择器 用 `.<class>` 来标记，如 `.cat`
   -  id 选择器 用 `#<id>` 来标记，如 `#cat`（优先级更高）
   -  属性选择器 用 `[<attr>=‘<value>’]`来标记，如 `[name=‘cat’]`
-  文本
   -  颜色 `color`
      -  名称方式，如 `red`
      -  十六进制，如 `#FF0000`
      -  十六进制缩写，如 `#F00`
      -  rgb(rgba)，如 `rgb(255, 0, 0)` 以及 `rgba(255, 0, 0, 1)`
      -  hsl(hsla)，如 `hsl(0, 100, 50)` 以及 `rgba(0, 100, 50, 1)`
   -  字体 `font-family`
   -  字体大小 `font-size`
-  图片
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
-  边框

   -  基本用法

      ```css
      .thin-red-border {
         border-color: red;
         border-width: 5px;
         border-style: solid;
      }
      ```

   -  加个圆角 `border-radius: 15px`，进一步，设置值为 `50%` 的话，就是个圆咯～

-  盒模型

   -  内容 `content`
   -  内边距 `padding` 也即边框到内容之间填充的距离
   -  边框 `border`
   -  外边距 `margin` 也即边框到相邻元素或者父容器之间的距离，还可以设置为负值以达到灵活的定位效果～

   ***

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

-  样式优先级
   -  important 声明
   -  内联样式
   -  ID 选择器
   -  Class 选择器
   -  继承样式
-  变量

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

### 应用视觉设计

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

-  浮动 `float`，值为 `left` 或 `right`，此时内容不再是沿着文档流自上而下排列，而是优先自左向右（或反之）排列
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

### 响应式设计

-  媒体查询

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

-  自适应大小

   ```css
   img {
      max-width: 100%;
      display: block;
      height: auto;
   }
   ```

-  使用相对视窗大小单位（`vw` 等）

   ```css
   img {
      width: 80vw;
   }
   ```

### 弹性盒子布局

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

---

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

### 网格布局

# References

1. [freecodecamp 中文社区](https://www.freecodecamp.one/)
