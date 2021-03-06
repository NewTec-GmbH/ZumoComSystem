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
 * @addtogroup Data
 * @{
 */

#ifndef __STORE_H__
#define __STORE_H__

#include <NVSManager.h>
#include <NetworkCredentials.h>
#include <User.h>
#include <FirmwareInfo.h>

 /** Manages, buffers, loads and saves all required data structures for the ComPlatform */
class Store
{
public:
    /**
     * Get Store instance
     *
     * @return Returns Store singleton instance
     */
    static Store& getInstance()
    {
        static Store instance;
        return instance;
    }

    /**
    * Get the network credentials for STA mode
    *
    * @return Returns the NetworkCredentials instance
    */
    const NetworkCredentials& getSTACredentials() const;

    /**
     * Set the network credentials for STA mode
     *
     * @param[in] credentials The new NetworkCredentials instance to be set
     */
    void setSTACredentials(const NetworkCredentials& credentials);

    /**
     * Save NetworkCredentials for STA mode to persistent storage
     *
     * @return Returns true if successful, false if error occured
     */
    bool saveSTACredentials();

    /**
     * Load NetworkCredentials for STA mode from persistent storage to store
     *
     * @return Returns true if succesful, false if error occured
     */
    bool loadSTACredentials();

    /**
     * Deletes the STA credentials from persistent storage
     * @return Returns true if succesful, false if error occured
     */
    bool deleteSTACredentials();

    /**
     * Returns the User instance
     *
     * @return Returns reference to User class instance
     */
    const User& getUsers() const;

    /**
     * Copies the passed User class instance into store
     * @param[in] users User class to be stored.
     */
    void setUsers(const User& users);

    /**
     * Save all registered users to persistent storage
     *
     * @return Returns true if successul, else false
     */
    bool saveUsers();

    /**
     * Loads all registered users from persistent storage
     *
     * @return Returns true if successful, else false
     */
    bool loadUsers();

    /**
     * Saves all FirmwareInfo entries to persistent storage
     *
     * @return Returns true if successful, else false
     */
    bool saveFirmwareInfo();

    /**
     * Loads all FirmwareInfo entries from persistent storage
     *
     * @return Returns true if successful, else false
     */
    bool loadFirmwareInfo();

    /**
     * Get the network credentials for AP mode
     *
     * @return Returns the NetworkCredentials instance
     */
    const NetworkCredentials& getAPCredentials() const;

    /**
     * Set the network credentials for AP mode
     *
     * @param[in] credentials The new NetworkCredentials instance to be set
     */
    void setAPCredentials(const NetworkCredentials& credentials);

    /**
     * Closes the store. Should be called when access to store is done.
     */
    void closeStore();

private:
    /** Instance of NVSManager for making data persistent */
    NVSManager m_nvsmgr;

    /** Instance of NetworkCredentials which contains SSID and passphrase for STA mode */
    NetworkCredentials m_staCredentials;

    /** Instance of NetworkCredentials which contains SSID and passphrase for AP mode */
    NetworkCredentials m_apCredentials;

    /** Instance of users */
    User m_users;

    /** Default constructor */
    Store();

    /** Destructor */
    ~Store();
};
#endif /** __STORE_H__ */

/**
 *  @}
 */