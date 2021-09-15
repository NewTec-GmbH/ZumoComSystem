<template>
  <div class="flash">
    <h1>This is the FLASH page</h1>
  </div>
</template>

<script lang="ts">
import { Options, Vue } from "vue-class-component";

@Options({})
export default class Flash extends Vue {
  msg!: string;
}
</script>
