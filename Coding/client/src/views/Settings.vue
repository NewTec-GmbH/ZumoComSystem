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
 * @file Settings.vue
 * @author Luis Moser
 * @brief Settings class
 * @date 09/22/2021
 *
 * @{
-->

<template>
  <div class="settings">
    <SettingsMenu class="settings-menu" @entry-click="entryClick" />

    <div
      v-if="selectedMenuEntry === 'connectivity-com' && hideView === false"
      class="settings-view"
    >
      <ConnectivityCOM />
    </div>

    <div v-else class="settings-view">
      <div class="info-pane">
        <svg class="info-image">
          <use
            :xlink:href="require('@/assets/icons/icons.svg') + '#info-black'"
          />
        </svg>
        <h1 class="info-text">No menu entry selected</h1>
      </div>
    </div>
  </div>
</template>

<script lang="ts">
import SettingsMenu from "@/components/SettingsMenu.vue";
import ConnectivityCOM from "@/views/COMSettings/ConnectivityCOM.vue";
import { defineComponent } from "vue";

export default defineComponent({
  name: "Settings",
  data() {
    return {
      selectedMenuEntry: "null",
      hideView: false,
    };
  },

  components: {
    SettingsMenu,
    ConnectivityCOM,
  },

  methods: {
    entryClick(event: any, item: string): void {
      this.hideView = false;
      this.selectedMenuEntry = item;
    },
  },

  watch: {
    "$store.state.seletedDevice.name": function (newValue, oldValue) {
      this.hideView = newValue != oldValue;
    },
  },
});
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.settings {
  display: flex;
  flex-direction: row;

  .settings-menu {
    width: 350px;

    border-right: solid 5px @ui_border_color;
    background: @view_background_color;
  }

  .settings-view {
    width: 100%;

    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;

    .info-image {
      width: 80px;
      height: 80px;
    }
  }
}
</style>
