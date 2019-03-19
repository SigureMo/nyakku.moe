<template>
  <div>
    <textarea v-model="input"></textarea>
    <div v-html="compiledMarkdown"></div>
  </div>
</template>

<script>
const config = require("../config.js");
const md = require("markdown-it")()
  .use(require("markdown-it-emoji"))
  .use(require("markdown-it-anchor"));
config.markdown.extendMarkdown(md);

export default {
  data() {
    return {
      input: "## Try it!"
    };
  },
  computed: {
    compiledMarkdown: function() {
      return md.render("\n\n---\n---\n\n" + this.input + "\n\n---\n---\n\n");
    }
  }
};
</script>

<style>
html,
body,
#editor {
  margin: 0;
  height: 100%;
  font-family: "Helvetica Neue", Arial, sans-serif;
  color: #333;
}

textarea,
#editor div {
  display: inline-block;
  width: 49%;
  height: 100%;
  vertical-align: top;
  box-sizing: border-box;
  padding: 0 20px;
}

textarea {
  border: none;
  border-right: 1px solid #ccc;
  resize: none;
  outline: none;
  background-color: #f6f6f6;
  font-size: 14px;
  font-family: "Monaco", courier, monospace;
  padding: 20px;
}

code {
  color: #f66;
}
</style>
