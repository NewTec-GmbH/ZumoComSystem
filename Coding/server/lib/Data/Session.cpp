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
 * @addtogroup Data
 * @{
 */

#include <Session.h>
#include <RequestResponseHandler.h>
#include <Log.h>
#include <iostream>

Session* Session::m_sessions[MAX_CLIENTS] = {nullptr};
uint8_t Session::m_numberOfActiveClients = 0;
SemaphoreHandle_t Session::m_sessionMutex = xSemaphoreCreateMutex();
static const String binaryIsReady = "BinaryFileIsReady";

Session::Session() :
    m_readBytes(0),
    m_streamByteIdx(0),
    m_expectingBytes(0),
    m_binaryBuffer(),
    m_expectBinary(false),
    m_expectedOperation(),
    m_sessionAuthenticated(false),
    m_linkedUser(nullptr),
    m_lastAccessTime(0),
    m_messageQueue(nullptr)
{
    m_messageQueue = xQueueCreate( 10, sizeof( char* ) );
}

Session::~Session()
{
    vQueueDelete( m_messageQueue );
}

bool Session::start()
{
    if (nullptr == m_sessionMutex)
    {
        LOG_ERROR("IO mutex could not be created!");
    }

    /* Small stack sufficient */
    /* Stack Size increased for WS message and API handling*/
    const uint16_t STACK_SIZE_BYTE = 8192;

    /* Use rather high priority to ensure that session are always timed out */
    const uint8_t PRIORITY = configMAX_PRIORITIES - 2;

    BaseType_t retCode = xTaskCreate(
        handleSession,
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
                newSession = new(std::nothrow) Session();
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
    String serialResponse;
    uint32_t messageSizeBytes = inputBuffer->getRecordSize();
    unsigned long readBufferStartTime = 0;
    char singleByteBuffer;

    LOG_INFO("New session message received!");
    LOG_INFO(String("API-Mode: ") + (true == m_expectBinary ? "BINARY_STREAM" : "TEXT"));

    /* Update timestamp */
    m_lastAccessTime = millis();

    if (true == m_expectBinary)
    {
        m_readBytes = 0;

        uint32_t recordSize = inputBuffer->getRecordSize();
        if (MAX_BUFFER_SIZE_BYTE >= recordSize)
        {
            std::istream inputStream{inputBuffer};
            while (m_readBytes < recordSize)
            {
                readBufferStartTime = millis();
                do
                {
                    if (true == inputStream.eof() && false == inputStream.bad())
                    {
                        LOG_WARN("Unexpected EOF in binary data stream prior actual EOF. Resetting EOF flag and trying again...");
                        inputStream.clear();
                    }
                    singleByteBuffer = inputStream.get();
                } while ((true == inputStream.eof()) && ((millis() - readBufferStartTime) < API_TIMEOUT_MS));

                if (false == inputStream.eof())
                {
                    m_binaryBuffer[m_readBytes] = singleByteBuffer;
                    m_readBytes++;
                    m_streamByteIdx++;
                }
                else
                {
                    break;
                }
            }

            /* All bytes of the websocket message have been successfully read */
            if (m_readBytes == recordSize)
            {
                
                char* cmdStr = new char[binaryIsReady.length() + 1];

                if (nullptr != cmdStr)
                {
                    strcpy(cmdStr, binaryIsReady.c_str());

                    if (pdFALSE == xQueueSend(m_messageQueue, &cmdStr, portMAX_DELAY))
                    {
                        LOG_ERROR("Could not deserialize the incoming ApiResponse!");
                        response.setStatusCode(BAD_REQUEST);
                        LOG_ERROR("Could not push message to Queue");
                    }
                }
                else
                {
                    response.setStatusCode(ERROR);
                    LOG_ERROR("Command (cmdStr) is nullptr");
                }
            }
            else
            {
                /* Clean up */
                RequestResponseHandler::getInstance().resetBinaryMode();

                /* Exit BINARY mode and switch back to TEXT mode */
                exitBinaryMode();

                response.setStatusCode(ERROR);
                LOG_ERROR("Could not read entire websocket buffer binary stream! Request discarded!");
            }
        }
        else
        {
            /* Clean up */
            RequestResponseHandler::getInstance().resetBinaryMode();

            /* Exit BINARY mode and switch back to TEXT mode */
            exitBinaryMode();

            response.setStatusCode(BAD_REQUEST);
            LOG_ERROR(String("Input record bigger than input buffer. Discarding data!. Please decrease record size! Max buffer size: ") + MAX_BUFFER_SIZE_BYTE);
        }
    }
    else
    {
        ApiRequest request;
        std::ostringstream stringStream;
        std::string inputString;

        if (messageSizeBytes <= MAX_TEXT_REQUEST_SIZE_BYTE)
        {
            /* Read entire buffer. Get the request payload text */
            stringStream << inputBuffer;
            inputString = stringStream.str();
            LOG_DEBUG(String("Incoming request data:\n") + inputString.c_str());        

            char* cmdStr = new char[inputString.length() + 1];

            if (nullptr != cmdStr)
            {
                strcpy(cmdStr, inputString.c_str());

                if (pdFALSE == xQueueSend(m_messageQueue, &cmdStr, portMAX_DELAY))
                {
                    response.setStatusCode(BAD_REQUEST);
                    LOG_ERROR("Could not push message to Queue");
                }
            }
            else
            {
                response.setStatusCode(ERROR);
                LOG_ERROR("Command (cmdStr) is nullptr");
            }
        }
        else
        {
            LOG_ERROR("Exceeded MAX_TEXT_REQUEST_SIZE_BYTE for API TEXT mode!");
            response.setStatusCode(BAD_REQUEST);
        }
    }

    /* Clear the input buffer */
    inputBuffer->discard();

    if((ERROR == response.getStatusCode()) || (BAD_REQUEST == response.getStatusCode()))
    {
        if (false == response.serialize(serialResponse))
        {
            serialResponse = "{\\\"statusCode\\\":" + String(ERROR) + "}";
            LOG_ERROR("Could not serialize the outgoing ApiResponse!");
        }

        /* Always send the ApiResponse */
        send(serialResponse.c_str(), SEND_TYPE_TEXT);
    }
}

void Session::onClose()
{
    /* Find this session in the sessions list and remove it */
    xSemaphoreTake(m_sessionMutex, portMAX_DELAY);
    for (uint8_t sessionIdx = 0; sessionIdx < MAX_CLIENTS; sessionIdx++)
    {
        if (this == m_sessions[sessionIdx])
        {
            if (true == m_expectBinary)
            {
                /* Clean up */
                RequestResponseHandler::getInstance().resetBinaryMode();

                /* Exit BINARY mode and switch back to TEXT mode */
                exitBinaryMode();
            }

            /* No need to delete instance, as this has already been done by HTTPConnection class */
            m_sessions[sessionIdx] = nullptr;
            m_numberOfActiveClients--;
            break;
        }
    }
    xSemaphoreGive(m_sessionMutex);
    LOG_INFO("Session closed!");
}

void Session::initBinaryMode(const String& operation, const uint32_t binarySize)
{
    /* Enable BINARY mode and set operation and binary stream size */
    m_expectBinary = true;
    m_expectedOperation = operation;
    m_expectingBytes = binarySize;

    /* Clear all indexes and buffers used for BINARY mode */
    m_readBytes = 0;
    m_streamByteIdx = 0;
    memset(m_binaryBuffer, 0, sizeof(m_binaryBuffer));

    LOG_INFO("Switching API to BINARY mode now!");
    LOG_INFO(String("Expecting ") + binarySize + String(" bytes during this session"));
}

void Session::exitBinaryMode()
{
    m_expectBinary = false;
    LOG_INFO("Switching API back to TEXT mode now!");
}

bool Session::isAuthenticated() const
{
    return m_sessionAuthenticated;
}

void Session::authenticateSession(User* user)
{
    if (nullptr != user)
    {
        m_sessionAuthenticated = true;
        m_linkedUser = user;
        LOG_INFO(String("Successfully authenticated a session for the user ") + user->getUsername());
    }
}

void Session::deauthenticateSession()
{
    if (true == m_sessionAuthenticated)
    {
        m_sessionAuthenticated = false;
        if (nullptr != m_linkedUser)
        {
            LOG_INFO(String("Session of user ") + m_linkedUser->getUsername() + String(" has been de-authenticated!"));
        }
    }
    else
    {
        if (nullptr != m_linkedUser)
        {
            LOG_WARN(String("Session of user ") + m_linkedUser->getUsername() + String(" is (already) not authenticated!"));
        }
    }
}

void Session::handleSession(void* parameter)
{
    Session* currentSession = nullptr;
    const uint16_t MILLISECONDS = 1000;
    unsigned long lastSessionTimeoutCheck = 0;
    unsigned long currentTimeStamp = 0;

    (void)parameter;

    while (true)
    {
        currentTimeStamp = millis();

        xSemaphoreTake(m_sessionMutex, portMAX_DELAY);
        // Check Session Timeout
        if ((currentTimeStamp - lastSessionTimeoutCheck) >= (SESSION_TIMEOUT_SECONDS * MILLISECONDS))
        {
            lastSessionTimeoutCheck = currentTimeStamp;

            for (uint8_t sessionIdx = 0; sessionIdx < MAX_CLIENTS; sessionIdx++)
            {
                currentSession = m_sessions[sessionIdx];

                /* Check if the session exists or has been stopped before timeout */
                if (nullptr != currentSession)
                {
                    if (((currentTimeStamp - currentSession->m_lastAccessTime) / MILLISECONDS) > SESSION_TIMEOUT_SECONDS)
                    {
                        currentSession->deauthenticateSession();

                        /* Switch back to TEXT mode and clean up used resources */
                        if (true == currentSession->m_expectBinary)
                        {
                            /* Clean up */
                            RequestResponseHandler::getInstance().resetBinaryMode();

                            /* Exit BINARY mode and switch back to TEXT mode */
                            currentSession->exitBinaryMode();
                        }
                    }
                }
            }
        }

        // Check WS Messages
        for (uint8_t sessionIdx = 0; sessionIdx < MAX_CLIENTS; sessionIdx++)
        {
            currentSession = m_sessions[sessionIdx];

            /* Check if the session exists or has been stopped before timeout */
            if (nullptr != currentSession)
            {
                char* cmdStr = nullptr;

                if (pdFALSE != xQueueReceive(currentSession->m_messageQueue, &cmdStr, 0))
                {
                    ApiResponse response;
                    String serialResponse;

                    LOG_DEBUG("Message Retreived!");

                    response.setStatusCode(SUCCESS);

                    if ((true == currentSession->m_expectBinary) && (0 == strcmp(cmdStr, binaryIsReady.c_str())))
                    {
                        LOG_DEBUG("Binary is expected and ready!");
                        /* Call the API service */
                        RequestResponseHandler::getInstance().makeRequest(currentSession->m_expectedOperation, response, currentSession);

                    }
                    else if ((false == currentSession->m_expectBinary) && (0 == strcmp(cmdStr, binaryIsReady.c_str())))
                    {
                        LOG_ERROR("Something went wrong here!");
                    }
                    else
                    {
                        ApiRequest request;
                        if (true == request.deserialize(String(cmdStr)))
                        {
                            LOG_DEBUG("Calling API");
                            /* Invoke the API call and send back response */
                            RequestResponseHandler::getInstance().makeRequest(request, response, currentSession);
                            LOG_DEBUG("API Finished");
                        }
                        else
                        {
                            LOG_ERROR("Could not deserialize the incoming ApiResponse!");
                            response.setStatusCode(BAD_REQUEST);
                        }
                    }


                    if (false == response.serialize(serialResponse))
                    {
                        serialResponse = "{\\\"statusCode\\\":" + String(ERROR) + "}";
                        LOG_ERROR("Could not serialize the outgoing ApiResponse!");
                    }

                    /* Always send the ApiResponse */
                    currentSession->send(serialResponse.c_str(), SEND_TYPE_TEXT);

                    /* Clean */
                    delete[] cmdStr;
                }
            }
        }
        xSemaphoreGive(m_sessionMutex);
        vTaskDelay(250 / portTICK_PERIOD_MS);
    }
}

const Permission* Session::getPermissions(uint8_t& numberOfPermissions)
{
    const Permission* permission = nullptr;

    /* Removed Conflicting Semaphore. handleSession Task has the Mutex when this method is called.*/

    // xSemaphoreTake(m_sessionMutex, portMAX_DELAY);

    if (nullptr != m_linkedUser)
    {
        permission = m_linkedUser->getPermissions(numberOfPermissions);
    }
    // xSemaphoreGive(m_sessionMutex);
    return permission;
}

/**
 *  @}
 */