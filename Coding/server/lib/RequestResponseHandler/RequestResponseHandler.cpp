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
#include <Log.h>

RequestResponseHandler::RequestResponseHandler() :
    m_echoDemoCommand(),
    m_sessionManager()
{
}

RequestResponseHandler::~RequestResponseHandler()
{
}

RequestResponseHandler& RequestResponseHandler::getInstance()
{
    static RequestResponseHandler instance;
    return instance;
}

void RequestResponseHandler::makeRequest(const ApiRequest& request, ApiResponse& response, Session* connectionCtx)
{
    if (request.getCommandId() == "authenticate")
    {
        m_sessionManager.aquireSession(request, response, connectionCtx);
    }
    else
    {
        const Command* apiService = getCommandOfApiRequest(request);
        if (nullptr != apiService)
        {
            if (NONE != apiService->getReqPermission())
            {
                if (true == m_sessionManager.checkSession(apiService, connectionCtx))
                {
                    apiService->run(request, response, connectionCtx);
                }
                else
                {
                    response.setStatusCode(UNAUTHORIZED);
                }
            }
            else
            {
                apiService->run(request, response, connectionCtx);
            }
        }
        else
        {
            LOG_ERROR(String("Service ") + request.getCommandId() + String(" is not implemented!"));
            response.setStatusCode(NOT_IMPLEMENTED);
        }
    }
}

void RequestResponseHandler::makeRequest(const String& commandId, ApiResponse& response, Session* connectionCtx)
{
    BinaryCommand* apiService = getCommandOfBinaryApiRequest(commandId);
    if (nullptr != apiService)
    {
        if (NONE != apiService->getBinaryReqPermission())
        {
            if (true == m_sessionManager.checkSession(apiService, connectionCtx))
            {
                apiService->run(response, connectionCtx);
            }
            else
            {
                response.setStatusCode(UNAUTHORIZED);

                /* Clean up */
                resetBinaryMode();

                /* Exit BINARY mode and switch back to TEXT mode */
                connectionCtx->exitBinaryMode();
            }
        }
        else
        {
            apiService->run(response, connectionCtx);
        }
    }
    else
    {
        LOG_ERROR(String("Service ") + commandId + String(" is not implemented!"));
        response.setStatusCode(NOT_IMPLEMENTED);

        /* Clean up */
        resetBinaryMode();

        /* Exit BINARY mode and switch back to TEXT mode */
        connectionCtx->exitBinaryMode();
    }
}

void RequestResponseHandler::resetBinaryMode()
{
    m_uploadZumoCommand.reset();
    LOG_INFO("API BINARY mode has been reset in RequestResponseHandler!");
}

const Command* RequestResponseHandler::getCommandOfApiRequest(const ApiRequest& request)
{
    const Command* command = nullptr;
    const String commandID = request.getCommandId();
    if (commandID == "uploadzumo")
    {
        command = &m_uploadZumoCommand;
    }
    else if (commandID == "echodemo")
    {
        command = &m_echoDemoCommand;
    }
    return command;
}

BinaryCommand* RequestResponseHandler::getCommandOfBinaryApiRequest(const String& commandId)
{
    BinaryCommand* command = nullptr;
    if (commandId == "uploadzumo")
    {
        command = &m_uploadZumoCommand;
    }
    return command;
}
