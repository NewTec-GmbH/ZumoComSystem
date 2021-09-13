<template>
  <teleport to="body">
    <div v-show="showTextDialog" class="dialog-background">
      <div v-show="showTextDialog" class="dialog-container">
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
@dialog-color: rgba(255, 165, 0, 0.5);
@view-color: #f7f7f7;

.dialog-background {
  position: absolute;
  z-index: 1000;
  display: flex;
  flex-direction: column;
  justify-content: center;
  top: 0;
  left: 0;
  width: 100vw;
  height: 100vh;
  background: rgba(0, 0, 0, 0.5);

  .dialog-container {
    display: flex;
    flex-direction: row;
    justify-content: center;

    width: 700px;
    height: 500px;
    border: solid;
    border-color: @dialog-color;
    background: @view-color;
    overflow: hidden;

    position: absolute;
    z-index: 1000;
    width: 40vw;
    height: 35vh;
    left: 50%;
    top: 50%;
    -webkit-transform: translate(-50%, -50%);
    transform: translate(-50%, -50%);

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
        font-family: "Trebuchet MS", "Lucida Sans Unicode", "Lucida Grande",
          "Lucida Sans", Arial, sans-serif;
        font-size: 14pt;
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