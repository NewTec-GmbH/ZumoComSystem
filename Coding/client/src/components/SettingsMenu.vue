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
 * @file SettingsMenu.vue
 * @author Luis Moser
 * @brief SettingsMenu class
 * @date 09/22/2021
 *
 * @{
-->

<template>
  <div class="settings-menu">
    <div
      v-if="$store.getters.selectedDevice.name === 'ComPlatform'"
      class="com-settings"
    >
      <div
        class="menu-entry"
        @click="$emit('entry-click', $event, 'connectivity-com')"
      >
        <svg class="entry-icon">
          <use
            :xlink:href="require('@/assets/icons/icons.svg') + '#wifi-black'"
          />
        </svg>
        <h1 class="entry-text">Connectivity</h1>
      </div>
    </div>

    <div
      v-else-if="$store.getters.selectedDevice.name === 'Zumo32U4 Robot'"
      class="zumo-settings"
    >
      <div class="info-pane">
        <svg class="info-image">
          <use
            :xlink:href="require('@/assets/icons/icons.svg') + '#info-black'"
          />
        </svg>
        <h1 class="info-text">No Settings available</h1>
      </div>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";

export default defineComponent({
  name: "SettingsMenu",
});
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.settings-menu {
  display: flex;
  flex-direction: column;

  .zumo-settings {
    margin-top: auto;
    margin-bottom: auto;

    .info-image {
      width: 80px;
      height: 80px;
    }
  }

  .menu-entry {
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: flex-start;

    cursor: pointer;
    border-bottom: solid @menu_border_color;

    .entry-icon {
      width: 30px;
      height: 30px;

      margin-left: 20px;
    }

    .entry-text {
      font-family: @text_font;
      margin-left: 20px;
    }
  }

  .menu-entry:hover {
    background: @ui_hover_color;
  }

  .settings-view {
    width: 100%;
  }
}
</style>
