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
 * @file Store.cpp
 * @author Luis Moser
 * @brief Store class
 * @date 06/18/2021
 * 
 * @{
 */

#include <Store.h>

bool Store::save()
{
    /** Generate the JSON string */
    String json = m_netCredentials.serialize();
    bool retCode = m_nvsmgr.updateEntry("netCredentials", json);
    if (false == retCode)
    {
        LOG_ERROR("Could not save network credentials to disk");
    }
    return retCode;
}

bool Store::load()
{
    /** Fetch JSON string from disk */
    String json = m_nvsmgr.readEntry("netCredentials");

    /** 
     * If there are saved credentials, restore them,
     * else, leave the object with its default values
     */
    bool retCode = (String("null") != json && m_netCredentials.deserialize(json));
    if (retCode == false)
    {
        LOG_ERROR("Could not load network credentials from disk");
    }
    return retCode;
}

NetworkCredentials Store::getNetworkCredentials()
{
    return m_netCredentials;
}

void Store::setNetworkCredentials(NetworkCredentials credentials)
{
    m_netCredentials = credentials;
}