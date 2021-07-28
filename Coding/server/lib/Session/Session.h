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
 * @file Session.h
 * @author Luis Moser
 * @brief Session header
 * @date 07/15/2021
 *
 * @{
 */

#ifndef __SESSION_H__
#define __SESSION_H__

#include <Arduino.h>
#include <Permission.h>
#include <WebsocketHandler.hpp>
#include <User.h>

 /** Simple class to store websocket sessions and their authentication status */
class Session : public httpsserver::WebsocketHandler
{
public:
    /**
     * Default Constructor
     */
    Session();

    /**
     * Destructor
     */
    ~Session();

    /**
     * Starts the timeout service
     *
     * @return Returns true if successful, else false
     */
    static bool start();

    /**
     * Called on each new session initiation by the WebSocketServer
     *
     * @return Returns the WebSocketHandler pointer
     */
    static httpsserver::WebsocketHandler* create();

    /**
     * Is called each time this session receives a message
     *
     * @param[in] inputBuffer The WebSocketInputStreambuf pointer
     */
    void onMessage(httpsserver::WebsocketInputStreambuf* inputBuffer);

    /**
     * Is called when this session needs to be closed
     */
    void onClose();

    /**
     * Returns if this session is authenticated
     *
     * @return Returns true if session is authenticated, else false
     */
    bool isAuthenticated() const;

    /**
     * Authenticates this session and links this session with the specified user
     *
     * @param[in] user Pointer to the user to be linked with this session
     */
    void authenticateSession(User* user);

    /**
     * Deauthenticates this session
     */
    void deauthenticateSession();

    /**
     * Returns the permissions of the user which is linked to this session
     *
     * @param[out] numberOfPermissions Specifies the length of the returned array
     * @return Returns the permissions of the linked user
     */
    const Permission* getPermissions(uint8_t& numberOfPermissions);

private:
    /**
     * Checks which sessions need to be invalidated because of timeout
     *
     * @param[in] parameter Generic input parameter for FreeRTOS task
     */
    static void handleSessionTimeout(void* parameter);

    /** Specifies the maximum number of concurrent websocket clients */
    static const uint8_t MAX_CLIENTS = 4;

    /** Specifies how many seconds need to pass before session gets deauthenticated due to timeout */
    static const uint16_t SESSION_TIMEOUT_SECONDS = 900;

    /** Stores all active Session instances/websocket sessions */
    static Session* m_sessions[];

    /** Stores how many clients are currently connected to websocket API */
    static uint8_t m_numberOfActiveClients;

    /** Specifies if the current session is authenticated */
    bool m_sessionAuthenticated;

    /** Specifies the linked user */
    User* m_linkedUser;

    /** Timestamp which gets updated each time a request is made with this session */
    unsigned long m_lastAccessTime;
};
#endif /** __SESSION_H__ */
