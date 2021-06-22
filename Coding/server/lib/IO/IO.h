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
 * @file IO.h
 * @author Luis Moser
 * @brief IO header
 * @date 06/21/2021
 * 
 * @{
 */

#include <Arduino.h>
#include <Logger.h>

/** Provides abstraction for IO functionality for ComPlatform */
class IO
{
private:
    /** The GPIO input pin used for the WiFi enable/system reset button*/
    static const uint8_t WIFI_AND_RESET_KEY_PIN = 0;

    /** The GPIO output pin used to write the RESET line of robot*/
    static const uint8_t ROBOT_RESET_PIN = 2;

    /** The time in ms while RESET line is pulled down*/
    static const uint32_t ROBOT_RESET_TIME = 500;

    /** The time in ms until interaction is long button press */
    static const uint32_t LONG_PRESS_TIME = 1000;

    /** 
     * The timespan between two two level transitions
     * (in ms) in which level changes are ignored 
     */
    static const uint8_t DEBOUNCE_DELAY_TIME = 50;

    /**
     * Mutex which is used to avoid that two or more concurrent
     * tasks, which use the IO class, can have write access to
     * the GPIOs at once
     */
    SemaphoreHandle_t ioMutex;

    /**
     * Default constructor
     */
    IO()
    {
        pinMode(WIFI_AND_RESET_KEY_PIN, INPUT_PULLUP);
        pinMode(ROBOT_RESET_PIN, OUTPUT);

        ioMutex = xSemaphoreCreateMutex();

        if(NULL == ioMutex)
        {
            LOG_ERROR("IO-Mutex could not be created!");
        }
    }

    /**
     * Destructor
     */
    ~IO()
    {
    }

    /**
     * Reads value of GPIO with bouncing button
     * 
     * @param[in] gpio The GPIO to be read
     * @return Returns LOW if button has been pressed,
     * returns HIGH if button has not been pressed
     */
    static uint8_t debouncedRead(uint8_t gpio);

    /**
     * ISR which resets the ComPlatform
     * which will be inovked
     * when WiFi/Reset key is being pressed
     */
    static void systemResetISR();

    /**
     * FreeRTOS task to reset system
     */
    static void resetTask(void* parameter);

public:
    /** 
     * Get IO instance
     * 
     * @return Returns the IO singleton instance
     */
    static IO &getInstance()
    {
        static IO instance;
        return instance;
    }

    /**
     * Reset the connected robot
     * with the help of the RESET line
     * which is connected to the GPIOs
     */
    void resetRobotNow();

    /**
     * Registers an ISR which resets the
     * ComPlatform system and which is 
     * invoked when WiFi/Reset key is pressed
     */
    void registerSystemReset();

    /**
     * Checks if the button is pressed,
     * while this method is called, blocks
     * while the button is pressed
     * for max. LONG_PRESS_TIME.
     * Checks if the key has been held for
     * thath long.
     * 
     * @return Returns true if key has been pressed
     * for specified time duration LONG_PRESS_TIME
     */
    bool blockingCheckWifiKeyLongPress();
};