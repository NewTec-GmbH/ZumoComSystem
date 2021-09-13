import { createStore } from 'vuex'

const store = createStore({
  state: {
    currentUser: String,
    seletedDevice: String,
    showLoginDialg: Boolean,
  },
  mutations: {
    setUser(state, username) {
      state.currentUser = username;
    },

    setDevice(state, device) {
      state.seletedDevice = device;
      console.log(device);
    },

    setLoginDialogVisibility(state, visible) {
      state.showLoginDialg = visible;
    }
  },
  actions: {},
  modules: {},
  getters: {
    currentUser: state => {
      return state.currentUser;
    },

    selectedDevice: state => {
      return state.seletedDevice;
    },

    loginDialogVisible: state => {
      return state.showLoginDialg;
    }
  }
});

export default store
