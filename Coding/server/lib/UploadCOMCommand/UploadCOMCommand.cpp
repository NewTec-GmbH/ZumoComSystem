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
 * @file UploadCOMCommand.cpp
 * @author Luis Moser
 * @brief UploadCOMCommand.h class
 * @date 08/17/2021
 *
 * @{
 */

#include <UploadCOMCommand.h>
#include <ArduinoJson.h>
#include <FirmwareInfo.h>
#include <Log.h>
#include <Store.h>
#include <Session.h>

const char* UploadCOMCommand::TARGET_SYSTEM = "COM";
const bool UploadCOMCommand::OVERWRITE_FIRMWAREINFO = true;

UploadCOMCommand::UploadCOMCommand() :
    Command("uploadcom", NONE),
    BinaryCommand("uploadcom", NONE),
    m_fwChecker(),
    m_writtenFirmwareBytes(0),
    m_isInitialized(false),
    m_otaHandle(),
    m_writePartitionSize(0)
{
}

UploadCOMCommand::~UploadCOMCommand()
{
}

void UploadCOMCommand::run(const ApiRequest& request, ApiResponse& response, Session* connectionCtx)
{
    /*
    Reserve memory on stack for JSON structure which consists of two key-value pairs.
    The value specified in DOC_SIZE has been computed with the help of the ArduinoJson Assistant v6
    which is accessible at: https://arduinojson.org/v6/assistant/
    */
    const size_t DOC_SIZE = 48;
    StaticJsonDocument<DOC_SIZE> jsonDocument;
    DeserializationError jsonRet = deserializeJson(jsonDocument, request.getJsonPayload());

    /* Check shapeliness of incoming JSON payload */
    if ((DeserializationError::Ok == jsonRet) && (true == jsonDocument.containsKey("fileSizeBytes")))
    {
        uint32_t firmwareFileSize = jsonDocument["fileSizeBytes"];

        /*
        Only switch to API BINARY mode and set the API service to be executed when the firmware size does
        not exceeds the memory limits. Additionally, when writing the firmware, the UploadCOMCommand API service
        will keep track of the written bytes and abort writing to FS if it exceeds the maximum reserved memory capacity
        */
        if (FirmwareChecker::MAX_COM_FW_BLOB_SIZE_BYTE >= firmwareFileSize)
        {
            /* Delete FirmwareInfo if existent */
            FirmwareInfo::deleteInfo(TARGET_SYSTEM);
            if (true == Store::getInstance().saveFirmwareInfo())
            {
                connectionCtx->initBinaryMode(request.getCommandId(), firmwareFileSize);
                response.setStatusCode(SUCCESS);
            }
            else
            {
                response.setStatusCode(ERROR);
                LOG_ERROR("Could not open API BINARY mode and set UploadCOMCommand as API service because could not clear FirmwareInfo in persistent storage!");
            }
        }
        else
        {
            response.setStatusCode(BAD_REQUEST);
            LOG_ERROR("Could not open API BINARY mode and set UploadCOMCommand as API service because firmware image is too large!");
        }
    }
    else
    {
        response.setStatusCode(BAD_REQUEST);
        LOG_ERROR("Error on deserializing the ApiRequest jsonPayload object. JSON may be malformed!");
        LOG_ERROR(String("ArduinoJson result: ") + jsonRet.c_str());
    }
}

void UploadCOMCommand::run(ApiResponse& response, Session* connectionCtx)
{
    bool writeSuccessful = true;
    bool firmwareValid = false;

    esp_err_t otaWriteRetCode = ESP_FAIL;
    esp_err_t validateRetCode = ESP_FAIL;

    uint16_t chunkSize = 0;
    uint16_t bufferStartIdx = 0;
    uint8_t* pBinaryBuffer = nullptr;

    String computedHashValue = "";

    m_fwChecker.deserializeHeader(connectionCtx->m_binaryBuffer, connectionCtx->m_readBytes);

    /* Initialize the OTA update process */
    if (false == m_isInitialized)
    {
        /* Get handle to OTA partition (the partition which is currently not booted from) */
        const esp_partition_t* writePartition = esp_ota_get_next_update_partition(nullptr);
        if (nullptr != writePartition)
        {
            m_writePartitionSize = writePartition->size;

            if (connectionCtx->m_expectingBytes <= m_writePartitionSize)
            {
                esp_err_t retCode = esp_ota_begin(writePartition, connectionCtx->m_expectingBytes, &m_otaHandle);
                if (ESP_OK != retCode)
                {
                    LOG_ERROR("Could not begin the OTA process. Aborting now...");
                    LOG_ERROR(String("OTA-RetCode: ") + retCode);
                }
                m_isInitialized = (ESP_OK == retCode);
                response.setStatusCode(SUCCESS);
            }
            else
            {
                m_isInitialized = false;
                response.setStatusCode(ERROR);
                LOG_ERROR("Provided firmware image does not fit into OTA partition! Aborting now...");
            }

            if (FirmwareChecker::MAX_COM_FW_BLOB_SIZE_BYTE > m_writePartitionSize)
            {
                LOG_WARN("Value of MAX_COM_FW_BLOB_SIZE_BYTE is greater than the actual OTA partition size!");
            }
        }
        else
        {
            m_isInitialized = false;
            response.setStatusCode(ERROR);
            LOG_ERROR("Could not get OTA partition handle! Please ensure you're using a partition table with two OTA and a OTA data partition. Aborting now...");
        }
    }

    if (true == m_isInitialized)
    {
        /* Firmware file is still being transferred */
        if (connectionCtx->m_streamByteIdx <= connectionCtx->m_expectingBytes)
        {
            if (connectionCtx->m_streamByteIdx > FirmwareHeader::HEADER_SIZE_BYTE)
            {
                LOG_DEBUG("Deserializing payload");

                /* Part of binary buffer consists of header data */
                if (connectionCtx->m_streamByteIdx - connectionCtx->m_readBytes < FirmwareHeader::HEADER_SIZE_BYTE)
                {
                    chunkSize = connectionCtx->m_streamByteIdx - FirmwareHeader::HEADER_SIZE_BYTE;
                    bufferStartIdx = connectionCtx->m_readBytes - chunkSize;
                    pBinaryBuffer = &connectionCtx->m_binaryBuffer[bufferStartIdx];

                    if (true == m_fwChecker.deserializePayload(pBinaryBuffer, chunkSize))
                    {
                        otaWriteRetCode = writePartition(pBinaryBuffer, chunkSize);
                        if (ESP_OK != otaWriteRetCode)
                        {
                            LOG_ERROR("Could not write firmware into OTA partition! Aborting now...");
                            LOG_ERROR(String("OTA-RetCode: ") + otaWriteRetCode);
                        }
                        writeSuccessful = (ESP_OK == otaWriteRetCode);
                    }
                    else
                    {
                        writeSuccessful = false;
                    }
                }
                /* Binary buffer only consists of payload data */
                else
                {
                    if (true == m_fwChecker.deserializePayload(connectionCtx->m_binaryBuffer, connectionCtx->m_readBytes))
                    {
                        otaWriteRetCode = writePartition(connectionCtx->m_binaryBuffer, connectionCtx->m_readBytes);
                        if (ESP_OK != otaWriteRetCode)
                        {
                            LOG_ERROR("Could not write firmware into OTA partition! Aborting now...");
                            LOG_ERROR(String("OTA-RetCode: ") + otaWriteRetCode);
                        }
                        writeSuccessful = (ESP_OK == otaWriteRetCode);
                    }
                    else
                    {
                        writeSuccessful = false;
                    }
                }
            }
        }

        if (true == writeSuccessful)
        {
            /* Firmware file has been fully transferred */
            if (connectionCtx->m_streamByteIdx >= connectionCtx->m_expectingBytes)
            {
                /* Finish the OTA update process */
                validateRetCode = esp_ota_end(m_otaHandle);
                if (ESP_OK == validateRetCode)
                {
                    /* Check integrity of downloaded firmware file */
                    firmwareValid = m_fwChecker.isValid(TARGET_SYSTEM);

                    /* Write additional meta-information/FirmwareInfo into the persistent storage */
                    if ((true == FirmwareInfo::putInfo(TARGET_SYSTEM, computedHashValue, firmwareValid, m_writtenFirmwareBytes, OVERWRITE_FIRMWAREINFO))
                        && (true == Store::getInstance().saveFirmwareInfo()))
                    {
                        response.setStatusCode(SUCCESS);
                        LOG_INFO("Successfully saved COM firmware image and saved FirmwareInfo in persistent storage");
                    }
                    else
                    {
                        response.setStatusCode(ERROR);
                        LOG_ERROR("Could not save FirmwareInfo in persistent storage!");
                    }
                }
                else
                {
                    response.setStatusCode(ERROR);
                    LOG_ERROR("Could not valide the written OTA partition! Aborting now...");
                    LOG_ERROR(String("OTA-RetCode: ") + otaWriteRetCode);
                }

                /* Clean up */
                reset();

                /* Exit BINARY mode and switch back to TEXT mode */
                connectionCtx->exitBinaryMode();
            }
        }
        else
        {
            reset();

            response.setStatusCode(ERROR);
            LOG_ERROR("Could not deserialize payload or write firmware to OTA partition!");

            /* Exit BINARY mode and switch back to TEXT mode */
            connectionCtx->exitBinaryMode();
        }
    }
    else
    {
        /* Clean up */
        reset();

        LOG_ERROR("Could not initialize the OTA update process!");
        response.setStatusCode(ERROR);

        /* Exit BINARY mode and switch back to TEXT mode */
        connectionCtx->exitBinaryMode();
    }

#ifdef ACTIVATE_LOGGING
    const uint8_t PRINT_BUFFER_SIZE = 128;
    const uint8_t MULTIPLICATOR = 100;
    char buffer[PRINT_BUFFER_SIZE];
    uint8_t processedBytsPercent = static_cast<uint8_t>((connectionCtx->m_streamByteIdx / (float)connectionCtx->m_expectingBytes) * MULTIPLICATOR);

    /* Print the data into the output buffer */
    sprintf(buffer, "Processed %d of %d total bytes (%d%%)", connectionCtx->m_streamByteIdx, connectionCtx->m_expectingBytes, processedBytsPercent);
    LOG_DEBUG(String(buffer));
#endif
}

void UploadCOMCommand::reset()
{
    esp_ota_end(m_otaHandle);
    m_fwChecker.reset();
    m_writtenFirmwareBytes = 0;
    m_isInitialized = false;
    m_writePartitionSize = 0;
}

esp_err_t UploadCOMCommand::writePartition(const uint8_t* dataChunk, const uint16_t chunkSize)
{
    esp_err_t otaWriteRetCode = ESP_FAIL;

    if (m_writePartitionSize >= (m_writtenFirmwareBytes + chunkSize))
    {
        otaWriteRetCode = esp_ota_write(m_otaHandle, dataChunk, chunkSize);
        m_writtenFirmwareBytes += chunkSize;
        LOG_DEBUG(String("Wrote ") + chunkSize + " bytes into OTA partition");
    }
    else
    {
        LOG_ERROR("Received firmware image is too big! Aborting firmware write now! Deleting file now...");
    }
    return otaWriteRetCode;
}
