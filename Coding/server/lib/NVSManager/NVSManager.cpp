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
 * @file NVSManager.cpp
 * @author Luis Moser
 * @brief NVSManager class
 * @date 06/17/2021
 *
 * @{
 */

#include <NVSManager.h>
#include <Log.h>

NVSManager::NVSManager() :
    m_preferences()
{
    /* Open/Create the namespace for key-value pairs with r/w access */
    m_preferences.begin("complatform", false);
    LOG_DEBUG("Opened complatform namespace for NVS");
}

NVSManager::~NVSManager()
{
    closeNVS();
}

bool NVSManager::putEntry(String key, String value)
{
    bool retCode = (m_preferences.putString(key.c_str(), value) > 0);
    if (false == retCode)
    {
        LOG_ERROR("Could not create/update string NVS entry");
    }
    return retCode;
}

bool NVSManager::putEntry(String key, uint8_t* value, size_t length)
{
    bool retCode = (m_preferences.putBytes(key.c_str(), value, length) == length);
    if (false == retCode)
    {
        LOG_ERROR("Could not create/update binary NVS entry");
    }
    return retCode;
}

bool NVSManager::readEntry(String key, uint8_t* buffer, size_t length)
{
    return (m_preferences.getBytes(key.c_str(), buffer, length) == length);
}

bool NVSManager::deleteEntry(String key)
{
    bool retCode = m_preferences.remove(key.c_str());
    if (false == retCode)
    {
        LOG_ERROR("NVS entry could not be deleted");
    }
    return retCode;
}

String NVSManager::readEntry(String key)
{
    return m_preferences.getString(key.c_str(), "null");
}

bool NVSManager::wipeNVS()
{
    bool retCode = m_preferences.clear();
    if (false == retCode)
    {
        LOG_ERROR("NVS could not be wiped");
    }
    return retCode;
}

void NVSManager::closeNVS()
{
    /* Close the currently opened namespace */
    m_preferences.end();
    LOG_DEBUG("Closed complatform namespace for NVS");
}
