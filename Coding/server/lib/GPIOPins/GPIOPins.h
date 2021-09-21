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
 * @file GPIOPins.h
 * @author Luis Moser
 * @brief GPIOPins header
 * @date 07/28/2021
 *
 * @{
 */

#ifndef __GPIOPINS_H__
#define __GPIOPINS_H__

#include <Arduino.h>

 /** Namespace for specifying all used GPIOs of the ESP32 */
namespace GPIOPins
{
    /** Pin for push button for system reset/AP mode start (ACTIVE LOW) */
    static const uint8_t PIN_WIFI_AND_RESET_KEY = 0;

    /** Pin for resetting the attached Zumo robot (ACTIVE LOW) */
    static const uint8_t PIN_ROBOT_RESET = 27;

    /** Pin for (dis-)connecting power from Zumo robot (ACTIVE LOW) */
    static const uint8_t PIN_ROBOT_ON_OFF = 15;

    /** Unconnected pin for reading random analog data to seed PRNG */
    static const uint8_t PIN_ANALOG_NOISE_SEED = 36;

    /** Pin for info LED RGB channel RED (ACTIVE LOW) */
    static const uint8_t INFO_LED_R = 16;

    /** Pin for info LED RGB channel GREEN (ACTIVE LOW) */
    static const uint8_t INFO_LED_G = 22;

    /** Pin for info LED RGB channel BLUE (ACTIVE LOW) */
    static const uint8_t INFO_LED_B = 21;
};
#endif /** __GPIOPINS_H__ */
