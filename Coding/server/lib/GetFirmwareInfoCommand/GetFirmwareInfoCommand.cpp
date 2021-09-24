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
 * @file GetFirmwareInfoCommand.cpp
 * @author Luis Moser
 * @brief GetFirmwareInfoCommand class
 * @date 09/16/2021
 *
 * @{
 */

#include <GetFirmwareInfoCommand.h>
#include <ArduinoJson.h>
#include <Log.h>
#include <FirmwareInfo.h>
#include <Arduino.h>

GetFirmwareInfoCommand::GetFirmwareInfoCommand() :
    Command("getfirmwareinfo", NONE)
{
}

GetFirmwareInfoCommand::~GetFirmwareInfoCommand()
{
}

void GetFirmwareInfoCommand::run(const ApiRequest& request, ApiResponse& response, Session* connectionCtx)
{
    /*
    Reserve memory on stack for JSON structure which consists of one key-value pair.
    The value specified in DOC_SIZE has been computed with the help of the ArduinoJson Assistant v6
    which is accessible at: https://arduinojson.org/v6/assistant/
    */
    const size_t DOC_SIZE = 48;
    StaticJsonDocument<DOC_SIZE> jsonDocument;
    DeserializationError jsonRet = deserializeJson(jsonDocument, request.getJsonPayload());

    const FirmwareInfo* firmwareInfo = nullptr;
    String serialFirmwareInfo = "";

    /* Check shapeliness of incoming JSON payload */
    if ((DeserializationError::Ok == jsonRet) && (true == jsonDocument.containsKey("target")))
    {
        /* Get the FirmwareInfo instance for the searched target system */
        String targetSystem = jsonDocument["target"].as<String>();
        firmwareInfo = FirmwareInfo::getInfo(targetSystem);

        /* Only proceed if FirmwareInfo exists */
        if (nullptr != firmwareInfo)
        {
            if (true == firmwareInfo->serializeInstance(serialFirmwareInfo))
            {
                response.setStatusCode(SUCCESS);
                response.setJsonPayload(serialFirmwareInfo);
                LOG_INFO(String("Successfully serialized requested FirmwareInfo for target ") + targetSystem);
            }
            else
            {
                response.setStatusCode(ERROR);
                LOG_ERROR(String("Could not serialize FirmwareInfo for target ") + targetSystem);
            }
        }
        else
        {
            response.setStatusCode(ERROR);
            LOG_WARN(String("Could not find FirmwareInfo for target ") + targetSystem);
        }
    }
    else
    {
        response.setStatusCode(BAD_REQUEST);
        LOG_ERROR("Error on deserializing the ApiRequest jsonPayload object. JSON may be malformed!");
        LOG_ERROR(String("ArduinoJson result: ") + jsonRet.c_str());
    }
}
