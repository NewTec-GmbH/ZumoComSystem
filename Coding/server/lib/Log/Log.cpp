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
 * @file Log.cpp
 * @author Luis Moser
 * @brief Log class
 * @date 06/14/2021
 * @addtogroup System Services
 * @{
 */

#include <Log.h>

Log::Log() :
    m_logLevel(LEVEL_DEBUG),
    m_output(nullptr)
{
}

Log::~Log()
{
}

const Log::LogLevel& Log::getLogLevel() const
{
    return m_logLevel;
}

void Log::setLogLevel(LogLevel level)
{
    if ((LEVEL_ERROR <= level) && (level < LEVE_MAX))
    {
        m_logLevel = level;
    }
}

void Log::writeLog(const char* fileNameFullPath, int line, LogLevel level, const String& msg)
{
    if (level <= m_logLevel)
    {
        if (nullptr != m_output)
        {
            const char* fileName    = strrchr(fileNameFullPath, '/');

            if (nullptr == fileName)
            {
                fileName = strrchr(fileNameFullPath, '\\');

                if (nullptr == fileName)
                {
                    fileName = fileNameFullPath;
                }
                else
                {
                    fileName++;
                }
            }
            else
            {
                fileName++;
            }

            switch(level)
            {
            case LEVEL_ERROR:
                m_output->print("[E]\t");
                break;

            case LEVEL_WARN:
                m_output->print("[W]\t");
                break;

            case LEVEL_INFO:
                m_output->print("[I]\t");
                break;

            case LEVEL_DEBUG:
                m_output->print("[D]\t");
                break;

            default:
                m_output->print("[?]\t");
                break;
            }
            
            m_output->printf("%30s",fileName);
            m_output->print(":");
            m_output->print(line, 10);
            m_output->print("\t");
            m_output->println(msg);
        }
    }
}

/**
 *  @}
 */