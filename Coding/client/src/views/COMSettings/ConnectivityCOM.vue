<template>
  <TextDialog
    :type="type"
    :showTextDialog="confirmDialogVisible"
    :text="infoText"
    @declined="declineClick"
    @accepted="acceptClick"
  />

  <div class="connectivity-settings-container">
    <Card class="settings-card">
      <template #title>STA-Mode Network Credentials</template>
      <template #header>
        <img class="card-icon" src="@/assets/icons/black/lock.svg" />
      </template>
      <template #content>
        <div>
          <Checkbox id="sta-checkbox" v-model="useSTAMode" :binary="true" />
          <label for="sta-checkbox">Use STA-Mode</label>
        </div>
        <div class="card-content-container">
          <span
            v-if="useSTAMode === true"
            class="p-float-label p-input-icon-left"
          >
            <i class="pi pi-wifi"></i>
            <InputText id="ssid" type="text" v-model="credentials.ssid" />
            <label for="ssid">SSID</label>
          </span>

          <span
            v-if="useSTAMode === true"
            class="p-float-label p-input-icon-left"
          >
            <i class="pi pi-key"></i>
            <InputText
              id="passphrase"
              type="password"
              v-model="credentials.passphrase"
            />
            <label for="passphrase">Passphrase</label>
          </span>

          <Button
            label="Save"
            icon="pi pi-save"
            iconPos="right"
            class="p-button-rounded"
            @click="save()"
          />
        </div>
      </template>
    </Card>
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import { NetworkCredentials } from "@/models/NetworkCredentials";
import { ApiRequest } from "@/models/ApiRequest";
import { ApiResponse } from "@/models/ApiResponse";
import { ResponseCode } from "@/models/ResponseCode";
import RequestResponseHandler from "@/api/RequestResponseHandler";
import Log from "@/utility/Log";
import TextDialog from "@/components/TextDialog.vue";

export default defineComponent({
  name: "ConnectivityCOM",
  data() {
    return {
      credentials: new NetworkCredentials(),
      useSTAMode: true,

      type: "no-yes",
      confirmDialogVisible: false,
      infoText:
        "In order for the changes to take effect, the ComPlatform needs to be rebooted. Do you want to reboot the ComPlatform now?",
    };
  },

  components: {
    TextDialog,
  },

  methods: {
    save() {
      /* Prepare the API command */
      let request = new ApiRequest();
      request.commandId = "setstacredentials";

      /* Send no credentials to force ComPlatform to delete network credentials and boot in AP-Mode */
      if (true === this.useSTAMode) {
        request.jsonPayload = JSON.stringify(this.credentials);
      }

      /* Send the request */
      if (true === RequestResponseHandler.getInstance().makeRequest(request)) {
        /* Register the event handler for incoming response message */
        RequestResponseHandler.getInstance().onResponse((event: any) => {
          /* Parse the response data */
          const response: ApiResponse = JSON.parse(event.data);

          if (response.statusCode == ResponseCode.UNAUTHORIZED) {
            this.$toast.add({
              severity: "warn",
              summary: "Missing Permission",
              detail:
                "You do not have the required permission to set the STA-Mode Network Credentials!",
              life: 3000,
            });

            if ("null" == this.$store.getters.currentUser) {
              this.$store.commit("setLoginDialogVisibility", true);
            }

            Log.warn(
              "Missing permission for setting the STA network credentials"
            );
          } else if (response.statusCode == ResponseCode.SUCCESS) {
            this.$toast.add({
              severity: "success",
              summary: "Network Credentials set",
              detail: "Successfully set the Network Credentials for STA-Mode!",
              life: 3000,
            });

            this.confirmDialogVisible = true;
          } else {
            this.$toast.add({
              severity: "error",
              summary: "Error setting Network Credentials",
              detail: "Could not set the Network Credentials for STA-Mode!",
              life: 3000,
            });

            Log.error("Could not set STA-Mode Network Credentials!");
          }
        });
      } else {
        this.$toast.add({
          severity: "error",
          summary: "Fatal Server Error",
          detail: "A fatal error occured when communicating with the server!",
          life: 3000,
        });

        Log.error("Fatal server error occured!");
      }
    },

    declineClick() {
      this.confirmDialogVisible = false;
    },

    acceptClick() {
      this.confirmDialogVisible = false;

      /* Prepare the API command */
      let request = new ApiRequest();
      request.commandId = "rebootcom";

      /* Send the request */
      if (true === RequestResponseHandler.getInstance().makeRequest(request)) {
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
          detail: "A fatal error occured when communicating with the server!",
          life: 3000,
        });

        Log.error("Fatal server error occured!");
      }
    },
  },
});
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.connectivity-settings-container {
  display: flex;
  flex-direction: column;

  width: 100%;
  height: 100%;

  .settings-card {
    margin: 10px 10px 10px 10px;

    .card-content-container {
      display: flex;
      flex-direction: column;

      .p-float-label {
        display: flex;
        flex-direction: column;
        width: 40%;

        margin-left: auto;
        margin-right: auto;

        margin-top: 20px;
        margin-bottom: 20px;
      }

      .p-button-rounded {
        width: 10%;
        margin-left: auto;
        margin-right: 20px;
      }
    }

    .card-icon {
      margin-top: 20px;
      width: 50px;
      height: 50px;
    }
  }
}
</style>
