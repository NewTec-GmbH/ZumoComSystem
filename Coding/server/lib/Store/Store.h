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
#include <Log.h>
#include <NetworkCredentials.h>
#include <KeyCert.h>
#include <User.h>

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
    NetworkCredentials getSTACredentials();

    /**
     * Set the network credentials for STA mode
     *
     * @param[in] credentials The new NetworkCredentials instance to be set
     */
    void setSTACredentials(NetworkCredentials credentials);

    /**
     * Save NetworkCredentials for STA mode to disk
     *
     * @return Returns true if successful, false if error occured
     */
    bool saveSTACredentials();

    /**
     * Load NetworkCredentials for STA mode from disk to store
     *
     * @return Returns true if succesful, false if error occured
     */
    bool loadSTACredentials();

    /**
    * Get the private RSA key and the public certificate
    *
    * @return Returns the KeyCert instance
    */
    KeyCert& getKeyCert();

    /**
     * Set the private RSA key and the public certificate
     *
     * @param[in] keycert The new KeyCert instance to be saved
     */
    void setKeyCert(KeyCert keycert);

    /**
     * Save KeyCert to disk
     *
     * @return Returns true if successful, false if error occured
     */
    bool saveKeyCert();

    /**
     * Load KeyCert from disk to store
     *
     * @return Returns true if succesful, false if error occured
     */
    bool loadKeyCert();

    /**
     * Returns the User instance
     *
     * @return Returns reference to User class instance
     */
    User& getUsers();

    /**
     * Copies the passed User class instance into store
     */
    void setUsers(User users);

    /**
     * Save all registered users to disk
     *
     * @return Returns true if successul, else false
     */
    bool saveUsers();

    /**
     * Loads all registered users from disk
     *
     * @return Returns true if successful, else false
     */
    bool loadUsers();

    /**
     * Get the network credentials for AP mode
     *
     * @return Returns the NetworkCredentials instance
     */
    NetworkCredentials getAPCredentials();

    /**
     * Set the network credentials for AP mode
     *
     * @param[in] credentials The new NetworkCredentials instance to be set
     */
    void setAPCredentials(NetworkCredentials credentials);

    /**
     * Closes the store. Should be called when access to store is done.
     */
    void closeStore();

private:
    /** Default constructor */
    Store();

    /** Destructor */
    ~Store();

    /** Instance of NVSManager for making data persistent */
    NVSManager m_nvsmgr;

    /** Instance of NetworkCredentials which contains SSID and passphrase for STA mode */
    NetworkCredentials m_staCredentials;

    /** Instance of NetworkCredentials which contains SSID and passphrase for AP mode */
    NetworkCredentials m_apCredentials;

    /** Instance of KeyCert to store private RSA key as well as public certificate for HTTPs and WSS servers */
    KeyCert m_keyCert;

    /** Instance of users */
    User m_users;
};
#endif /** __STORE_H__ */
