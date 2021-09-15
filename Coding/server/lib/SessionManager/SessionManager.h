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
 * @file SessionManager.h
 * @author Luis Moser
 * @brief SessionManager header
 * @date 07/16/2021
 *
 * @{
 */

#ifndef __SESSIONMANAGER_H__
#define __SESSIONMANAGER_H__


#include <Arduino.h>
#include <Store.h>
#include <Session.h>
#include <ApiRequest.h>
#include <ApiResponse.h>
#include <Command.h>
#include <BinaryCommand.h>

 /** Simple class for managing the websocket sessions */
class SessionManager
{
public:
    /**
     * Default Constructor
     */
    SessionManager();

    /**
     * Desturctor
     */
    ~SessionManager();

    /**
     * Checks if the current session is authorized to invoke the specified API service
     *
     * @param[in] command Pointer to command which needs to be invoked
     * @param[in] connectionCtx Pointer to the currently used session whose permissions should be checked
     *
     * @return Returns true if successful, else false
     */
    bool checkSession(const Command* const command, Session* connectionCtx) const;

    /**
     * Checks if the current session is authorized to invoke the specified API service
     *
     * @param[in] command Pointer to command which needs to be invoked
     * @param[in] connectionCtx Pointer to the currently used session whose permissions should be checked
     *
     * @return Returns true if successful, else false
     */
    bool checkSession(const BinaryCommand* command, Session* connectionCtx) const;

    /**
     * Requests authentication for this session. Remembers user and its permissions
     *
     * @param[in] request The authentication request including the user credentials to be checked
     * @param[out] response Reference to the ApiResponse
     * @param[in] connectionCtx Pointer to the currently used session which should get authenticated
     */
    void aquireSession(const ApiRequest& request, ApiResponse& response, Session* connectionCtx) const;

    /**
     * Request for invalidation for this session
     *
     * @param[out] response Reference to the ApiResponse
     * @param[in] connectionCtx Pointer to the currently used session which should get authenticated
     */
    void invalidateSession(ApiResponse& response, Session* connectionCtx);
};
#endif /** __SESSIONMANAGER_H__ */
