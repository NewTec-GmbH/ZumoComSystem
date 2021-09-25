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
 * @file Key.h
 * @author Luis Moser
 * @brief Key header
 * @date 06/25/2021
 *
 * @{
 */

#ifndef __KEY_H__
#define __KEY_H__

#include <Arduino.h>
#include <IO.h>
#include <System.h>

 /** Class for accessing active-low push keys */
class Key
{
public:
    /**
     * Get Key instance
     *
     * @return Returns singleton instance
     */
    static Key& getInstance()
    {
        static Key instance;
        return instance;
    }

    /**
     * Registers an ISR which resets the ComPlatform system and which is invoked when key is pressed
     */
    void registerSystemReset();

    /**
     * Checks if the key connected to WIFI_AND_RESET_KEY_PI is being pressed. Automatically debounces the key
     *
     * @return Returns true, if button has been pressed, otherwise false
     */
    bool readKey() const;

private:
    /** Reference to IO class */
    IO& m_io;

    /** Specifies push duration for a long-press event */
    static const uint32_t LONG_PRESS_TIME_MS = 1000;

    /**
    * Default Constructor
    */
    Key();

    /**
     * Destructor
     */
    ~Key();

    /**
     * Task which checks the push key level and resets the ComPlatform
     */
    static void resetTask(void* parameter);

    /**
     * ISR which resets the ComPlatform which will be inovked when push key is being pressed
     */
    static void systemResetISR();
};
#endif /** __KEY_H__ */
