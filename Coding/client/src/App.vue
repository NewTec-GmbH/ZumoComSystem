<template>
  <div class="complatform">
    <Toast position="bottom-center" />
    <Sidebar class="sidebar" />
    <div class="header-view-container">
      <Header class="header" />
      <router-view class="view" />
      <TextDialog
        :type="type"
        :showTextDialog="infoDialogVisible"
        :text="infoText"
      />
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import Sidebar from "@/components/Sidebar.vue";
import Header from "@/components/Header.vue";
import TextDialog from "@/components/TextDialog.vue";
import WebSocketClient from "@/api/WebSocketClient";
import Log from "@/utility/Log";

export default defineComponent({
  name: "App",
  components: {
    Sidebar,
    Header,
    TextDialog,
  },
  data() {
    return {
      type: "info",
      infoDialogVisible: false,
      infoText: "Connecting to Server. Please wait ...",
    };
  },
  beforeCreate() {
    /* Establish the WebSocket connection on app start by creating a new instance */
    WebSocketClient.getInstance();

    /* Set default values on start */
    this.$store.commit("setDevice", { name: "Zumo32U4 Robot" });
    this.$store.commit("setUser", "null");
    this.$store.commit("setLoginDialogVisibility", false);
  },

  mounted() {
    /* Show info dialog as long as WebSocket client is not connected */
    this.infoDialogVisible = true;

    /* Hide the info dialog when connected */
    WebSocketClient.getInstance().onOpen(() => {
      this.infoDialogVisible = false;

      this.$toast.add({
        severity: "success",
        summary: "Connected",
        detail: "Successfully connected to server!",
        life: 3000,
      });

      Log.debug("New WebSocket connection opened!");
    });

    /* Hide the info dialog when connected */
    WebSocketClient.getInstance().onClose(() => {
      this.infoDialogVisible = true;
      this.$store.commit("setUser", "null");

      Log.debug("WebSocket connection closed!");
    });

    /* Hide the info dialog when connected */
    WebSocketClient.getInstance().onError(() => {
      this.infoDialogVisible = true;
      this.$store.commit("setUser", "null");

      this.$toast.add({
        severity: "error",
        summary: "Server Connection Error",
        detail: "A fatal connection error occured!",
        life: 3000,
      });

      Log.debug("Fatal WebSocket error occured!");
    });
  },
});
</script>

<style lang="less">
@import "~@/styles/global.less";

.complatform {
  display: flex;
  flex-direction: row;
  height: 100vh;
}

.header-view-container {
  display: flex;
  width: 100%;
  height: 100vh;

  flex-direction: column;
  background-color: @view_background_color;
}

.sidebar {
  display: flex;
  flex: 0 0 auto;
}

.header {
  display: flex;
  flex: 0 0 auto;
  align-self: flex-start;
}

.view {
  display: flex;
  height: 100vh;
  flex: 1 1 auto;
  margin: 20px 20px 20px 20px;
  background-color: @view_background_color;
}

#app {
  font-family: @text_font;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}

#nav {
  padding: 30px;

  a {
    font-weight: bold;
    color: #2c3e50;

    &.router-link-exact-active {
      color: #42b983;
    }
  }
}
</style>
