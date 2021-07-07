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
 * @file WebServer.h
 * @author Luis Moser
 * @brief WebServer header
 * @date 07/07/2021
 * 
 * @{
 */

#ifndef __WEBSERVER_H__
#define __WEBSERVER_H__

#include <Arduino.h>
#include <Store.h>
#include <Log.h>
#include <FileManager.h>
#include <HTTPSServer.hpp>
#include <HTTPRequest.hpp>
#include <HTTPResponse.hpp>

class HTTPsWebServer
{
private:
    /** TCP port which is used for frontend delivery as well as backend API services */
    static const uint16_t SHARED_TCP_PORT = 443;

    /** Max number of concurrent clients which can access the server */
    static const uint8_t MAX_CLIENTS = 4;

    /** HTTPSServer instance */
    httpsserver::HTTPSServer m_httpsServer; 

    /** Stores all HTTP routes */
    httpsserver::ResourceNode m_homeRoute{"/", "GET", &handleHome};

    /** Store instance */
    Store &m_store = Store::getInstance();

    /** Registers the route for the home page */
    bool registerHome();

    /** Registers all API services */
    bool registerServices();

    /** Handles incoming requests for home page */
    static void handleHome(httpsserver::HTTPRequest *request, httpsserver::HTTPResponse *response);

public:
    /**
     * Default Constructor
     */
    HTTPsWebServer();
    /**
     * Destructor
     */
    ~HTTPsWebServer();

    /**
     * Starts the HTTPs and WSS servers
     */
    bool startServer();

    /**
     * Stops the HTTPs and WSS servers
     */
    void stopServer();

    /**
     * This method needs to be called in a loop so that the HTTPs and WSS servers can receive CPU time
     */
    void handleServer();
};
#endif /** __WEBSERVER_H__ */