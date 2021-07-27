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
 * @file RequestResponseHandler.h
 * @author Luis Moser
 * @brief RequestResponseHandler header
 * @date 07/16/2021
 *
 * @{
 */

#ifndef __REQUESTRESPONSEHANDLER_H__
#define __REQUESTRESPONSEHANDLER_H__

#include <Arduino.h>
#include <SessionManager.h>
#include <EchoDemoCommand.h>
#include <Command.h>
#include <Session.h>

 /** Simple class which handles requests and responses between the API service implementations and the webserver */
class RequestResponseHandler
{
public:
    /** Get the singleton instance of RequestResponseHandler
    *
    * @return Returns the RequestResponseHandler instance
    */
    static RequestResponseHandler& getInstance();

    /**
     * Make a new request to the API
     *
     * @param[in] request Reference to the incoming ApiRequest
     * @param[out] response Reference to the outgoing ApiResponse
     * @param[in] connectionCtx Pointer to Session class instance
     */
    void makeRequest(ApiRequest& request, ApiResponse& response, Session* connectionCtx);

private:
    /**
     * Default Constructor
     */
    RequestResponseHandler();

    /**
     * Destructor
     */
    ~RequestResponseHandler();

    /**
     * Returns pointer to API service class which corresponds to passed service id inside request
     *
     * @param[in] request The API request to be checked for its service id
     * @return Returns pointer to correct service class instance. Returns nullpointer if there is no such service
     */
    Command* getCommandOfApiRequest(ApiRequest& request);

    /** Specifies how many API services are registered */
    static const uint8_t NUMBER_OF_API_SERVICES = 1;

    /** Stores pointers to all registered API services */
    Command* m_apiServices[NUMBER_OF_API_SERVICES];

    /** Instance of SessionManager */
    SessionManager m_sessionManager;
};
#endif /** __REQUESTRESPONSEHANDLER_H__ */
