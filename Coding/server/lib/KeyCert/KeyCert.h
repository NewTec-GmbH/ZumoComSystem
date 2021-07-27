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
 * @file KeyCert.h
 * @author Luis Moser
 * @brief KeyCert header
 * @date 06/22/2021
 *
 * @{
 */

#ifndef __KEYCERT_H__
#define __KEYCERT_H__

#include <SSLCert.hpp>
#include <Arduino.h>

 /** Data structure for HTTPS/WSS server which supports JSON serialization */
class KeyCert
{
public:
    /**
    * Default Constructor
    */
    KeyCert();

    /**
    * Destructor
    */
    ~KeyCert();

    /**
    * Generates a new SSLCert for this class instance
    *
    * @return Returns true if successful, else false
    */
    bool generateNewCert();

    /**
     * Get the SSL cert required for HTTPSServer
     *
     * @return Returns SSLCert instance
     */
    httpsserver::SSLCert* getSSLCert();

    /**
     * Serializes this KeyCert object.
     *
     * @param[out] keyBuffer The output buffer to be filled with the serialized binary RSA key. Allocate memory previously
     * @param[out] certBuffer The output buffer to be filled with the serialized binary SSL cert. Allocate memory previously
     */
    void serialize(uint8_t* keyBuffer, uint8_t* certBuffer);

    /**
     * Deserializes this KeyCert object. All passed data is copied. Free passed buffers after this call
     *
     * @param[in] keyBuffer The input buffer which containts the serialized binary RSA key.
     * @param[in] certBuffer The input buffer which containts the serialized binary SSL cert.
     */
    void deserialize(uint8_t* keyBuffer, uint8_t* certBuffer);

    /** Size of the binary RSA key in bytes */
    static const size_t RSA_KEY_SIZE_BYTE = 1190;

    /** Size of the binary cert in bytes */
    static const size_t CERT_SIZE_BYTE = 766;

private:
    /**
     * Helper method which cleans up the SSLCert internal's memory which has been dynamically allocated
     */
    void freeSSLMemory();

    /**
    * The DER-X509 certificate which stores the private RSA key as well as the public certificate.
    * This data structure is used by the HTTPs/WSS servers
    */
    httpsserver::SSLCert m_sslCert;

    /** Stores the binary RSA key */
    static uint8_t m_binaryKey[RSA_KEY_SIZE_BYTE];

    /** Stores the binary SSL certificate */
    static uint8_t m_binaryCert[CERT_SIZE_BYTE];

    /** Saves if a SSL certificate has been generated for this instance */
    bool m_certGenerated;
};
#endif
