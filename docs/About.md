# About me

<p align="center"><a href="https://github.com/SigureMo" target="_blank" rel="noopener noreferrer"><img :src="$withBase('/sigure_mo.png')" alt="SigureMo" height=200 width=200></a></p>
<p align="center">
  <a href="https://github.com/SigureMo" class="zi zi_tmGithub"></a>
  <a href="mailto:sigure_mo@163.com" class="zi zi_envelope"></a>
  <a href="tencent://AddContact/?fromId=45&fromSubId=1&subcmd=all&uin=240377379&website=www.oicqzone.com" class="zi zi_tmQq"></a>
</p>

Sigure_Mo，大三材料喵，跨考 CS 准备中 ε≡٩(๑>₃<)۶ ~

已成功入坑 {{ dist_times }} ~

-  主要方向
   -  DeepLearning
   -  网络爬虫
-  主要语言
   -  Python
   -  C++

## Status

-  偶尔写写 <i class="zi zi_tmPython"></i> 小脚本 ~
-  偶尔学学 DL ~
-  偶尔刷刷 PAT ~
-  偶尔卖卖 萌 :joy: ~
-  一直在学习 ……（手动滑稽）

## Comments

<Valine></Valine>

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
      setInterval(this.refresh, 1000);
   }
}
</script>

<link rel="stylesheet" href="https://ico.z01.com/zico.min.css">
