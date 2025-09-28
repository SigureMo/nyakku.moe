<!-- ref: https://diygod.me/friends/ -->
<template>
  <div class="friend-link">
    <a :href="url" :title="name" target="_blank">
      <img :src="avatar" :alt="name" />
      <p class="friend-name">{{ name }}</p>
      <p class="friend-description">{{ desc }}</p>
    </a>
  </div>
</template>

<script>
export default {
  name: 'FriendLink',
  props: ['name', 'url', 'desc', 'avatar'],
}
</script>

<style lang="stylus" scoped>
div.friend-link {
  width: 50%;
  float: left;
  position: relative;
  padding-left: 100px;
}

@media (max-width: $MQMobile) {
  div.friend-link {
    width: 100%;
  }
}

div.friend-link:hover {
  border-radius: 10px;
  background-color: #c9f2e9;
}

img {
  position: absolute;
  top: 5px;
  left: 5px;
  width: 80px;
  height: 80px;
  border-radius: 50%;
}

p {
  overflow: hidden;
  text-overflow: ellipsis;
  white-space: nowrap;
}

p.friend-name {
  padding-top: 20px;
  font-size: 16px;
  font-weight: bold;
  color: black;
  margin: 0;
}

p.friend-description {
  padding: 15px 0;
  margin: 0;
  line-height: 24px;
  color: gray;
}
</style>
