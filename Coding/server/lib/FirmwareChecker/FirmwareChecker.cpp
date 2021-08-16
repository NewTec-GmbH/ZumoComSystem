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
 * @file FirmwareChecker.cpp
 * @author Luis Moser
 * @brief FirmwareChecker class
 * @date 08/02/2021
 *
 * @{
 */

#include <FirmwareChecker.h>
#include <Log.h>

const char* FirmwareChecker::EXPECTED_ID = "CPSFW";
const char* FirmwareChecker::EXPECTED_HASH_ALG = "SHA256";
const char* FirmwareChecker::EXPECTED_SIGN_ALG = "RSA2048PKCS#1v15";

FirmwareChecker::FirmwareChecker() :
    m_fwHeader(),
    m_crypto(),
    m_readPayloadBytes(0)
{
}

FirmwareChecker::~FirmwareChecker()
{
}

void FirmwareChecker::deserializeHeader(const uint8_t* dataChunk, const uint16_t chunkSize)
{
    m_fwHeader.deserialize(dataChunk, chunkSize);
}

bool FirmwareChecker::deserializePayload(const uint8_t* dataChunk, const uint16_t chunkSize)
{
    m_readPayloadBytes += chunkSize;
    return m_crypto.updateVerifySignature(dataChunk, chunkSize);
}

bool FirmwareChecker::reset()
{
    bool retCode = false;
    m_readPayloadBytes = 0;
    m_fwHeader.reset();
    if (true == m_crypto.resetVerifySignature())
    {
        retCode = true;
        LOG_DEBUG("Successfully cleared all data in FirmwareChecker");
    }
    else
    {
        LOG_ERROR("Could not clear all data in FirmwareChecker!");
    }
    return retCode;
}

bool FirmwareChecker::idOK()
{
    String id;
    m_fwHeader.getID(id);
    return (id == EXPECTED_ID);
}

void FirmwareChecker::getTarget(String& target) const
{
    m_fwHeader.getTarget(target);
}

bool FirmwareChecker::getComputedHashValue(String& outputString)
{
    return m_crypto.getComputedHashValue(outputString);
}

bool FirmwareChecker::isValid(const String& expectedTarget)
{
    String readTarget;
    String readHashAlg;
    String readSignAlg;
    uint8_t readFileVersion;

    bool validFileId = false;
    bool validTarget = false;
    bool validFileVersion = false;
    bool validHashAlg = false;
    bool validSignAlg = false;
    bool validSignature = false;
    bool validPayloadSize = false;

    /* Check file ID */
    validFileId = idOK();
    if (false == validFileId)
    {
        LOG_ERROR("Invalid ID in firmware header!");

#ifdef ACTIVATE_LOGGING
        String id;
        m_fwHeader.getID(id);
        LOG_INFO(String("Actual firmware ID is: ") + id);
#endif    
    }

    /* Check target system */
    m_fwHeader.getTarget(readTarget);
    if (readTarget == expectedTarget)
    {
        validTarget = true;
    }
    else
    {
        LOG_ERROR("Unexpected target in firmware header!");
        LOG_ERROR(String("Actual target is: ") + readTarget);
    }

    /* Check file version */
    readFileVersion = m_fwHeader.getVersion();
    if (EXPECTED_VERSION == readFileVersion)
    {
        validFileVersion = true;
    }
    else
    {
        LOG_ERROR("Unexpected version in firmware header!");
        LOG_ERROR(String("Actual file version is: ") + readFileVersion);
    }

    /* Check used hash algorithm */
    m_fwHeader.getHashAlg(readHashAlg);
    if (readHashAlg == EXPECTED_HASH_ALG)
    {
        validHashAlg = true;
    }
    else
    {
        LOG_ERROR("Unexpected hash algorithm in firmware header!");
        LOG_ERROR(String("Actual hashing algorithm: ") + readHashAlg);
    }

    /* Check used sign algorithm */
    m_fwHeader.getSignAlg(readSignAlg);
    if (readSignAlg == EXPECTED_SIGN_ALG)
    {
        validSignAlg = true;
    }
    else
    {
        LOG_ERROR("Unexpected signing algorithm in firmware header!");
        LOG_ERROR(String("Actual signing algorithm: ") + readSignAlg);
    }

    /* Check signature */
    validSignature = m_crypto.verifySignature(m_fwHeader.getSignature(), FirmwareHeader::SIGNATURE_SIZE_BYTE);
    if (false == validSignature)
    {
        LOG_ERROR("Invalid signature in firmware header!");
    }

    /* Check payload size */
    if (readTarget == "COM")
    {
        validPayloadSize = (m_readPayloadBytes <= MAX_COM_FW_BLOB_SIZE_BYTE);
    }
    else if (readTarget == "ZUMO")
    {
        validPayloadSize = (m_readPayloadBytes <= MAX_ZUMO_FW_BLOB_SIZE_BYTE);
    }

    if (false == validPayloadSize)
    {
        LOG_ERROR("Firmware payload too big!");
    }
    return (validFileId && validTarget && validFileVersion && validHashAlg && validSignAlg && validSignature && validPayloadSize);
}
