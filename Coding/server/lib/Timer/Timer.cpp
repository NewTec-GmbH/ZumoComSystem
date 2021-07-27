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
 * @file Timer.cpp
 * @author Luis Moser
 * @brief Timer class
 * @date 07/22/2021
 *
 * @{
 */

#include <Timer.h>

uint8_t Timer::m_numberOfActiveTimers = 0;

Timer::Timer(uint32_t callAfterSeconds) :
    m_timerHandle(nullptr)
{
    const bool RISING_EDGE_COUNT_UP_TRIGGER = true;
    const bool AUTO_RELOAD_COUNTER = true;
    uint32_t MAX_COUNTER_VALUE = (COUNTER_CLOCK_SPEED_HZ / PRESCALER_FACTOR) * callAfterSeconds;

    m_timerHandle = timerBegin(m_numberOfActiveTimers, PRESCALER_FACTOR, RISING_EDGE_COUNT_UP_TRIGGER);
    if (nullptr != m_timerHandle)
    {
        timerAlarmWrite(m_timerHandle, MAX_COUNTER_VALUE, AUTO_RELOAD_COUNTER);
        m_numberOfActiveTimers++;
    }
}

Timer::~Timer()
{
    if (nullptr != m_timerHandle)
    {
        timerEnd(m_timerHandle);
        m_numberOfActiveTimers--;
    }
}

bool Timer::timerAvailable()
{
    return (m_numberOfActiveTimers < AVAILABLE_TIMERS);
}

bool Timer::registerISR(void (*isrFunction)(void))
{
    bool retCode = false;
    if (nullptr != m_timerHandle)
    {
        const bool RISING_EDGE_INVOKE_TRIGGER = true;
        timerAttachInterrupt(m_timerHandle, isrFunction, RISING_EDGE_INVOKE_TRIGGER);
        retCode = true;
    }
    return retCode;
}

bool Timer::detachISR()
{
    bool retCode = false;
    if (nullptr != m_timerHandle)
    {
        timerDetachInterrupt(m_timerHandle);
        retCode = true;
    }
    return retCode;
}

bool Timer::enableTimer()
{
    bool retCode = false;
    if (nullptr != m_timerHandle)
    {
        timerAlarmEnable(m_timerHandle);
        retCode = true;
    }
    return retCode;
}

bool Timer::disableTimer()
{
    bool retCode = false;
    if (nullptr != m_timerHandle)
    {
        timerAlarmDisable(m_timerHandle);
        retCode = true;
    }
    return retCode;
}
