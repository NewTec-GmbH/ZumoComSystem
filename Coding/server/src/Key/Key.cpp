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
 * @file Key.cpp
 * @author Luis Moser
 * @brief Key class
 * @date 06/25/2021
 * 
 * @{
 */

#include <Key.h>

bool Key::blockingCheckWifiKeyLongPress()
{
    // Stop time from now on
    unsigned long startTime = millis();

    // Store the current time when next reading is done
    unsigned long currentTime;

    do
    {
        // Registered a released key. Abort
        if (HIGH == m_io.readGPIODebounced(WIFI_AND_RESET_KEY_PIN))
        {
            return false;
        }
        currentTime = millis();
    } while ((currentTime - startTime) < LONG_PRESS_TIME);

    return true;
}

void Key::registerSystemReset()
{
    attachInterrupt(WIFI_AND_RESET_KEY_PIN, Key::systemResetISR, FALLING);
    LOG_DEBUG("System-Reset ISR registered");
}

void Key::systemResetISR()
{
    // Create a new FreeRTOS task
    xTaskCreate(
        resetTask,
        "SystemReset",
        16384,
        NULL,
        1,
        NULL);
}

void Key::resetTask(void *parameter)
{
    if (LOW == IO::getInstance().readGPIODebounced(WIFI_AND_RESET_KEY_PIN))
    {
        System::getInstance().reset();
    }

    // Destroy this task
    vTaskDelete(NULL);
}