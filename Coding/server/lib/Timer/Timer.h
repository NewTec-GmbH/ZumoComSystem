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
 * @file Timer.h
 * @author Luis Moser
 * @brief Timer header
 * @date 07/22/2021
 *
 * @{
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include <Arduino.h>

 /** Simple class for registering cyclical ISR callbacks */
class Timer
{
private:
    /** Pointer to the timer handle */
    hw_timer_t* m_timerHandle;

    /** Specifies the counting frequency of the timer */
    static const uint32_t COUNTER_CLOCK_SPEED_HZ = 80000000;

    /** Specifies by which factor the counting frequency shall be divided */
    static const uint16_t PRESCALER_FACTOR = 40000;

    /** Specifies how many hardware timers are available on this target */
    static const uint8_t AVAILABLE_TIMERS = 4;

    /** Stores how many timers are currently used */
    static uint8_t m_numberOfActiveTimers;

public:
    /**
     * Constructor
     *
     * @param[in] callAfterSeconds specifies how many seconds need to be waited until next ISR invocation takes place
     */
    Timer(uint32_t callAfterSeconds);

    /**
     * Destructor
     */
    ~Timer();

    /**
     * Returns if there are still timers available
     *
     * @return Returns true if there is still a timer available
     */
    static bool timerAvailable();

    /**
     * Attaches the specified function to the timer event
     *
     * @return Returns true if successful, else false
     */
    bool registerISR(void (*isrFunction)(void));

    /**
     * Detaches the previously registered ISR from timer event
     *
     * @return Returns true if successful, else false
     */
    bool detachISR();

    /**
     * Enable the timer so that the ISRs can be invoked on timer event
     *
     * @return Returns true if successful, else false
     */
    bool enableTimer();

    /**
     * Disable the timer so that the ISRs cannot be invoked by the timer event anymore
     *
     * @return Returns true if successful, else false
     */
    bool disableTimer();
};
#endif /** __TIMER_H__ */
