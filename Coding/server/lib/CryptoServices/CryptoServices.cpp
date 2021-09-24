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
 * @file CryptoServices.cpp
 * @author Luis Moser
 * @brief CryptoServices class
 * @date 07/20/2021
 *
 * @{
 */

#include <Log.h>
#include <CryptoServices.h>
#include <GPIOPins.h>
#include <PublicSigningKey.h>

CryptoServices::CryptoServices() :
    m_hasherInstance(),
    m_hashBuffer(),
    m_hashAvailable(false),
    m_messageDigesetInitialized(false),
    m_publicKeyContext(),
    m_messageDigestContext()
{
}

CryptoServices::~CryptoServices()
{
    if (true == m_messageDigesetInitialized)
    {
        mbedtls_md_free(&m_messageDigestContext);
    }
}

bool CryptoServices::getRandomSalt(String& outputString) const
{
    /* Initialize the random generator with seed with entropy from analog noise */
    randomSeed(analogRead(GPIOPins::PIN_ANALOG_NOISE_SEED));

    bool retCode = true;
    const uint16_t MAX_VALUE = 255;
    const uint8_t NUMBER_OF_PRINTABLE_CHARS = 2;
    char strBuffer[NUMBER_OF_PRINTABLE_CHARS + 1];

    /* Clear output buffer */
    outputString = "";

    for (uint8_t hexIdx = 0; hexIdx < SALT_LENGTH_BYTE; hexIdx++)
    {
        uint8_t randomNumber = static_cast<uint8_t>(random(MAX_VALUE + 1));
        if (NUMBER_OF_PRINTABLE_CHARS != sprintf(strBuffer, "%02X", randomNumber))
        {
            retCode = false;
            break;
        }
        outputString += strBuffer;
    }
    return retCode;
}

bool CryptoServices::hashBlake2b(const String& cleartext, const String& salt, String& outputString)
{
    bool retCode = true;

    String inputString = cleartext + salt;
    uint8_t outputHash[BLAKE2b_LENGTH_BYTE];

    const uint8_t NUMBER_OF_PRINTABLE_CHARS = 2;
    char strBuffer[NUMBER_OF_PRINTABLE_CHARS + 1];

    m_hasherInstance.reset(BLAKE2b_LENGTH_BYTE);
    m_hasherInstance.update(inputString.c_str(), inputString.length());
    m_hasherInstance.finalize(outputHash, BLAKE2b_LENGTH_BYTE);

    /* Clear output buffer */
    outputString = "";

    for (uint8_t hexIdx = 0; hexIdx < BLAKE2b_LENGTH_BYTE; hexIdx++)
    {
        if (NUMBER_OF_PRINTABLE_CHARS != sprintf(strBuffer, "%02X", outputHash[hexIdx]))
        {
            retCode = false;
            break;
        }
        outputString += strBuffer;
    }
    return retCode;
}

void CryptoServices::resetSHA256Hash()
{
    m_hashAvailable = false;
    mbedtls_md_free(&m_messageDigestContext);
    m_messageDigesetInitialized = false;
    LOG_DEBUG("Successfully cleared all data in CryptoServices");
}

bool CryptoServices::updateSHA256Hash(const uint8_t* dataChunk, const uint16_t chunkSize)
{
    bool setupSuccess = true;
    bool startSuccess = true;
    bool updateSuccess = false;

    if (false == m_messageDigesetInitialized)
    {
        mbedtls_md_init(&m_messageDigestContext);

        setupSuccess = (0 == mbedtls_md_setup(&m_messageDigestContext, mbedtls_md_info_from_type(MBEDTLS_MD_SHA256), 0));
        if (false == setupSuccess)
        {
            LOG_ERROR("Could not set up the message digest context!");
        }

        startSuccess = (0 == mbedtls_md_starts(&m_messageDigestContext));
        if (false == startSuccess)
        {
            LOG_ERROR("Could not start the message digest");
        }

        m_messageDigesetInitialized = (true == setupSuccess) && (true == startSuccess);
    }

    if ((true == setupSuccess) && (true == startSuccess))
    {
        updateSuccess = (0 == mbedtls_md_update(&m_messageDigestContext, dataChunk, chunkSize));
    }
    return updateSuccess;
}

void CryptoServices::finalizeSHA256Hash()
{
    if (0 == mbedtls_md_finish(&m_messageDigestContext, m_hashBuffer))
    {
        m_hashAvailable = true;
    }
    else
    {
        m_hashAvailable = false;
    }

    mbedtls_md_free(&m_messageDigestContext);
    m_messageDigesetInitialized = false;
}

bool CryptoServices::getSHA256String(String& outputString)
{
    bool retCode = true;
    const uint8_t NUMBER_OF_PRINTABLE_CHARS = 2;
    char strBuffer[NUMBER_OF_PRINTABLE_CHARS + 1];

    if (false == m_hashAvailable)
    {
        finalizeSHA256Hash();
    }

    if (true == m_hashAvailable)
    {
        for (int i = 0; i < SHA256_LENGTH_BYTE; i++)
        {
            if (NUMBER_OF_PRINTABLE_CHARS == sprintf(strBuffer, "%02X", m_hashBuffer[i]))
            {
                outputString += strBuffer;
            }
            else
            {
                outputString = "null";
                retCode = false;
                break;
            }
        }
    }
    else
    {
        LOG_WARN("No hash available to return!");
        retCode = false;
    }
    return retCode;
}

bool CryptoServices::verifySignature(const uint8_t* signature, const uint16_t signatureSize)
{
    bool retCode = false;

    if (false == m_hashAvailable)
    {
        finalizeSHA256Hash();
    }

    if (true == m_hashAvailable)
    {

#ifdef ACTIVATE_LOGGING
        String hexString;
        if (true == getSHA256String(hexString))
        {
            LOG_DEBUG(String("Calculated SHA256 hash value: ") + hexString);
        }
#endif

        mbedtls_pk_init(&m_publicKeyContext);

        /* Parse the public PEM-RSA2048 key and compare the decrypted signature with the passed SHA256 hash */
        int32_t parseRetCode = mbedtls_pk_parse_public_key(&m_publicKeyContext, reinterpret_cast<const unsigned char*>(PublicSigningKey::PUB_RSA_SIGN_KEY), PublicSigningKey::KEY_LENGTH_BYTES);
        if (0 == parseRetCode)
        {
            int32_t verifyRetCode = mbedtls_pk_verify(&m_publicKeyContext, MBEDTLS_MD_SHA256, m_hashBuffer, SHA256_LENGTH_BYTE, signature, signatureSize);
            if (0 == verifyRetCode)
            {
                retCode = true;
            }
            else
            {
                LOG_ERROR("Invalid firmware image signature!");
                LOG_ERROR(String("RetCode: ") + verifyRetCode);
            }
        }
        else
        {
            LOG_ERROR("Could not parse hard-coded public RSA key!");
            LOG_ERROR(String("RetCode: ") + parseRetCode);
        }

        mbedtls_pk_free(&m_publicKeyContext);
    }
    else
    {
        m_hashAvailable = false;
        LOG_ERROR("Could not compute/get SHA256 hash value of firmware/payload!");
    }
    return retCode;
}
