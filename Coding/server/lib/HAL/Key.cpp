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
 * @addtogroup HAL
 * @{
 */

#include <Key.h>
#include <Log.h>
#include <GPIOPins.h>

Key::Key() :
    m_io(IO::getInstance())
{
}

Key::~Key()
{
}

void Key::registerSystemReset()
{
    attachInterrupt(GPIOPins::PIN_WIFI_AND_RESET_KEY, Key::systemResetISR, FALLING);
    LOG_DEBUG("System-Reset ISR registered");
}

bool Key::readKey() const
{
    return (LOW == m_io.readGPIODebounced(GPIOPins::PIN_WIFI_AND_RESET_KEY));
}

void Key::resetTask(void* parameter)
{
    if (true == Key::getInstance().readKey())
    {
        System::getInstance().reset();
    }

    /* Destroy this task */
    vTaskDelete(nullptr);
}

void Key::systemResetISR()
{
    /* Use large stack to be able to use Serial.println() without issues */
    const uint16_t STACK_SIZE_BYTE = 8192;

    /* Set task to highest possible priority to always ensure that reset can be invoked */
    const uint8_t PRIORITY = configMAX_PRIORITIES - 1;

    /* Create a new FreeRTOS task */
    BaseType_t retCode = xTaskCreate(
        resetTask,
        "SystemReset",
        STACK_SIZE_BYTE,
        nullptr,
        PRIORITY,
        nullptr);

    if (pdPASS != retCode)
    {
        LOG_ERROR("Could not start system reset task!");
    }
}

/**
 *  @}
 */