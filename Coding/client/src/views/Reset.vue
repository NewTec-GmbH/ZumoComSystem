<template>
  <div class="reset">
    <h1>This is the RESET page</h1>
  </div>
</template>

<script lang="ts">
import { Options, Vue } from "vue-class-component";

@Options({})
export default class Reset extends Vue {
  msg!: string;
}
</script>
