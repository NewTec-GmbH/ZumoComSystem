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
 * @file FileManager.h
 * @author Luis Moser
 * @brief FileManager header
 * @date 07/07/2021
 *
 * @{
 */

#ifndef __FILEMANAGER_H__
#define __FILEMANAGER_H__

#include <Arduino.h>
#include <Log.h>
#include <FS.h>
#include <SPIFFS.h>

 /** Class used for simply reading and writing binary files */
class FileManager
{
public:
    /**
     * Default Constructor
     */
    FileManager();

    /**
     * Destructor
     */
    ~FileManager();

    /**
     * Formats the data partition with SPIFFS file system and restores the directory structure
     * @return Returns true if successful, else false
     */
    static bool initFS();

    /**
     * Opens a new file for further access.
     *
     * @param[in] fileName The file to be accessed. Needs to start with '/'
     * @param[in] mode The access mode to be used on the file
     * @return Returns true if successful, else false
     */
    bool openFile(String fileName, const char* mode);

    /**
     * Closes a previously opened file and writes all unwritten data to file
     */
    void closeFile();

    /**
     * Sets the file pointer to the beginning (byte 0) of the file
     *
     * @return Returns true if successful, else false
     */
    bool resetFilePointer();

    /**
     * Reads the content from the opened file into the specified buffer in 4K blocks (4096 byte).
     * If the file size exceeds 4K, this method needs to be called multiple times.
     * If the remaining data to be read is smaller than 4K, only the remaining bytes will be written into the buffer.
     * Please note, that the buffer needs to be allocated first.
     *
     * @param[out] buffer The buffer to be filled with the file data
     * @return Returns how many bytes have been written into the output buffer. Returns -1 in case of error
     */
    int16_t read4KBlock(uint8_t* buffer);

    /**
     * Writes the content from the specified buffer into the opened file in 4K blocks (4096 byte).
     * If the data to be written exceeds 4K, this method needs to be called multiple times.
     * Please note, that only that many bytes will be written, which have been specified with the size argument.
     *
     * @param[in] buffer The buffer whose data should be written into file
     * @param[in] size The number of bytes to be written from the buffer into the file
     * @return Returns the number of written bytes. Returns -1 in case of error
     */
    int16_t write4KBlock(uint8_t* buffer, uint16_t size);

    /**
     * Checks if the specified file exists
     * @param[in] fileName The absoulte path to the file to be checked for existence
     * @return Returns if the the file is existing
     */
    static bool fileExists(String fileName);

    /**
     * Returns the size of the currently opened file in bytes.
     *
     * @return Returns the size of the file in bytes. Returns -1 if file does not exist.
     */
    int32_t getFileSize();

    /**
     * Returns the size of the specified file in bytes
     *
     * @param[in] fileName The absoulte path to the file to be checked for size
     * @return Returns the size of the file
     */
    static int32_t getFileSize(String fileName);

    /**
     * Lists all existing files in which are located in root directory.
     *
     * @return Returns string array which contains the file names of all existing files
     */
    static std::vector<String> listFiles();

private:
    /**
     * Prints information about the current state of the FS
     *
     * @return Returns the string containing the FS informations
     */
    static String getInfo();

    /** Handle to the currently opened filed */
    File m_fileHandle;
};
#endif /** __FILEMANAGER_H__ */
