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
 * @file FirmwareInfo.h
 * @author Luis Moser
 * @brief FirmwareInfo header
 * @date 08/02/2021
 *
 * @{
 */

#ifndef __FIRMWAREINFO_H__
#define __FIRMWAREINFO_H__

#include <Arduino.h>

 /** Class/data structure for saving and (de-)serializing information about saved firmare images */
class FirmwareInfo
{
public:
    /**
     * Default Constructor
     */
    FirmwareInfo();

    /**
     * Destructor
     */
    ~FirmwareInfo();

    /**
     * Add a new firmware image information entry to the database.
     *
     * @param[in] targetSystem Specifies the target system of the new firmware
     * @param[in] payloadHashValue Specifies the payload hash value of the new firmware
     * @param[in] isValid Specifies if the new firmware image is valid or not
     * @param[in] sizeBytes Specifies the size of the new firmwage image in bytes
     * @param[in] updateInfo Specifies if existing FirmwareInfo shall be ovewritten if existent
     * @return Returns true if successful, else false
     */
    static bool putInfo(const String& targetSystem, const String& payloadHashValue, const bool isValid, const uint32_t sizeBytes, const bool updateInfo);

    /**
     * Returns the FirmwareInfo instance for the specified target system
     *
     * @param[in] targetSystem The target system whose FirmareInfo should be returned
     * @return Returns pointer to FirmwareInfo instance if existent, else null pointer
     */
    static const FirmwareInfo* getInfo(const String& targetSystem);

    /**
     * Deletes an existing firmware image information entry from the database if it is existing
     *
     * @param[in] targetSystem The entry for the specified target system to be deleted
     */
    static void deleteInfo(const String& targetSystem);

    /**
     * Serializes the entire database to JSON string
     *
     * @param[out] serial The serialized JSON string
     * @return Returns true if successful, else false
     */
    static bool serialize(String& serial);

    /**
     * Serializes the current instance
     *
     * @param[out] serial The serialized JSON string
     * @return Returns true if successful, else false
     */
    bool serializeInstance(String& serial) const;

    /**
     * Deserializes the passed JSON string and re-creates the data structure
     *
     * @param[in] serial The serialized JSON string
     * @return Returns true if successful, else false
     */
    static bool deserialize(const String& serial);

    /**
     * Returns the target system of this FirmwareInfo instance
     *
     * @return Returns the target system string
     */
    const String& getTargetSystem() const;

    /**
     * Returns the payload hash value of this FirmwareInfo instance
     *
     * @return Returns the hash value of the firmware payload
     */
    const String& getPayloadHashValue() const;

    /**
     * Returns if this FirmwareInfo instance firmware is valid
     *
     * @return Returns true if valid, else false
     */
    bool isValid() const;

private:
    /** Specifies the max number of saved FirmwareInfo instances */
    static const uint8_t NUMBER_OF_SAVED_FIRMWARES = 2;

    /** Stores how many FirmwareInfo instances are actually existing */
    static uint8_t m_savedFirmwares;

    /** Stores all FirmareInfo instances */
    static FirmwareInfo m_fwInfos[];

    /** Specifies if the firmwware image is available/the buffer entry is available */
    bool m_available;

    /** Specifies the target system of the new firmware image */
    String m_targetSystem;

    /** Specifies the hash value of the firmware/payload */
    String m_payloadHashValue;

    /** Specifies if the new firmware image is valid */
    bool m_isValid;

    /** Specifies the size in bytes of the new firmware image */
    uint32_t m_sizeBytes;
};
#endif /** __FIRMWAREINFO_H__ */
