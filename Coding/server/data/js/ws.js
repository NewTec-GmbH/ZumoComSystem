/*
    NewTec GmbH 2022   -   www.newtec.de
    https://github.com/NewTec-GmbH/ZumoComSystem
*/

// Module definition
var cpjs = cpjs | {};

// Definition of Websocket
cpjs = {
    ws: {}
};

// Constructor of Websocket Client
cpjs.ws.Client = function (options) {

    this.socket = null;
    this.cmdQueue = [];
    this.pendingCmd = null;
    this.onEvent = null;

    this._sendCmdFromQueue = function () {
        var msg = "";

        if (0 < this.cmdQueue.length) {
            this.pendingCmd = this.cmdQueue.shift();
            if ("uploadChunk" == this.pendingCmd.commandId) {
                msg = Uint8Array.from(this.pendingCmd.jsonPayload);
            }
            else {
                msg = JSON.stringify({
                    commandId: this.pendingCmd.commandId,
                    jsonPayload: this.pendingCmd.jsonPayload
                });
            }
            
            this.socket.send(msg);

            console.info("Command sent: " + this.pendingCmd.commandId);
        }
    };

    this._sendCmd = function (cmd) {

        this.cmdQueue.push(cmd);

        if (null === this.pendingCmd) {
            this._sendCmdFromQueue();
        }
    };

    this._sendEvt = function (evt) {
        if (null !== this.onEvent) {
            this.onEvent(evt);
        }
    }
};

// Connect Websocket to Server
cpjs.ws.Client.prototype.connect = function (options) {
    return new Promise(function (resolve, reject) {
        var wsUrl;

        if (("string" !== typeof options.protocol) ||
            ("string" !== typeof options.hostname) ||
            ("number" !== typeof options.port) ||
            ("string" !== typeof options.endpoint)) {

            reject();
        } else {

            if ("function" === typeof options.onEvent) {
                this.onEvent = options.onEvent;
            }

            try {
                wsUrl = options.protocol + "://" + options.hostname + ":" + options.port + options.endpoint;
                this.socket = new WebSocket(wsUrl);

                this.socket.onopen = function (openEvent) {
                    console.debug("Websocket opened.");
                    resolve(this);
                }.bind(this);

                this.socket.onclose = function (closeEvent) {
                    console.debug("Websocket closed.");
                    if ("function" === typeof options.onClosed) {
                        options.onClosed();
                    }

                    options.evtCallback = null;
                };

                this.socket.onmessage = function (messageEvent) {
                    console.debug("Websocket message: " + messageEvent.data);
                    this._onMessage(messageEvent.data);
                }.bind(this);

            } catch (exception) {
                console.error(exception);
                options.evtCallback = null;
                reject();
            }
        }
    }.bind(this));
};

// Handler of Websocket Messages
cpjs.ws.Client.prototype._onMessage = function (msg) {
    if (null === this.pendingCmd) {
        console.error("No pending command, but response received.");
    }
    else {
        var data = JSON.parse(msg);

        if (200 == data.statusCode) {
            console.log("Response received for command: " + this.pendingCmd.commandId);
            if ("undefined" !== typeof data.jsonPayload) {
                // JSON Payload is received
                this.pendingCmd.resolve(JSON.parse(data.jsonPayload));
            }
            else {
                // No JSON Payload received
                this.pendingCmd.resolve();
            }
        } else {
            console.error("Command " + this.pendingCmd.commandId + " failed.");
            this.pendingCmd.reject(data.statusCode);
        }

        this.pendingCmd = null;
    }

    this._sendCmdFromQueue();
    return;
};

// API Command: Get Firmware Information (targetSystem, payloadHash, isValid, sizeBytes)
cpjs.ws.Client.prototype.getFirmwareInfo = function (target) {
    return new Promise(function (resolve, reject) {
        if ((null === this.socket) || (typeof (target) === undefined)) {
            reject();
        } else {
            this._sendCmd({
                commandId: "getfirmwareinfo",
                jsonPayload: "{\"target\":\"" + target + "\"}",
                resolve: resolve,
                reject: reject
            });
        }
    }.bind(this));
};

