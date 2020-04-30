import APlayer from "@moefe/vue-aplayer";
import Meting from "./Meting.vue";

export default ({ Vue }) => {
  Vue.use(APlayer, {
    defaultCover: "https://github.com/u3u.png",
    productionTip: true,
  });
  Vue.component("Meting", Meting);
};
