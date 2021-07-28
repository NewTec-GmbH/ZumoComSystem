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
 * @file ApiResponse.cpp
 * @author Luis Moser
 * @brief ApiResponse class
 * @date 07/14/2021
 *
 * @{
 */

#include <ApiResponse.h>
#include <ArduinoJson.h>
#include <Log.h>

ApiResponse::ApiResponse() :
    m_statusCode(),
    m_jsonPayload()
{
}

ApiResponse::~ApiResponse()
{
}

bool ApiResponse::serialize(String& serial)
{
    bool retCode = false;
    size_t docSize = 0;
    static String prevJsonPayload = "";

    /*
    Reserve memory on stack for JSON structure which consists of two key-value pairs.
    The status code and the json payload are not copied into the StaticJsonDocument by default.
    */
    static const size_t KEY_VALUE_PAIRS = 2;
    StaticJsonDocument<JSON_OBJECT_SIZE(KEY_VALUE_PAIRS)> jsonDocument;

    /*
    Pass the const int/string data to ArduinoJson so that ArduinoJson
    will not copy/duplicate the values
    */
    jsonDocument["statusCode"] = static_cast<const uint16_t>(m_statusCode);

    /* Optionally serialize jsonPayload if set */
    if ((m_jsonPayload != prevJsonPayload) && (m_jsonPayload != ""))
    {
        jsonDocument["jsonPayload"] = m_jsonPayload.c_str();
        prevJsonPayload = m_jsonPayload;
    }

    docSize = measureJson(jsonDocument);
    retCode = ((0 < docSize) && (docSize == serializeJson(jsonDocument, serial)));
    if (true == retCode)
    {
        LOG_DEBUG("ApiResponse successfully serialized to JSON");
    }
    else
    {
        LOG_ERROR("ApiResponse could not be serialized to JSON!");
    }
    return retCode;
}

void ApiResponse::setJsonPayload(const String& jsonPayload)
{
    m_jsonPayload = jsonPayload;
}

void ApiResponse::setStatusCode(const ResponseCode& statusCode)
{
    m_statusCode = statusCode;
}
