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
 * @file TextDialog.vue
 * @author Luis Moser
 * @brief TextDialog class
 * @date 09/22/2021
 *
 * @{
-->

<template>
  <teleport to="body">
    <div v-show="showTextDialog" class="dialog-background">
      <div class="dialog-container">
        <div v-if="type === 'info'">
          <img src="@/assets/icons/black/info.svg" />
          <p class="text-block">{{ text }}</p>
          <ProgressSpinner />
        </div>

        <div v-else-if="type === 'confirm'">
          <img src="@/assets/icons/black/question.svg" />
          <p class="text-block">{{ text }}</p>
          <div class="button-container">
            <Button
              class="p-button-rounded p-button-success"
              @click="$emit('accepted')"
              >Confirm</Button
            >
          </div>
        </div>

        <div v-else-if="type === 'no-yes'">
          <img src="@/assets/icons/black/question.svg" />
          <p class="text-block">{{ text }}</p>
          <div class="button-container">
            <Button
              label="Abort"
              class="p-button-rounded p-button-danger"
              @click="$emit('declined')"
            />
            <Button
              label="Accept"
              class="p-button-rounded p-button-success"
              @click="$emit('accepted')"
            />
          </div>
        </div>
      </div>
    </div>
  </teleport>
</template>

<script lang="ts">
import { defineComponent } from "vue";

export default defineComponent({
  name: "LoginDialog",
  props: ["showTextDialog", "type", "text"],
});
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.dialog-background {
  width: 100vw;
  height: 100vh;

  position: absolute;
  z-index: 1000;

  left: 0;
  top: 0;

  display: flex;
  flex-direction: column;
  justify-content: center;

  background: @dialog_backdrop_color;

  .dialog-container {
    display: flex;
    justify-content: center;

    width: 700px;
    height: 500px;

    position: absolute;
    z-index: 1000;

    left: 50%;
    top: 50%;

    -webkit-transform: translate(-50%, -50%);
    transform: translate(-50%, -50%);

    border: solid @ui_border_color;
    background: @view_background_color;

    div {
      display: flex;
      flex-direction: column;
      justify-content: center;

      img {
        width: 80px;
        height: 80px;

        margin-bottom: 20px;
        margin-left: auto;
        margin-right: auto;
      }

      .text-block {
        font-family: @text_font;
        font-size: @text_secondary_size;
        text-align: center;
      }

      .button-container {
        display: flex;
        flex-direction: row;
        margin-top: 20px;

        Button {
          margin: 20px 20px 20px 20px;
          width: 100px;
        }
      }
    }
  }
}
</style>
