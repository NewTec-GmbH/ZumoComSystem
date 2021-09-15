<template>
  <div class="upload">
    <h1>This is the UPLOAD page</h1>
  </div>
</template>

<script lang="ts">
import { Options, Vue } from "vue-class-component";

@Options({})
export default class Upload extends Vue {
  msg!: string;
}
</script>
