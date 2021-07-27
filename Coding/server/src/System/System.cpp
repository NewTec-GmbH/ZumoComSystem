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
#include <KeyCert.h>
#include <User.h>
#include <Key.h>
#include <Log.h>

SemaphoreHandle_t System::m_genKeyCertSemaphore = {0};

System::System() :
    m_store(Store::getInstance()),
    m_wifimgr(),
    m_webServer()
{
}

System::~System()
{
}

void System::init()
{
    NetworkCredentials apCredentials;

    /* Register an ISR for ComPlatform reset on Reset key push */
    Key::getInstance().registerSystemReset();
    LOG_DEBUG("Reset-ISR registered");

    LOG_DEBUG("Init/setup task running on core #" + String(xPortGetCoreID()));

    /* Initialize and aquire binary semaphore */
    m_genKeyCertSemaphore = xSemaphoreCreateBinary();
    if (nullptr == m_genKeyCertSemaphore)
    {
        LOG_ERROR("KeyCert generation semaphore could not be created!");
    }

    /* Check if a KeyCert exists, if not, generate new one asynchronously */
    registerKeyCertGenTask();

    /* Generate the unique SSID for this specific ComPlatform system */
    apCredentials.setSSID("ComPlatform", false);
    apCredentials.setPassphrase("21091986");
    m_store.setAPCredentials(apCredentials);

    /* Read WiFi key if AP should be spawned */
    if (true == Key::getInstance().readKey())
    {
        m_wifimgr.startAP();
    }
    else
    {
        /* Load NetworkCredentials from persistent storage */
        if (true == m_store.loadSTACredentials())
        {
            m_wifimgr.startSTA();
        }
        else
        {
            LOG_ERROR("No NetworkCredentials available");
            m_wifimgr.startAP();
            LOG_INFO("AP spwaned because there are no network credentials available");
        }
    }

    /* Initialize the file system */
    FileManager::initFS();

    /* Load Users */
    if (true == m_store.loadUsers())
    {
        LOG_DEBUG("Successfully loaded users from persistent storage");
    }
    else
    {
        LOG_ERROR("Could not load users from persistent storage");
    }

    /* Create and save admin account with default credentials and full priviliges if it is missing */
    if (true == User::checkAdminAccount())
    {
        m_store.saveUsers();
    }

    /* Start the background task to enable session timeouts */
    Session::start();

    /* Await KeyCert generation task execution */
    xSemaphoreTake(m_genKeyCertSemaphore, portMAX_DELAY);
    xSemaphoreGive(m_genKeyCertSemaphore);

    /* Init HTTPs and WSS servers */
    if (true == m_webServer.startServer())
    {
        LOG_DEBUG("HTTPs and WSS servers successfully started");
    }
    else
    {
        LOG_ERROR("Could not start the HTTPs and WSS servers!");
    }

    LOG_INFO("ComPlatform fully booted up...");
}

void System::reset()
{
    LOG_INFO("ComPlatform will be restarted now...");

    /* Shut down DNS servers and WiFi module */
    m_wifimgr.stopAP();
    m_wifimgr.stopSTA();

    /* Close NVS and store */
    m_store.closeStore();

    /* Shut down HTTPS/WSS servers */
    m_webServer.stopServer();

    ESP.restart();
}

void System::handleServices()
{
    m_wifimgr.handleAP_DNS();
    m_webServer.handleServer();

    static const uint8_t SLEEP_TIME_MS = 1;
    delay(SLEEP_TIME_MS);
}

void System::genKeyCertTask(void* parameter)
{
    Store& store = Store::getInstance();

    LOG_DEBUG("KeyCert generation task running on core #" + String(xPortGetCoreID()));

    /* Generate and save a new KeyCert */
    if (false == store.loadKeyCert())
    {
        LOG_DEBUG("Missing KeyCert. Generating new SSLCert...");

        if (true == store.getKeyCert().generateNewCert())
        {
            LOG_DEBUG("New KeyCert created");

            if (true == store.saveKeyCert())
            {
                LOG_DEBUG("New KeyCert saved");
            }
            else
            {
                LOG_ERROR("Could not save the created SSL certificate to persistent storage");
            }
        }
        else
        {
            LOG_ERROR("Could not generate a new SSL certificate. Rebooting in 2 seconds...");

            const uint16_t ERROR_REBOOT_DELAY_TIME_MS = 2000;
            delay(ERROR_REBOOT_DELAY_TIME_MS);
            System::getInstance().reset();
        }

        LOG_DEBUG("New KeyCert successfully created");
    }
    else
    {
        LOG_DEBUG("KeyCert successfully loaded from persistent storage!");
    }

    /* Notify init task about finished task */
    xSemaphoreGive(m_genKeyCertSemaphore);

    /* Destroy this task */
    vTaskDelete(nullptr);
}

void System::registerKeyCertGenTask()
{
    /* Big stack required, otherwise RSA2048 key generation would override stack canary */
    const uint16_t STACK_SIZE_BYTE = 16384;

    /* Use lowest possible priority because this task does not have a blocking system call */
    const uint8_t PRIORITY = 0;

    /* Pin task to core 1 to avoid CPU time starvation of idle task */
    const uint8_t CPU_CORE = 1;

    xTaskCreatePinnedToCore(
        genKeyCertTask,
        "KeyCertGen",
        STACK_SIZE_BYTE,
        nullptr,
        PRIORITY,
        nullptr,
        CPU_CORE);
}
