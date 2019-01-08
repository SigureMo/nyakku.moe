<template>
  <div id="vcomments"></div>
</template>

<script>
export default {
  // https://valine.js.org/
  name: "Valine",
  mounted: function() {
    // require window
    const Valine = require("valine");
    if (typeof window !== "undefined") {
      this.window = window;
      window.AV = require("leancloud-storage");
    }

    new Valine({
      el: "#vcomments",
      appId: "E0ei2XbovnHMSlL4tQM2mVDo-gzGzoHsz",
      appKey: "zSYs7qvWjLlEvF9tMcVMUUUr",
      notify: false,
      verify: false,
      avatar: "mm",
      placeholder: "(*/ω＼*)"
    });
  }
};
</script>
