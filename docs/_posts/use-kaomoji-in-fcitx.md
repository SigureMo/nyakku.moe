---
title: 在 fcitx 中使用颜文字
date: 2020-04-21
category: 迹
tags:
   - Linux
---

::: tip

在 Linux 下的 fcitx 输入法虽然简陋了点，但好在扩展性更高，很多内容都支持自定义，比如说颜文字等等

:::

<!-- more -->

## 使用 QuickPhrase

fcitx 包含了 [QuickPhrase](https://fcitx-im.org/wiki/QuickPhrase) 这个附加组件，它支持预定义一些映射以进行快速输入，是配置颜文字的不二选择

配置起来很简单，新建 `~/.config/fcitx/data/QuickPhrase.mb` 文件，并在其中添加一些映射就好啦，下面是我喜欢的颜文字，可以直接将这些内容粘贴过去

```
kaixin φ(≧ω≦*)♪
jing Σ<(=っ°Д °)っ
haoye ヽ(✿ﾟ▽ﾟ)ノ
maozhua (ฅ>ω<*ฅ)
wulian (*/ω＼*)
miaowu ○ω●
kun (´-ωก`)
huang ( ๑ˊ•̥▵•)੭₎₎
jidong ː̗̀(o›ᴗ‹o)ː̖́
bixinxin (●'◡'●)ﾉ❤
jiayou up!(˘•ω•˘)ง
miao ⌯'ㅅ'⌯
heng <( ‵□′)>
shengqi ヾ(｡｀Д´｡)ﾉ
lengzhu (°ー°〃),
sha (๑•̌.•̑๑)ˀ̣ˀ̣
kaixinxin ♪⸜(๑ ॑꒳ ॑๑)⸝♪✰
zhuazhua ฅ ฅ
haixiu ⁄(⁄ ⁄ ⁄ω⁄ ⁄ ⁄)⁄
aini (୨୧•͈ᴗ•͈)◞︎ᶫᵒᵛᵉ   ♡
momotou ( ´･ω･)ﾉ(._.`)
xieyan ( ´◔ ‸◔`)
zhayan (●• ̀ω•́ )✧
zaima ( ๑ˊ•̥▵•)੭₎₎
xixi (⋈◍＞◡＜◍)
wuyu (⇀‸↼‶)
rouyanjing ( ‘-ωก̀ )
xianzhuozi （╯‵□′）╯︵┴─┴
heng (╬ Ò ‸ Ó)
heng s(・｀ヘ´・;)ゞ
huanhu ヾ(❀^ω^)ﾉﾞ
geinixinxin (｡･ω･｡)ﾉ♡
miao (=・ω・=)
xinxin ٩(๛ ˘ ³˘)۶❤
mengmeng (｡･ω･｡)
heng (๑‾᷅^‾᷅๑)
kira (・ω< )★
xixi (๑>؂<๑）
sahuahua ✿ヽ(°▽°)ノ✿
hehe （⌒▽⌒）
meng (｀・ω・´)
meng (^・ω・^ )
meng (｡･ω･｡)
haixiu ✧(≖ ◡ ≖✿)
bukaixin (´･_･`)
momotou ( ´･･)ﾉ(._.`)
bukaixin ( •̥́ ˍ •̀ू )
haixiu  ⁄(⁄ ⁄•⁄ω⁄•⁄ ⁄)⁄
geinixinxin (´ ｡•ω•｡)っ⌒♡
kaixin (๑˃◡˂๑)
anzhongguancha |･ω･｀)
xinxin |˛˙꒳​˙)♡
```

修改后重启输入法即可，之后只需要先按下 `;` 键（可在 `fcitx 配置 -> 附加组件` 修改）就能激活 QuickPhrase 模式，再按下映射的提示词就能看到对应的颜文字啦

此外，QuickPhrase 也是支持 emoji 的，只不过它只支持 shortcode 的输入方式，比如 `:joy:` 对应 :joy:，也就是说即便是在 QuickPhrase 模式下也还是需要先输入 `:` 才能生效，如果你不习惯的话可以用一下 [levinit/fcitx-emoji](https://github.com/levinit/fcitx-emoji)

## References

1. [猫颜文字 For Fcitx QuickPhrase](https://felixc.at/2012/05/kitty-for-fcitx-quickphrase/)
