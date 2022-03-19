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
 * @file NVSManager.h
 * @author Luis Moser
 * @brief NVSManager header
 * @date 06/17/2021
 *
 * @{
 */

#ifndef __NVSMANAGER_H__
#define __NVSMANAGER_H__

#include <Arduino.h>
#include <Preferences.h>

 /** Hardware abstraction to easily store and retrieve key-value string pairs */
class NVSManager
{
public:
    /**
     * Default constructor
     */
    NVSManager();

    /**
     * Destructor
     */
    ~NVSManager();

    /**
     * Creates or updates a new string key-value pair in persistent storage
     *
     * @param[in] key The key name of passed value
     * @param[in] value The string value to be saved
     * @return Returns true if successful, else false
     */
    bool putEntry(const String& key, const String& value);

    /**
     * Creates or updates a new binary key-value pair in persistent storage
     *
     * @param[in] key The key name of passed value
     * @param[in] value The binary value to be saved
     * @param[in] length The length in bytes of the data to be written
     * @return Returns true if successful, else false
     */
    bool putEntry(const String& key, const uint8_t* value, const size_t length);

    /**
     * Deletes a key-value pair from persistent storage
     *
     * @param[in] key The key-value pair to be removed
     * @return Returns true if successful, else false
     */
    bool deleteEntry(const String& key);

    /**
     * Returns the string value of the key-value pair from persistent storage.
     *
     * @param[in] key The key-value pair to be read.
     * @param[out] outputString Contains value in case of success or empty case of failure.
     */
    void readEntry(const String& key, String& outputString);

    /**
     * Returns the binary value of the key-value pair from persistent storage
     *
     * @param[in] key The key-value pair to be read
     * @param[out] buffer The buffer to be filled with the read data
     * @param[in] length The lenght in bytes of the passed buffer
     * @return Returns true if successful, else false
     */
    bool readEntry(const String& key, uint8_t* buffer, const size_t length);

    /**
     * Completely removes all key-value pairs from persistent storage
     *
     * @returns Returns true if successful, else false
     */
    bool wipeNVS();

    /**
     * Closes the NVS namespace. Should be called when access to NVS is done.
     */
    void closeNVS();

private:
    /* Instance of ESP32 preferences */
    Preferences m_preferences;
};
#endif /** __NVSMANAGER_H__ */
