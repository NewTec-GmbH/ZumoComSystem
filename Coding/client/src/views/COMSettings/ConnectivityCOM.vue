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
      RequestResponseHandler.getInstance()
        .makeRequest(request, this)
        .then((response: ApiResponse) => {
          if (response.statusCode == ResponseCode.SUCCESS) {
            this.confirmDialogVisible = true;
          }
        });
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
      RequestResponseHandler.getInstance()
        .makeRequest(request, this)
        .then((response: ApiResponse) => {
          if (response.statusCode == ResponseCode.SUCCESS) {
            /* Reload the page afer two seconds to reconnect */
            setTimeout(() => {
              this.$router.go(0);
            }, 2000);
          }
        });
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
