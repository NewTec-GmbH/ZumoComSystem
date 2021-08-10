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
 * @file UploadZumoCommand.h
 * @author Luis Moser
 * @brief UploadZumoCommand header
 * @date 08/03/2021
 *
 * @{
 */

#ifndef __UPLOADZUMOCOMMAND_H__
#define __UPLOADZUMOCOMMAND_H__

#include <FirmwareChecker.h>
#include <ApiResponse.h>
#include <Command.h>
#include <FileManager.h>

 /** Class which implements the firmare upload for the Zumo robot system */
class UploadZumoCommand : public Command
{
public:
    /**
     * Default Constructor
     */
    UploadZumoCommand();

    /**
     * Destructor
     */
    ~UploadZumoCommand();

    /**
     * Implements the API service business logic
     *
     * @param[in] request Reference to the incoming ApiRequest
     * @param[out] response Reference to the outgoing ApiResponse
     * @param[in] connectionCtx Pointer to Session class instance
     */
    void run(const ApiRequest& request, ApiResponse& response, Session* connectionCtx) const;

    /**
     * Implement the binary API service business logic
     *
     * @param[in] fwChecker Reference to the FirmwareChecker instance
     * @param[out] response Reference to the outgoing ApiResponse
     * @param[in] connectionCtx Pointer to Session class instance
     */
    void run(FirmwareChecker& fwChecker, ApiResponse& response, Session* connectionCtx);

private:
    /** Instance of the FileManager */
    FileManager m_fileManager;

    /** Specifies how many bytes of the firmware payload have been written into the file sytem */
    uint32_t m_writtenFirmwareBytes;

    /**
     * Helper function for writing the firmware payload into the file system
     *
     * @param[in] dataChunk Pointer to the input buffer which contains the data to be written to the file system
     * @param[in] chunkSize Specifies the size of the passed input buffer. Can be of 4096 bytes in size at max
     * @param[out] response The ApiResponse instance
     */
    void writeFile(const uint8_t* dataChunk, const uint16_t chunkSize, ApiResponse& response);
};
#endif /** __UPLOADZUMOCOMMAND_H__ */
