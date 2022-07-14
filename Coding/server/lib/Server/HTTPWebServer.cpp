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
 * @file HTTPWebServer.cpp
 * @author Luis Moser
 * @brief HTTPWebServer class
 * @date 07/07/2021
 * @addtogroup Server
 * @{
 */

#include <HTTPWebServer.h>
#include <Log.h>
#include <HTTPRequest.hpp>
#include <HTTPResponse.hpp>
#include <ResponseCode.h>
#include <Session.h>

const KeyValue HTTPWebServer::m_servedFileTypes[] =
{
    {".html", "text/html"},
    {".css", "text/css"},
    {".js", "application/javascript"},
    {".jpg", "image/jpeg"},
    {".png", "image/png"},
    {".ico", "image/vnd.microsoft.icon"},
    {".svg", "image/svg+xml"},
    {".ttf", "font/ttf"},
    {".woff", "font/woff"},
    {".eot", "font/eot"},
};

HTTPWebServer::HTTPWebServer() :
    m_httpsServer(SHARED_TCP_PORT, MAX_CLIENTS),
    m_fileServeRoute("", "", &registerFileServing),
    m_apiRoute("/api", &Session::create)
{
}

HTTPWebServer::~HTTPWebServer()
{
    stopServer();
}

bool HTTPWebServer::startServer()
{
    m_httpsServer.registerNode(&m_fileServeRoute);
    m_httpsServer.setDefaultNode(&m_fileServeRoute);
    LOG_INFO("Registered file serving route");

    m_httpsServer.registerNode(&m_apiRoute);
    LOG_INFO("Registered websocket API route");

    return ((1 == m_httpsServer.start()) && (true == m_httpsServer.isRunning()));
}

void HTTPWebServer::stopServer()
{
    m_httpsServer.stop();
    LOG_DEBUG("HTTPs and WSS servers have been stopped");
}

void HTTPWebServer::handleServer()
{
    m_httpsServer.loop();
}

void HTTPWebServer::registerFileServing(httpsserver::HTTPRequest* request, httpsserver::HTTPResponse* response)
{
    if (request->getMethod() == "GET")
    {
        String requestedFile = request->getRequestString().c_str();
        String mimeType;

        /* Rewrite to index.html */
        if ((requestedFile == "/") || (requestedFile == ""))
        {
            requestedFile = "/index.html";
        }

        getMIMEType(requestedFile, mimeType);

        if ((true == FileManager::fileExists(requestedFile))
            && (false == mimeType.isEmpty()))
        {
            FileManager     fileMgr;            
            int16_t         writtenBytes    = 0;

            if (true == fileMgr.openFile(requestedFile, FILE_READ))
            {
                const uint16_t  BUFFER_SIZE_BYTES   = 4096;
                uint8_t*        buffer              = nullptr;
                
                buffer = new(std::nothrow) uint8_t[BUFFER_SIZE_BYTES];

                if (nullptr == buffer)
                {
                    response->setStatusCode(ERROR);
                    response->println("Internal error!");
                }
                else
                {
                    response->setHeader("Content-Length", httpsserver::intToString(fileMgr.getFileSize()));
                    response->setHeader("Content-Type", mimeType.c_str());

                    do
                    {
                        writtenBytes = fileMgr.read4KBlock(buffer);

                        if (-1 == writtenBytes)
                        {
                            response->setStatusCode(ERROR);
                            response->println("An error occurred while reading the file!");
                        }
                        else
                        {
                            response->write(buffer, writtenBytes);
                        }

                    } while ((0 != writtenBytes) && (-1 != writtenBytes));

                    delete[] buffer;
                    buffer = nullptr;
                }

                fileMgr.closeFile();
            }
            else
            {
                response->setStatusCode(NOT_FOUND);
                response->println("Couldn't open resource!");
            }
        }
        else
        {
            response->setStatusCode(NOT_FOUND);
            response->println("Could not find such resource!");
        }
    }
    else
    {
        request->discardRequestBody();
        response->setStatusCode(METHOD_NOT_ALLOWED);
        response->println("Invalid request!");
    }
}

void HTTPWebServer::getMIMEType(const String& filePath, String& mimeType)
{
    const uint8_t arrLength = sizeof(m_servedFileTypes) / sizeof(m_servedFileTypes[0]);

    mimeType.clear();

    for (uint8_t endingIdx = 0; endingIdx < arrLength; endingIdx++)
    {
        if (true == filePath.endsWith(m_servedFileTypes[endingIdx].key))
        {
            mimeType = m_servedFileTypes[endingIdx].value;
            break;
        }
    }
}

/**
 *  @}
 */