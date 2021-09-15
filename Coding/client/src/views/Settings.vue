<template>
  <div class="settings">
    <SettingsMenu class="settings-menu" @entry-click="entryClick" />

    <div
      v-if="selectedMenuEntry === 'connectivity-com' && hideView === false"
      class="settings-view"
    >
      <ConnectivityCOM />
    </div>

    <div v-else class="settings-view">
      <div class="info-pane">
        <img src="@/assets/icons/black/info.svg" class="info-image" />
        <h1 class="info-text">No menu entry selected</h1>
      </div>
    </div>
  </div>
</template>

<script lang="ts">
import { Options, Vue } from "vue-class-component";
import SettingsMenu from "@/components/SettingsMenu.vue";
import ConnectivityCOM from "@/views/COMSettings/ConnectivityCOM.vue";
import { defineComponent } from "vue";
import LoginDialog from "@/components/LoginDialog.vue";
import Menu from "primevue/menu";
import { ApiRequest } from "@/models/ApiRequest";
import { ApiResponse } from "@/models/ApiResponse";
import { ResponseCode } from "@/models/ResponseCode";
import RequestResponseHandler from "@/api/RequestResponseHandler";
import Log from "@/utility/Log";

export default defineComponent({
  name: "Settings",

  data() {
    return {
      selectedMenuEntry: "null",
      hideView: false,
    };
  },

  components: {
    SettingsMenu,
    ConnectivityCOM,
  },

  methods: {
    entryClick(event: any, item: string) {
      this.hideView = false;
      this.selectedMenuEntry = item;
    },
  },

  watch: {
    "$store.state.seletedDevice.name": function (newValue, oldValue) {
      this.hideView = newValue != oldValue;
    },
  },
});
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.settings {
  display: flex;
  flex-direction: row;

  .settings-menu {
    width: 350px;

    border-right: solid 5px @ui_border_color;
    background: @view_background_color;
  }

  .settings-view {
    width: 100%;

    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;

    .info-image {
      width: 80px;
      height: 80px;
    }
  }
}
</style>
