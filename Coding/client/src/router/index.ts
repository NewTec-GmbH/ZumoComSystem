import { createRouter, createWebHashHistory, RouteRecordRaw } from "vue-router";
import Home from "../views/Home.vue";
import Settings from "../views/Settings.vue";
import Debug from "../views/Debug.vue";
import Flash from "../views/Flash.vue";
import Upload from "../views/Upload.vue";

const routes: Array<RouteRecordRaw> = [
  {
    path: "/",
    name: "Home",
    component: Home,
  },
  {
    path: "/debug",
    name: "Debug",
    component: Debug,
  },
  {
    path: "/flash",
    name: "Flash",
    component: Flash,
  },
  {
    path: "/upload",
    name: "Upload",
    component: Upload,
  },
  {
    path: "/settings",
    name: "Settings",
    component: Settings,
  },
];

const router = createRouter({
  history: createWebHashHistory(),
  routes,
});

export default router;
