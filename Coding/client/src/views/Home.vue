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
 * @file Home.vue
 * @author Luis Moser
 * @brief Home class
 * @date 09/22/2021
 *
 * @{
-->

<template>
  <div class="home">
    <div class="text-container">
      <h1 class="welcome-text">
        Speed up your Embedded System Development with the ComPlatform!
      </h1>
      <h2 class="sub-welcome-text">
        Upload your Firmware faster and easier than ever before!
      </h2>
    </div>

    <div class="card-container">
      <Card class="info-card">
        <template #title>Configuration made easy!</template>
        <template #header>
          <img class="card-icon" src="@/assets/icons/black/settings.svg" />
        </template>
        <template #content>
          The ComPlatform system allows you to enable or disable the WiFi
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
        <template #content>
          The firmware you wrote and flashed halts your system? No worries! The
          web interface of the ComPlatform makes it easy to reboot both the
          ComPlatform system as well as the attached Zumo32U4 robot with ease!
        </template>
      </Card>

      <Card class="info-card">
        <template #title>
          Debugging your Code? Nothing easier than that!
        </template>
        <template #header>
          <img class="card-icon" src="@/assets/icons/black/debug.svg" />
        </template>
        <template #content>
          Imagine a world without buggy software. With the help of the
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
        <template #content>
          Cable spaghetti, annoying USB cables and the need to catch the robot
          and attach it to your computer each time you want to update your
          firmware? Are you familiar with this struggle? With the help of the
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
        <template #content>
          The ComPlatform offers a powerful user management system where each
          user can have its own user account, protected by a securely stored
          password. Each user has a specific set of rights, which decides which
          operations are allowed to be executed. Adding new API services to the
          ComPlatform is super easy! Just write your service and integrate it
          into the ComPlatform! Read the docs and get started now!
        </template>
      </Card>

      <Card class="info-card">
        <template #title>A Hacker's Nightmare!</template>
        <template #header>
          <img class="card-icon" src="@/assets/icons/black/security.svg" />
        </template>
        <template #content>
          The ComPlatform project focuses on information security! Specified API
          services require user authentication and specific user rights. The
          entire data traffic is fully encrypted, all user passwords are
          securely stored and all uploaded firmware images have to be
          cryptographically signed with a private key, otherwise they won't be
          flashed!
        </template>
      </Card>
    </div>
  </div>
</template>

<script lang="ts">
import { Options, Vue } from "vue-class-component";

@Options({
  components: {},
})
export default class Home extends Vue {}
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.card-container {
  display: flex;
  flex-direction: row;
  flex-wrap: wrap;
  justify-content: center;
  align-items: flex-start;

  .info-card {
    width: 30%;
    margin: 10px 10px 10px 10px;

    .card-icon {
      margin-top: 20px;
      width: 50px;
      height: 50px;
    }
  }
}

.text-container {
  display: flex;
  flex-direction: column;
  text-align: left;
  margin-left: 20px;

  h1 {
    width: 300px;
  }
}
</style>
