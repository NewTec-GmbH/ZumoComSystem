<template>
  <div class="sidebar">
    <nav class="top-nav">
      <router-link to="/" class="Home">
        <img class="icon" src="@/assets/icons/white/home.svg" />
      </router-link>

      <router-link to="/upload" class="Upload">
        <img class="icon" src="@/assets/icons/white//upload.svg" />
      </router-link>

      <router-link to="/flash" class="Flash">
        <img class="icon" src="@/assets/icons/white/flash.svg" />
      </router-link>

      <router-link to="/debug" class="Debug">
        <img class="icon" src="@/assets/icons/white/debug.svg" />
      </router-link>
    </nav>

    <nav class="bottom-nav">
      <router-link to="/reset" class="Reset">
        <img class="icon" src="@/assets/icons/white/reset.svg" />
      </router-link>

      <router-link to="/settings" class="Settings">
        <img class="icon" src="@/assets/icons/white/settings.svg" />
      </router-link>
    </nav>
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";
export default defineComponent({
  name: "Sidebar",
});
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.sidebar {
  width: 10vh;

  display: flex;
  flex-direction: column;

  background: @ui_background_color;
  border-right: 5px solid @ui_border_color;

  .top-nav {
    display: flex;
    flex-direction: column;
    align-items: center;

    a {
      margin-top: 20px;
      margin-bottom: 20px;
      width: 100%;
    }

    a:hover {
      background: @ui_hover_color;
    }

    .isSelected {
      background: @ui_hover_color;
      &:hover {
        background: @ui_hover_color;
      }
    }
  }

  .bottom-nav {
    display: flex;
    flex-direction: column;

    align-items: center;

    margin-top: auto;
    margin-bottom: 10px;

    a {
      margin-top: 20px;
      margin-bottom: 20px;
      width: 100%;
    }

    a:hover {
      background: @ui_hover_color;
    }

    .isSelected {
      background: @ui_hover_color;
      &:hover {
        background: @ui_hover_color;
      }
    }
  }
}

.icon {
  width: @icon_height_width;
  height: @icon_height_width;
}
</style>
