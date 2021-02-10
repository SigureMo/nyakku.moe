<template>
  <div class="custom-layout">
    <div class="main-div">
      <!-- <Content /> is to show the rendered markdown content of this page -->
      <Content class="content" />
    </div>
    <div v-if="vssue" id="post-comments" class="main-div">
      <Vssue :title="vssueTitle" :issue-id="vssueId" />
    </div>
  </div>
</template>

<script>
export default {
  name: 'AboutLayout',
  computed: {
    vssue() {
      return (
        this.$themeConfig.comments !== false &&
        this.$frontmatter.vssue !== false &&
        (this.vssueTitle || this.vssueId)
      )
    },

    vssueTitle() {
      return this.$frontmatter['vssue-title'] || this.$frontmatter.title || undefined
    },

    vssueId() {
      return this.$frontmatter['vssue-id'] || undefined
    },
  },
}
</script>
