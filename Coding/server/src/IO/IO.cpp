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
 * @file IO.cpp
 * @author Luis Moser
 * @brief IO class
 * @date 06/21/2021
 *
 * @{
 */

#include <IO.h>

IO::IO() :
    m_ioMutex(xSemaphoreCreateMutex())
{
    if (NULL == m_ioMutex)
    {
        LOG_ERROR("IO mutex could not be created!");
    }
}

IO::~IO()
{
}

void IO::setPinMode(uint8_t gpio, uint8_t mode)
{
    pinMode(gpio, mode);
}

uint8_t IO::readGPIODebounced(uint8_t gpio)
{
    /* The last time a bounce took place */
    unsigned long lastBounceTime = 0;

    /* The previous GPIO reading. Assume active-low input */
    uint8_t lastKeyState = HIGH;

    /* Stores the current GPIO reading */
    uint8_t reading = HIGH;

    /* Code taken and modified from: https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce */
    do
    {
        reading = digitalRead(gpio);

        /* Voltage level transition occured */
        if (reading != lastKeyState)
        {
            /* Stop time from now on to decide if next reading should be ignored */
            lastBounceTime = millis();
        }

        /* Check if bouncing timespan elapsed. Evaluate current level */
        if ((millis() - lastBounceTime) > DEBOUNCE_DELAY_TIME_MS)
        {
            return reading;
        }

        lastKeyState = reading;
    } while (true);
}

uint8_t IO::readGPIO(uint8_t gpio)
{
    return digitalRead(gpio);
}

void IO::writeGPIO(uint8_t gpio, uint8_t value)
{
    xSemaphoreTake(m_ioMutex, portMAX_DELAY);
    digitalWrite(gpio, value);
    xSemaphoreGive(m_ioMutex);
}
