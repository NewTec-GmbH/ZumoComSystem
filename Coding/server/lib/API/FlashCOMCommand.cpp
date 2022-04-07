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
 * @file FlashCOMCommand.cpp
 * @author Luis Moser
 * @brief FlashCOMCommand.h class
 * @date 08/18/2021
 * @addtogroup API
 * @{
 */

#include <FlashCOMCommand.h>
#include <Permission.h>
#include <Store.h>
#include <FirmwareInfo.h>
#include <Log.h>
#include <esp_ota_ops.h>
#include <System.h>

const char* FlashCOMCommand::TARGET_SYSTEM = "COM";
const uint16_t FlashCOMCommand::REBOOT_DELAY_MS = 5000;

FlashCOMCommand::FlashCOMCommand() :
    Command("flashcom", FLASH_COM)
{
}

FlashCOMCommand::~FlashCOMCommand()
{
}

void FlashCOMCommand::run(const ApiRequest& request, ApiResponse& response, Session* connectionCtx)
{
    esp_err_t flashRetCode = ESP_FAIL;

    const FirmwareInfo* fwInfo = nullptr;
    Store& store = Store::getInstance();

    if (true == store.loadFirmwareInfo())
    {
        fwInfo = FirmwareInfo::getInfo(TARGET_SYSTEM);

        if ((true == fwInfo->isValid())
            && (fwInfo->getTargetSystem() == TARGET_SYSTEM))
        {
            const esp_partition_t* otaPartition = esp_ota_get_next_update_partition(nullptr);
            if (nullptr != otaPartition)
            {
                flashRetCode = esp_ota_set_boot_partition(otaPartition);
                if (ESP_OK == flashRetCode)
                {
                    /* Delete the FirmwareInfo because new free OTA slot will be empty */
                    FirmwareInfo::deleteInfo(TARGET_SYSTEM);
                    if (true == store.saveFirmwareInfo())
                    {
                        response.setStatusCode(SUCCESS);
                        LOG_INFO("Successfully flashed the firmware image to the COM system");
                        LOG_WARN(String("Rebooting in ") + REBOOT_DELAY_MS + String(" milliseconds!"));

                        delay(REBOOT_DELAY_MS);

                        /* Shut down all system services and reboot the ComPlatform */
                        System::getInstance().reset();
                    }
                    else
                    {
                        response.setStatusCode(ERROR);
                        LOG_ERROR("Could not delete FirmwareInfo for COM system!");
                    }
                }
                else
                {
                    response.setStatusCode(ERROR);
                    LOG_ERROR("Could not set the OTA partition to boot from");
                    LOG_ERROR(String("OTA-RetCode: ") + flashRetCode);
                }
            }
            else
            {
                response.setStatusCode(ERROR);
                LOG_ERROR("Could not find the OTA partition!");
            }
        }
        else
        {
            response.setStatusCode(ERROR);
            LOG_ERROR("Could not flash the firmware image to COM system because firmware is invalid!");
        }
    }
    else
    {
        response.setStatusCode(ERROR);
        LOG_ERROR("Could not fetch FirmwareInfo for COM system from persistent storage!");
    }
}

/**
 *  @}
 */
