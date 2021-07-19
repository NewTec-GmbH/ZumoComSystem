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
 * @file Session.cpp
 * @author Luis Moser
 * @brief Session class
 * @date 07/15/2021
 *
 * @{
 */

#include <Session.h>
#include <RequestResponseHandler.h>

Session* Session::m_sessions[MAX_CLIENTS] = {};

uint8_t Session::m_numberOfActiveClients = 0;

Session::Session() :
    m_sessionAuthenticated(false),
    m_lastAccessTime(0)
{
}

Session::~Session()
{
}

httpsserver::WebsocketHandler* Session::create()
{
    Session* newSession = nullptr;
    if (m_numberOfActiveClients < MAX_CLIENTS)
    {
        for (uint8_t sessionIdx = 0; sessionIdx < MAX_CLIENTS; sessionIdx++)
        {
            if (nullptr == m_sessions[sessionIdx])
            {
                newSession = new Session();
                m_sessions[sessionIdx] = newSession;
                m_numberOfActiveClients++;
                break;
            }
        }
        LOG_INFO("New websocket session successfully opened!");
    }
    return newSession;
}

void Session::onMessage(httpsserver::WebsocketInputStreambuf* inputBuffer)
{
    LOG_DEBUG("New session message received!");

    /* Update timestamp */
    m_lastAccessTime = millis();

    /* Get the request payload text */
    std::ostringstream stringStream;
    stringStream << inputBuffer;
    std::string str = stringStream.str();
    LOG_DEBUG(String("Incoming request data:\n") + str.c_str());

    ApiResponse response;
    ApiRequest request;

    if (true == request.deserialize(str.c_str()))
    {
        /* Invoke the API call and send back response */
        RequestResponseHandler::getInstance().makeRequest(request, response, this);
    }
    else
    {
        response.setStatusCode(BAD_REQUEST);
    }
    send(response.serialize().c_str(), SEND_TYPE_TEXT);
}

void Session::onClose()
{
    LOG_INFO("Session closed!");

    /* Find this session in the sessions list and remove it */

    for (uint8_t sessionIdx = 0; sessionIdx < MAX_CLIENTS; sessionIdx++)
    {
        if (this == m_sessions[sessionIdx])
        {
            /* No need to delete instance, as this has already been done by HTTPConnection class */
            m_sessions[sessionIdx] = nullptr;
            m_numberOfActiveClients--;
            break;
        }
    }
}
