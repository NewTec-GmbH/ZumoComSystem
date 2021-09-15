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
import { ApiResponse } from "@/models/ApiResponse";
import { ResponseCode } from "@/models/ResponseCode";
import RequestResponseHandler from "@/api/RequestResponseHandler";
import Log from "@/utility/Log";
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
            if (
              true === RequestResponseHandler.getInstance().makeRequest(request)
            ) {
              /* Register the event handler for incoming response message */
              RequestResponseHandler.getInstance().onResponse((event: any) => {
                /* Parse the response data */
                const response: ApiResponse = JSON.parse(event.data);

                if (response.statusCode == ResponseCode.UNAUTHORIZED) {
                  this.$toast.add({
                    severity: "warn",
                    summary: "Missing Permission",
                    detail:
                      "You do not have the required permission to reboot the Zumo32U4 Robot!",
                    life: 3000,
                  });

                  if ("null" == this.$store.getters.currentUser) {
                    this.$store.commit("setLoginDialogVisibility", true);
                  }

                  Log.warn("Missing permission for rebooting Zumo32U4 robot");
                } else if (response.statusCode == ResponseCode.SUCCESS) {
                  this.$toast.add({
                    severity: "success",
                    summary: "Rebooted",
                    detail: "Successfully rebooted Zumo32U4 Robot!",
                    life: 3000,
                  });

                  Log.debug("Successfully rebooted Zumo32U4 Robot!");
                } else {
                  this.$toast.add({
                    severity: "error",
                    summary: "Error Rebooting",
                    detail: "Could not reboot Zumo32U4 Robot!",
                    life: 3000,
                  });

                  Log.error("Could not reboot Zumo32U4 Robot!");
                }
              });
            } else {
              this.$toast.add({
                severity: "error",
                summary: "Fatal Server Error",
                detail:
                  "A fatal error occured when communicating with the server!",
                life: 3000,
              });

              Log.error("Fatal server error occured!");
            }
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
            if (
              true === RequestResponseHandler.getInstance().makeRequest(request)
            ) {
              /* Register the event handler for incoming response message */
              RequestResponseHandler.getInstance().onResponse((event: any) => {
                /* Parse the response data */
                const response: ApiResponse = JSON.parse(event.data);

                if (response.statusCode == ResponseCode.UNAUTHORIZED) {
                  this.$toast.add({
                    severity: "warn",
                    summary: "Missing Permission",
                    detail:
                      "You do not have the required permission to reboot the ComPlatform!",
                    life: 3000,
                  });

                  if ("null" == this.$store.getters.currentUser) {
                    this.$store.commit("setLoginDialogVisibility", true);
                  }

                  Log.warn("Missing permission for rebooting ComPlatform");
                } else if (response.statusCode == ResponseCode.SUCCESS) {
                  this.$toast.add({
                    severity: "success",
                    summary: "Rebooted",
                    detail:
                      "ComPlatform successfully rebooted! Reloading this page in two seconds!",
                    life: 3000,
                  });

                  /* Reload the page afer two seconds to reconnect */
                  setTimeout(() => {
                    this.$router.go(0);
                  }, 2000);

                  Log.debug("Successfully rebooted ComPlatform");
                } else {
                  this.$toast.add({
                    severity: "error",
                    summary: "Error Rebooting",
                    detail: "Could not reboot ComPlatform!",
                    life: 3000,
                  });

                  Log.debug("Could not reboot ComPlatform!");
                }
              });
            } else {
              this.$toast.add({
                severity: "error",
                summary: "Fatal Server Error",
                detail:
                  "A fatal error occured when communicating with the server!",
                life: 3000,
              });

              Log.error("Fatal server error occured!");
            }
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
