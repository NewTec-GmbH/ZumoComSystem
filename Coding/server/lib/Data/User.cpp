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
 * @file User.cpp
 * @author Luis Moser
 * @brief User class
 * @date 07/20/2021
 * @addtogroup Data
 * @{
 */

#include <User.h>
#include <ArduinoJson.h>
#include <Log.h>

User* User::m_registeredUsers[MAX_REGISTERED_USERS] = {nullptr};
SemaphoreHandle_t User::m_usersMutex = xSemaphoreCreateMutex();
uint8_t User::m_numberOfRegisteredUsers = 0;
CryptoServices User::m_crypto;
const char* User::DEFAULT_ADMIN_USERNAME = "admin";
const char* User::DEFAULT_ADMIN_PASSWORD = "21091986";
const char* User::DEFAULT_USER_USERNAME = "student";
const char* User::DEFAULT_USER_PASSWORD = "nt2021nt";

User::User() :
    m_username(),
    m_hashedPassword(),
    m_passwordSalt(),
    m_permissions{},
    m_numberOfPermissions(0)
{
}

User::~User()
{
}

bool User::registerAdminAccount()
{
    const uint8_t NUMBER_OF_PERMISSIONS = 1;
    Permission permission = ANY;

    return putUser(DEFAULT_ADMIN_USERNAME, DEFAULT_ADMIN_PASSWORD, &permission, NUMBER_OF_PERMISSIONS, false);
}

bool User::registerDefaultUser()
{
    const uint8_t NUMBER_OF_PERMISSIONS = 1;
    Permission permission = DEBUG_ZUMO;

    return putUser(DEFAULT_USER_USERNAME, DEFAULT_USER_PASSWORD, &permission, NUMBER_OF_PERMISSIONS, false);
}

const Permission* User::getPermissions(uint8_t& numberOfPermissions) const
{
    numberOfPermissions = m_numberOfPermissions;
    return m_permissions;
}

String User::getUsername()
{
    return this->m_username;
}

User* User::getUser(const String& username)
{
    User* retUser = nullptr;
    int8_t userIdx = getUserIdx(username);
    if (-1 != userIdx)
    {
        retUser = m_registeredUsers[userIdx];
    }
    return retUser;
}

bool User::checkCredentials(const String& username, const String& password)
{
    bool retCode = true;
    String computedHash;

    xSemaphoreTake(m_usersMutex, portMAX_DELAY);
    int8_t userIdx = getUserIdx(username);

    if (-1 != userIdx)
    {
        m_crypto.hashBlake2b(password, m_registeredUsers[userIdx]->m_passwordSalt, computedHash);

        if (computedHash.length() == m_registeredUsers[userIdx]->m_hashedPassword.length())
        {
            for (uint8_t charIdx = 0; charIdx < computedHash.length(); charIdx++)
            {
                if (m_registeredUsers[userIdx]->m_hashedPassword[charIdx] != computedHash[charIdx])
                {
                    retCode = false;
                }
            }
        }
        else
        {
            retCode = false;
        }
    }
    else
    {
        retCode = false;
    }
    xSemaphoreGive(m_usersMutex);
    return retCode;
}

bool User::putUser(const String& username, const String& password, const Permission* permissions, const uint8_t numberOfPermissions, const bool updateUser)
{
    bool saltRetCode = false;
    bool hashRetCode = false;
    bool retCode = false;
    bool deleted = true;

    String randomSalt;
    String hashedPassword;

    /* Fully re-create user if it needs to be updated */
    if (true == updateUser)
    {
        deleted = deleteUser(username);
    }

    xSemaphoreTake(m_usersMutex, portMAX_DELAY);

    if ((true == deleted)
        && (-1 == getUserIdx(username))
        && (m_numberOfRegisteredUsers < MAX_REGISTERED_USERS)
        && ((MIN_USERNAME_CHARS <= username.length()) && (username.length() <= MAX_USERNAME_CHARS))
        && ((MIN_PASSWORD_CHARS <= password.length()) && (password.length() <= MAX_PASSWORD_CHARS)))
    {
        for (uint8_t userIdx = 0; userIdx < MAX_REGISTERED_USERS; userIdx++)
        {
            if (nullptr == m_registeredUsers[userIdx])
            {
                /* Generate a unique and random salt for hash */
                saltRetCode = m_crypto.getRandomSalt(randomSalt);

                /* Calculate the salted hash */
                hashRetCode = m_crypto.hashBlake2b(password, randomSalt, hashedPassword);

                if ((true == saltRetCode) && (true == hashRetCode))
                {
                    User* newUser = new(std::nothrow) User();
                    if (nullptr != newUser)
                    {
                        newUser->m_username = username;
                        newUser->m_passwordSalt = randomSalt;
                        newUser->m_hashedPassword = hashedPassword;
                        newUser->m_numberOfPermissions = numberOfPermissions;

                        /* Deep copy permissions */
                        for (uint8_t permIdx = 0; permIdx < numberOfPermissions; permIdx++)
                        {
                            newUser->m_permissions[permIdx] = permissions[permIdx];
                        }

                        m_registeredUsers[userIdx] = newUser;
                        m_numberOfRegisteredUsers++;

                        retCode = true;
                    }
                    else
                    {
                        LOG_ERROR("Out of memory. Could not create new user!");
                    }
                }
                break;
            }
        }
    }

    if (false == retCode)
    {
        LOG_ERROR("Could not create user " + username);
    }

    xSemaphoreGive(m_usersMutex);
    return retCode;
}

bool User::deleteUser(const String& username)
{
    bool retCode = false;

    xSemaphoreTake(m_usersMutex, portMAX_DELAY);
    int8_t userIdx = getUserIdx(username);

    if (-1 != userIdx)
    {
        delete m_registeredUsers[userIdx];
        m_registeredUsers[userIdx] = nullptr;
        m_numberOfRegisteredUsers--;
        retCode = true;
    }
    xSemaphoreGive(m_usersMutex);
    return retCode;
}

bool User::serialize(String& serialized) const
{
    bool retCode = false;
    size_t docSize = 0;

    /*
    Reserve memory on heap for JSON structure.
    The data is not copied into the DynamicJsonDocument.
    The value specified in DOC_SIZE has been computed with the help of the ArduinoJson Assistant v6
    which is accessible at: https://arduinojson.org/v6/assistant/
    */
    const size_t DOC_SIZE = 16384;
    DynamicJsonDocument jsonDocument(DOC_SIZE);

    JsonObject userObjects[MAX_REGISTERED_USERS];
    JsonArray userRights[MAX_REGISTERED_USERS];

    xSemaphoreTake(m_usersMutex, portMAX_DELAY);
    for (uint8_t userIdx = 0; userIdx < MAX_REGISTERED_USERS; userIdx++)
    {
        if (nullptr != m_registeredUsers[userIdx])
        {
            userObjects[userIdx] = jsonDocument.createNestedObject();
            userObjects[userIdx]["username"] = m_registeredUsers[userIdx]->m_username.c_str();
            userObjects[userIdx]["hashedPassword"] = m_registeredUsers[userIdx]->m_hashedPassword.c_str();
            userObjects[userIdx]["passwordSalt"] = m_registeredUsers[userIdx]->m_passwordSalt.c_str();
            userObjects[userIdx]["numberOfPermissions"] = static_cast<const uint8_t>(m_registeredUsers[userIdx]->m_numberOfPermissions);

            userRights[userIdx] = userObjects[userIdx].createNestedArray("permissions");

            for (uint8_t permIdx = 0; permIdx < m_registeredUsers[userIdx]->m_numberOfPermissions; permIdx++)
            {
                userRights[userIdx].add(static_cast<const uint8_t>(m_registeredUsers[userIdx]->m_permissions[permIdx]));
            }
        }
    }
    xSemaphoreGive(m_usersMutex);

    docSize = measureJson(jsonDocument);
    retCode = ((0 < docSize) && (docSize == serializeJson(jsonDocument, serialized)));
    if (true == retCode)
    {
        LOG_DEBUG("Users successfully serialized to JSON");
        LOG_DEBUG(serialized);
    }
    else
    {
        LOG_ERROR("Could not serialize users to JSON!");
    }
    return retCode;
}

bool User::deserialize(const String& serial)
{
    bool retCode = true;

    /* Clean up prior deserialization */
    m_numberOfRegisteredUsers = 0;

    xSemaphoreTake(m_usersMutex, portMAX_DELAY);
    for (uint8_t userIdx = 0; userIdx < MAX_REGISTERED_USERS; userIdx++)
    {
        if (nullptr != m_registeredUsers[userIdx])
        {
            delete m_registeredUsers[userIdx];
            m_registeredUsers[userIdx] = nullptr;
        }
    }

    /*
     Reserve memory on heap for JSON structure.
     The data is copied into the DynamicJsonDocument by default.
     The value specified in DOC_SIZE has been computed with the help of the ArduinoJson Assistant v6
     which is accessible at: https://arduinojson.org/v6/assistant/
     */
    const size_t DOC_SIZE = 16384;
    DynamicJsonDocument jsonDocument(DOC_SIZE);
    DeserializationError jsonRet = deserializeJson(jsonDocument, serial);

    if (DeserializationError::Ok == jsonRet)
    {
        JsonArray userObjects = jsonDocument.as<JsonArray>();

        for (uint8_t userIdx = 0; userIdx < userObjects.size(); userIdx++)
        {
            User* newUser = new(std::nothrow) User();
            if (nullptr != newUser)
            {
                newUser->m_username = userObjects[userIdx]["username"].as<String>();
                newUser->m_hashedPassword = userObjects[userIdx]["hashedPassword"].as<String>();
                newUser->m_passwordSalt = userObjects[userIdx]["passwordSalt"].as<String>();
                newUser->m_numberOfPermissions = userObjects[userIdx]["numberOfPermissions"];

                JsonArray userRights = userObjects[userIdx]["permissions"];

                for (uint8_t permIdx = 0; permIdx < newUser->m_numberOfPermissions; permIdx++)
                {
                    newUser->m_permissions[permIdx] = userRights[permIdx];
                }

                m_registeredUsers[userIdx] = newUser;
                m_numberOfRegisteredUsers++;
            }
            else
            {
                LOG_ERROR("Out of memory. Could not create new user!");
                retCode = false;
                break;
            }
        }
    }
    else
    {
        retCode = false;
        LOG_ERROR("Error on deserializing the NetworkCredentials JSON object");
        LOG_ERROR(jsonRet.c_str());
    }

    xSemaphoreGive(m_usersMutex);
    return retCode;
}

int8_t User::getUserIdx(const String& username)
{
    int8_t retIdx = -1;

    for (uint8_t userIdx = 0; userIdx < MAX_REGISTERED_USERS; userIdx++)
    {
        if ((nullptr != m_registeredUsers[userIdx])
            && (m_registeredUsers[userIdx]->m_username == username))
        {
            retIdx = userIdx;
            break;
        }
    }
    return retIdx;
}

/**
 *  @}
 */