import { createApp } from "vue";
import App from "./App.vue";
import router from "./router";
import store from "./store/";
import PrimeVue from "primevue/config";

import Card from "primevue/card";
import Button from "primevue/button";
import Dropdown from "primevue/dropdown";
import ToastService from "primevue/toastservice";
import Toast from "primevue/toast";
import InputText from "primevue/inputtext";
import ProgressBar from "primevue/progressbar";
import ProgressSpinner from "primevue/progressspinner";
import Menu from 'primevue/menu';
import Checkbox from 'primevue/checkbox';
import FileUpload from 'primevue/fileupload';

import "primevue/resources/themes/saga-blue/theme.css";
import "primevue/resources/primevue.min.css";
import "primeicons/primeicons.css";

const app = createApp(App);
app.use(store);
app.use(router);
app.use(PrimeVue);
app.use(ToastService)

app.component("Card", Card);
app.component("Button", Button);
app.component("Dropdown", Dropdown);
app.component("Toast", Toast);
app.component("InputText", InputText);
app.component("ProgressBar", ProgressBar);
app.component("ProgressSpinner", ProgressSpinner);
app.component("Toast", Toast);
app.component("Menu", Menu);
app.component("Checkbox", Checkbox);
app.component("FileUpload", FileUpload);

app.mount("#app");
