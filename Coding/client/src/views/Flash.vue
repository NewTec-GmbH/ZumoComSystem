<!--
BSD 3-Clause License

Copyright (c) 2021, NewTec GmbH
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
-->

<!--
 * @file Flash.vue
 * @author Luis Moser
 * @brief Flash class
 * @date 09/22/2021
 *
 * @{
-->

<template>
  <div class="flash">
    <TextDialog
      :type="type"
      :showTextDialog="confirmDialogVisible"
      :text="infoText"
      @declined="confirmDialogVisible = false"
      @accepted="flash"
    />

    <FirmwareCard class="firmware-card" />

    <Button
      label="Flash firmware now!"
      icon="pi pi-chevron-circle-right"
      iconPos="right"
      class="p-button-lg p-button-rounded"
      @click="confirmDialogVisible = true"
      :disabled="!flashEnabled"
    />
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import FirmwareCard from "@/components/FirmwareCard.vue";
import Log from "@/utility/Log";
import RequestResponseHandler from "@/api/RequestResponseHandler";
import { ApiRequest } from "@/models/ApiRequest";
import { ResponseCode } from "@/models/ResponseCode";
import { FirmwareInfo } from "@/models/FirmwareInfo";
import TextDialog from "@/components/TextDialog.vue";

export default defineComponent({
  name: "Flash",
  data() {
    return {
      type: "no-yes",
      flashEnabled: true,
      confirmDialogVisible: false,
      infoText:
        "Are you sure you want to flash the firmware now? This process can brick your device!",
    };
  },
  components: {
    FirmwareCard,
    TextDialog,
  },
  mounted(): void {
    const autoFlash = this.$route.query.autoFlash;
    if (autoFlash && "true" === autoFlash) {
      Log.info("Auto-flashing enabled. Flashing firmware image now!");
      this.flash();
    }
  },

  methods: {
    async flash(): Promise<void> {
      let request = new ApiRequest();
      request.commandId = "getfirmwareinfo";

      /* Set the target system */
      if ("ComPlatform" === this.$store.getters.selectedDevice.name) {
        request.jsonPayload = JSON.stringify({ target: "COM" });
      } else if ("Zumo32U4 Robot" === this.$store.getters.selectedDevice.name) {
        request.jsonPayload = JSON.stringify({ target: "ZUMO" });
      }

      let response = await RequestResponseHandler.getInstance().makeRequest(
        request,
        this
      );
      request.jsonPayload = "";

      const firmwareInfo: FirmwareInfo = JSON.parse(response.jsonPayload);
      if (true == firmwareInfo.isValid) {
        /* Set the target system */
        if ("ComPlatform" === this.$store.getters.selectedDevice.name) {
          request.commandId = "flashcom";
        } else if (
          "Zumo32U4 Robot" === this.$store.getters.selectedDevice.name
        ) {
          request.commandId = "flashzumo";
        }

        response = await RequestResponseHandler.getInstance().makeRequest(
          request,
          this
        );

        if (ResponseCode.SUCCESS === response.statusCode) {
          this.$toast.add({
            severity: "success",
            summary: "Flash Success",
            detail:
              "Successfully flashed the firmware onto the target platform!",
            life: 5000,
          });

          /* Reboot if the target platform is COM */
          if ("uploadcom" === request.commandId) {
            this.$toast.add({
              severity: "info",
              summary: "Rebooting ComPlatform",
              detail:
                "In order for the changes to take effect, the ComPlatform will be rebooted in 2 seconds!",
              life: 5000,
            });

            /* Reboot the ComPlatform and reload the page afer five seconds to reconnect */
            setTimeout(() => {
              this.$router.go(0);
            }, 5000);

            setTimeout(() => {
              request.commandId = "rebootcom";
              RequestResponseHandler.getInstance().makeRequest(request, this);
            }, 2000);
          }
        } else {
          this.$toast.add({
            severity: "error",
            summary: "Flash Error",
            detail: "Could not flash the firmware onto the target platform!",
            life: 5000,
          });
        }
      } else {
        this.$toast.add({
          severity: "error",
          summary: "Flash Error",
          detail: "Uploaded firmware is invalid and cannot be flashed!",
          life: 5000,
        });
      }
    },
  },
});
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.flash {
  display: flex;
  flex-direction: column;
  align-items: center;

  .firmware-card {
    width: 80%;
    margin-bottom: 20px;
  }

  Button {
    width: 80%;
  }
}
</style>
