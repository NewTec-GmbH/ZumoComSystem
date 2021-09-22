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
 * @file Header.vue
 * @author Luis Moser
 * @brief Header class
 * @date 09/22/2021
 *
 * @{
-->

<template>
  <div class="header">
    <div class="header-ui">
      <div class="device-selection">
        <Menu ref="menu" :model="menuEntries" :popup="true" />
        <Dropdown
          v-model="selectedDevice"
          :options="devices"
          optionLabel="name"
          placeholder="Select a Device"
        />
        <svg v-if="selectedDevice.name === 'ComPlatform'" class="device-icon">
          <use
            :xlink:href="
              require('@/assets/icons/icons.svg') + '#complatform-white'
            "
          />
        </svg>

        <svg
          v-else-if="selectedDevice.name === 'Zumo32U4 Robot'"
          class="device-icon"
        >
          <use
            :xlink:href="
              require('@/assets/icons/icons.svg') + '#zumorobot-white'
            "
          />
        </svg>
      </div>

      <div class="user-selection">
        <p v-if="currentUser != 'null'" class="username-label">
          {{ currentUser }}
        </p>
        <div @click="userIconClick">
          <svg v-if="currentUser != 'null'" class="username-icon">
            <use
              :xlink:href="require('@/assets/icons/icons.svg') + '#user-white'"
            />
          </svg>
        </div>

        <Button
          v-if="currentUser == 'null'"
          label="Sign in"
          icon="pi pi-user"
          iconPos="right"
          class="p-button-rounded"
          @click="signIn"
        />
      </div>
    </div>
  </div>
  <LoginDialog v-bind:show="showLoginDialog" />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import LoginDialog from "@/components/LoginDialog.vue";
import Menu from "primevue/menu";
import { ApiRequest } from "@/models/ApiRequest";
import { ApiResponse } from "@/models/ApiResponse";
import { ResponseCode } from "@/models/ResponseCode";
import RequestResponseHandler from "@/api/RequestResponseHandler";
import Log from "@/utility/Log";

export default defineComponent({
  name: "Header",
  data() {
    return {
      /** The available devices in the contet menu */
      devices: [{ name: "Zumo32U4 Robot" }, { name: "ComPlatform" }],

      menuEntries: [
        {
          label: "Sign out",
          icon: "pi pi-sign-out",
          command: () => {
            /* De-authenticate the WebSocket session! */
            let request = new ApiRequest();
            request.commandId = "deauthenticate";

            /* Send the request */
            RequestResponseHandler.getInstance()
              .makeRequest(request, this)
              .then((response: ApiResponse) => {
                if (response.statusCode == ResponseCode.SUCCESS) {
                  this.$store.commit("setUser", "null");
                  Log.info("Successfully signed out!");
                }
              });
          },
        },
      ],
    };
  },
  components: {
    LoginDialog,
  },

  computed: {
    selectedDevice: {
      get() {
        return this.$store.getters.selectedDevice;
      },
      set(value) {
        this.$store.commit("setDevice", value);
      },
    },

    currentUser: {
      get() {
        return this.$store.getters.currentUser;
      },
      set(value) {
        this.$store.commit("setUser", value);
      },
    },
  },

  methods: {
    signIn(): void {
      this.$store.commit("setLoginDialogVisibility", true);
    },

    userIconClick(event: any): void {
      (this.$refs.menu as Menu).toggle(event);
    },
  },
});
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.header {
  height: 10vh;
  width: 100%;
  background: @ui_background_color;
  border-bottom: 5px solid @ui_border_color;

  .header-ui {
    display: flex;
    height: 100%;
    margin-left: auto;
    margin-right: 40px;

    .user-selection {
      display: flex;
      align-items: center;
      margin-left: 20px;
      margin-right: 20px;

      .username-label {
        font-family: @text_font;
        font-size: @text_secondary_size;
        color: @text_color_bright_ui;
      }

      .username-icon {
        width: @icon_height_width;
        height: @icon_height_width;
        margin-left: 15px;

        cursor: pointer;
      }
    }

    .device-selection {
      display: flex;
      align-items: center;
      margin-right: 40px;

      .device-icon {
        width: @icon_height_width;
        height: @icon_height_width;
        margin-left: 15px;
      }
    }
  }
}
</style>
