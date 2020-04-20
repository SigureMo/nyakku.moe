---
title: About me
sidebar: false
layout: AboutLayout
---

SigureMo（<ruby> 時 <rp>(</rp><rt>し</rt><rp>)</rp> 雨 <rp>(</rp><rt>ぐれ</rt><rp>)</rp> Mo </ruby>），小辣鸡一枚，本科材料喵，拟跨考 CS ε≡٩(๑>₃<)۶ ~

::: tip Status

Focus on CV & DL

:::

已成功入坑 {{ dist_times }} ~

## 会点啥？

-  前端啥也不会
-  后端啥也不懂
-  入门时候学了点爬虫
-  最近学了点 DeepLearning 也不太会用

## 没事都干嘛？

-  使用 Python 做做爬虫相关以及小的 DL 项目
-  有时使用 C++ 刷题
-  还有时也用 JS 以及 Vue 完善博客
-  没事在 GitHub 仰望各位 dalao
-  还能干嘛？

## 做过些啥？

-  [Bilili](https://github.com/SigureMo/bilili) B 站视频、弹幕下载工具
-  [mooc-dl](https://github.com/SigureMo/mooc-dl) 中国大学 MOOC 全课件下载器
-  [Shoeprint Recognition](https://cattidea.github.io/shoeprint-recognition/) “恒锐杯”鞋印花纹图像类别判定挑战赛
-  [VuePress Lovely Plugins](https://www.sigure.xyz/vuepress-lovely-plugins/) 一些 VuePress 小插件

## 还想说点啥？

本仓库全部代码使用 [MIT](https://github.com/SigureMo/notev/blob/master/LICENSE) 协议进行开源，但是本仓库全部文档内容使用 [CC 4.0 BY-SA](https://creativecommons.org/licenses/by-sa/4.0/) 协议进行发布

<script>
export default {
   props: ['slot-key'],
   data() {
      return {
         dist_times: "xx days xx h xx m xx s"
      };
   },
   methods: {
      refresh() {
         let start_date = '2018-02-06 00:15:00.0';
         start_date = start_date.substring(0,19);
         start_date = start_date.replace(/-/g,'/');
         let start_timestamp = new Date(start_date).getTime();
         let now_timestamp = new Date();

         let dist_timestamp = now_timestamp - start_timestamp;
         let dist_days = Math.floor(dist_timestamp / (24*3600*1000));
         let dist_hours = Math.floor((dist_timestamp % (24*3600*1000)) / (3600*1000));
         let dist_mins = Math.floor((dist_timestamp % (3600*1000)) / (60*1000));
         let dist_secs = Math.floor((dist_timestamp % (60*1000)) / 1000);
         this.dist_times = `${dist_days} days ${dist_hours} h ${dist_mins} m ${dist_secs} s`;
      }
   },
   mounted () {
      this.refresh();
      setInterval(this.refresh, 1000);
   }
}
</script>
