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
 * @file System.h
 * @author Luis Moser
 * @brief System header
 * @date 06/22/2021
 * @addtogroup System Services
 * @{
 */

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

class Store;
class WiFiManager;
class HTTPWebServer;

#include <Arduino.h>

/** Class responsible for initializing the ComPlatform, starting, handling and stopping all running services */
class System
{
public:
    /**
     * Get System instance
     *
     * @return Returns System singleton instance
     */
    static System& getInstance()
    {
        static System instance;
        return instance;
    }

    /**
     * Initializes the ComPlatform and starts all services
     */
    void init();

    /**
     * This method needs to be called in loop() so that all required services can receive CPU time
     */
    void handleServices();

    /**
     * Shuts down all services and reboots the ComPlatform
     */
    void reset();

private:
    /** Reference to store */
    Store& m_store;

    /** Instance of WiFiManager */
    WiFiManager* m_wifimgr;

    /** Instance of HTTPWebServer */
    HTTPWebServer* m_webServer;

    /** Specifies how long the service handling task should be put to sleep */
    static const uint8_t SERVICE_HANDLING_SLEEP_TIME_MS = 1;

    /**
     * Default Constructor
     */
    System();

    /**
     * Destructor
     */
    ~System();
};
#endif /** __SYSTEM_H__ */

/**
 *  @}
 */