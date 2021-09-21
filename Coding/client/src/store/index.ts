import { createStore } from "vuex";

const store = createStore({
  state: {
    /** The currently logged in user/username */
    currentUser: String,

    /** The global device selection */
    seletedDevice: String,

    /** Specifies if login dialog should be showed */
    showLoginDialg: Boolean,
  },
  mutations: {
    setUser(state, username) {
      state.currentUser = username;
    },

    setDevice(state, device) {
      state.seletedDevice = device;
    },

    setLoginDialogVisibility(state, visible) {
      state.showLoginDialg = visible;
    },
  },
  getters: {
    currentUser: (state) => {
      return state.currentUser;
    },

    selectedDevice: (state) => {
      return state.seletedDevice;
    },

    loginDialogVisible: (state) => {
      return state.showLoginDialg;
    },
  },
});
export default store;
