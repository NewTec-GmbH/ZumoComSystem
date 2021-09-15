<template>
  <div class="debug">
    <h1>This is the DEBUG page</h1>
  </div>
</template>

<script lang="ts">
import { Options, Vue } from "vue-class-component";

@Options({})
export default class Debug extends Vue {
  msg!: string;
}
</script>
