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
 * @file WebServer.cpp
 * @author Luis Moser
 * @brief WebServer class
 * @date 07/07/2021
 * 
 * @{
 */

#include <HTTPsWebServer.h>

HTTPsWebServer::HTTPsWebServer() : m_httpsServer(Store::getInstance().getKeyCert().getSSLCert(), SHARED_TCP_PORT, MAX_CLIENTS)
{
}

HTTPsWebServer::~HTTPsWebServer()
{
    stopServer();
}

bool HTTPsWebServer::startServer()
{
    m_httpsServer.registerNode(&m_homeRoute);

    return ((1 == m_httpsServer.start()) && (true == m_httpsServer.isRunning()));
}

void HTTPsWebServer::stopServer()
{
    m_httpsServer.stop();
    LOG_DEBUG("HTTPs and WSS servers have been stopped");
}

void HTTPsWebServer::handleServer()
{
    m_httpsServer.loop();
}

void HTTPsWebServer::handleHome(httpsserver::HTTPRequest *request, httpsserver::HTTPResponse *response)
{
    response->setHeader("Content-Type", "text/html");
    String html = "<html><head></head><body><h1>Congratulations! You are successfully accessing the ComPlatform!</body></html>";
    response->println(html);
}