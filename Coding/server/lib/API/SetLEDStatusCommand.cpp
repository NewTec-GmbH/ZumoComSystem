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
 * @file SetLEDStatusCommand.cpp
 * @author Gabryel Reyes
 * @brief SetLEDStatusCommand class
 * @date 09/12/2022
 * @addtogroup API
 * @{
 */

#include <SetLEDStatusCommand.h>
#include <ArduinoJson.h>
#include <Log.h>
#include <GPIOPins.h>
#include <Arduino.h>

SetLEDStatusCommand::SetLEDStatusCommand() :
    Command("setledstatus", NONE),
    m_io(IO::getInstance())
{
}

SetLEDStatusCommand::~SetLEDStatusCommand()
{
}

void SetLEDStatusCommand::run(const ApiRequest &request, ApiResponse &response, Session *connectionCtx)
{
    /*
    Reserve memory on stack for JSON structure which consists of one key-value pair.
    The value specified in DOC_SIZE has been computed with the help of the ArduinoJson Assistant v6
    which is accessible at: https://arduinojson.org/v6/assistant/
    */
    const size_t DOC_SIZE = 128;
    StaticJsonDocument<DOC_SIZE> jsonDocument;
    DeserializationError jsonRet = deserializeJson(jsonDocument, request.getJsonPayload());

    /* Check shapeliness of incoming JSON payload */
    if ((DeserializationError::Ok == jsonRet) && (true == jsonDocument.containsKey("led") && (true == jsonDocument.containsKey("status"))))
    {
        String targetLED = jsonDocument["led"].as<String>();
        uint8_t targetStatus = jsonDocument["status"].as<uint8_t>();

        if ((HIGH == targetStatus) || (LOW == targetStatus))
        {
            LOG_INFO("Setting LED " + targetLED + " to " + targetStatus);
            if (targetLED.equals("RED"))
            {
                m_io.setPinMode(GPIOPins::INFO_LED_R, OUTPUT);
                m_io.writeGPIO(GPIOPins::INFO_LED_R, targetStatus);
            }
            else if (targetLED.equals("GREEN"))
            {
                m_io.setPinMode(GPIOPins::INFO_LED_G, OUTPUT);
                m_io.writeGPIO(GPIOPins::INFO_LED_G, targetStatus);
            }
            else if (targetLED.equals("BLUE"))
            {
                m_io.setPinMode(GPIOPins::INFO_LED_B, OUTPUT);
                m_io.writeGPIO(GPIOPins::INFO_LED_B, targetStatus);
            }
            else
            {
                response.setStatusCode(BAD_REQUEST);
                LOG_ERROR("Unknown LED requested");
            }
        }
    }
    else
    {
        response.setStatusCode(BAD_REQUEST);
        LOG_ERROR("Error on deserializing the ApiRequest jsonPayload object. JSON may be malformed!");
        LOG_ERROR(String("ArduinoJson result: ") + jsonRet.c_str());
    }
}

/**
 *  @}
 */