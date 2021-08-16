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
 * @file UploadZumoCommand.cpp
 * @author Luis Moser
 * @brief UploadZumoCommand class
 * @date 08/03/2021
 *
 * @{
 */

#include <UploadZumoCommand.h>
#include <Store.h>
#include <Session.h>
#include <FirmwareInfo.h>
#include <ArduinoJson.h>
#include <Log.h>

UploadZumoCommand::UploadZumoCommand() :
    Command("uploadzumo", NONE),
    BinaryCommand("uploadzumo", NONE),
    m_fileManager(),
    m_fwChecker(),
    m_writtenFirmwareBytes(0)
{
}

UploadZumoCommand::~UploadZumoCommand()
{
}

void UploadZumoCommand::run(const ApiRequest& request, ApiResponse& response, Session* connectionCtx) const
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
        connectionCtx->initBinaryMode(request.getCommandId(), firmwareFileSize);
        response.setStatusCode(SUCCESS);
    }
    else
    {
        response.setStatusCode(BAD_REQUEST);
        LOG_ERROR("Error on deserializing the ApiRequest jsonPayload object. JSON may be malformed!");
        LOG_ERROR(String("ArduinoJson result: ") + jsonRet.c_str());
    }
}

void UploadZumoCommand::run(ApiResponse& response, Session* connectionCtx)
{
    m_fwChecker.deserializeHeader(connectionCtx->m_binaryBuffer, connectionCtx->m_readBytes);

    const char* FIRMWARE_FILENAME = "/zumo_firmware.bin";
    const char* TARGET_SYSTEM = "ZUMO";
    const bool OVERWRITE_FIRMWAREINFO = true;

    bool fileOpened = false;
    bool writeSuccessful = true;
    bool firmwareValid = false;

    uint16_t chunkSize = 0;
    uint16_t bufferStartIdx = 0;
    uint8_t* pBinaryBuffer = nullptr;

    String computedHashValue = "";

    fileOpened = m_fileManager.fileOpened();
    if (false == fileOpened)
    {
        fileOpened = m_fileManager.openFile(FIRMWARE_FILENAME, FILE_WRITE);
    }

    if (true == fileOpened)
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

                    writeSuccessful = ((true == m_fwChecker.deserializePayload(pBinaryBuffer, chunkSize))
                        && (true == writeFile(pBinaryBuffer, chunkSize)));
                }
                /* Binary buffer only consists of payload data */
                else
                {
                    writeSuccessful = ((true == m_fwChecker.deserializePayload(connectionCtx->m_binaryBuffer, connectionCtx->m_readBytes))
                        && (true == writeFile(connectionCtx->m_binaryBuffer, connectionCtx->m_readBytes)));
                }
            }
        }

        if (true == writeSuccessful)
        {
            /* Firmware file has been fully transferred */
            if (connectionCtx->m_streamByteIdx >= connectionCtx->m_expectingBytes)
            {
                /* Flush the buffer and close the firmware image file */
                m_fileManager.closeFile();

                /* Check integrity of downloaded firmware file */
                firmwareValid = m_fwChecker.isValid(TARGET_SYSTEM);

                /* Write additional meta-information/FirmwareInfo into the persistent storage */
                if ((true == m_fwChecker.getComputedHashValue(computedHashValue)
                    && (true == FirmwareInfo::putInfo(TARGET_SYSTEM, computedHashValue, firmwareValid, m_writtenFirmwareBytes, OVERWRITE_FIRMWAREINFO))
                    && (true == Store::getInstance().saveFirmwareInfo())))
                {
                    response.setStatusCode(SUCCESS);
                    LOG_INFO("Successfully saved ZUMO firmware image and saved FirmwareInfo in persistent storage");
                }
                else
                {
                    response.setStatusCode(ERROR);
                    LOG_ERROR("Could not save FirmwareInfo in persistent storage!");
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
            /* Exit BINARY mode and switch back to TEXT mode */

            response.setStatusCode(ERROR);
            LOG_ERROR("Could not deserialize payload or write firmware to file system!");

            connectionCtx->exitBinaryMode();
        }
    }
    else
    {
        /* Clean up */
        reset();

        LOG_ERROR(String("Could not open file: ") + FIRMWARE_FILENAME);
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
    sprintf(buffer, "Processed %d of %d bytes (%d%%)", connectionCtx->m_streamByteIdx, connectionCtx->m_expectingBytes, processedBytsPercent);
    LOG_DEBUG(String(buffer));
#endif
}

bool UploadZumoCommand::writeFile(const uint8_t* dataChunk, const uint16_t chunkSize)
{
    bool retCode = true;
    uint16_t writtenBytes = 0;

    if (FirmwareChecker::MAX_ZUMO_FW_BLOB_SIZE_BYTE >= (m_writtenFirmwareBytes + chunkSize))
    {
        writtenBytes = m_fileManager.write4KBlock(dataChunk, chunkSize);
        m_writtenFirmwareBytes += writtenBytes;
        LOG_DEBUG(String("Wrote ") + writtenBytes + " bytes into file system");

        if (chunkSize != writtenBytes)
        {
            retCode = false;
            LOG_ERROR("Could not entirely write firmware image chunk into file system!");
        }
    }
    else
    {
        retCode = false;
        LOG_ERROR("Received firmware image is too big! Aborting firmware write now!");
    }
    return retCode;
}

void UploadZumoCommand::reset()
{
    m_writtenFirmwareBytes = 0;
    m_fileManager.closeFile();
    if (true == m_fwChecker.reset())
    {
        LOG_INFO("UploadZumoCommand has been successfuly reset!");
    }
    else
    {
        LOG_ERROR("Could not reset FirmwareChecker/UploadZumoCommand!");
    }
}
