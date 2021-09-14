<template>
  <div class="header">
    <div class="header-ui">
      <div class="device-selection">
        <Dropdown
          v-model="selectedDevice"
          :options="devices"
          optionLabel="name"
          placeholder="Select a Device"
        />
        <img
          v-if="selectedDevice.name === 'ComPlatform'"
          src="@/assets/icons/white/complatform.svg"
          class="device-icon"
        />
        <img
          v-else-if="selectedDevice.name === 'Zumo32U4 Robot'"
          src="@/assets/icons/white/zumorobot.svg"
          class="device-icon"
        />
      </div>

      <div class="user-selection">
        <p v-if="currentUser != 'null'" class="username-label">
          {{ currentUser }}
        </p>
        <img
          v-if="currentUser != 'null'"
          src="@/assets/icons/white/user.svg"
          class="username-icon"
        />
        <Button
          v-else
          label="Sign in"
          icon="pi pi-user"
          iconPos="right"
          class="p-button-rounded"
          @click="signIn()"
        />
      </div>
    </div>
  </div>
  <LoginDialog v-bind:show="showLoginDialog" />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import { mapGetters } from "vuex";
import LoginDialog from "@/components/LoginDialog.vue";

export default defineComponent({
  name: "Header",
  data() {
    return {
      devices: [{ name: "Zumo32U4 Robot" }, { name: "ComPlatform" }],
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
  },
});
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.header {
  display: flex;
  height: 10vh;
  width: 100%;
  flex-direction: row;

  background: @view_background_color;
  overflow: hidden;
  border-bottom: 5px solid @ui_border_color;

  .header-ui {
    display: flex;
    height: 100%;
    align-self: flex-end;
    margin-left: auto;
    margin-right: 40px;

    .user-selection {
      display: flex;
      flex-direction: row;
      align-items: center;
      margin-left: 20px;
      margin-right: 20px;

      .username-label {
        font-family: "Trebuchet MS", "Lucida Sans Unicode", "Lucida Grande",
          "Lucida Sans", Arial, sans-serif;
        font-size: 16pt;
        color: white;
      }

      .username-icon {
        width: 40px;
        height: 40px;
        margin-left: 15px;
      }

      .p-button-rounded {
        margin-left: 30px;
      }
    }

    .device-selection {
      display: flex;
      align-items: center;
      margin-left: 20px;
      margin-right: 20px;

      .device-icon {
        width: 40px;
        height: 40px;
        margin-left: 15px;
      }
    }
  }
}
</style>
