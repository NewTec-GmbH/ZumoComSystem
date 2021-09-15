<template>
  <div class="settings">
    <h1>This is the SETTINGS page</h1>
  </div>
</template>

<script lang="ts">
import { Options, Vue } from "vue-class-component";

@Options({})
export default class Settings extends Vue {
  msg!: string;
}
</script>
