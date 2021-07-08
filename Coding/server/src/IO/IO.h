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
#include <Log.h>

/** Provides abstraction for IO functionality for ComPlatform */
class IO
{
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
     * Specifies the GPIO pin direction
     * 
     * @param[in] gpio The GPIO pin to be set
     * @param[in] mode The direction of the GPIO pin
     */
    void setPinMode(uint8_t gpio, uint8_t mode);

    /**
     * Reads the specified GPIO input but also works with bouncing input signals (e.g. from push keys)
     * 
     * @param[in] gpio The GPIO pin to be read
     * @return Returns the read GPIO value
     */
    uint8_t readGPIODebounced(uint8_t gpio);

    /**
     * Reads the specified GPIO input
     * 
     * @param[in] gpio The GPIO pin to be read
     * @return Returns the read GPIO value
     */
    uint8_t readGPIO(uint8_t gpio);

    /**
     * Writes to the specified GPIO output
     * 
     * @param[in] gpio The GPIO pin to be written to
     * @param[in] value The value to be written
     */
    void writeGPIO(uint8_t gpio, uint8_t value);

private:
    /**
     * Default constructor
     */
    IO();

    /**
     * Destructor
     */
    ~IO();

    /**
     * Mutex which is used to avoid that two or more concurrent tasks,
     * which use the IO class, can have write access to the GPIOs at once
     */
    SemaphoreHandle_t m_ioMutex;

    /** The timespan between two two level transitions in which level changes are ignored */
    static const uint8_t DEBOUNCE_DELAY_TIME_MS = 50;
};