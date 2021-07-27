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
 * @file KeyCert.cpp
 * @author Luis Moser
 * @brief KeyCert class
 * @date 06/22/2021
 *
 * @{
 */

#include <KeyCert.h>
#include <Log.h>

uint8_t KeyCert::m_binaryKey[RSA_KEY_SIZE_BYTE] = { 0 };
uint8_t KeyCert::m_binaryCert[CERT_SIZE_BYTE] = { 0 };

KeyCert::KeyCert() :
    m_sslCert(),
    m_certGenerated(false)
{
}

KeyCert::~KeyCert()
{
    freeSSLMemory();
}

bool KeyCert::generateNewCert()
{
    freeSSLMemory();

    int retCode = createSelfSignedCert(
        m_sslCert,
        httpsserver::KEYSIZE_2048,
        "CN=complatform.local,O=NT,C=DE",
        "20210101000000",
        "20310101000000");

    if (0 != retCode)
    {
        m_certGenerated = false;
        LOG_ERROR("Could not generate a new certificate!");
    }
    else
    {
        m_certGenerated = true;
    }
    return (0 == retCode);
}

httpsserver::SSLCert* KeyCert::getSSLCert()
{
    return &m_sslCert;
}

void KeyCert::serialize(uint8_t* keyBuffer, uint8_t* certBuffer)
{
    if (true == m_certGenerated)
    {
        memcpy(keyBuffer, m_sslCert.getPKData(), RSA_KEY_SIZE_BYTE);
        memcpy(certBuffer, m_sslCert.getCertData(), CERT_SIZE_BYTE);
    }
    else
    {
        memcpy(keyBuffer, m_binaryKey, RSA_KEY_SIZE_BYTE);
        memcpy(certBuffer, m_binaryCert, CERT_SIZE_BYTE);
    }
}

void KeyCert::deserialize(const uint8_t* keyBuffer, const uint8_t* certBuffer)
{
    freeSSLMemory();

    memcpy(m_binaryKey, keyBuffer, RSA_KEY_SIZE_BYTE);
    memcpy(m_binaryCert, certBuffer, CERT_SIZE_BYTE);

    m_sslCert.setPK(m_binaryKey, RSA_KEY_SIZE_BYTE);
    m_sslCert.setCert(m_binaryCert, CERT_SIZE_BYTE);
}

void KeyCert::freeSSLMemory()
{
    /* Free up memory which might have been allocated previously after generating a certificate */
    if ((true == m_certGenerated) && (nullptr != m_sslCert.getPKData()) && (nullptr != m_sslCert.getCertData()))
    {
        m_sslCert.clear();
        m_certGenerated = false;
    }
}
