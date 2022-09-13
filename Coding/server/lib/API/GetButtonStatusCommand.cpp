/*
BSD 3-Clause License

Copyright (c) 2022, NewTec GmbH
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
 * @file GetButtonStatusCommand.cpp
 * @author Gabryel Reyes
 * @brief GetButtonStatusCommand class
 * @date 09/12/2022
 * @addtogroup API
 * @{
 */

#include <GetButtonStatusCommand.h>
#include <ArduinoJson.h>
#include <Log.h>
#include <GPIOPins.h>
#include <Arduino.h>

GetButtonStatusCommand::GetButtonStatusCommand() :
    Command("getbuttonstatus", NONE),
    m_io(IO::getInstance())
{
}

GetButtonStatusCommand::~GetButtonStatusCommand()
{
}

void GetButtonStatusCommand::run(const ApiRequest& request, ApiResponse& response, Session* connectionCtx)
{
    String serialButtonStatus = "";
    
    uint8_t statusButtonA = m_io.readGPIODebounced(GPIOPins::PIN_BUTTON_A);
    uint8_t statusButtonB = m_io.readGPIODebounced(GPIOPins::PIN_BUTTON_B);
    uint8_t statusButtonC = m_io.readGPIODebounced(GPIOPins::PIN_BUTTON_C);

    serialButtonStatus = "{\"A\":" + String(statusButtonA) +
                         ", \"B\":" + String(statusButtonB) +
                         ", \"C\":" + String(statusButtonC) + "}";

    response.setStatusCode(SUCCESS);
    response.setJsonPayload(serialButtonStatus);
}

/**
 *  @}
 */