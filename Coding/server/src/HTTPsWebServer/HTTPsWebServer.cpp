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

const String HTTPsWebServer::m_servedFileTypes[][2] = {
    {".html", "text/html"},
    {".css", "text/css"},
    {".js", "application/javascript"},
    {".jpg", "application/jpeg"} };

HTTPsWebServer::HTTPsWebServer() :
    m_httpsServer(Store::getInstance().getKeyCert().getSSLCert(), SHARED_TCP_PORT, MAX_CLIENTS),
    m_fileServeRoute("", "", &registerFileServing),
    m_store(Store::getInstance())
{
}

HTTPsWebServer::~HTTPsWebServer()
{
    stopServer();
}

bool HTTPsWebServer::startServer()
{
    m_httpsServer.registerNode(&m_fileServeRoute);
    m_httpsServer.setDefaultNode(&m_fileServeRoute);

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

void HTTPsWebServer::registerFileServing(httpsserver::HTTPRequest* request, httpsserver::HTTPResponse* response)
{
    FileManager m_fileManager;

    uint16_t writtenBytes = 0;
    static uint8_t buffer[4096];

    String mimeType;

    if (request->getMethod() == "GET")
    {
        String requestedFile = request->getRequestString().c_str();

        /* Rewrite to index.html */
        if ((requestedFile == "/") || (requestedFile == ""))
        {
            requestedFile = "/index.html";
        }

        /* Get the absolute path */
        requestedFile = "/webspace" + requestedFile;

        mimeType = getMIMEType(requestedFile);

        if ((true == FileManager::fileExists(requestedFile)) && (mimeType != "null"))
        {
            m_fileManager.openFile(requestedFile, FileManager::READ);

            response->setHeader("Content-Length", httpsserver::intToString(m_fileManager.getFileSize()));
            response->setHeader("Content-Type", mimeType.c_str());

            do
            {
                writtenBytes = m_fileManager.read4KBlock(buffer);
                response->write(buffer, writtenBytes);
            } while (0 != writtenBytes);

            m_fileManager.closeFile();
        }
        else
        {
            response->setStatusCode(404);
            response->println("Could not find such resource!");
        }
    }
    else
    {
        request->discardRequestBody();
        response->setStatusCode(405);
        response->println("Invalid request!");
    }
}

String HTTPsWebServer::getMIMEType(String filePath)
{
    String mimeType = "null";

    const uint8_t arrLength = sizeof(m_servedFileTypes) / sizeof(m_servedFileTypes[0]);

    for (uint8_t endingIdx = 0; endingIdx < arrLength; endingIdx++)
    {
        if (true == filePath.endsWith(m_servedFileTypes[endingIdx][0]))
        {
            mimeType = m_servedFileTypes[endingIdx][1];
            break;
        }
    }
    return mimeType;
}