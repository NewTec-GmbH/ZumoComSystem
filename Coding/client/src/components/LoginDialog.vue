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
 * @file LoginDialog.vue
 * @author Luis Moser
 * @brief LoginDialog class
 * @date 09/22/2021
 *
 * @{
-->

<template>
  <teleport to="body">
    <div v-show="showLoginDialog" class="dialog-background">
      <div class="login-dialog">
        <h1>Please enter your user credentials!</h1>

        <div class="form">
          <span class="p-float-label p-input-icon-left">
            <i class="pi pi-user"></i>
            <InputText
              id="username"
              type="text"
              v-model="usercredentials.username"
            />
            <label for="username">Username</label>
          </span>

          <span class="p-float-label p-input-icon-left">
            <i class="pi pi-key"></i>
            <InputText
              id="password"
              type="password"
              v-model="usercredentials.password"
            />
            <label for="password">Password</label>
          </span>
        </div>

        <div v-if="loginSuccess === false" class="error-container">
          <svg class="error-icon">
            <use xlink:href="@/assets/icons/icons.svg#error-red" />
          </svg>

          <p class="error-label">
            Could not sign in with provided user credentials!
          </p>
        </div>

        <ProgressBar
          v-if="spinnerVisible === true"
          class="progress-bar"
          mode="indeterminate"
        />

        <div class="buttons">
          <Button
            label="Cancel"
            icon="pi pi-times"
            iconPos="right"
            class="p-button-rounded p-button-danger"
            @click="cancelClick()"
          />

          <Button
            label="Login"
            icon="pi pi-sign-in"
            iconPos="right"
            class="p-button-rounded"
            @click="signInClick()"
          />
        </div>
      </div>
    </div>
  </teleport>
</template>

<script lang="ts">
import RequestResponseHandler from "@/api/RequestResponseHandler";
import { defineComponent } from "vue";
import Log from "@/utility/Log";
import { ApiResponse } from "@/models/ApiResponse";
import { ApiRequest } from "@/models/ApiRequest";
import { UserCredentials } from "@/models/UserCredentials";
import { ResponseCode } from "@/models/ResponseCode";

export default defineComponent({
  name: "LoginDialog",
  computed: {
    showLoginDialog: {
      get() {
        return this.$store.getters.loginDialogVisible;
      },
      set(value) {
        this.$store.commit("setLoginDialogVisibility", value);
      },
    },
  },

  data() {
    return {
      usercredentials: new UserCredentials(),
      spinnerVisible: false,
      loginSuccess: true,
    };
  },

  methods: {
    reset() {
      this.showLoginDialog = false;
      this.spinnerVisible = false;
      this.loginSuccess = true;
    },

    cancelClick() {
      this.reset();
    },

    async signInClick() {
      this.spinnerVisible = true;

      /* Prepare the API command */
      let request = new ApiRequest();
      request.commandId = "authenticate";
      request.jsonPayload = JSON.stringify(this.usercredentials);

      /* Send the request */
      RequestResponseHandler.getInstance()
        .makeRequest(request, this)
        .then((response: ApiResponse) => {
          if (response.statusCode == ResponseCode.SUCCESS) {
            this.$store.commit("setUser", this.usercredentials.username);
            this.reset();

            this.$toast.add({
              severity: "success",
              summary: "Login Success",
              detail: "Successfully signed in!",
              life: 5000,
            });

            Log.debug("Successfully logged in!");
          } else {
            this.$store.commit("setUser", "null");
            this.loginSuccess = false;
            this.spinnerVisible = false;

            Log.debug("Could not log in!");
          }
        });
    },
  },
});
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.dialog-background {
  position: absolute;
  z-index: 1000;

  width: 100vw;
  height: 100vh;
  top: 0;
  left: 0;

  background: @dialog_backdrop_color;

  .login-dialog {
    width: 500px;
    height: 500px;

    position: absolute;
    z-index: 1000;

    left: 50%;
    top: 50%;
    -webkit-transform: translate(-50%, -50%);
    transform: translate(-50%, -50%);

    display: flex;
    flex-direction: column;
    justify-content: center;

    background: @view_background_color;
    border: solid @ui_border_color;

    h1 {
      text-align: center;
    }

    .buttons {
      margin-left: auto;
      margin-right: 40px;
      margin-top: 20px;

      Button {
        margin-left: 20px;
      }
    }

    .form {
      margin-left: 40px;
      margin-right: 40px;

      .p-float-label {
        display: flex;
        flex-direction: column;

        margin-top: 40px;
        margin-bottom: 40px;
      }
    }

    .error-container {
      display: flex;
      align-items: center;
      justify-content: flex-start;

      margin-left: 40px;
      margin-right: 40px;

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

    .progress-bar {
      height: 4px;
      margin: 40px 40px 40px 40px;
    }
  }
}
</style>
