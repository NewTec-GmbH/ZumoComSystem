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
 * @file System.cpp
 * @author Luis Moser
 * @brief System class
 * @date 06/22/2021
 * 
 * @{
 */
#include <System.h>

void System::init()
{
    /* Specifies time how long ComPlatform should wait when error occured before reboot happens */
    const uint16_t ERROR_REBOOT_DELAY_TIME_MS = 2000;

    bool retCode = false;

    /* Instance which contains private RSA key and SSL cert for WSS and HTTPs servers */
    KeyCert keycert;

    /* Generate the unique SSID for this specific ComPlatform system */
    NetworkCredentials apCredentials;
    apCredentials.setSSID("ComPlatform", false);
    apCredentials.setPassphrase("21091986");
    m_store.setAPCredentials(apCredentials);

    /* Register an ISR for ComPlatform reset on Reset key push */
    Key::getInstance().registerSystemReset();
    LOG_DEBUG("Reset-ISR registered");

    /* Read WiFi key if AP should be spawned */
    bool isAccessPointRequested = Key::getInstance().readKey();

    /* Generate and save a new KeyCert */
    retCode = m_store.loadKeyCert();
    if (false == retCode)
    {
        LOG_DEBUG("Missing KeyCert. Generating new SSLCert...");
        keycert = m_store.getKeyCert();
        if (true == keycert.generateNewCert())
        {
            LOG_DEBUG("New KeyCert created");
            if (true == m_store.saveKeyCert())
            {
                LOG_DEBUG("New KeyCert saved");
            }
            else
            {
                LOG_ERROR("Could not save the created SSL certificate to disk");
            }
        }
        else
        {
            LOG_ERROR("Could not generate a new SSL certificate. Rebooting in 2 seconds...");
            delay(ERROR_REBOOT_DELAY_TIME_MS);
            System::getInstance().reset();
        }
    }

    if (true == isAccessPointRequested)
    {
        m_wifimgr.startAP();
    }
    else
    {
        /* Load NetworkCredentials */
        if (true == m_store.loadSTACredentials())
        {
            m_wifimgr.startSTA();
        }
        else
        {
            LOG_ERROR("No NetworkCredentials available");
            m_wifimgr.startAP();
            LOG_DEBUG("AP spwaned because there are no network credentials available");
        }
    }

    LOG_DEBUG("ComPlatform successfully booted up!");

    /* Load Users */
    /* Load Permissions */
    /* Init HTTPs Server */
    /* Init WSS Server */
}

void System::handleServices()
{
    const uint8_t SLEEP_TIME_MS = 1;

    m_wifimgr.handleAP_DNS();
    delay(SLEEP_TIME_MS);
}

void System::reset()
{
    LOG_DEBUG("ComPlatform will be restarted");
    m_wifimgr.stopAP();
    m_wifimgr.stopSTA();
    ESP.restart();
}