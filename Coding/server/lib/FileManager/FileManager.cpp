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
 * @file FileManager.cpp
 * @author Luis Moser
 * @brief FileManager class
 * @date 07/07/2021
 *
 * @{
 */

#include <FileManager.h>
#include <SPIFFS.h>
#include <Log.h>

FileManager::FileManager() :
    m_fileHandle()
{
}

FileManager::~FileManager()
{
    closeFile();
}

bool FileManager::initFS()
{
    bool retCode = false;
    if (false == SPIFFS.begin(false))
    {
        LOG_WARN("No SPIFFS file system found. Formatting now...");

        if (true == SPIFFS.format())
        {
            LOG_DEBUG("Data partition successfully formatted!");

            if (true == SPIFFS.begin(false))
            {
                LOG_INFO("SPIFFS file system successfully mounted");
                retCode = true;
            }
            else
            {
                LOG_WARN("No SPIFFS file system found. Could not mount the file system!");
            }
        }
        else
        {
            LOG_ERROR("Could not format data partition");
        }
    }
    else
    {
        LOG_DEBUG("File system successfully initialized");
        retCode = true;
    }

#if (0 != ACTIVATE_LOGGING)
    String outputString;
    getInfo(outputString);
    LOG_INFO(outputString);
#endif

    return retCode;
}

void FileManager::closeFS()
{
    /* Unmount the FS */
    SPIFFS.end();
    LOG_INFO("SPIFFS FS successfully unmounted!");
}

bool FileManager::openFile(const String& fileName, const char* mode)
{
    bool retCode = true;
    const uint8_t MAX_FILENAME_LENGTH = 31;

    /* Close possibily opened files */
    if (true == m_fileHandle)
    {
        closeFile();
    }

    /* SPIFFS filenames are limited in length */
    if (MAX_FILENAME_LENGTH >= fileName.length())
    {
        m_fileHandle = SPIFFS.open(fileName, mode);
    }

    if (false == m_fileHandle)
    {
        LOG_ERROR("File " + String(fileName) + " could not be opened!");
        retCode = false;
    }
    return retCode;
}

bool FileManager::fileOpened()
{
    return (true == m_fileHandle);
}

bool FileManager::deleteFile(const String& fileName)
{
    bool retCode = true;
    if (true == fileExists(fileName))
    {
        retCode = SPIFFS.remove(fileName);
    }

    if (true == retCode)
    {
        LOG_INFO(String("File ") + fileName + String(" has been successfully deleted if it has been existent!"));
    }
    else
    {
        LOG_ERROR(String("File ") + fileName + String(" could not be deleted!"));
    }
    return retCode;
}

void FileManager::closeFile()
{
    if (true == m_fileHandle)
    {
        m_fileHandle.flush();
        m_fileHandle.close();
        LOG_INFO("File has been successfully flushed and closed!");
    }
}

bool FileManager::resetFilePointer()
{
    bool retCode = false;

    /* Set file pointer to first byte of file */
    if (true == m_fileHandle)
    {
        retCode = m_fileHandle.seek(0, SeekSet);
    }
    return retCode;
}

int16_t FileManager::read4KBlock(uint8_t* buffer)
{
    const uint16_t BUFFER_SIZE_BYTES = 4096;
    int16_t readBytes = -1;

    if (true == m_fileHandle)
    {
        readBytes = m_fileHandle.readBytes(reinterpret_cast<char*>(const_cast<uint8_t*>(buffer)), BUFFER_SIZE_BYTES);
    }
    return readBytes;
}

int16_t FileManager::write4KBlock(const uint8_t* buffer, const uint16_t& size)
{
    const uint16_t BUFFER_SIZE_BYTES = 4096;
    int16_t writtenBytes = -1;

    if ((true == m_fileHandle) && (size <= BUFFER_SIZE_BYTES))
    {
        writtenBytes = m_fileHandle.write(buffer, size);
    }
    return writtenBytes;
}

bool FileManager::fileExists(const String& fileName)
{
    return SPIFFS.exists(fileName);
}

int32_t FileManager::getFileSize() const
{
    return m_fileHandle.size();
}

int32_t FileManager::getFileSize(const String& fileName)
{
    File fileHandle;
    int32_t fileSize = -1;

    SPIFFS.begin(false);
    fileHandle = SPIFFS.open(fileName, "r");

    if (true == fileHandle)
    {
        fileSize = fileHandle.size();
    }
    fileHandle.close();
    SPIFFS.end();

    return fileSize;
}

void FileManager::getInfo(String& infoString)
{
    size_t  totalBytes          = SPIFFS.totalBytes();
    size_t  usedBytes           = SPIFFS.usedBytes();
    uint8_t usedBytesPercent    = static_cast<uint8_t>(((usedBytes * 100) / totalBytes));

    /* Print the data into the output buffer */
    infoString  = "Data partition size in bytes: ";
    infoString += totalBytes;
    infoString += ", Used bytes: ";
    infoString += usedBytes;
    infoString += "(";
    infoString += usedBytesPercent;
    infoString += "%)";
}
