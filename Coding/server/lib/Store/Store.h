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
 * @file Store.h
 * @author Luis Moser
 * @brief Store header
 * @date 06/18/2021
 * 
 * @{
 */

#ifndef __STORE_H__
#define __STORE_H__

#include <NVSManager.h>
#include <NetworkCredentials.h>
#include <Logger.h>

/** Manages, buffers, loads and saves all required data structures for the ComPlatform */
class Store
{
public:
    /** 
     * Get Store instance
     * 
     * @return Returns Store singleton instance
     */
    static Store &getInstance()
    {
        static Store instance;
        return instance;
    }

    /** 
     * Save non-volatile data to disk
     * 
     * @return Returns true if successful, false if error occured
     */
    bool save();

    /**
     * Load non-volatile data from disk to store
     * 
     * @return Returns true if succesful, false if error occured
     */
    bool load();

    /** 
     * Get the network credentials 
     * 
     * @return Returns the NetworkCredentials instance
     */
    NetworkCredentials getNetworkCredentials();

    /**
     * Set the network credentials
     * 
     * @param[in] credentials The new NetworkCredentials instance to be saved
     */
    void setNetworkCredentials(NetworkCredentials credentials);

private:
    /** Default constructor */
    Store()
    {
    }

    /** Destructor */
    ~Store()
    {
    }

    /** Instance of NVSManager for making data persistent */
    NVSManager m_nvsmgr;

    /** Instance of NetworkCredentials to manage SSID and PSK */
    NetworkCredentials m_netCredentials;
};
#endif /** __STORE_H__ */