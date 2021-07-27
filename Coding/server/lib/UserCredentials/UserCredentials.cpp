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
 * @file UserCredentials.cpp
 * @author Luis Moser
 * @brief UserCredentials class
 * @date 07/23/2021
 *
 * @{
 */

#include <UserCredentials.h>
#include <ArduinoJson.h>
#include <Log.h>

UserCredentials::UserCredentials() :
    m_username(),
    m_password()
{
}

UserCredentials::~UserCredentials()
{
}

const String& UserCredentials::getUsername() const
{
    return m_username;
}

const String& UserCredentials::getPassword() const
{
    return m_password;
}

bool UserCredentials::deserialize(const String& serial)
{
    /*
    Reserve memory on stack for JSON structure which consists of two key-value pairs.
    The value specified in DOC_SIZE has been computed with the help of the ArduinoJson Assistant v6
    which is accessible at: https://arduinojson.org/v6/assistant/
    */
    const size_t DOC_SIZE = 384;
    StaticJsonDocument<DOC_SIZE> jsonDocument;
    DeserializationError jsonRet = deserializeJson(jsonDocument, serial);

    bool retCode = false;

    if (DeserializationError::Ok == jsonRet)
    {
        m_username = jsonDocument["username"].as<String>();
        m_password = jsonDocument["password"].as<String>();
        retCode = true;
    }
    else
    {
        LOG_ERROR("Error on deserializing the UserCredentials JSON object");
        LOG_ERROR(jsonRet.c_str());
    }
    return retCode;
}
