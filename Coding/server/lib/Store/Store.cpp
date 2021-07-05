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
 * 
 * @{
 */

#include <Store.h>

bool Store::saveNetworkCredentials()
{
    bool retCode = m_nvsmgr.putEntry("netCredentials", m_netCredentials.serialize());
    if (false == retCode)
    {
        LOG_ERROR("Could not save NetworkCredentials to disk");
    }
    return retCode;
}

bool Store::loadNetworkCredentials()
{
    String json = m_nvsmgr.readEntry("netCredentials");
    bool retCode = ((String("null") != json) && (true == m_netCredentials.deserialize(json)));
    if (false == retCode)
    {
        LOG_ERROR("Could not load NetworkCredentials from disk");
    }
    return retCode;
}

bool Store::saveKeyCert()
{
    uint8_t *keyBuffer = new uint8_t[KeyCert::RSA_KEY_SIZE_BYTE];
    uint8_t *certBuffer = new uint8_t[KeyCert::CERT_SIZE_BYTE];

    m_keyCert.serialize(keyBuffer, certBuffer);

    bool putRSAResult = m_nvsmgr.putEntry("rsakey", keyBuffer, KeyCert::RSA_KEY_SIZE_BYTE);
    bool putCertResult = m_nvsmgr.putEntry("sslcert", certBuffer, KeyCert::CERT_SIZE_BYTE);

    delete[] keyBuffer;
    delete[] certBuffer;

    bool success = (true == putRSAResult) && (true == putCertResult);
    if (false == success)
    {
        LOG_ERROR("Could not save KeyCert to disk");
    }
    return success;
}

bool Store::loadKeyCert()
{
    uint8_t *keyBuffer = new uint8_t[KeyCert::RSA_KEY_SIZE_BYTE];
    uint8_t *certBuffer = new uint8_t[KeyCert::CERT_SIZE_BYTE];

    bool getRSAResult = m_nvsmgr.readEntry("rsakey", keyBuffer, KeyCert::RSA_KEY_SIZE_BYTE);
    bool getCertResult = m_nvsmgr.readEntry("sslcert", certBuffer, KeyCert::CERT_SIZE_BYTE);

    bool success = (true == getRSAResult) && (true == getCertResult);

    if (true == success)
    {
        m_keyCert.deserialize(keyBuffer, certBuffer);
    }
    else
    {
        LOG_ERROR("Could not load KeyCert from disk");
    }

    delete[] keyBuffer;
    delete[] certBuffer;

    return success;
}

NetworkCredentials Store::getNetworkCredentials()
{
    return m_netCredentials;
}

void Store::setNetworkCredentials(NetworkCredentials credentials)
{
    m_netCredentials = credentials;
}

KeyCert &Store::getKeyCert()
{
    return m_keyCert;
}

void Store::setKeyCert(KeyCert keycert)
{
    m_keyCert = keycert;
}