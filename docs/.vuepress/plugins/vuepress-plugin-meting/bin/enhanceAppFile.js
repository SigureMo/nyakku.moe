import Meting from "./Meting.vue";

export default ({ Vue }) => {
  if (typeof window !== "undefined") {
    localStorage.setItem("aplayer-setting", "[]");
    Vue.use(require("@moefe/vue-aplayer").default);
  }
  Vue.component("Meting", Meting);
};
