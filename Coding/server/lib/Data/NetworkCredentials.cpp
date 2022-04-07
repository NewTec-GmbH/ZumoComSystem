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
 * @addtogroup Data
 * @{
 */

#include <NetworkCredentials.h>
#include <Log.h>
#include <ArduinoJson.h>

NetworkCredentials::NetworkCredentials() :
    m_ssid(),
    m_passphrase()
{
}

NetworkCredentials::~NetworkCredentials()
{
}

const String& NetworkCredentials::getSSID() const
{
    return m_ssid;
}

bool NetworkCredentials::setSSID(const String& ssid, const bool staMode)
{
    bool retCode = true;
    if ((true == staMode) && (ssid.length() <= MAX_SSID_LENGTH_CHARS))
    {
        m_ssid = ssid;
    }
    else if ((false == staMode) && (ssid.length() <= (MAX_SSID_LENGTH_CHARS - RESERVED_DEVICE_ID_CHARS)))
    {
        /* Append a unique 6 byte device MAC address in hex format (12 chars) */
        m_ssid = ssid + "_" + String(static_cast<unsigned long>(ESP.getEfuseMac()), HEX);
    }
    else
    {
        retCode = false;
    }
    return retCode;
}

const String& NetworkCredentials::getPassphrase() const
{
    return m_passphrase;
}

bool NetworkCredentials::setPassphrase(const String& passphrase)
{
    bool retCode = false;
    if ((passphrase.length() >= MIN_PASSPHRASE_LENGTH_CHARS) && (passphrase.length() <= MAX_PASSPHRASE_LENGTH_CHARS))
    {
        m_passphrase = passphrase;
        retCode = true;
    }
    return retCode;
}

bool NetworkCredentials::serialize(String& serial) const
{
    bool retCode = false;
    size_t docSize = 0;

    /*
    Reserve memory on stack for JSON structure which consists of two key-value pairs.
    The ssid and the passphrase are not copied into the StaticJsonDocument by default.
    */
    static const size_t KEY_VALUE_PAIRS = 2;
    StaticJsonDocument<JSON_OBJECT_SIZE(KEY_VALUE_PAIRS)> jsonDocument;

    /*
    Pass the const/non-volatile char* pointers to ArduinoJson so that ArduinoJson
    will not copy/duplicate the string values
    */

    jsonDocument["ssid"] = m_ssid.c_str();
    jsonDocument["passphrase"] = m_passphrase.c_str();

    docSize = measureJson(jsonDocument);
    retCode = ((0 < docSize) && (docSize == serializeJson(jsonDocument, serial)));
    if (true == retCode)
    {
        LOG_DEBUG("Network credentials successfully serialized to JSON");
        LOG_DEBUG(serial);
    }
    else
    {
        LOG_ERROR("Could not serialize network credentials!");
    }
    return retCode;
}

bool NetworkCredentials::deserialize(const String& serial, const bool staCredentials)
{
    /*
    Reserve memory on stack for JSON structure which consists of two key-value pairs.
    The value specified in DOC_SIZE has been computed with the help of the ArduinoJson Assistant v6
    which is accessible at: https://arduinojson.org/v6/assistant/
    */
    const size_t DOC_SIZE = 192;
    StaticJsonDocument<DOC_SIZE> jsonDocument;
    DeserializationError jsonRet = deserializeJson(jsonDocument, serial);

    bool retCode = ((DeserializationError::Ok == jsonRet)
        && (true == setSSID(jsonDocument["ssid"].as<String>(), staCredentials))
        && (true == setPassphrase(jsonDocument["passphrase"].as<String>())));

    if (false == retCode)
    {
        LOG_ERROR("Error on deserializing the NetworkCredentials JSON object. JSON may either be malformed or SSID or passphrase are not complying with IEEE 802.11");
        LOG_ERROR(jsonRet.c_str());
    }
    return retCode;
}

/**
 *  @}
 */