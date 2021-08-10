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
 * @file CryptoServices.h
 * @author Luis Moser
 * @brief CryptoServices header
 * @date 07/20/2021
 *
 * @{
 */

#ifndef __CRYPTOSERVICES_H__
#define __CRYPTOSERVICES_H__

#include <Arduino.h>
#include <BLAKE2b.h>
#include <mbedtls/md.h>
#include <mbedtls/pk.h>

 /** Simple class which provides basic cryptography algorithms */
class CryptoServices
{
public:
    /**
     * Default Constructor
     */
    CryptoServices();

    /**
     * Destructor
     */
    ~CryptoServices();

    /**
     * Returns a random salt string with SALT_LENGTH_BYTE characters
     *
     * @param[in] outputString The random salt string
     * @return Returns true if successful, else false
     */
    bool getRandomSalt(String& outputString) const;

    /**
     * Generates the Blake2b hash value of the cleartext and its salt
     *
     * @param[in] cleartext Reference to the cleartext string
     * @param[in] salt Reference to the salt string
     * @param[out] outputString The calculated hash value
     * @return Returns true if successful, else false
     */
    bool hashBlake2b(const String& cleartext, const String& salt, String& outputString);

    /**
     * Computes the SHA256 hash required for the signature verification based on passed binary data.
     * Needs to be called until the entire binary data stream has been read.
     * Call resetVerifySignature() to start from scratch and discard all previous calculations.
     * Call verifySignature() to get/finish hash computation and start verifying the RSA2048 signature
     *
     * @param[in] dataChunk Pointer to the input buffer which contains the binary data to be hashed
     * @param[in] dataSize Specifies the size of the passed input buffer. Can be of 4096 bytes in size at max
     * @return Returns true if successful, else false
     */
    bool updateVerifySignature(const uint8_t* dataChunk, const uint16_t dataSize);

    /**
     * Discards all previous computations/updateVerifySignature() calls and starts verification from scratch
     *
     * @return Returns true if successful, else false
     */
    bool resetVerifySignature();

    /**
     * Returns the computed hash value if it is available
     *
     * @param[in] outputString The output hex string
     * @return Returns true if successful, else false
     */
    bool getComputedHashValue(String& outputString);

    /**
     * Verifies the passed RSA2048 PKCS#1 v1.5 signature by decrypting the signature and comparing
     * the resulting hash with the pre-calculated hash of the passed binary data.
     * Please note, that only PKCS#1 padding is supported. Any other padding algorithms, such as OAEP or PSS are not supported.
     * Please note, that the signature needs to include additional meta information about the used hashing algorithm,
     * otherwise mbedTLS will not be able to verify the signature. Therefore do not calculate the digest separately when using OpenSSL!
     *
     * Example:
     *
     * CORRECT:     'openssl dgst -sha256 -sign privkey.pem < binary.bin > binary.sig.bin'
     *
     * INCORRECT:   'openssl dgst -sha256 -binary <binary.bin > binary.sha256.bin'
     *              'openssl rsautl -sign -inkey privkey.pem < binary.sha256.bin > binary.sig.bin'
     *
     * The hard-coded public RSA2048 key, which is placed in PublicSigningKey.h, will be used for signature verification.
     *
     * @param[in] signature Pointer to the signature binary data input buffer to be checked
     * @param[in] signatureSize The size of the passed binary buffer in bytes.
     * @return Returns true if signature is valid, else false
     */
    bool verifySignature(const uint8_t* signature, const uint16_t signatureSize);

private:
    /** Specifies the lenght of the random salt to be generated in byte */
    static const uint8_t SALT_LENGTH_BYTE = 64;

    /** Specifies the length of the output hash to be calculated */
    static const uint8_t BLAKE2b_LENGTH_BYTE = 64;

    /** Specifies the number of bytes used for a SHA256 hash */
    static const uint16_t SHA256_LENGTH_BYTE = 32;

    /** Instance of the Blake2 class from Crypto library */
    BLAKE2b m_hasherInstance;

    /** Stores the binary SHA256 hash value */
    uint8_t m_hashBuffer[SHA256_LENGTH_BYTE];

    /** Specifies if the hash has been computed */
    bool m_hashAvailable;

    /** Instance of the public key cryptography context */
    mbedtls_pk_context m_publicKeyContext;

    /** Instance of the message digest context */
    mbedtls_md_context_t m_messageDigestContext;
};
#endif /** __CRYPTOSERVICES_H__ */
