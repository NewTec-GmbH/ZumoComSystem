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
 * @file FirmwareCard.vue
 * @author Luis Moser
 * @brief FirmwareCard class
 * @date 09/22/2021
 *
 * @{
-->

<template>
  <div class="firmware-card">
    <div class="card-container">
      <Card class="firmware-card">
        <template v-if="firmwareAvailable === true" #title
          >Firmware available</template
        >
        <template v-else #title>No Firmware available!</template>

        <template #header>
          <svg v-if="firmwareAvailable === true" class="card-icon">
            <use
              :xlink:href="
                require('@/assets/icons/icons.svg') + '#success-black'
              "
            />
          </svg>

          <svg v-else class="card-icon">
            <use
              :xlink:href="require('@/assets/icons/icons.svg') + '#error-black'"
            />
          </svg>
        </template>

        <template v-if="firmwareAvailable === true" #content>
          <div class="card-content">
            <h2><b>Target:</b> {{ fwInfo.targetSystem }}</h2>
            <h2><b>SHA256:</b> {{ fwInfo.payloadHash }}</h2>
            <h2><b>Valid:</b> {{ fwInfo.isValid }}</h2>
            <h2><b>Bytes:</b> {{ fwInfo.sizeBytes }}</h2>
          </div>

          <div v-if="fwInfo.isValid === false" class="error-container">
            <svg class="error-icon">
              <use
                :xlink:href="require('@/assets/icons/icons.svg') + '#error-red'"
              />
            </svg>

            <p class="error-label">
              Invalid firmware! You cannot flash this image!
            </p>
          </div>
        </template>
      </Card>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import { FirmwareInfo } from "@/models/FirmwareInfo";
import RequestResponseHandler from "@/api/RequestResponseHandler";
import Log from "@/utility/Log";
import { ApiResponse } from "@/models/ApiResponse";
import { ApiRequest } from "@/models/ApiRequest";
import { ResponseCode } from "@/models/ResponseCode";

export default defineComponent({
  name: "FirmwareCard",
  props: ["update"],

  computed: {
    selectedDevice: function (): string {
      return this.$store.getters.selectedDevice.name;
    },
  },

  data() {
    return {
      firmwareAvailable: false,
      fwInfo: new FirmwareInfo(),
    };
  },

  mounted() {
    this.updateFirmwareCard();
  },

  watch: {
    update: function (newValue, oldValue) {
      if (newValue != oldValue) {
        /* Update FirmwareCard when store variable is set */
        this.updateFirmwareCard();
      }
    },

    selectedDevice: function (newValue, oldValue) {
      if (newValue != oldValue) {
        /* Update FirmwareCard when dropdown selection is changed */
        this.updateFirmwareCard();
      }
    },
  },

  methods: {
    updateFirmwareCard() {
      let targetSystem = "";
      if ("Zumo32U4 Robot" === this.$store.getters.selectedDevice.name) {
        targetSystem = "ZUMO";
      } else if ("ComPlatform" === this.$store.getters.selectedDevice.name) {
        targetSystem = "COM";
      }

      /* Prepare the API command */
      let request = new ApiRequest();
      request.commandId = "getfirmwareinfo";
      request.jsonPayload = JSON.stringify({ target: targetSystem });

      /* Send the request */
      RequestResponseHandler.getInstance()
        .makeRequest(request, this, true)
        .then((response: ApiResponse) => {
          Log.debug("Got FirmwareInfo response");

          if (response.statusCode == ResponseCode.SUCCESS) {
            /* Set the new FirmwareInfo data */
            this.firmwareAvailable = true;
            this.fwInfo = JSON.parse(response.jsonPayload);
          } else {
            this.firmwareAvailable = false;
          }
        });
    },
  },
});
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.firmware-card {
  margin: 10px 10px 10px 10px;

  .card-icon {
    margin-top: 20px;
    width: 50px;
    height: 50px;
  }

  .card-content {
    display: flex;
    flex-direction: column;

    h2 {
      margin: 10px 10px 10px 10px;
      text-align: left;
    }
  }

  .error-container {
    display: flex;
    align-items: center;

    margin-left: 10px;
    margin-top: 10px;

    .error-label {
      font-family: @text_font;
      font-size: @text_secondary_size;
      color: @text_color_warning;
    }

    .error-icon {
      width: @icon_height_width;
      height: @icon_height_width;
      margin-right: 20px;
    }
  }
}
</style>
