<template>
  <div class="firmware-card">
    <div class="card-container">
      <Card class="firmware-card">
        <template v-if="firmwareAvailable === true" #title
          >Firmware available</template
        >
        <template v-else #title>No Firmware available!</template>

        <template #header>
          <img
            v-if="firmwareAvailable === true"
            class="card-icon"
            src="@/assets/icons/black/success.svg"
          />
          <img v-else class="card-icon" src="@/assets/icons/black/error.svg" />
        </template>

        <template v-if="firmwareAvailable === true" #content>
          <div class="card-content">
            <h2><b>Target:</b> {{ targetSystem }}</h2>
            <h2><b>SHA256:</b> {{ payloadHash }}</h2>
            <h2><b>Valid:</b> {{ isValid }}</h2>
            <h2><b>Bytes:</b> {{ sizeBytes }}</h2>
          </div>
        </template>
      </Card>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";

export default defineComponent({
  name: "FirmwareCard",
  props: [
    "firmwareAvailable",
    "targetSystem",
    "sizeBytes",
    "payloadHash",
    "isValid",
  ],
});
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.firmware-card {
  margin: 10px 10px 10px 10px;

  .card-icon {
    margin-top: 20px;
    width: 50px;
    height: 50px;
  }

  .card-content {
    display: flex;
    flex-direction: column;


    h2 {
      margin: 10px 10px 10px 10px;
      text-align: left;
    }
  }
}
</style>
