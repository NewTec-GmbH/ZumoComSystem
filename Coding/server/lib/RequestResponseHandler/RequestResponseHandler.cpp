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
 * @file RequestResponseHandler.cpp
 * @author Luis Moser
 * @brief RequestResponseHandler class
 * @date 07/16/2021
 *
 * @{
 */

#include <RequestResponseHandler.h>

RequestResponseHandler::RequestResponseHandler() :
    m_apiServices{new EchoDemoCommand()},
    m_sessionManager()
{
}

RequestResponseHandler::~RequestResponseHandler()
{
    for (uint8_t apiServiceIdx = 0; apiServiceIdx < NUMBER_OF_API_SERVICES; apiServiceIdx++)
    {
        delete m_apiServices[apiServiceIdx];
    }
}

RequestResponseHandler& RequestResponseHandler::getInstance()
{
    static RequestResponseHandler instance;
    return instance;
}

void RequestResponseHandler::makeRequest(ApiRequest& request, ApiResponse& response, Session* connectionCtx)
{
    if (request.getCommandId() == "authenticate")
    {
        m_sessionManager.aquireSession(request, response, connectionCtx);
    }
    else
    {
        Command* apiService = getCommandOfApiRequest(request);
        if (nullptr != apiService)
        {
            if (NONE != apiService->getReqPermission())
            {
                if (true == m_sessionManager.checkSession(apiService, connectionCtx))
                {
                    apiService->run(request, response);
                }
                else
                {
                    response.setStatusCode(UNAUTHORIZED);
                }
            }
            else
            {
                apiService->run(request, response);
            }
        }
        else
        {
            response.setStatusCode(NOT_IMPLEMENTED);
        }
    }
}

Command* RequestResponseHandler::getCommandOfApiRequest(ApiRequest& request)
{
    Command* command = nullptr;
    if (request.getCommandId() == "echodemo")
    {
        command = m_apiServices[0];
    }
    return command;
}
