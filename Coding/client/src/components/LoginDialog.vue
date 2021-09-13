<template>
  <div v-show="showLoginDialog === true" class="login-dialog">
    <p class="header-label">Please enter your user credentials!</p>
    <div class="form">
      <span class="p-float-label p-input-icon-left">
        <i class="pi pi-user"></i>
        <InputText id="username" type="text" v-model="username" />
        <label for="username">Username</label>
      </span>

      <span class="p-float-label p-input-icon-left">
        <i class="pi pi-key"></i>
        <InputText id="password" type="password" v-model="password" />
        <label for="password">Password</label>
      </span>
    </div>

    <div v-if="loginSuccess === false" class="error-container">
      <img src="@/assets/icons/red/error.svg" class="error-icon" />
      <p class="error-label">Could not sign in with provided credentials!</p>
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
      username: "",
      password: "",

      spinnerVisible: false,
      loginSuccess: true,
    };
  },

  methods: {
    reset() {
      this.showLoginDialog = false;
      this.spinnerVisible = false;
      this.username = "";
      this.password = "";
      this.loginSuccess = true;
    },

    cancelClick() {
      this.reset();
    },

    signInClick() {
      this.spinnerVisible = true;

      let credentials = new UserCredentials();
      credentials.username = this.username;
      credentials.password = this.password;

      let request = new ApiRequest();
      request.commandId = "authenticate";
      request.jsonPayload = JSON.stringify(credentials);

      /* Send the request */
      if (true === RequestResponseHandler.getInstance().makeRequest(request)) {
        /* Register the event handler for incoming response message */
        RequestResponseHandler.getInstance().onResponse((event: any) => {
          /* Parse the response data */
          const response: ApiResponse = JSON.parse(event.data);
          if (response.statusCode == ResponseCode.SUCCESS) {
            this.$store.commit("setUser", this.username);
            this.reset();
            Log.debug("Successfully logged in!");
          } else {
            this.$store.commit("setUser", "null");
            this.loginSuccess = false;
            this.spinnerVisible = false;
            Log.debug("Could not log in!");
          }
        });
      } else {
        this.$store.commit("setUser", "null");
        this.loginSuccess = false;
        this.spinnerVisible = false;
        Log.debug("Could not send login request!");
      }
    },
  },
});
</script>

<style lang="less" scoped>
@dialog-color: rgba(255, 165, 0, 0.5);
@view-color: #f7f7f7;

.login-dialog {
  display: flex;
  flex-direction: column;

  width: 500px;
  height: 500px;
  border: solid;
  border-color: @dialog-color;
  background: @view-color;
  overflow: hidden;

  position: absolute;
  z-index: 1000;
  width: 40vw;
  height: 50vh;
  left: 50%;
  top: 50%;
  -webkit-transform: translate(-50%, -50%);
  transform: translate(-50%, -50%);

  .buttons {
    margin-top: 0px;
    margin-left: auto;
    Button {
      margin: 40px 40px 40px 40px;
      margin-left: auto;
    }
  }

  .header-label {
    font-family: "Trebuchet MS", "Lucida Sans Unicode", "Lucida Grande",
      "Lucida Sans", Arial, sans-serif;
    font-size: 16pt;
  }

  .p-float-label {
    margin: 40px 40px 40px 40px;
    display: flex;
    flex-direction: column;
  }

  .error-container {
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: flex-start;
    margin: 0px 40px 40px 40px;

    .error-label {
      font-family: "Trebuchet MS", "Lucida Sans Unicode", "Lucida Grande",
        "Lucida Sans", Arial, sans-serif;
      font-size: 12pt;
      color: darkred;
    }

    .error-icon {
      width: 40px;
      height: 40px;
      margin-right: 40px;
    }
  }

  .progress-bar {
    height: 5px;
    margin: 0px 40px 0px 40px;
  }
}
</style>