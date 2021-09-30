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
 * @file App.vue
 * @author Luis Moser
 * @brief App class
 * @date 09/22/2021
 *
 * @{
-->

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
  beforeCreate(): void {
    /* Establish the WebSocket connection on app start by creating a new instance */
    WebSocketClient.getInstance();

    /* Set default values on start */
    this.$store.commit("setDevice", { name: "Zumo32U4 Robot" });
    this.$store.commit("setUser", "null");
    this.$store.commit("setLoginDialogVisibility", false);
  },

  methods: {
    registerWSEvents(): void {
      /* Hide the info dialog when connected */
      WebSocketClient.getInstance().onOpen(() => {
        this.infoDialogVisible = false;

        this.$toast.add({
          severity: "success",
          summary: "Connected",
          detail: "Successfully connected to server!",
          life: 5000,
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
          detail:
            "A fatal connection error occured! Reconnecting in two seconds!",
          life: 5000,
        });

        Log.debug(
          "Fatal WebSocket error occured! Reconnecting in two seconds!"
        );

        /* Reload the page afer two seconds to reconnect */
        setTimeout(() => {
          this.$router.go(0);
        }, 2000);
      });
    },
  },

  mounted(): void {
    /* Show info dialog as long as WebSocket client is not connected */
    this.infoDialogVisible = true;

    this.registerWSEvents();
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
