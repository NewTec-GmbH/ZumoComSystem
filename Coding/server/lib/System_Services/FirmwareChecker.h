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
 * @file FirmwareChecker.h
 * @author Luis Moser
 * @brief FirmwareChecker header
 * @date 08/02/2021
 * @addtogroup System Services
 * @{
 */

#ifndef __FIRMWARECHECKER_H__
#define __FIRMWARECHECKER_H__

#include <Arduino.h>
#include <FirmwareHeader.h>
#include <CryptoServices.h>

 /** Class for deserializing the firmware binary stream and checking the authenticity and integrity of ZUMO/COM firmware */
class FirmwareChecker
{
public:
    /** Specifies the maximum firmware payload size in bytes when the firmware is uploaded for the Zumo robot platform */
    static const uint32_t MAX_ZUMO_FW_BLOB_SIZE_BYTE = 28672;

    /** Specifies the maximum firmware payload size in bytes when the firmware is uploaded for the ComPlatform */
    static const uint32_t MAX_COM_FW_BLOB_SIZE_BYTE = 1310720;

    /**
     * Default Constructor
     */
    FirmwareChecker();

    /**
     * Destructor
     */
    ~FirmwareChecker();

    /**
     * Deserializes the passed binary data and re-creates the header structure.
     * Call this method until all bytes specified in HEADER_SIZE_BYTE in FirmwareHeader.h
     * have been successfully read.
     *
     * @param[in] dataChunk Pointer to the input buffer which contains the header binary data to be deserialized
     * @param[in] chunkSize Specifies the size of the passed input buffer. Can be of 4096 bytes in size at max
     */
    void deserializeHeader(const uint8_t* dataChunk, const uint16_t chunkSize);

    /**
     * Deserializes the passed payload and automatically incrementally computes the payload SHA256 hash value
     * which later will be compared with the decrypted signature hash value from the header, when the isValid() method is called.
     * Call this method until all bytes specified in MAX_ZUMO_FW_BLOB_SIZE_BYTE or MAX_COM_FW_BLOB_SIZE_BYTE in have been successfully read.
     * Do not call this method when you read the header data!
     *
     * @param[in] dataChunk Pointer to the input buffer which contains the header binary data to be deserialized
     * @param[in] chunkSize Specifies the size of the passed input buffer. Can be of 4096 bytes in size at max
     * @return Returns true if successful, else false
     */
    bool deserializePayload(const uint8_t* dataChunk, const uint16_t chunkSize);

    /**
     * Discards the computed hash value and starts computation from scratch
     */
    void reset();

    /**
     * Checks if the magic number/ID of the firmware header is correct
     *
     * @return Returns true if magic number/ID is valid, else false
     */
    bool idOK();

    /**
     * Reads the target which is specified in the firmware header file
     *
     * @param[out] target Contains the string which specifies the target system of this firmware file
     */
    void getTarget(String& target) const;

    /**
     * Returns the computed hash value if it is available
     *
     * @param[in] outputString The output hex string
     * @return Returns true if successful, else false
     */
    bool getComputedHashValue(String& outputString);

    /**
     * Checks if the passed firmware header is valid, if the target system matches, if the firmware payload size does not exceed
     * the reserved memory size and checks if the signature of the firmware file is valid.
     *
     * @param[in] expectedTarget The target system which is expected for this firmware file
     * @return Returns true if firmware file is valid, else false
     */
    bool isValid(const String& expectedTarget);

private:
    /** The ID string to be expected in the firmware header */
    static const char* EXPECTED_ID;

    /** The numeric 8 bit file version to be expected in the firmwar header */
    static const uint8_t EXPECTED_VERSION = 1;

    /** The used hash algorithm to be expected in the firmware header */
    static const char* EXPECTED_HASH_ALG;

    /** The used signing algorithm to be expected in the firmware header */
    static const char* EXPECTED_SIGN_ALG;

    /** The FirmwareHeader instance which containts the header data */
    FirmwareHeader m_fwHeader;

    /** The CryptoServices instance to be used for hashing and signature checks */
    CryptoServices m_crypto;

    /** Specifiess how many payload bytes have been read */
    uint32_t m_readPayloadBytes;
};
#endif /** __FIRMWARECHECKER_H__ */

/**
 *  @}
 */