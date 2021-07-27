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
 * @file ApiRequest.cpp
 * @author Luis Moser
 * @brief ApiRequest class
 * @date 07/14/2021
 *
 * @{
 */

#include <ApiRequest.h>
#include <ArduinoJson.h>
#include <Log.h>

ApiRequest::ApiRequest() :
    m_commandId(),
    m_jsonPayload()
{
}

ApiRequest::~ApiRequest()
{
}

bool ApiRequest::deserialize(String serial)
{
    /*
    Reserve memory on heap for JSON structure which consists of two key-value pairs.
    The value specified in DOC_SIZE has been computed with the help of the ArduinoJson Assistant v6
    which is accessible at: https://arduinojson.org/v6/assistant/
    */
    bool retCode = false;

    const size_t DOC_SIZE = 2048;
    DynamicJsonDocument jsonDocument(DOC_SIZE);
    DeserializationError jsonRet = deserializeJson(jsonDocument, serial);

    /* Check shapeliness of incoming JSON request */
    if ((DeserializationError::Ok == jsonRet) && (true == jsonDocument.containsKey("commandId")))
    {
        m_commandId = jsonDocument["commandId"].as<String>();

        if (true == jsonDocument.containsKey("jsonPayload"))
        {
            m_jsonPayload = jsonDocument["jsonPayload"].as<String>();
        }
        retCode = true;
    }
    else
    {
        LOG_ERROR("Error on deserializing the ApiRequest JSON object. JSON may be malformed!");
        LOG_ERROR(String("ArduinoJson result: ") + jsonRet.c_str());
    }
    return retCode;
}

String ApiRequest::getCommandId()
{
    return m_commandId;
}

String ApiRequest::getJsonPayload()
{
    return m_jsonPayload;
}
