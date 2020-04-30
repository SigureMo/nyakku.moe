<template>
  <APlayer mutex fixed :audio="audio" :lrcType="3" />
</template>

<script>
export default {
  name: "Meting",
  data() {
    return {
      meta: {
        metingApi: METING_API,
        auto: METING_AUTO,
        server: METING_SERVER,
        type: METING_TYPE,
        id: METING_ID,
      },
      ...APLAYER_OPTIONS,
    };
  },

  mounted() {
    if (this.meta.auto) this._parse_link();

    const params = {
      server: this.meta.server,
      type: this.meta.type,
      id: this.meta.id,
      r: Math.random(),
    };

    let url = this.meta.metingApi;
    let paramsArray = [];
    Object.keys(params).forEach((key) =>
      paramsArray.push(key + "=" + params[key])
    );
    url += "?" + paramsArray.join("&");

    fetch(url, {
      headers: {
        referer: null,
      },
    })
      .then((res) => res.json())
      .then((result) => (this.audio = result));
  },

  methods: {
    _parse_link() {
      let rules = [
        ["music.163.com.*song.*id=(\\d+)", "netease", "song"],
        ["music.163.com.*album.*id=(\\d+)", "netease", "album"],
        ["music.163.com.*artist.*id=(\\d+)", "netease", "artist"],
        ["music.163.com.*playlist.*id=(\\d+)", "netease", "playlist"],
        ["music.163.com.*discover/toplist.*id=(\\d+)", "netease", "playlist"],
        ["y.qq.com.*song/(\\w+).html", "tencent", "song"],
        ["y.qq.com.*album/(\\w+).html", "tencent", "album"],
        ["y.qq.com.*singer/(\\w+).html", "tencent", "artist"],
        ["y.qq.com.*playsquare/(\\w+).html", "tencent", "playlist"],
        ["y.qq.com.*playlist/(\\w+).html", "tencent", "playlist"],
        ["xiami.com.*song/(\\w+)", "xiami", "song"],
        ["xiami.com.*album/(\\w+)", "xiami", "album"],
        ["xiami.com.*artist/(\\w+)", "xiami", "artist"],
        ["xiami.com.*collect/(\\w+)", "xiami", "playlist"],
      ];

      for (let rule of rules) {
        let patt = new RegExp(rule[0]);
        let res = patt.exec(this.meta.auto);
        if (res !== null) {
          this.meta.server = rule[1];
          this.meta.type = rule[2];
          this.meta.id = res[1];
          return;
        }
      }
    },
  },
};
</script>
