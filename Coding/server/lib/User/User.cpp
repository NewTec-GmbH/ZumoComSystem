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
 *
 * @{
 */

#include <User.h>

User* User::m_registeredUsers[MAX_REGISTERED_USERS];
uint8_t User::m_numberOfRegisteredUsers = 0;
CryptoServices User::m_crypto;

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

int8_t User::getUserIdx(const String& username)
{
    int8_t retIdx = -1;

    for (uint8_t userIdx = 0; userIdx < MAX_REGISTERED_USERS; userIdx++)
    {
        if ((nullptr != m_registeredUsers[userIdx])
            && m_registeredUsers[userIdx]->m_username == username)
        {
            retIdx = userIdx;
            break;
        }
    }
    return retIdx;
}

bool User::checkAdminAccount()
{
    const uint8_t NUMBER_OF_PERMISSIONS = 1;
    Permission permission = ANY;
    return putUser("admin", "21091986", &permission, NUMBER_OF_PERMISSIONS, false);
}

Permission* User::getPermissions(uint8_t& numberOfPermissions)
{
    numberOfPermissions = m_numberOfPermissions;
    return m_permissions;
}

User* User::getUser(String username)
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
    int8_t userIdx = getUserIdx(username);
    String computedHash;

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
    return retCode;
}

bool User::putUser(const String& username, const String& password, const Permission* permissions, const uint8_t numberOfPermissions, const bool updateUser)
{
    String randomSalt;
    String hashedPassword;
    bool retCode = false;
    bool deleted = true;

    /* Fully re-create user if it needs to be updated */
    if (true == updateUser)
    {
        deleted = deleteUser(username);
    }

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
                User* newUser = new User();
                newUser->m_username = username;

                /* Generate a unique and random salt for hash */
                m_crypto.getRandomSalt(randomSalt);
                newUser->m_passwordSalt = randomSalt;

                /* Calculate the salted hash */
                m_crypto.hashBlake2b(password, randomSalt, hashedPassword);
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
                break;
            }
        }
    }
    else
    {
        LOG_ERROR("Could not create user " + username);
    }
    return retCode;
}

bool User::deleteUser(const String& username)
{
    bool retCode = false;
    int8_t userIdx = getUserIdx(username);

    if (-1 != userIdx)
    {
        m_registeredUsers[userIdx] = nullptr;
        m_numberOfRegisteredUsers--;
        delete m_registeredUsers[userIdx];
        retCode = true;
    }
    return retCode;
}

void User::serialize(String& serialized)
{
    /*
    Reserve memory on heap for JSON structure.
    The data is not copied into the DynamicJsonDocument by default.
    The value specified in DOC_SIZE has been computed with the help of the ArduinoJson Assistant v6
    which is accessible at: https://arduinojson.org/v6/assistant/
    */
    const size_t DOC_SIZE = 16384;
    DynamicJsonDocument jsonDocument(DOC_SIZE);

    // TODO: Calculate dynamically based on constant!

    JsonObject userObjects[MAX_REGISTERED_USERS];
    JsonArray userRights[MAX_REGISTERED_USERS];

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

    serializeJson(jsonDocument, serialized);
    LOG_DEBUG("Users successfully serialized to JSON");
}

bool User::deserialize(String& serial)
{
    bool retCode = false;

    /* Clean up prior deserialization */
    m_numberOfRegisteredUsers = 0;
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
            User* newUser = new User();
            newUser->m_username = userObjects[userIdx]["username"].as<String>();
            newUser->m_hashedPassword = userObjects[userIdx]["hashedPassword"].as<String>();
            newUser->m_passwordSalt = userObjects[userIdx]["passwordSalt"].as<String>();
            newUser->m_numberOfPermissions = userObjects[userIdx]["numberOfPermissions"];

            JsonArray userRights = userObjects[userIdx]["permissions"];

            for (uint8_t permIdx = 0; permIdx < newUser->m_numberOfPermissions; permIdx++)
            {
                newUser->m_permissions[permIdx] = static_cast<Permission>(userRights[permIdx]);
            }

            m_registeredUsers[userIdx] = newUser;
            m_numberOfRegisteredUsers++;
        }
        retCode = true;
    }
    else
    {
        LOG_ERROR("Error on deserializing the NetworkCredentials JSON object");
        LOG_ERROR(jsonRet.c_str());
    }
    return retCode;
}
