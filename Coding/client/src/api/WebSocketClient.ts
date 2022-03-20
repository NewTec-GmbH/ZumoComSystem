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
 * @file WebSocketClient.ts
 * @author Luis Moser
 * @brief WebSocketClient class
 * @date 09/08/2021
 *
 * @{
 */

import Log from "@/utility/Log";

/** Class for connecting to WebSocket servers */
export default class WebSocketClient {
  /** Specifies the host endpoint URL */
  private readonly m_host: string;

  /** WebSocket instance */
  private m_socketClient: WebSocket;

  /** Singleton instance of this class */
  private static m_instance: WebSocketClient;

  /**
   * Default Constructor
   */
  private constructor() {
    this.m_host = "wss://" + location.hostname + "/api";
    /* Connect with specified endpoint */
    this.m_socketClient = new WebSocket(this.m_host);
    Log.debug("Trying to connect to WebSocket host at " + this.m_host);
  }

  /**
   * Returns the instance of WebSocketClient
   * @returns Returns the singleton
   */
  public static getInstance(): WebSocketClient {
    if (!this.m_instance) {
      this.m_instance = new WebSocketClient();
      Log.debug("New WebSocketClient instance created!");
    }
    return this.m_instance;
  }

  /**
   * Register function which is called on WebSocket connection open callback
   * @param fnPtr The function to be registered
   */
  public onOpen(fnPtr: any): void {
    this.m_socketClient.onopen = fnPtr;
  }

  /**
   * Register function which is called on WebSocket connection close callback
   * @param fnPtr The function to be registered
   */
  public onClose(fnPtr: any): void {
    this.m_socketClient.onclose = fnPtr;
  }

  /**
   * Register function which is called on WebSocket connection error callback
   * @param fnPtr The function to be registered
   */
  public onError(fnPtr: any): void {
    this.m_socketClient.onerror = fnPtr;
  }

  /**
   * Registers a new callback which calls the specified function when the WebSocket client
   * receives a new message
   *
   * @param fnPtr The function to be registered
   */
  public onMessage(fnPtr: any): void {
    this.m_socketClient.onmessage = fnPtr;
  }

  /**
   * Closes the opened WebSocket connection
   */
  public disconnect(): void {
    Log.debug("Trying to close WebSocket connection!");
    this.m_socketClient.close();
  }

  /**
   * Returns the WebSocketClient state
   *
   * @returns Returns the current state of the WebSocket connection
   */
  public getState(): number {
    return this.m_socketClient.readyState;
  }

  /**
   * Sends either a string or a byte buffer to the WebSocket endpoint
   *
   * @param payload The data to be transmitted
   * @return Returns true if successful, else false
   */
  public send(payload: string | Uint8Array): boolean {
    let retCode = false;

    if (WebSocket.OPEN == this.getState()) {
      this.m_socketClient.send(payload);
      retCode = true;
    }

    if (false === retCode) {
      Log.error(
        "Could not send WebSocket data because connection is not opened!"
      );
    }
    return retCode;
  }
}
