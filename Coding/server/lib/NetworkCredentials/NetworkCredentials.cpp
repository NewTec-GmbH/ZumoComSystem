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
 * @file NetworkCredentials.cpp
 * @author Luis Moser
 * @brief NetworkCredentials class
 * @date 06/17/2021
 * 
 * @{
 */

#include <NetworkCredentials.h>
#include <Log.h>

String NetworkCredentials::getSSID()
{
    return m_ssid;
}

bool NetworkCredentials::setSSID(String ssid)
{
    bool retCode = false;
    if (ssid.length() <= MAX_SSID_LENGTH_CHARS)
    {
        m_ssid = ssid;
        retCode = true;
    }
    return retCode;
}

String NetworkCredentials::getPassphrase()
{
    return m_passphrase;
}

bool NetworkCredentials::setPassphrase(String passphrase)
{
    bool retCode = false;
    if ((passphrase.length() >= MIN_PASSPHRASE_LENGTH_CHARS) && (passphrase.length() <= MAX_PASSPHRASE_LENGTH_CHARS))
    {
        m_passphrase = passphrase;
        retCode = true;
    }
    return retCode;
}

String NetworkCredentials::serialize()
{
    /* 
    Reserve memory on stack for JSON structure which consists of two key-value pairs.
    The ssid and the passphrase are not copied into the StaticJsonDocument by default. 
    */
    const uint8_t KEY_VALUE_PAIRS = 2;
    StaticJsonDocument<JSON_OBJECT_SIZE(KEY_VALUE_PAIRS)> jsonDocument;

    /*
    Pass the const/non-volatile char* pointers to ArduinoJson so that ArduinoJson 
    will not copy/duplicate the string values
    */
    jsonDocument["ssid"] = m_ssid.c_str();
    jsonDocument["passphrase"] = m_passphrase.c_str();

    String serialized;
    serializeJson(jsonDocument, serialized);
    LOG_DEBUG("Network credentials successfully serialized to JSON");
    return serialized;
}

bool NetworkCredentials::deserialize(String serial)
{
    /* 
    Reserve memory on stack for JSON structure which consists of two key-value pairs.
    The ssid and the passphrase are copied into the StaticJsonDocument by default.
    The value specified in DOC_SIZE has been computed with the help of the ArduinoJson Assistant v6
    which is accessible at: https://arduinojson.org/v6/assistant/
    */
    const uint8_t DOC_SIZE = 192;
    StaticJsonDocument<DOC_SIZE> jsonDocument;
    DeserializationError jsonRet = deserializeJson(jsonDocument, serial);

    bool retCode = false;
    if (DeserializationError::Ok == jsonRet)
    {
        m_ssid = jsonDocument["ssid"].as<String>();
        m_passphrase = jsonDocument["passphrase"].as<String>();
        retCode = true;
    }
    else
    {
        LOG_ERROR("Error on deserializing the NetworkCredentials JSON object");
        LOG_ERROR(jsonRet.c_str());
    }
    return retCode;
}
