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

const char* FileManager::m_directories[] = { "/webspace/", "/firmware/" };

FileManager::FileManager() : m_fileHandle()
{
    if (true == LITTLEFS.begin(false))
    {
        LOG_DEBUG("LittleFS file system successfully mounted");
    }
    else
    {
        LOG_WARN("No LittleFS file system existing. Formatting data partition now...");
        if (true == LITTLEFS.begin(true))
        {
            LOG_DEBUG("New LittleFS file system successfuly created");
            createDirectoryStructure();
        }
        else
        {
            LOG_ERROR("Could not create a new LittleFS file system!");
        }
    }

    LOG_INFO(getInfo());
}

FileManager::~FileManager()
{
    closeFile();
    LITTLEFS.end();

    LOG_DEBUG("LittleFS file system unmounted");
}

bool FileManager::formatFS()
{
    LITTLEFS.begin(false);
    bool retCode = LITTLEFS.format();

    createDirectoryStructure();

    if (true == retCode)
    {
        LOG_DEBUG("Data partition successfully formatted!");
    }
    else
    {
        LOG_ERROR("Could not format data partition!");
    }
    LITTLEFS.end();
    return retCode;
}

bool FileManager::openFile(String filePath, FileMode mode)
{
    bool retCode = true;

    if (READ == mode)
    {
        m_fileHandle = LITTLEFS.open(filePath, "r");
    }
    else if (READWRITE == mode)
    {
        m_fileHandle = LITTLEFS.open(filePath, "w+");
    }

    if (!m_fileHandle)
    {
        LOG_ERROR("File " + String(filePath) + " could not be opened!");
        retCode = false;
    }
    return retCode;
}

void FileManager::closeFile()
{
    m_fileHandle.flush();
    m_fileHandle.close();
    LOG_DEBUG("File " + String(m_fileHandle.name()) + " flushed and closed");
}

void FileManager::resetFilePointer()
{
    /* Set file pointer to first byte of file */
    m_fileHandle.seek(0, SeekSet);
}

uint16_t FileManager::read4KBlock(uint8_t* buffer)
{
    static const uint16_t BUFFER_SIZE_BYTES = 4096;
    return m_fileHandle.readBytes(reinterpret_cast<char*>(const_cast<uint8_t*>(buffer)), BUFFER_SIZE_BYTES);
}

uint16_t FileManager::write4KBlock(uint8_t* buffer, uint16_t size)
{
    static const uint16_t BUFFER_SIZE_BYTES = 4096;
    uint16_t writtenBytes = 0;
    if (size <= BUFFER_SIZE_BYTES)
    {
        writtenBytes = m_fileHandle.write(buffer, size);
    }
    return writtenBytes;
}

bool FileManager::fileExists(String filePath)
{
    return LITTLEFS.exists(filePath);
}

int32_t FileManager::getFileSize()
{
    return m_fileHandle.size();
}

int32_t FileManager::getFileSize(String filePath)
{
    int32_t fileSize = -1;
    bool mountSuccessful = LITTLEFS.begin(false);
    File fileHandle = LITTLEFS.open(filePath, "r");

    if ((true == mountSuccessful) && fileHandle && (false == fileHandle.isDirectory()))
    {
        fileSize = fileHandle.size();
    }
    fileHandle.close();
    LITTLEFS.end();

    return fileSize;
}

std::vector<String> FileManager::listDirectory(String directoryPath)
{
    std::vector<String> existingFiles;
    LITTLEFS.begin(false);

    File selectedDirectory = LITTLEFS.open(directoryPath, "r");
    File currentFile = selectedDirectory.openNextFile();

    while (currentFile)
    {
        existingFiles.push_back(currentFile.name());
        currentFile = selectedDirectory.openNextFile();
    }

    currentFile.close();
    selectedDirectory.close();
    LITTLEFS.end();

    return existingFiles;
}

String FileManager::getInfo()
{
    size_t capacity = LITTLEFS.totalBytes();
    size_t usedBytes = LITTLEFS.usedBytes();
    uint8_t usedBytesPercent = static_cast<uint8_t>((usedBytes / (float)capacity) * 100);

    char buffer[128];
    sprintf(buffer, "Data partition size in bytes: %d, Used bytes: %d (%d%%)", capacity, usedBytes, usedBytesPercent);
    return String(buffer);
}

void FileManager::createDirectoryStructure()
{
    LITTLEFS.begin(false);
    size_t noOfDirectories = sizeof(m_directories) / sizeof(char*);
    for (uint8_t dirNo = 0; dirNo < noOfDirectories; dirNo++)
    {
        LITTLEFS.mkdir(m_directories[dirNo]);
    }
    LITTLEFS.end();

    LOG_DEBUG("Directory structure created");
}
