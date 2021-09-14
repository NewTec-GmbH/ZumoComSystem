<template>
  <div class="flash">
    <!-- <h1>This is the FLASH page</h1> -->
    <LoginDialog />
  </div>
</template>

<script lang="ts">
import LoginDialog from "@/components/LoginDialog.vue";
import { Options, Vue } from "vue-class-component";

@Options({
  components: { LoginDialog },
  props: {
    msg: String,
  },
})
export default class Flash extends Vue {
  msg!: string;
}
</script>
