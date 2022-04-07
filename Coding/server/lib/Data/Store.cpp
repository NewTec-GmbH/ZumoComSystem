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
 * @file Store.cpp
 * @author Luis Moser
 * @brief Store class
 * @date 06/18/2021
 * @addtogroup Data
 * @{
 */

#include <Store.h>
#include <Log.h>

Store::Store() :
    m_nvsmgr(),
    m_staCredentials(),
    m_apCredentials(),
    m_keyCert(),
    m_users()
{
}

Store::~Store()
{
    closeStore();
}

const NetworkCredentials& Store::getSTACredentials() const
{
    return m_staCredentials;
}

void Store::setSTACredentials(const NetworkCredentials& credentials)
{
    m_staCredentials = credentials;
}

bool Store::saveSTACredentials()
{
    String serialized;
    bool serializeRetCode = m_staCredentials.serialize(serialized);
    bool saveRetCode = m_nvsmgr.putEntry("netCredentials", serialized);
    bool retCode = ((true == serializeRetCode) && (true == saveRetCode));

    if (false == retCode)
    {
        LOG_ERROR("Could not save NetworkCredentials to persistent storage");
    }
    return retCode;
}

bool Store::loadSTACredentials()
{
    const bool  ARE_STA_CREDENTIALS = true;
    String      json;
    bool        isSuccessful        = true;

    m_nvsmgr.readEntry("netCredentials", json);

    if (false == m_staCredentials.deserialize(json, ARE_STA_CREDENTIALS))
    {
        LOG_ERROR("Could not load NetworkCredentials from persistent storage");
        isSuccessful = false;
    }

    return isSuccessful;
}

bool Store::deleteSTACredentials()
{
    return m_nvsmgr.deleteEntry("netCredentials");
}

KeyCert& Store::getKeyCert()
{
    return m_keyCert;
}

void Store::setKeyCert(const KeyCert& keycert)
{
    m_keyCert = keycert;
}

bool Store::saveKeyCert()
{
    /* Stores if writing to NVS was successful */
    bool        putRSAResult    = false;
    bool        putCertResult   = false;
    bool        isSuccessful    = false;
    size_t      keyBufferSize   = 0;
    size_t      certBufferSize  = 0;
    uint8_t*    keyBuffer       = nullptr;
    uint8_t*    certBuffer      = nullptr;

    m_keyCert.serialize(nullptr, keyBufferSize, nullptr, certBufferSize);

    keyBuffer   = new(std::nothrow) uint8_t[keyBufferSize];
    certBuffer  = new(std::nothrow) uint8_t[certBufferSize];

    if ((nullptr == keyBuffer) || (nullptr == certBuffer))
    {
        LOG_ERROR("Out of memory. Could not create buffers for KeyCert serialization!");
    }
    else
    {
        m_keyCert.serialize(keyBuffer, keyBufferSize, certBuffer, certBufferSize);

        putRSAResult    = m_nvsmgr.putEntry("rsakey", keyBuffer, keyBufferSize);
        putCertResult   = m_nvsmgr.putEntry("sslcert", certBuffer, certBufferSize);

        if ((false == putRSAResult) || (false == putCertResult))
        {
            LOG_ERROR("Could not save KeyCert to persistent storage");
        }
        else
        {
            isSuccessful = true;
        }
    }

    if (nullptr != keyBuffer)
    {
        delete[] keyBuffer;
    }

    if (nullptr != certBuffer)
    {
        delete[] certBuffer;
    }

    return isSuccessful;
}

bool Store::loadKeyCert()
{
    bool        getRSAResult    = false;
    bool        getCertResult   = false;
    bool        isSuccessful    = false;
    size_t      keyBufferSize   = 0;
    size_t      certBufferSize  = 0;
    uint8_t*    keyBuffer       = nullptr;
    uint8_t*    certBuffer      = nullptr;

    getRSAResult    = m_nvsmgr.readEntry("rsakey", nullptr, keyBufferSize);
    getCertResult   = m_nvsmgr.readEntry("sslcert", nullptr, certBufferSize);
    
    if ((true == getRSAResult) &&
        (true == getCertResult) &&
        (0 < keyBufferSize) &&
        (0 < certBufferSize))
    {
        keyBuffer   = new(std::nothrow) uint8_t[keyBufferSize];
        certBuffer  = new(std::nothrow) uint8_t[certBufferSize];

        if ((nullptr == keyBuffer) || (nullptr == certBuffer))
        {
            LOG_ERROR("Out of memory. Could not create buffers for KeyCert deserialization!");
        }
        else
        {
            /* Stores if reading from NVS was successful */
            getRSAResult    = m_nvsmgr.readEntry("rsakey", keyBuffer, keyBufferSize);
            getCertResult   = m_nvsmgr.readEntry("sslcert", certBuffer, certBufferSize);

            if ((false == getRSAResult) || (false == getCertResult))
            {
                LOG_ERROR("Could not load KeyCert from persistent storage");
            }
            else
            {
                m_keyCert.deserialize(keyBuffer, keyBufferSize, certBuffer, certBufferSize);

                isSuccessful = true;
            }
        }

        if (nullptr != keyBuffer)
        {
            delete[] keyBuffer;
        }

        if (nullptr != certBuffer)
        {
            delete[] certBuffer;
        }
    }

    return isSuccessful;
}

const User& Store::getUsers() const
{
    return m_users;
}

void Store::setUsers(const User& users)
{
    m_users = users;
}

bool Store::saveUsers()
{
    String serialized;
    bool serializeRetCode = m_users.serialize(serialized);
    bool saveRetCode = m_nvsmgr.putEntry("users", serialized);
    bool retCode = ((true == serializeRetCode) && (true == saveRetCode));
    if (false == retCode)
    {
        LOG_ERROR("Could not save users to persistent storage");
    }
    return retCode;
}

bool Store::loadUsers()
{
    String  json;
    bool    isSuccessful    = true;

    m_nvsmgr.readEntry("users", json);

    if (false == m_users.deserialize(json))
    {
        LOG_ERROR("Could not load users from persistent storage");
        isSuccessful = false;
    }

    return isSuccessful;
}

bool Store::saveFirmwareInfo()
{
    String serialized;
    bool serializeRetCode = FirmwareInfo::serialize(serialized);
    bool saveRetCode = m_nvsmgr.putEntry("fwinfo", serialized);
    bool retCode = ((true == serializeRetCode) && (true == saveRetCode));
    if (false == retCode)
    {
        LOG_ERROR("Could not save FirmwareInfo to persistent storage");
    }
    return retCode;
}

bool Store::loadFirmwareInfo()
{
    String  json;
    bool    isSuccessful    = true;

    m_nvsmgr.readEntry("fwinfo", json);

    if (false == FirmwareInfo::deserialize(json))
    {
        LOG_ERROR("Could not load FirmwareInfo from persistent storage");
        isSuccessful = false;
    }

    return isSuccessful;
}

const NetworkCredentials& Store::getAPCredentials() const
{
    return m_apCredentials;
}

void Store::setAPCredentials(const NetworkCredentials& credentials)
{
    m_apCredentials = credentials;
}

void Store::closeStore()
{
    m_nvsmgr.closeNVS();
}

/**
 *  @}
 */