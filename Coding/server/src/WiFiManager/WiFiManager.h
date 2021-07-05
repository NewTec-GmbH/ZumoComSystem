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
 * @file WiFiManager.h
 * @author Luis Moser
 * @brief WiFiManager header
 * @date 06/25/2021
 * 
 * @{
 */

#ifndef __WIFIMANAGER_H__
#define __WIFIMANAGER_H__

#include <Store.h>
#include <Log.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <DNSServer.h>

/** Class which manages STA and AP mode */
class WiFiManager
{
public:
    /**
     * Default Constructor
     */
    WiFiManager()
    {
    }

    /**
     * Destructor
     */
    ~WiFiManager()
    {
    }

    /**
     * Starts the access point of the ComPlatform if the STA mode is not active
     * 
     * @return Returns true if successful, else false
     */
    bool startAP();

    /**
     * Stops the access point if it has been started before
     * 
     * @return Returns true if successful, else false
     */
    bool stopAP();

    /**
     * This method needs to be called in a loop so that the DNS server can receive CPU time
     */
    void handleAP_DNS();

    /**
     * Starts the station mode of the ComPlatform if the AP mode is not active
     * 
     * @return Returns true if active, else false
     */
    bool startSTA();

    /**
     * Stops the station mode if it has been started before
     * 
     * @return Returns true if active, else false
     */
    bool stopSTA();

private:
    /** Reference to store */
    Store &m_store = Store::getInstance();

    /** The SSID to be used for AP mode **/
    String AP_SSID = "ComPlatform";

    /** The passphrase to be used for AP mode **/
    String AP_PASSPHRASE = "21091986";

    /** Instance of DNS server for AP mode */
    DNSServer m_dnsServer;

    /** Used port for DNS service */
    const uint8_t DNS_PORT = 53;

    /** Saves if DNS could be started successfully */
    bool m_dnsRetCode = false;

    /** ComPlatform's hostname */
    const String HOSTNAME = "complatform.local";

    /** The WiFi channel to be used */
    const uint8_t WIFI_CHANNEL_NO = 1;

    /** The max number of clients which can access AP at once */
    const uint8_t MAX_CLIENT_NO = 4;

    /** Delay time until the ComPlatform reboots after WiFi failure */
    const uint16_t ERROR_REBOOT_DELAY_TIME_MS = 2000;

    /** Delay time until ComPlatform tries to re-connect to WiFi */
    const uint16_t WIFI_CONNECT_RETRY_DELAY_MS = 500;

    /** Saves if AP mode is active */
    bool m_apActive = false;

    /** Saves if STA mode is active */
    bool m_staActive = false;
};
#endif /** __WIFIMANAGER_H__ */