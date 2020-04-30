const { resolve } = require("path");

module.exports = (options = {}, context) => ({
  define() {
    const {
      metingApi = "https://api.i-meto.com/meting/api",
      auto = "",
      server,
      type,
      id,
      ...aplayerOptions
    } = options;

    aplayerOptions.audio = aplayerOptions.audio || [];

    return {
      METING_API: metingApi,
      METING_AUTO: auto,
      METING_SERVER: server,
      METING_TYPE: type,
      METING_ID: id,
      APLAYER_OPTIONS: aplayerOptions,
    };
  },

  enhanceAppFiles: resolve(__dirname, "./bin/enhanceAppFile.js"),
  globalUIComponents: "Meting",
});
