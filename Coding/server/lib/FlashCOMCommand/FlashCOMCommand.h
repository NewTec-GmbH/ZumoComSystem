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
 * @file FlashCOMCommand.h
 * @author Luis Moser
 * @brief FlashCOMCommand.h header
 * @date 08/18/2021
 *
 * @{
 */

#ifndef __FLASHCOMCOMMAND_H__
#define __FLASHCOMCOMMAND_H__

#include <Command.h>

 /** Class which implements the firmare flash for the COM system */
class FlashCOMCommand : public Command
{
public:
    /**
     * Default Constructor
     */
    FlashCOMCommand();

    /**
     * Destructor
     */
    ~FlashCOMCommand();

    /**
     * Implements the API service business logic
     *
     * @param[in] request Reference to the incoming ApiRequest
     * @param[out] response Reference to the outgoing ApiResponse
     * @param[in] connectionCtx Pointer to Session class instance
     */
    void run(const ApiRequest& request, ApiResponse& response, Session* connectionCtx) const;

private:
    /** Dedicated target of the firmware file */
    static const char* TARGET_SYSTEM;
};
#endif /** __FLASHCOMCOMMAND_H__ */
