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
 * @file FirmwareInfo.cpp
 * @author Luis Moser
 * @brief FirmwareInfo class
 * @date 08/02/2021
 * @addtogroup Data
 * @{
 */

#include <FirmwareInfo.h>
#include <ArduinoJson.h>
#include <Log.h>

FirmwareInfo FirmwareInfo::m_fwInfos[NUMBER_OF_SAVED_FIRMWARES];
uint8_t FirmwareInfo::m_savedFirmwares = 0;

FirmwareInfo::FirmwareInfo() :
    m_available(false),
    m_targetSystem(),
    m_payloadHashValue(),
    m_isValid(false),
    m_sizeBytes(0)
{
}

FirmwareInfo::~FirmwareInfo()
{
}

bool FirmwareInfo::putInfo(const String& targetSystem, const String& payloadHashValue, const bool isValid, const uint32_t sizeBytes, const bool updateInfo)
{
    bool retCode = false;

    /* Fully re-create FirmwareInfo if it needs to be updated */
    if ((true == updateInfo) && (nullptr != getInfo(targetSystem)))
    {
        deleteInfo(targetSystem);
    }

    if ((nullptr == getInfo(targetSystem))
        && (NUMBER_OF_SAVED_FIRMWARES > m_savedFirmwares))
    {
        for (uint8_t fwIdx = 0; fwIdx < NUMBER_OF_SAVED_FIRMWARES; fwIdx++)
        {
            FirmwareInfo& info = m_fwInfos[fwIdx];
            if (info.m_available == false)
            {
                info.m_available = true;
                info.m_targetSystem = targetSystem;
                info.m_payloadHashValue = payloadHashValue;
                info.m_isValid = isValid;
                info.m_sizeBytes = sizeBytes;

                m_savedFirmwares++;
                retCode = true;
                break;
            }
        }

        if (retCode == false)
        {
            LOG_ERROR("Could not find a free buffer entry for new FirmwareInfo even though database is not full!");
        }
    }
    else
    {
        LOG_ERROR("Cannot store a new FirmwareInfo entry. Database is full!");
        LOG_DEBUG("Number of saved Firmwares: " + String(m_savedFirmwares));
    }
    return retCode;
}

const FirmwareInfo* FirmwareInfo::getInfo(const String& targetSystem)
{
    const FirmwareInfo* fwInfo = nullptr;

    LOG_DEBUG("Number of saved Firmwares: " + String(m_savedFirmwares));

    if (0 < m_savedFirmwares)
    {
        for (uint8_t fwIdx = 0; fwIdx < NUMBER_OF_SAVED_FIRMWARES; fwIdx++)
        {
            FirmwareInfo& info = m_fwInfos[fwIdx];
            if ((info.m_targetSystem == targetSystem) && (true == info.m_available))
            {
                fwInfo = &info;
                break;
            }
        }
    }
    return fwInfo;
}

void FirmwareInfo::deleteInfo(const String& targetSystem)
{
    if (0 < m_savedFirmwares)
    {
        for (uint8_t fwIdx = 0; fwIdx < NUMBER_OF_SAVED_FIRMWARES; fwIdx++)
        {
            FirmwareInfo& info = m_fwInfos[fwIdx];
            if ((info.m_targetSystem == targetSystem) && (true == info.m_available))
            {
                info.m_available = false;
                m_savedFirmwares--;

                LOG_INFO(String("Successfully deleted FirmwareInfo for target system ") + targetSystem);
                break;
            }
        }
    }
}

bool FirmwareInfo::serialize(String& serial)
{
    bool retCode = false;
    size_t docSize = 0;
    const size_t DOC_SIZE = 256;
    StaticJsonDocument<DOC_SIZE> jsonDocument;

    for (uint8_t fwIdx = 0; fwIdx < NUMBER_OF_SAVED_FIRMWARES; fwIdx++)
    {
        FirmwareInfo& info = m_fwInfos[fwIdx];
        if (true == info.m_available)
        {
            JsonObject firmware = jsonDocument.createNestedObject();
            firmware["targetSystem"] = info.m_targetSystem.c_str();
            firmware["sizeBytes"] = info.m_sizeBytes;
            firmware["payloadHash"] = info.m_payloadHashValue.c_str();
            firmware["isValid"] = info.m_isValid;
        }
    }

    docSize = measureJson(jsonDocument);
    retCode = ((0 < docSize) && (docSize == serializeJson(jsonDocument, serial)));
    if (true == retCode)
    {
        LOG_DEBUG("FirmwareInfo successfully serialized to JSON");
        LOG_DEBUG(serial);
    }
    else
    {
        LOG_ERROR("Could not serialize FirmwareInfo to JSON!");
    }
    return retCode;
}

bool FirmwareInfo::serializeInstance(String& serial) const
{
    bool retCode = false;
    size_t docSize = 0;

    /*
    Reserve memory on stack for JSON structure which consists of four key-value pairs.
    */
    const size_t DOC_SIZE = 192;
    StaticJsonDocument<DOC_SIZE> jsonDocument;

    /*
    Pass the const/non-volatile char* pointers to ArduinoJson so that ArduinoJson
    will not copy/duplicate the string values
    */
    jsonDocument["targetSystem"] = m_targetSystem.c_str();
    jsonDocument["sizeBytes"] = m_sizeBytes;
    jsonDocument["payloadHash"] = m_payloadHashValue.c_str();
    jsonDocument["isValid"] = m_isValid;

    docSize = measureJson(jsonDocument);
    retCode = ((0 < docSize) && (docSize == serializeJson(jsonDocument, serial)));
    if (true == retCode)
    {
        LOG_DEBUG("Network credentials successfully serialized to JSON");
        LOG_DEBUG(serial);
    }
    else
    {
        LOG_ERROR("Could not serialize network credentials!");
    }
    return retCode;
}

bool FirmwareInfo::deserialize(const String& serial)
{
    bool retCode = true;

    /* Clean up prior deserialization */
    for (uint8_t fwIdx = 0; fwIdx < NUMBER_OF_SAVED_FIRMWARES; fwIdx++)
    {
        FirmwareInfo& info = m_fwInfos[fwIdx];
        info.m_available = false;
    }
    m_savedFirmwares = 0;

    const size_t DOC_SIZE = 384;
    StaticJsonDocument<DOC_SIZE> jsonDocument;
    DeserializationError jsonRet = deserializeJson(jsonDocument, serial);

    if (DeserializationError::Ok == jsonRet)
    {
        JsonArray firmwareObjects = jsonDocument.as<JsonArray>();

        for (uint8_t fwIdx = 0; fwIdx < firmwareObjects.size(); fwIdx++)
        {
            FirmwareInfo& info = m_fwInfos[fwIdx];
            info.m_available = true;
            info.m_targetSystem = firmwareObjects[fwIdx]["targetSystem"].as<String>();
            info.m_sizeBytes = firmwareObjects[fwIdx]["sizeBytes"];
            info.m_payloadHashValue = firmwareObjects[fwIdx]["payloadHash"].as<String>();
            info.m_isValid = firmwareObjects[fwIdx]["isValid"];

            m_savedFirmwares++;
        }
    }
    else
    {
        retCode = false;
        LOG_ERROR("Error on deserializing the FirmwareInfo JSON object");
        LOG_ERROR(jsonRet.c_str());
    }
    return retCode;
}

const String& FirmwareInfo::getTargetSystem() const
{
    return m_targetSystem;
}

const String& FirmwareInfo::getPayloadHashValue() const
{
    return m_payloadHashValue;
}

bool FirmwareInfo::isValid() const
{
    return m_isValid;
}

/**
 *  @}
 */