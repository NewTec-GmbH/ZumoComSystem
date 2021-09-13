/*
BSD 3-Clause License

Copyright (c) 2021, NewTec GmbH
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @file RequestResponseHandler.ts
 * @author Luis Moser
 * @brief RequestResponseHandler class
 * @date 09/08/2021
 *
 * @{
 */

import WebSocketClient from "@/api/WebSocketClient";
import Log from "@/utility/Log";
import { ApiResponse } from "@/models/ApiResponse";
import { ApiRequest } from "@/models/ApiRequest";

/** Class for accessing the backend WebSocket API and calling the API services */
export default class RequestResponseHandler {
    /** WebSocketClient instance */
    private m_wsClient: WebSocketClient;

    /** RequestResponseHandler singleton instance */
    private static m_reqResHandler = new RequestResponseHandler();

    /**
     * Default Constructor
     */
    private constructor() {
        this.m_wsClient = WebSocketClient.getInstance();
    }

    /**
     * Returns the singleton instance
     * 
     * @returns Returns the RequestResponseHandler instance
     */
    public static getInstance(): RequestResponseHandler {
        return this.m_reqResHandler;
    }

    /**
     * Makes a new request to the WebSocket backend API
     * 
     * @param request The ApiRequest to be invoked
     * @return Returns true if successful, else false
     */
    public makeRequest(request: ApiRequest): boolean {
        const json = JSON.stringify(request);
        const retCode = this.m_wsClient.send(json);

        if (false === retCode) {
            Log.error("Could not send request because WebSocketClient is not opened!");
        }
        return retCode;
    }

    /**
     * Sends a binary data buffer to the WebSocket endpoint
     * 
     * @param dataChunk The binary data to be sent to the WebSocket endpoint
     * @return Returns true if successful, else false
     */
    public sendBinary(dataChunk: Uint8Array): boolean {
        const retCode = this.m_wsClient.send(dataChunk);

        if (false === retCode) {
            Log.error("Could not send request because WebSocketClient is not opened!");
        }
        return retCode;
    }

    /**
     * Registers a new callback function when the WebSocket client receives a new response
     * 
     * @param fnPtr The function to be registered for callback
     */
    public onResponse(fnPtr: any): void {
        this.m_wsClient.onMessage(fnPtr);
    }
}