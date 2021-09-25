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
 * @file NetworkCredentials.h
 * @author Luis Moser
 * @brief NetworkCredentials header
 * @date 06/16/2021
 *
 * @{
 */

#ifndef __NETWORKCREDENTIALS_H__
#define __NETWORKCREDENTIALS_H__

#include <Arduino.h>

 /** Data structure for network credentials which supports JSON serialization */
class NetworkCredentials
{
public:
    /**
     * Default constructor
     */
    NetworkCredentials();

    /**
     * Destructor
     */
    ~NetworkCredentials();

    /**
     * Returns the Service Set Identifier (SSID)
     *
     * @return Returns the SSID string
    */
    const String& getSSID() const;

    /**
     * Sets Service Set Identifier. Please note that the lenght of the SSID should not exceed 32 printable chars
     *
     * @param[in] ssid The SSID to be set
     * @param[in] staMode Specifies if credentials are to be used in STA mode.
     * @return Returns true if the SSID is well-formed, else false
     */
    bool setSSID(const String& ssid, const bool staMode);

    /**
     * Returns the WiFi passphrase
     *
     * @return Returns the passphrase string
     */
    const String& getPassphrase() const;

    /**
     * Sets the passphrase used for the WiFi. Please note that the length of the passphrase should range between 8 and 63 printable chars
     * if this NetworkCredentials instance is used for STA mode and limited in the range between 8 and 50 printable chars if the AP mode is
     * used because the unique device ID will be appended for SSID uniqueness.
     *
     * @param[in] passphrase The passphrase to be set
     * @return Returns true if the passphrase is well-formed, else false
     */
    bool setPassphrase(const String& passphrase);

    /**
     * Returns JSON string
     *
     * @param[out] serial The serialized object as JSON string
     * @return Returns true if successful, else false
     */
    bool serialize(String& serial) const;

    /**
     * Re-creates object from serialized JSON string.
     * Checks validity of SSID and passphrase and only deserializes them when they are valid
     *
     * @param serial The serialized JSON string
     * @param staCredentials Specifies if the passed credentials are used for STA mode
     * @return Returns true if SSID and passphrase are well-formed and the deserialization was successful, else false
     */
    bool deserialize(const String& serial, const bool staCredentials);

private:
    /** Maximum number of printable chars (excluding null terminator) for SSIDs according to IEEE 802.11 */
    static const uint8_t MAX_SSID_LENGTH_CHARS = 31;

    /** Minimum number of printable chars (excluding null terminator) for passphrases according to IEEE 802.11*/
    static const uint8_t MIN_PASSPHRASE_LENGTH_CHARS = 8;

    /** Maximum number of printable chars (excluding null terminator) for passphrases according to IEEE 802.11*/
    static const uint8_t MAX_PASSPHRASE_LENGTH_CHARS = 63;

    /** The SSID to be stored */
    String m_ssid;

    /** The WiFi passphrase to be stored */
    String m_passphrase;
};
#endif /** __NETWORKCREDENTIALS_H__ */
