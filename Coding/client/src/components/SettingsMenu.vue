<template>
  <div class="settings-menu">
    <div
      v-if="$store.getters.selectedDevice.name === 'ComPlatform'"
      class="com-settings"
    >
      <div
        class="menu-entry"
        @click="$emit('entry-click', $event, 'connectivity-com')"
      >
        <img class="entry-icon" src="@/assets/icons/black/wifi.svg" />
        <h1 class="entry-text">Connectivity</h1>
      </div>
    </div>

    <div
      v-else-if="$store.getters.selectedDevice.name === 'Zumo32U4 Robot'"
      class="zumo-settings"
    >
      <div class="info-pane">
        <img src="@/assets/icons/black/info.svg" class="info-image" />
        <h1 class="info-text">No Settings available</h1>
      </div>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";

export default defineComponent({
  name: "SettingsMenu",
  data() {
    return {};
  },
  methods: {},
});
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.settings-menu {
  display: flex;
  flex-direction: column;

  .zumo-settings {
    margin-top: auto;
    margin-bottom: auto;

    .info-image {
      width: 80px;
      height: 80px;
    }
  }

  .menu-entry {
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: flex-start;

    cursor: pointer;
    border-bottom: solid @menu_border_color;

    .entry-icon {
      width: 30px;
      height: 30px;

      margin-left: 20px;
    }

    .entry-text {
      font-family: @text_font;
      margin-left: 20px;
    }
  }

  .menu-entry:hover {
    background: @ui_hover_color;
  }

  .settings-view {
    width: 100%;
  }
}
</style>
