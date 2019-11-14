---
title: About me
sidebar: false
publish: false
---

<p align="center"><img :src="$withBase('/sigure_mo.png')" alt="SigureMo" height=200 width=200></p>
<p align="center">
  <a href="https://github.com/SigureMo" class="zi zi_tmGithub"></a>
  <a href="mailto:sigure_mo@163.com" class="zi zi_envelope"></a>
  <a href="tencent://AddContact/?fromId=45&fromSubId=1&subcmd=all&uin=240377379&website=www.oicqzone.com" class="zi zi_tmQq"></a>
</p>

Sigure_Mo，小辣鸡一枚，本科材料喵，拟跨考 CS ε≡٩(๑>₃<)۶ ~

已成功入坑 {{ dist_times }} ~

## 会点啥？

-  前端啥也不会
-  后端啥也不懂
-  入门时候学了点爬虫
-  最近学了点 DeepLearning 也不太会用

## 没事都干嘛？

-  使用 Python 做做爬虫相关以及小的 DL 项目
-  最近在用 C++ 刷题
-  有时候也用 JS 以及 Vue 完善博客
-  没事在 GitHub 仰望各位 dalao
-  还能干嘛？

## 做过些啥？

-  [Course Crawler](https://www.sigure.xyz/course-crawler/) 慕课课程下载工具，Fork 于 Foair
-  [Shoeprint Recognition](https://www.sigure.xyz/shoeprint-recognition/) “恒锐杯”鞋印花纹图像类别判定挑战赛
-  [vuepress-reco](https://github.com/vuepress-reco) vuepress 主题 reco 及插件相关开发

## 还想说点啥？

本仓库全部代码使用 [MIT](https://github.com/SigureMo/notev/blob/master/LICENSE) 协议进行开源，但是本仓库全部文档内容使用 [CC 4.0 BY-SA](https://creativecommons.org/licenses/by-sa/4.0/) 协议进行发布

## 有啥愿望吗？

-  想学的有好多啊，想有空玩玩前端，还想把 ML 系统学一下，还想学一下编译原理，还想……（想 peach 去吧）
-  新的 N 年后能拥有属于自己的 MacBook
-  新的一年能早一分钟睡（反正别越睡越晚就行啦 :joy:）

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

<link rel="stylesheet" href="https://ico.z01.com/zico.min.css">
