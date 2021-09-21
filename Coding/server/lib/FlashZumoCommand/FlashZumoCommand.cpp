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
 * @file FlashZumoCommand.cpp
 * @author Luis Moser
 * @brief FlashZumoCommand.h class
 * @date 09/20/2021
 *
 * @{
 */

#include <FlashZumoCommand.h>
#include <Permission.h>
#include <FileManager.h>
#include <Store.h>
#include <Log.h>
#include <Zumo32U4.h>

const char* FlashZumoCommand::FIRMWARE_FILENAME = "/zumo_firmware.bin";
const char* FlashZumoCommand::TARGET_SYSTEM = "ZUMO";

FlashZumoCommand::FlashZumoCommand() :
    Command("flashzumo", FLASH_ZUMO),
    m_zumoDriver(Zumo32U4::getInstance())
{
}

FlashZumoCommand::~FlashZumoCommand()
{
}

bool FlashZumoCommand::checkFirmwareIntegrity(const FirmwareInfo& info)
{
    const uint16_t BUFFER_SIZE_BYTES = 4096;
    uint8_t readBuffer[BUFFER_SIZE_BYTES];
    uint16_t readBytes = 0;

    /* Read header */

    // TODO: Check integrity
    // do
    // {
    //     readBytes = fileManager.read4KBlock(readBuffer);
    // } while (0 != readBytes);

    // TODO
    return true;
}

void FlashZumoCommand::run(const ApiRequest& request, ApiResponse& response, Session* connectionCtx)
{
    const FirmwareInfo* fwInfo = nullptr;
    Store& store = Store::getInstance();

    FileManager fileManager;

    const uint16_t BUFFER_SIZE_BYTES = 4096;
    uint8_t readBuffer[BUFFER_SIZE_BYTES];
    uint16_t readBytes = 0;

    bool writeSuccess = true;

    if (true == store.loadFirmwareInfo())
    {
        if (true == fileManager.openFile(FIRMWARE_FILENAME, FILE_READ))
        {
            fwInfo = FirmwareInfo::getInfo(TARGET_SYSTEM);
            if ((nullptr != fwInfo)
                && (true == fwInfo->isValid())
                && (fwInfo->getTargetSystem() == TARGET_SYSTEM))
            {
                if (true == checkFirmwareIntegrity(*fwInfo))
                {
                    uint16_t firmwareSize = fileManager.getFileSize();
                    m_zumoDriver.beginWriteFirmware(firmwareSize, fwInfo->getPayloadHashValue());

                    do
                    {
                        readBytes = fileManager.read4KBlock(readBuffer);
                        if (0 < readBytes) {
                            writeSuccess = m_zumoDriver.writeFirmwareChunk(readBuffer, readBytes);
                            if (false == writeSuccess)
                            {
                                break;
                            }
                        }

                    } while (0 != readBytes);

                    if (true == writeSuccess)
                    {
                        if (true == m_zumoDriver.finalizeWriteFirmware())
                        {
                            response.setStatusCode(SUCCESS);
                            LOG_INFO("Successfully flashed the firmware to ZUMO!");
                        }
                        else
                        {
                            LOG_ERROR("Could not validate the written firmware image!");
                        }
                    }
                    else
                    {
                        response.setStatusCode(ERROR);
                        LOG_ERROR("Could not write firmware into ZUMO!");
                    }
                }
                else
                {
                    response.setStatusCode(ERROR);
                    LOG_ERROR("Could not flash the firmware image to ZUMO system because firmware integrity is corrupted!");
                }
            }
            else
            {
                response.setStatusCode(ERROR);
                LOG_ERROR("Could not flash the firmware image to ZUMO system because firmware is invalid!");
            }

            fileManager.closeFile();
        }
        else
        {
            response.setStatusCode(ERROR);
            LOG_ERROR("Could not open the firmware file for ZUMO system");
        }
    }
    else
    {
        response.setStatusCode(ERROR);
        LOG_ERROR("Could not fetch FirmwareInfo for ZUMO system from persistent storage!");
    }
}
