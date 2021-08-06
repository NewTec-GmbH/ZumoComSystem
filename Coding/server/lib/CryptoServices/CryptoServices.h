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

#include <Arduino.h>
#include <BLAKE2b.h>

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

private:
    /** Specifies the lenght of the random salt to be generated in byte */
    static const uint8_t SALT_LENGTH_BYTE = 64;

    /** Specifies the length of the output hash to be calculated */
    static const uint8_t HASH_LENGTH_BYTE = 64;

    /** Instance of the Blake2 class from Crypto library */
    BLAKE2b m_hasherInstance;
};
