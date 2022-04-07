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
 * @file FirmwareHeader.h
 * @author Luis Moser
 * @brief FirmwareHeader header
 * @date 08/02/2021
 * @addtogroup Data
 * @{
 */

#ifndef __FIRMWAREHEADER_H__
#define __FIRMWAREHEADER_H__

#include <Arduino.h>

 /** Class/data structure for deserializing the binary raw firmware image header and re-creating the header structure */
class FirmwareHeader
{
public:
    /** Specifies the file id/magic number field size in bytes */
    static const uint8_t ID_SIZE_BYTE = 16;

    /** Specifies the target system field size in bytes */
    static const uint8_t TARGET_SIZE_BYTE = 16;

    /** Specifies the file version field size in bytes */
    static const uint8_t VERSION_SIZE_BYTE = 1;

    /** Specifies the hash algorithm field size in bytes */
    static const uint8_t HASH_ALG_SIZE_BYTE = 16;

    /** Specifies the signing algorithm field size in bytes */
    static const uint8_t SIGN_ALG_SIZE_BYTE = 32;

    /** Specifies the signature field size in bytes */
    static const uint16_t SIGNATURE_SIZE_BYTE = 256;

    /** Specifies the total firmware header field size in bytes */
    static const uint16_t HEADER_SIZE_BYTE = ID_SIZE_BYTE + TARGET_SIZE_BYTE + VERSION_SIZE_BYTE +
        HASH_ALG_SIZE_BYTE + SIGN_ALG_SIZE_BYTE + SIGNATURE_SIZE_BYTE;

    /**
     * Default Constructor
     */
    FirmwareHeader();

    /**
     * Destructor
     */
    ~FirmwareHeader();

    /**
     * Deserializes the passed binary data and re-creates the header structure.
     * Call this method until all bytes specified in HEADER_SIZE_BYTE have been successfully read.
     * Do not continue to call this method when you continue reading payload data only!
     *
     * @param[in] dataChunk Pointer to the input buffer which contains the header binary data to be deserialized
     * @param[in] chunkSize Specifies the size of the passed input buffer. Can be of 4096 bytes in size at max
     */
    void deserialize(const uint8_t* dataChunk, const uint16_t chunkSize);

    /**
     * Resets the read byte index and allows to deserialize the the header from scratch
     */
    void reset();

    /**
     * Reads the file ID string which is inside the header
     *
     * @param[out] id Contains the string id specified inside the header
     */
    void getID(String& id) const;

    /**
    * Reads the file version uint8_t which is inside the header
    *
    * @return Returns the file version specified inside the header
    */
    uint8_t getVersion() const;

    /**
    * Reads the hash algorithm string which is inside the header
    *
    * @param[out] alg Contains the string hash algorithm inside the header
    */
    void getHashAlg(String& alg) const;

    /**
    * Reads the signing algorithm string which is inside the header
    *
    * @param[out] alg Contains the string hash signing inside the header
    */
    void getSignAlg(String& alg) const;

    /**
    * Reads the target system string which is inside the header
    *
    * @param[out] target Contains the string target system inside the header
    */
    void getTarget(String& target) const;

    /**
    * Reads the signature uint8_t buffer which is inside the header.
    * The size in bytes of the buffer is specified in SIGNATURE_SIZE_BYTE.
    *
    * @return Returns const pointer to the signature uint8_t buffer inside the header
    */
    const uint8_t* getSignature() const;

private:
    /** Stores how many header bytes have already been read */
    uint16_t m_readHeaderBytes;

    /** Stores the id field of the header */
    uint8_t m_idBuffer[ID_SIZE_BYTE];

    /** Stores the target system field of the header */
    uint8_t m_targetBuffer[TARGET_SIZE_BYTE];

    /** Stores the file version field of the header */
    uint8_t m_versionBuffer[VERSION_SIZE_BYTE];

    /** Stores the hash algorithm field of the header */
    uint8_t m_hashAlgBuffer[HASH_ALG_SIZE_BYTE];

    /** Stores the signing algorithm field of the header */
    uint8_t m_signAlgBuffer[SIGN_ALG_SIZE_BYTE];

    /** Stores the signature field of the header */
    uint8_t m_signatureBuffer[SIGNATURE_SIZE_BYTE];
};
#endif /** __FIRMWAREHEADER_H__ */

/**
 *  @}
 */