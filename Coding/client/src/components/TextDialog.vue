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
          <ProgressSpinner />
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
          <ProgressSpinner />
          <div class="button-container">
            <Button
              class="p-button-rounded p-button-danger"
              @click="$emit('declined')"
              >No</Button
            >
            <Button
              class="p-button-rounded p-button-success"
              @click="$emit('accepted')"
              >Yes</Button
            >
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

      Button {
        margin-left: 20px;
        margin-right: 20px;
      }

      ProgressSpinner {
        margin-top: 20px;
      }

      .button-container {
        justify-content: flex-end;
        margin-top: 20px;
      }
    }
  }
}
</style>
