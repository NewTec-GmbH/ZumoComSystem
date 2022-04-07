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
 * @file UploadCOMCommand.h
 * @author Luis Moser
 * @brief UploadCOMCommand.h header
 * @date 08/17/2021
 * @addtogroup API
 * @{
 */

#ifndef __UPLOADCOMCOMMAND_H__
#define __UPLOADCOMCOMMAND_H__

#include <Command.h>
#include <BinaryCommand.h>
#include <FirmwareChecker.h>
#include <esp_ota_ops.h>

 /** Class which implements the firmare upload for the COM system */
class UploadCOMCommand : public Command, public BinaryCommand
{
public:
    /**
     * Default Constructor
     */
    UploadCOMCommand();

    /**
     * Destructor
     */
    ~UploadCOMCommand();

    /**
     * Implements the API service business logic
     *
     * @param[in] request Reference to the incoming ApiRequest
     * @param[out] response Reference to the outgoing ApiResponse
     * @param[in] connectionCtx Pointer to Session class instance
     */
    void run(const ApiRequest& request, ApiResponse& response, Session* connectionCtx);

    /**
     * Implement the binary API service business logic
     *
     * @param[out] response Reference to the outgoing ApiResponse
     * @param[in] connectionCtx Pointer to Session class instance
     */
    void run(ApiResponse& response, Session* connectionCtx);

    /**
     * Clears all data from previous command execution
     */
    void reset();

private:
    /** Dedicated target of the firmware file */
    static const char* TARGET_SYSTEM;

    /** Specifies if FirmwareInfo should be overwritten */
    static const bool OVERWRITE_FIRMWAREINFO;

    /** Instance of FirmwareChecker for verifying header and payload */
    FirmwareChecker m_fwChecker;

    /** Specifies how many bytes of the firmware payload have been written into the file sytem */
    uint32_t m_writtenFirmwareBytes;

    /** Specifies if the OTA update process has been initialized */
    bool m_isInitialized;

    /** Handle for writing firmware */
    esp_ota_handle_t m_otaHandle;

    /** Specifies the actual OTA partitions size in bytes */
    uint32_t m_writePartitionSize;

    /**
     * Writes the data into the OTA partition
     *
     * @param[in] dataChunk The data to be written
     * @param[in] chunkSize The size of the passed binary buffer
     */
    esp_err_t writePartition(const uint8_t* dataChunk, const uint16_t chunkSize);
};
#endif /** __UPLOADCOMCOMMAND_H__ */

/**
 *  @}
 */