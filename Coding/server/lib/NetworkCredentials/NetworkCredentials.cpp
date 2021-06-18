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
#include <Logger.h>

NetworkCredentials::NetworkCredentials(String ssid, String psk) : m_ssid(ssid), m_psk(psk)
{
    LOG_DEBUG("New network credentials generated");
}

NetworkCredentials::NetworkCredentials()
{
    LOG_DEBUG("New network credentials generated");
}

NetworkCredentials::~NetworkCredentials()
{
    LOG_DEBUG("Network credentials destructed");
}

String NetworkCredentials::getSSID()
{
    return m_ssid;
}

void NetworkCredentials::setSSID(String ssid)
{
    m_ssid = ssid;
}

String NetworkCredentials::getPSK()
{
    return m_psk;
}

void NetworkCredentials::setPSK(String psk)
{
    m_psk = psk;
}

String NetworkCredentials::serialize()
{
    /** 
     * Reserve memory on stack for JSON structure
     * which consists of two key-value pairs 
     */
    const uint8_t size = JSON_OBJECT_SIZE(2);
    StaticJsonDocument<size> jsonDocument;

    /**
     * Pass the const/non-volatile char*
     * pointers to ArduinoJson so that
     * ArduinoJson will not copy/duplicate
     * the string values
     */
    jsonDocument["ssid"] = m_ssid.c_str();
    jsonDocument["psk"] = m_psk.c_str();

    String serialized;
    serializeJson(jsonDocument, serialized);
    LOG_DEBUG("Network credentials successfully serialized to JSON");
    return serialized;
}

bool NetworkCredentials::deserialize(String serial)
{
    /** 
     * Reserve memory on stack for JSON structure
     * which consists of two key-value pairs
     */
    StaticJsonDocument<32> jsonDocument;

    /** 
     * Get a dynamic r/w buffer for deserialization
     * so that ArduinoJson can replace JSON syntax
     * with \0 terminators for each string value
    */
    uint32_t bufferSize = strlen(serial.c_str()) + 1;
    char *buffer = new char[bufferSize];
    serial.toCharArray(buffer, bufferSize);

    DeserializationError retCode = deserializeJson(jsonDocument, buffer);
    /** retCode > 0 in case of arbitrary error */
    if (DeserializationError::Ok == retCode)
    {
        m_ssid = jsonDocument["ssid"].as<String>();
        m_psk = jsonDocument["psk"].as<String>();
        delete[] buffer;
        return true;
    }
    else
    {
        delete[] buffer;
        LOG_ERROR("Error on deserializing the JSON object");
        LOG_ERROR(retCode.c_str());
        return false;
    }
}
