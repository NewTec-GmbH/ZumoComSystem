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
 * @file FlashZumoCommand.h
 * @author Luis Moser
 * @brief FlashZumoCommand.h header
 * @date 08/23/2021
 * @addtogroup API
 * @{
 */

#ifndef __FLASHZUMOCOMMAND_H__
#define __FLASHZUMOCOMMAND_H__

#include <Command.h>

class Zumo32U4;

/** Class which implements the firmare flash for the Zumo system */
class FlashZumoCommand : public Command
{
public:
    /**
     * Default Constructor
     */
    FlashZumoCommand();

    /**
     * Destructor
     */
    ~FlashZumoCommand();

    /**
     * Implements the API service business logic
     *
     * @param[in] request Reference to the incoming ApiRequest
     * @param[out] response Reference to the outgoing ApiResponse
     * @param[in] connectionCtx Pointer to Session class instance
     */
    void run(const ApiRequest& request, ApiResponse& response, Session* connectionCtx);

private:
    /** Reference to instance of Zumo robot driver used for flashing */
    Zumo32U4& m_zumoDriver;

    /** The firmware target system string */
    static const char* TARGET_SYSTEM;

    /** The filename string used for storing and loading the firmware in the FS */
    static const char* FIRMWARE_FILENAME;
};
#endif /** __FLASHZUMOCOMMAND_H__ */

/**
 *  @}
 */