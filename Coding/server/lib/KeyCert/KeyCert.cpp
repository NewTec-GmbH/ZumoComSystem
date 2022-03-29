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

KeyCert::KeyCert() :
    m_binaryCert(nullptr),
    m_binaryCertSize(0),
    m_binaryKey(nullptr),
    m_binaryKeySize(0),
    m_sslCert()
{
}

KeyCert::~KeyCert()
{
    if (nullptr != m_binaryCert)
    {
        delete[] m_binaryCert;
        m_binaryCert = nullptr;
        m_binaryCertSize = 0;
    }

    if (nullptr != m_binaryKey)
    {
        delete[] m_binaryKey;
        m_binaryKey = nullptr;
        m_binaryKeySize = 0;
    }
}

bool KeyCert::generateNewCert()
{
    /* Release certificate and key, because the creation of the
     * self signed certificate will allocate them.
     */
    if (nullptr != m_binaryCert)
    {
        delete[] m_binaryCert;
        m_binaryCert = nullptr;
        m_binaryCertSize = 0;
    }

    if (nullptr != m_binaryKey)
    {
        delete[] m_binaryKey;
        m_binaryKey = nullptr;
        m_binaryKeySize = 0;
    }

    /* It will always allocate buffer for the certificate and the key.
     * No chance to prevent it.
     *
     * Attention: Usually the allocated buffers should be released
     *            via m_sslCert.clear(), but this method uses delete
     *            instead of delete[] which may cause a memory leak.
     *            Therefore the buffers will be released at least in
     *            the destructor here.
     */
    int retCode = createSelfSignedCert(
        m_sslCert,
        httpsserver::KEYSIZE_2048,
        "CN=complatform,O=NT,C=DE",
        "20210101000000",
        "20310101000000");

    if (0 != retCode)
    {
        LOG_ERROR("Could not generate a new certificate!");
    }
    else
    {
        m_binaryCert        = m_sslCert.getCertData();
        m_binaryCertSize    = m_sslCert.getCertLength();
        m_binaryKey         = m_sslCert.getPKData();
        m_binaryKeySize     = m_sslCert.getPKLength();
    }

    return (0 == retCode);
}

httpsserver::SSLCert* KeyCert::getSSLCert()
{
    return &m_sslCert;
}

void KeyCert::serialize(uint8_t* keyBuffer, size_t& keyBufferSize, uint8_t* certBuffer, size_t& certBufferSize)
{
    if (nullptr == keyBuffer)
    {
        keyBufferSize = m_binaryKeySize;
    }
    else if (m_binaryKeySize <= keyBufferSize)
    {
        memcpy(keyBuffer, m_binaryKey, m_binaryKeySize);
    }
    else
    {
        LOG_ERROR("Key serialization failed.");
    }

    if (nullptr == certBuffer)
    {
        certBufferSize = m_binaryCertSize;
    }
    else if (m_binaryCertSize <= certBufferSize)
    {
        memcpy(certBuffer, m_binaryCert, m_binaryCertSize);
    }
    else
    {
        LOG_ERROR("Certificate serialization failed.");
    }
}

void KeyCert::deserialize(const uint8_t* keyBuffer, size_t keyBufferSize, const uint8_t* certBuffer, size_t certBufferSize)
{
    if (nullptr != keyBuffer)
    {
        if (nullptr != m_binaryKey)
        {
            if (m_binaryKeySize != keyBufferSize)
            {
                delete[] m_binaryKey;
                m_binaryKey = nullptr;
                m_binaryKeySize = 0;
            }
        }

        if (nullptr == m_binaryKey)
        {
            m_binaryKey = new(std::nothrow) uint8_t[keyBufferSize];

            if (nullptr != m_binaryKey)
            {
                m_binaryKeySize = keyBufferSize;
            }
        }

        if (nullptr == m_binaryKey)
        {
            LOG_ERROR("Key deserialization failed.");
        }
        else
        {
            memcpy(m_binaryKey, keyBuffer, m_binaryKeySize);

            m_sslCert.setPK(m_binaryKey, m_binaryKeySize);

            LOG_INFO(String("PK with size of ") + m_binaryKeySize + " set.");
        }
    }

    if (nullptr != certBuffer)
    {
        if (nullptr != m_binaryCert)
        {
            if (m_binaryCertSize != certBufferSize)
            {
                delete[] m_binaryCert;
                m_binaryCert = nullptr;
                m_binaryCertSize = 0;
            }
        }

        if (nullptr == m_binaryCert)
        {
            m_binaryCert = new(std::nothrow) uint8_t[keyBufferSize];

            if (nullptr != m_binaryCert)
            {
                m_binaryCertSize = certBufferSize;
            }
        }

        if (nullptr == m_binaryCert)
        {
            LOG_ERROR("Certificate deserialization failed.");
        }
        else
        {
            memcpy(m_binaryCert, certBuffer, m_binaryCertSize);

            m_sslCert.setCert(m_binaryCert, m_binaryCertSize);

            LOG_INFO(String("Certificate with size of ") + m_binaryCertSize + " set.");
        }
    }
}
