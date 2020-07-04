<template>
  <div class="custom-layout">
    <div class="main-div friend-links">
      <FriendLink
        v-for="friend in friends"
        :name="friend.name"
        :url="friend.url"
        :description="friend.description"
        :avatar="friend.avatar"
      />
    </div>
    <div class="main-div">
      <Content class="content" />
    </div>
    <div v-if="vssue" id="post-comments" class="main-div">
      <Vssue :title="vssueTitle" :issue-id="vssueId" />
    </div>
  </div>
</template>

<script>
export default {
  name: "FriendsLayout",
  computed: {
    friends() {
      console.log(this.shuffle(this.$themeConfig.friends));
      return this.shuffle(this.$themeConfig.friends);
    },

    vssue() {
      return (
        this.$themeConfig.comments !== false &&
        this.$frontmatter.vssue !== false &&
        (this.vssueTitle || this.vssueId)
      );
    },

    vssueTitle() {
      return (
        this.$frontmatter["vssue-title"] || this.$frontmatter.title || undefined
      );
    },

    vssueId() {
      return this.$frontmatter["vssue-id"] || undefined;
    },
  },

  methods: {
    shuffle(arr) {
      for (let i = arr.length - 1; i > 0; i--) {
        const r = Math.floor(Math.random() * i);
        [arr[i], arr[r]] = [arr[r], arr[i]];
      }
      return arr;
    },
  },
};
</script>

<style scoped>
div.friend-links {
  overflow: auto;
}
</style>
