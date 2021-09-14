<template>
  <div class="home">
    <div class="text-container">
      <p class="welcome-text">
        Speed up your embedded systems development with the ComPlatform!
      </p>
      <p class="sub-welcome-text">
        Upload your firmware faster and easier than ever before!
      </p>
    </div>

    <div class="card-container">
      <Card class="info-card">
        <template #title>Configuration made easy!</template>
        <template #header>
          <img class="card-icon" src="@/assets/icons/black/settings.svg" />
        </template>
        <template #content
          >The ComPlatform system allows you to enable or disable the WiFi
          station mode and provides an easy configuration interface for you to
          configure the network credentials which are used to connect to an
          external WiFi access point!
        </template>
      </Card>

      <Card class="info-card">
        <template #title>Intuitive Power Management!</template>
        <template #header>
          <img class="card-icon" src="@/assets/icons/black/reset.svg" />
        </template>
        <template #content
          >The firmware you wrote and flashed halts your system? No worries! The
          web interface of the ComPlatform makes it easy to reboot both the
          ComPlatform system as well as the attached Zumo32U4 robot with ease!
        </template>
      </Card>

      <Card class="info-card">
        <template #title>
          Debugging your code? Nothing easier than that!
        </template>
        <template #header>
          <img class="card-icon" src="@/assets/icons/black/debug.svg" />
        </template>
        <template #content
          >Imagine a world without buggy software. With the help of the
          ComPlatform system and its intuitive debugging console, you can get to
          that dream one step closer now! The web interface allows you to
          analyze the data which has been received by the attached robot through
          the USB serial interface!
        </template>
      </Card>

      <Card class="info-card">
        <template #title>Upload & Flash your Firmware? Done.</template>
        <template #header>
          <img class="card-icon" src="@/assets/icons/black/flash.svg" />
        </template>
        <template #content
          >Cable spaghetti, annoying USB cables and the need to catch the robot
          and attach it to your computer each time you want to update your
          firmware. Are you familiar with this struggle? With the help of the
          ComPlatform you no longer have to loose any nerves on this issue!
          Simply upload your new firmware onto the ComPlatform and flash it! The
          intuitive OTA service allows you to update the firmware of the
          attached Zumo32U4 robot as well as the attached ComPlatform system
          itself!
        </template>
      </Card>

      <Card class="info-card">
        <template #title>Powerful User Management & Easy to extend</template>
        <template #header>
          <img class="card-icon" src="@/assets/icons/black/user.svg" />
        </template>
        <template #content
          >The ComPlatform offers a powerful user management system where each
          user can have its own user account, protected by a securely stored
          password. Each user has a specific set of rights, which decides which
          operations are allowed to be executed. Adding new API services to the
          ComPlatform is super easy! Just write your service and integrate it
          into the ComPlatform! Read the docs and get started now!
        </template>
      </Card>

      <Card class="info-card">
        <template #title>A hacker's nightmare!</template>
        <template #header>
          <img class="card-icon" src="@/assets/icons/black/security.svg" />
        </template>
        <template #content
          >The ComPlatform project focuses on information security! Specified
          API services require user authentication and specific user rights. Th
          entire data traffic is fully encrypted, all user passwords are
          securely stored and all uploaded firmware images have to be
          cryptographically signed with a private key, otherwise they won't be
          flashed!</template
        >
      </Card>
    </div>
  </div>
</template>

<script lang="ts">
import { Options, Vue } from "vue-class-component";
import Card from "primevue/card";
import Log from "@/utility/Log";

@Options({
  components: {},
})
export default class Home extends Vue {}
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.home {
  display: flex;
  flex-direction: row;
}

.card-icon {
  margin-top: 20px;
  width: 50px;
  height: 50px;
}

.card-container {
  display: flex;
  flex-direction: row;
  flex-wrap: wrap;
  justify-content: center;
  align-items: flex-start;
}

.text-container {
  display: flex;
  flex-direction: column;
  margin-left: 20px;

  .welcome-text {
    font-size: 22pt;
    font-weight: bold;
    text-align: left;
    font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;
    width: 300px;
  }

  .sub-welcome-text {
    font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;
    font-size: 14pt;
  }
}

.info-card {
  width: 30%;
  margin: 10px 10px 10px 10px;
}
</style>
