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

#include <CryptoServices.h>
#include <GPIOPins.h>

CryptoServices::CryptoServices() :
    m_hasherInstance()
{
    /* Initialize the random generator with seed with entropy from analog noise */
    randomSeed(analogRead(GPIOPins::PIN_ANALOG_NOISE_SEED));
}

CryptoServices::~CryptoServices()
{
}

bool CryptoServices::getRandomSalt(String& outputString) const
{
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
    uint8_t outputHash[HASH_LENGTH_BYTE];

    const uint8_t NUMBER_OF_PRINTABLE_CHARS = 2;
    char strBuffer[NUMBER_OF_PRINTABLE_CHARS + 1];

    m_hasherInstance.reset(HASH_LENGTH_BYTE);
    m_hasherInstance.update(inputString.c_str(), inputString.length());
    m_hasherInstance.finalize(outputHash, HASH_LENGTH_BYTE);

    /* Clear output buffer */
    outputString = "";

    for (uint8_t hexIdx = 0; hexIdx < HASH_LENGTH_BYTE; hexIdx++)
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
