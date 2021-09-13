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
  data() {
    return {};
  },
});
</script>

<style lang="less" scoped>
@sidebar-color: #FFA500;

@hover-color: #754C00;

.sidebar {
  display: flex;
  flex-direction: column;

  width: 10vh;
  height: 100vh;
  background: @sidebar-color;
  overflow: hidden;
  border-right: 5px solid #FFC55C;

  .top-nav {
    display: flex;
    flex-direction: column;
    align-content: space-between;
    align-items: center;

    a {
      margin-top: 20px;
      margin-bottom: 20px;
      width: 100%;
    }

    a:hover {
      background: @hover-color;
    }

    .isSelected {
      background: @hover-color;
      &:hover {
        background: @hover-color;
      }
    }
  }

  .bottom-nav {
    display: flex;
    flex-direction: column;
    align-content: space-between;
    align-items: center;
    margin-top: auto;
    margin-bottom: 10px;

    a {
      margin-top: 20px;
      margin-bottom: 20px;
      width: 100%;
    }

    a:hover {
      background: @hover-color;
    }

    .isSelected {
      background: @hover-color;
      &:hover {
        background: @hover-color;
      }
    }
  }
}

.icon {
  width: 40px;
  height: 40px;
}
</style>