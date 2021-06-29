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
#include <ArduinoJson.h>

/** Data structure for network credentials which supports JSON serialization */
class NetworkCredentials
{
public:
    /** Custom constructor with arguments */
    NetworkCredentials(String ssid, String psk) : m_ssid(ssid), m_psk(psk)
    {
    }

    /** Default constructor */
    NetworkCredentials()
    {
    }

    /** Destructor */
    ~NetworkCredentials()
    {
    }

    /** Returns Service Set Identifier 
     * 
     * @return Returns the SSID string
    */
    String getSSID();

    /** Sets Service Set Identifier
     * 
     * @param[in] ssid The SSID to be set
     */
    void setSSID(String ssid);

    /** Returns Pre Shared Key
     * 
     * @return Returns the PSK string
     */
    String getPSK();

    /** Sets Pre Shared Key
     * 
     * @param[in] psk The PSK to be set
     */
    void setPSK(String psk);

    /** Returns JSON string
     * 
     * @return Returns the serialized object in JSON string
     */
    String serialize();

    /** Re-creates object from mserialized JSON string
     * 
     * @param serial The serialized JSON string
     * @return Returns false in case of failure, true in case of success
     */
    bool deserialize(String serial);

private:
    /** The SSID to be stored */
    String m_ssid;

    /** The PSK to be stored */
    String m_psk;
};
#endif /** __NETWORKCREDENTIALS_H__ */