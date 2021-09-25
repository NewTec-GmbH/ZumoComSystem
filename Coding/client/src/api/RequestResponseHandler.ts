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
import { ResponseCode } from "@/models/ResponseCode";

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
   * @param context The current context (this)
   * @param hideErrors Set to true if errors should be not displayed with toast
   * @return Returns ApiResponse promise
   */
  public async makeRequest(
    request: ApiRequest,
    context: any,
    hideErrors = false
  ): Promise<ApiResponse> {
    return new Promise<ApiResponse>((resolve) => {
      let apiResponse = new ApiResponse();

      /* Send the ApiRequest JSON to the API server */
      if (true === this.m_wsClient.send(JSON.stringify(request))) {
        /* Await the server ApiResponse response */
        this.m_wsClient.onMessage((event: any) => {
          apiResponse = JSON.parse(event.data);

          /* Evalutate the return code */
          if (ResponseCode.SUCCESS === apiResponse.statusCode) {
            Log.debug(
              "Successfully executed ApiRequest command " + request.commandId
            );
            resolve(apiResponse);
          } else if (ResponseCode.UNAUTHORIZED === apiResponse.statusCode) {
            Log.debug(
              "Unauthorized access to ApiRequest command " + request.commandId
            );

            context.$toast.add({
              severity: "warn",
              summary: "Missing Permission",
              detail:
                "You do not have the required permission to execute the command " +
                request.commandId,
              life: 5000,
            });

            if ("null" == context.$store.getters.currentUser) {
              context.$store.commit("setLoginDialogVisibility", true);
            }
            resolve(apiResponse);
          } else {
            if (false === hideErrors) {
              context.$toast.add({
                severity: "error",
                summary: "API Service error",
                detail:
                  "Could not execute command " +
                  request.commandId +
                  "!\nRepsonse Code: " +
                  ResponseCode[apiResponse.statusCode],
                life: 5000,
              });
            }
            resolve(apiResponse);
          }
        });
      } else {
        Log.debug(
          "Fatal server error occured while sending ApiRequest command " +
            request.commandId
        );
        apiResponse.statusCode = ResponseCode.ERROR;

        context.$toast.add({
          severity: "error",
          summary: "Fatal Server Error",
          detail: "A fatal server communication error occured!",
          life: 5000,
        });
        resolve(apiResponse);
      }
    });
  }

  /**
   * Sends a binary data buffer to the WebSocket endpoint
   *
   * @param dataChunk The binary data to be sent to the WebSocket endpoint
   * @param context The current context (this)
   * @return Returns true if successful, else false
   */
  public async sendBinary(
    dataChunk: Uint8Array,
    context: any
  ): Promise<ApiResponse> {
    return new Promise<ApiResponse>((resolve) => {
      let apiResponse = new ApiResponse();

      /* Send the ApiRequest JSON to the API server */
      if (true === this.m_wsClient.send(dataChunk)) {
        /* Await the server ApiResponse response */
        this.m_wsClient.onMessage((event: any) => {
          apiResponse = JSON.parse(event.data);

          /* Evalutate the return code */
          if (ResponseCode.SUCCESS === apiResponse.statusCode) {
            Log.debug(
              "Successfully sent binary chunk with " +
                dataChunk.length +
                " bytes"
            );
          } else if (ResponseCode.UNAUTHORIZED === apiResponse.statusCode) {
            Log.warn("Unauthorized to send binary chunk!");

            context.$toast.add({
              severity: "warn",
              summary: "Missing Permission",
              detail:
                "You do not have the required permission to send binary data!\nRepsonse Code: " +
                ResponseCode[apiResponse.statusCode],
              life: 5000,
            });
          } else {
            context.$toast.add({
              severity: "error",
              summary: "API Service error",
              detail:
                "Could not send binary data!\nRepsonse Code: " +
                ResponseCode[apiResponse.statusCode],
              life: 5000,
            });
          }
          resolve(apiResponse);
        });
      } else {
        Log.error("Fatal server error occured while sending binary data");
        apiResponse.statusCode = ResponseCode.ERROR;

        context.$toast.add({
          severity: "error",
          summary: "Fatal Server Error",
          detail: "A fatal server communication error occured!",
          life: 5000,
        });
        resolve(apiResponse);
      }
    });
  }
}
