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
#include <WiFi.h>
#include <System.h>

const String WiFiManager::HOSTNAME = "complatform.local";

WiFiManager::WiFiManager() : m_store(Store::getInstance()),
                             m_dnsServer(),
                             m_dnsRetCode(false),
                             m_apActive(false),
                             m_staActive(false)

{
}

WiFiManager::~WiFiManager()
{
}

bool WiFiManager::startAP()
{
    /* The IP address to be used for AP mode */
    IPAddress ipaddr;

    NetworkCredentials apCredentials = m_store.getAPCredentials();

    if ((false == m_staActive) && (false == m_apActive))
    {
        /* Start AP and DNS services */
        m_apActive = WiFi.softAP(apCredentials.getSSID().c_str(), apCredentials.getPassphrase().c_str(), WIFI_CHANNEL_NO, false, MAX_CLIENT_NO);
        ipaddr = WiFi.softAPIP();

        if (true == m_apActive)
        {
            LOG_DEBUG("AP successfully started");
            LOG_INFO("SSID: " + apCredentials.getSSID());
            LOG_INFO("Passphrase: " + apCredentials.getPassphrase());
            LOG_INFO("IP-Address: " + ipaddr.toString());

            /* Register A-Record which translates to current IP address (DNS) */
            m_dnsRetCode = m_dnsServer.start(DNS_PORT, HOSTNAME.c_str(), ipaddr);
            if (true == m_dnsRetCode)
            {
                LOG_DEBUG("DNS server successfully started");
                LOG_INFO("Hostname: " + HOSTNAME);
            }
            else
            {
                LOG_ERROR("Could not start DNS service. Rebooting in 2 seconds...");
                delay(ERROR_REBOOT_DELAY_TIME_MS);
                System::getInstance().reset();
            }
        }
        else
        {
            LOG_ERROR("Could not start AP mode. Rebooting in 2 seconds...");
            delay(ERROR_REBOOT_DELAY_TIME_MS);
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
        m_dnsServer.processNextRequest();
    }
}

bool WiFiManager::stopAP()
{
    /* Disconnect all clients and shut down WiFi module */
    bool retCode = false;
    if (true == m_apActive)
    {
        m_dnsServer.stop();
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
        LOG_ERROR("Could not shut down AP mode because AP is not active");
    }
    return retCode;
}

bool WiFiManager::startSTA()
{
    NetworkCredentials staCredentials = m_store.getSTACredentials();

    if ((false == m_apActive) && (false == m_staActive))
    {
        WiFi.begin(staCredentials.getSSID().c_str(), staCredentials.getPassphrase().c_str());

        /* Try to connect until there is a connection */
        while (WL_CONNECTED != WiFi.status())
        {
            delay(WIFI_CONNECT_RETRY_DELAY_MS);
            LOG_INFO("Connecting to external network...");
        }

        if (WL_CONNECTED == WiFi.status())
        {
            m_staActive = true;
            LOG_DEBUG("STA mode successfully started");
            LOG_INFO("SSID: " + staCredentials.getSSID());
            LOG_INFO("IP-Address: " + WiFi.localIP().toString());

            /* Register A-Record which translates to current IP address (mDNS) */
            MDNS.begin(HOSTNAME.c_str());
            LOG_DEBUG("mDNS server successfully started");
        }
        else
        {
            m_staActive = false;
            LOG_ERROR("Could not start STA mode. Rebooting in 2 seconds...");
            delay(ERROR_REBOOT_DELAY_TIME_MS);
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
    /* Disconnect from AP and shut down WiFi module */
    bool retCode = false;
    if (m_staActive)
    {
        /* Stop the DNS service */
        MDNS.end();

        /* Shut down STA mode */
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
        LOG_ERROR("Could not shut down STA mode because STA mode is not active");
    }
    return retCode;
}