// API Command: Log-in user
cpjs.ws.Client.prototype.authenticate = function(username, password) {
    return new Promise(function (resolve, reject) {
        if ((null === this.socket) || (typeof (username) === undefined) || (typeof (password) === undefined)) {
            reject();
        } else {
            this._sendCmd({
                commandId: "authenticate",
                jsonPayload: "{\"username\":\"" + username + "\", \"password\":\"" + password + "\"}",
                resolve: resolve,
                reject: reject
            });
        }
    }.bind(this));
};

// API Command: Log-out user
cpjs.ws.Client.prototype.deauthenticate = function() {
    return new Promise(function (resolve, reject) {
        if ((null === this.socket)) {
            reject();
        } else {
            this._sendCmd({
                commandId: "deauthenticate",
                jsonPayload: "",
                resolve: resolve,
                reject: reject
            });
        }
    }.bind(this));
};

// API Command: Flash Zumo
cpjs.ws.Client.prototype.flash = function(targetPlatform) {
    return new Promise(function (resolve, reject) {
        if ((null === this.socket) || (typeof (targetPlatform) === undefined)) {
            reject();
        } else {
            this._sendCmd({
                commandId: (("ZUMO" == targetPlatform) ? "flashzumo" : "flashcom"),
                jsonPayload: "",
                resolve: resolve,
                reject: reject
            });
        }
    }.bind(this));
};

// API Command: Upload Firmware
cpjs.ws.Client.prototype.upload = function(sizeBytes, targetPlatform) {
    return new Promise(function (resolve, reject) {
        if ((null === this.socket) || (typeof (sizeBytes) === undefined) || (typeof (targetPlatform) === undefined)) {
            reject();
        } else {
            this._sendCmd({
                commandId: (("ZUMO" == targetPlatform) ? "uploadzumo" : "uploadcom"),
                jsonPayload: "{\"fileSizeBytes\":\"" + sizeBytes + "\"}",
                resolve: resolve,
                reject: reject
            });
        }
    }.bind(this));
};

// API Command: Upload Binary Chunks
cpjs.ws.Client.prototype.uploadChunk = function(dataChunk) {
    return new Promise(function (resolve, reject) {
        if ((null === this.socket) || (typeof (dataChunk) === undefined)) {
            reject();
        } else {
            this._sendCmd({
                commandId: "uploadChunk",
                jsonPayload: Uint8Array.from(dataChunk), // Keeping name even if it is not JSON Format in order to prevent exception-handling.
                resolve: resolve,
                reject: reject
            });
        }
    }.bind(this));
};

// API Command: Reboot
cpjs.ws.Client.prototype.reboot = function(targetPlatform) {
    return new Promise(function (resolve, reject) {
        if ((null === this.socket) || (typeof (targetPlatform) === undefined)) {
            reject();
        } else {
            this._sendCmd({
                commandId: (("ZUMO" == targetPlatform) ? "rebootzumo" : "rebootcom"),
                jsonPayload: "",
                resolve: resolve,
                reject: reject
            });
        }
    }.bind(this));
};

// API Command: Echo Demo
cpjs.ws.Client.prototype.echodemo = function() {
    return new Promise(function (resolve, reject) {
        if ((null === this.socket)) {
            reject();
        } else {
            this._sendCmd({
                commandId: "echodemo",
                jsonPayload: "Albert Einstein",
                resolve: resolve,
                reject: reject
            });
        }
    }.bind(this));
};

// API Command: Set STA Credentials
cpjs.ws.Client.prototype.setstacredentials = function(ssid, passphrase) {
    return new Promise(function (resolve, reject) {
        if ((null === this.socket) || (typeof (ssid) === undefined) || (typeof (passphrase) === undefined)) {
            reject();
        } else {
            this._sendCmd({
                commandId: "setstacredentials",
                jsonPayload: "{\"ssid\":\"" + ssid + "\", \"passphrase\":\"" + passphrase + "\"}",
                resolve: resolve,
                reject: reject
            });
        }
    }.bind(this));
};

// API Command: Set LED Status
cpjs.ws.Client.prototype.setledstatus = function(led, status) {
    return new Promise(function (resolve, reject) {
        if ((null === this.socket) || (typeof (led) === undefined) || (typeof (status) === undefined)) {
            reject();
        } else {
            this._sendCmd({
                commandId: "setledstatus",
                jsonPayload: "{\"led\":\"" + led + "\", \"status\":\"" + status + "\"}",
                resolve: resolve,
                reject: reject
            });
        }
    }.bind(this));
};