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
#include <Log.h>

Session* Session::m_sessions[MAX_CLIENTS] = {nullptr};
uint8_t Session::m_numberOfActiveClients = 0;
SemaphoreHandle_t Session::m_sessionMutex = xSemaphoreCreateMutex();

Session::Session() :
    m_sessionAuthenticated(false),
    m_linkedUser(nullptr),
    m_lastAccessTime(0)
{
}

Session::~Session()
{
}

bool Session::start()
{
    if (nullptr == m_sessionMutex)
    {
        LOG_ERROR("IO mutex could not be created!");
    }

    /* Small stack sufficient */
    const uint16_t STACK_SIZE_BYTE = 4096;

    /* Use rather high priority to ensure that session are always timed out */
    const uint8_t PRIORITY = configMAX_PRIORITIES - 2;

    BaseType_t retCode = xTaskCreate(
        handleSessionTimeout,
        "HandleSessionTimeout",
        STACK_SIZE_BYTE,
        nullptr,
        PRIORITY,
        nullptr);

    return (pdPASS == retCode);
}

httpsserver::WebsocketHandler* Session::create()
{
    Session* newSession = nullptr;
    xSemaphoreTake(m_sessionMutex, portMAX_DELAY);
    if (m_numberOfActiveClients < MAX_CLIENTS)
    {
        for (uint8_t sessionIdx = 0; sessionIdx < MAX_CLIENTS; sessionIdx++)
        {
            if (nullptr == m_sessions[sessionIdx])
            {
                newSession = new Session();
                if (nullptr != newSession)
                {
                    m_sessions[sessionIdx] = newSession;
                    m_numberOfActiveClients++;
                }
                else
                {
                    LOG_ERROR("Out of memory. Could not create new session!");
                }
                break;
            }
        }
        LOG_INFO("New websocket session successfully opened!");
    }
    xSemaphoreGive(m_sessionMutex);
    return newSession;
}

void Session::onMessage(httpsserver::WebsocketInputStreambuf* inputBuffer)
{
    ApiResponse response;
    ApiRequest request;
    std::ostringstream stringStream;
    std::string inputString;
    String serialResponse;

    LOG_DEBUG("New session message received!");

    /* Update timestamp */
    m_lastAccessTime = millis();

    /* Get the request payload text */
    stringStream << inputBuffer;
    inputString = stringStream.str();
    LOG_DEBUG(String("Incoming request data:\n") + inputString.c_str());

    String serial = inputString.c_str();
    if (true == request.deserialize(serial))
    {
        /* Invoke the API call and send back response */
        RequestResponseHandler::getInstance().makeRequest(request, response, this);
    }
    else
    {
        response.setStatusCode(BAD_REQUEST);
    }

    if (false == response.serialize(serialResponse))
    {
        serialResponse = "{\\\"statusCode\\\":" + String(ERROR) + "}";
    }
    send(serialResponse.c_str(), SEND_TYPE_TEXT);
}

void Session::onClose()
{
    /* Find this session in the sessions list and remove it */
    xSemaphoreTake(m_sessionMutex, portMAX_DELAY);
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
    xSemaphoreGive(m_sessionMutex);
    LOG_INFO("Session closed!");
}

bool Session::isAuthenticated() const
{
    return m_sessionAuthenticated;
}

void Session::authenticateSession(User* user)
{
    m_sessionAuthenticated = true;
    m_linkedUser = user;
}

void Session::deauthenticateSession()
{
    m_sessionAuthenticated = false;
}

void Session::handleSessionTimeout(void* parameter)
{
    Session* currentSession = nullptr;
    const uint16_t MILLISECONDS = 1000;

    while (true)
    {
        unsigned long currentTimeStamp = millis();
        xSemaphoreTake(m_sessionMutex, portMAX_DELAY);
        for (uint8_t sessionIdx = 0; sessionIdx < MAX_CLIENTS; sessionIdx++)
        {
            currentSession = m_sessions[sessionIdx];

            /* Check if the session exists or has been stopped before timeout */
            if (nullptr != currentSession)
            {
                if (((currentTimeStamp - currentSession->m_lastAccessTime) / MILLISECONDS) > SESSION_TIMEOUT_SECONDS)
                {
                    currentSession->deauthenticateSession();
                }
            }
        }
        xSemaphoreGive(m_sessionMutex);

        /* Put task to sleep and re-check after SESSION_TIMEOUT_SECONDS */
        delay(SESSION_TIMEOUT_SECONDS * MILLISECONDS);
    }
}

const Permission* Session::getPermissions(uint8_t& numberOfPermissions)
{
    const Permission* permission = nullptr;
    xSemaphoreTake(m_sessionMutex, portMAX_DELAY);
    if (nullptr != m_linkedUser)
    {
        permission = m_linkedUser->getPermissions(numberOfPermissions);
    }
    xSemaphoreGive(m_sessionMutex);
    return permission;
}
