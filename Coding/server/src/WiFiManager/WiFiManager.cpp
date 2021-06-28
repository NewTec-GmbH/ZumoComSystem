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
 * @file WiFiManager.cpp
 * @author Luis Moser
 * @brief WiFiManager class
 * @date 06/25/2021
 * 
 * @{
 */

#include <WiFiManager.h>
#include <APCredentials.h>
#include <WiFi.h>
#include <System.h>

bool WiFiManager::startAP()
{
    if ((false == m_staActive) && (false == m_apActive))
    {
        // Start AP and DNS services
        const uint8_t CHANNEL_NR = 1;
        const uint8_t MAX_CLIENT_NR = 4;
        const uint16_t REBOOT_DELAY_TIME_MS = 2000;

        m_apActive = WiFi.softAP(AP_SSID, AP_PSK, CHANNEL_NR, false, MAX_CLIENT_NR);
        IPAddress ipaddr = WiFi.softAPIP();

        if (true == m_apActive)
        {
            LOG_DEBUG("AP successfully started");
            LOG_DEBUG("SSID: " + String(AP_SSID) + ", PSK: " + AP_PSK);
            LOG_DEBUG("IP-Address: " + ipaddr.toString());

            // Register A-Record which translates to current IP address (DNS)
            m_dnsRetCode = m_dnsServer->start(DNS_PORT, HOSTNAME, ipaddr);
            if (true == m_dnsRetCode)
            {
                LOG_DEBUG("mDNS server successfully started");
                LOG_DEBUG(String(HOSTNAME));
            }
            else
            {
                LOG_ERROR("Could not start DNS service. Rebooting in 2 seconds...");
                delay(REBOOT_DELAY_TIME_MS);
                System::getInstance().reset();
            }
        }
        else
        {
            LOG_ERROR("Could not start AP mode. Rebooting in 2 seconds...");
            delay(REBOOT_DELAY_TIME_MS);
            System::getInstance().reset();
        }
    }
    else
    {
        LOG_ERROR("Could not start AP mode because STA mode or AP mode are still active");
    }

    return (m_apActive && m_dnsRetCode);
}

void WiFiManager::handleAP_DNS()
{
    if ((true == m_apActive) && (true == m_dnsRetCode))
    {
        m_dnsServer->processNextRequest();
    }
}

bool WiFiManager::stopAP()
{
    // Disconnect all clients and shut down WiFi module
    bool retCode = false;
    if (true == m_apActive)
    {
        m_dnsServer->stop();
        retCode = WiFi.softAPdisconnect(false);
        if (true == retCode)
        {
            LOG_DEBUG("AP mode successfully shut down");
        }
        else
        {
            LOG_ERROR("Could not shut down AP mode");
        }
    }
    else
    {
        retCode = false;
        LOG_ERROR("Could not shut down AP mode because AP is not active");
    }
    return retCode;
}

bool WiFiManager::startSTA()
{
    if ((false == m_apActive) && (false == m_staActive))
    {
        const uint16_t RECONECCT_RETRY_DELAY_MS = 500;
        const uint16_t REBOOT_DELAY_TIME_MS = 2000;

        NetworkCredentials credentials = m_store.getNetworkCredentials();
        WiFi.begin(credentials.getSSID().c_str(), credentials.getPSK().c_str());
        while (WL_CONNECTED != WiFi.status())
        {
            delay(RECONECCT_RETRY_DELAY_MS);
            LOG_DEBUG("Connecting to external network...");
        }

        if (WL_CONNECTED == WiFi.status())
        {
            m_staActive = true;
            LOG_DEBUG("STA mode successfully started");
            LOG_DEBUG("SSID: " + credentials.getSSID());
            LOG_DEBUG("IP-Address: " + WiFi.localIP().toString());

            // Register A-Record which translates to current IP address (mDNS)
            MDNS.begin(HOSTNAME);
            LOG_DEBUG("DNS server successfully started");
        }
        else
        {
            m_staActive = false;
            LOG_ERROR("Could not start STA mode. Rebooting in 2 seconds...");
            delay(REBOOT_DELAY_TIME_MS);
            System::getInstance().reset();
        }
    }
    else
    {
        LOG_ERROR("Could not start STA mode because STA mode or AP mode are still active");
    }
    return m_staActive;
}

bool WiFiManager::stopSTA()
{
    // Disconnect from AP and shut down WiFi module
    bool retCode = false;
    if (m_staActive)
    {
        // Stop the DNS service
        MDNS.end();

        // Shut down STA mode
        retCode = WiFi.disconnect(false);
        if (true == retCode)
        {
            LOG_DEBUG("STA mode successfully shut down");
        }
        else
        {
            LOG_ERROR("Could not shut down STA mode");
        }
    }
    else
    {
        retCode = false;
        LOG_ERROR("Could not shut down STA mode because STA mode is not active");
    }
    return retCode;
}
