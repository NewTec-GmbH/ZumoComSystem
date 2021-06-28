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
 * @file Robot.h
 * @author Luis Moser
 * @brief Robot header
 * @date 06/25/2021
 * 
 * @{
 */

#ifndef __ROBOT_H__
#define __ROBOT_H__

#include <Arduino.h>
#include <IO.h>

/** Class for accessing robot */
class Robot
{
public:
    /**
     * Get Robot instance
     * 
     * @return Returns singleton instance
     */
    static Robot &getInstance()
    {
        static Robot instance;
        return instance;
    }

    /**
     * Reset the connected robot
     * with the help of the RESET line
     * which is connected to the GPIOs
     */
    void resetRobotNow();

private:
    /**
     * Default Constructor
     */
    Robot()
    {
        m_io.setPinMode(ROBOT_RESET_PIN, OUTPUT);
    }

    /**
     * Destructor
     */
    ~Robot()
    {
    }

    /** Reference to IO class */
    IO &m_io = IO::getInstance();

    /** The GPIO output pin used to write the RESET line of robot*/
    static const uint8_t ROBOT_RESET_PIN = 2;

    /** The time in ms while RESET line is pulled down*/
    static const uint32_t ROBOT_RESET_TIME = 500;
};
#endif /** __ROBOT_H__ */