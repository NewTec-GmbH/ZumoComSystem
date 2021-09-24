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
 * @file FirmwareHeader.cpp
 * @author Luis Moser
 * @brief FirmwareHeader class
 * @date 08/02/2021
 *
 * @{
 */

#include <FirmwareHeader.h>
#include <Log.h>

FirmwareHeader::FirmwareHeader() :
    m_readHeaderBytes(0),
    m_idBuffer(),
    m_targetBuffer(),
    m_versionBuffer(),
    m_hashAlgBuffer(),
    m_signAlgBuffer(),
    m_signatureBuffer()
{
}

FirmwareHeader::~FirmwareHeader()
{
}

void FirmwareHeader::deserialize(const uint8_t* dataChunk, const uint16_t chunkSize)
{
    const uint16_t idEndIdx = ID_SIZE_BYTE;
    const uint16_t targetEndIdx = idEndIdx + TARGET_SIZE_BYTE;
    const uint16_t versionEndIdx = targetEndIdx + VERSION_SIZE_BYTE;
    const uint16_t hashAlgEndIdx = versionEndIdx + HASH_ALG_SIZE_BYTE;
    const uint16_t signAlgEndIdx = hashAlgEndIdx + SIGN_ALG_SIZE_BYTE;
    const uint16_t signatureEndIdx = signAlgEndIdx + SIGNATURE_SIZE_BYTE;

    uint16_t readIdx = 0;
    uint8_t byteBuffer = 0;

    uint16_t oldReadIdx = m_readHeaderBytes;
    for (uint16_t byteIdx = oldReadIdx; byteIdx < oldReadIdx + chunkSize; byteIdx++)
    {
        if (HEADER_SIZE_BYTE > byteIdx)
        {
            byteBuffer = dataChunk[readIdx];

            /* Write read data into corresponding output buffer */
            if (idEndIdx > byteIdx)
            {
                m_idBuffer[byteIdx] = byteBuffer;
            }
            else if ((idEndIdx <= byteIdx) && (targetEndIdx > byteIdx))
            {
                m_targetBuffer[(byteIdx - idEndIdx)] = byteBuffer;
            }
            else if (targetEndIdx == byteIdx)
            {
                m_versionBuffer[0] = byteBuffer;
            }
            else if ((versionEndIdx <= byteIdx) && (hashAlgEndIdx > byteIdx))
            {
                m_hashAlgBuffer[(byteIdx - versionEndIdx)] = byteBuffer;
            }
            else if ((hashAlgEndIdx <= byteIdx) && (signAlgEndIdx > byteIdx))
            {
                m_signAlgBuffer[(byteIdx - hashAlgEndIdx)] = byteBuffer;
            }
            else if ((signAlgEndIdx <= byteIdx) && (signatureEndIdx > byteIdx))
            {
                m_signatureBuffer[(byteIdx - signAlgEndIdx)] = byteBuffer;
            }

            readIdx++;
            m_readHeaderBytes++;


#ifdef ACTIVATE_LOGGING
            const uint8_t PRINT_BUFFER_SIZE = 128;
            const uint8_t MULTIPLICATOR = 100;
            char buffer[PRINT_BUFFER_SIZE];
            uint8_t processedBytsPercent = static_cast<uint8_t>((m_readHeaderBytes / (float)HEADER_SIZE_BYTE) * MULTIPLICATOR);

            /* Print the data into the output buffer */
            sprintf(buffer, "Processed %d of %d header bytes (%d%%)", m_readHeaderBytes, HEADER_SIZE_BYTE, processedBytsPercent);
            LOG_DEBUG(String(buffer));
#endif
        }
        else
        {
            break;
        }
    }
}
void FirmwareHeader::reset()
{
    m_readHeaderBytes = 0;
    memset(m_idBuffer, 0, sizeof(m_idBuffer));
    memset(m_targetBuffer, 0, sizeof(m_targetBuffer));
    memset(m_versionBuffer, 0, sizeof(m_versionBuffer));
    memset(m_hashAlgBuffer, 0, sizeof(m_hashAlgBuffer));
    memset(m_signAlgBuffer, 0, sizeof(m_signAlgBuffer));
    memset(m_signatureBuffer, 0, sizeof(m_signatureBuffer));
    LOG_DEBUG("Successfully cleared all data in FirmwareHeader");
}
void FirmwareHeader::getID(String& id) const
{
    id = String(reinterpret_cast<const char*>(m_idBuffer));
}
uint8_t FirmwareHeader::getVersion() const
{
    return m_versionBuffer[0];
}
void FirmwareHeader::getHashAlg(String& alg) const
{
    alg = String(reinterpret_cast<const char*>(m_hashAlgBuffer));
}
void FirmwareHeader::getSignAlg(String& alg) const
{
    alg = String(reinterpret_cast<const char*>(m_signAlgBuffer));
}
void FirmwareHeader::getTarget(String& target) const
{
    target = String(reinterpret_cast<const char*>(m_targetBuffer));
}
const uint8_t* FirmwareHeader::getSignature() const
{
    return m_signatureBuffer;
}
