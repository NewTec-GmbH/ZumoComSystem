<template>
  <div class="sidebar">
    <Menu
      v-if="$store.getters.selectedDevice.name === 'Zumo32U4 Robot'"
      ref="menu"
      :model="zumoMenu"
      :popup="true"
    />
    <Menu
      v-else-if="$store.getters.selectedDevice.name === 'ComPlatform'"
      ref="menu"
      :model="comMenu"
      :popup="true"
    />

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
      <img
        class="icon"
        src="@/assets/icons/white/reset.svg"
        @click="resetClick"
      />

      <router-link to="/settings" class="Settings">
        <img class="icon" src="@/assets/icons/white/settings.svg" />
      </router-link>
    </nav>
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import { ApiRequest } from "@/models/ApiRequest";
import RequestResponseHandler from "@/api/RequestResponseHandler";
import Menu from "primevue/menu";

export default defineComponent({
  name: "Sidebar",
  data() {
    return {
      zumoMenu: [
        {
          label: "Reboot Zumo32U4 Robot",
          icon: "pi pi-power-off",
          command: () => {
            /* Prepare the API command */
            let request = new ApiRequest();
            request.commandId = "rebootzumo";

            /* Send the request */
            RequestResponseHandler.getInstance().makeRequest(request, this);
          },
        },
      ],
      comMenu: [
        {
          label: "Reboot ComPlatform",
          icon: "pi pi-power-off",
          command: () => {
            /* Prepare the API command */
            let request = new ApiRequest();
            request.commandId = "rebootcom";

            /* Send the request */
            RequestResponseHandler.getInstance().makeRequest(request, this);
          },
        },
      ],
    };
  },
  methods: {
    resetClick(event: any) {
      (this.$refs.menu as Menu).toggle(event);
    },
  },
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
  }

  .bottom-nav {
    display: flex;
    flex-direction: column;

    align-items: center;

    margin-top: auto;
    margin-bottom: 40px;
  }

  a {
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

.icon {
  width: @icon_height_width;
  height: @icon_height_width;

  margin-top: 20px;
  margin-bottom: 20px;

  width: 100%;
}

.icon:hover {
  background: @ui_hover_color;
  cursor: pointer;
}
</style>
