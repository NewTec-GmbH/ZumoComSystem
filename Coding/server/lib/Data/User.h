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
 * @file User.h
 * @author Luis Moser
 * @brief User header
 * @date 07/20/2021
 *
 * @{
 */

#ifndef __USER_H__
#define __USER_H__

#include <Arduino.h>
#include <Permission.h>
#include <CryptoServices.h>

 /** Class which stores all registered users, implements CRUD operations and provides (de-)serialization */
class User
{
public:
    /**
     * Default Constructor
     */
    User();

    /**
     * Destructor
     */
    ~User();

    /**
     * Creates a fully priviliged admin account with default credentials if it not existent
     *
     * @return Returns true if user has been created, else false
     */
    static bool registerAdminAccount();

    /**
     * Creates a less priviliged default account with default credentials if it not existent
     *
     * @return Returns true if user has been created, else false
     */
    static bool registerDefaultUser();

    /**
     * Returns the permissions and the number of permissions of the specified user
     *
     * @param[out] numberOfPermissions Contains the number of permissions this user has
     *
     * @return Returns pointer to array of users permissions
     */
    const Permission* getPermissions(uint8_t& numberOfPermissions) const;

    /**
     * Returns the username of this User instance
     *
     * @return Returns the username of the User instance
     */
    String getUsername();

    /**
     * Returns pointer to specified user
     *
     * @param[in] username The user to be fetched
     * @return Returns the specified user instance
     */
    static User* getUser(const String& username);

    /**
     * Checks if the passed username and password are correct
     *
     * @param[in] username The username of the user to be checked
     * @param[in] password The password of the specified user to be checked
     * @return Returns true if credentials are correct, else false
     */
    static bool checkCredentials(const String& username, const String& password);

    /**
     * Creates a new user with the specified password and permissions. Password is hashed. Will not automatically be serialized and saved!
     *
     * @param[in] username The username of the user to be created
     * @param[in] password The password of the user to be created
     * @param[in] permissions Pointer to array of permissions which should be assigned to user
     * @param[in] numberOfPermissions Size of passed permissions array
     * @param[in] updateUser Specifies if the user should be created or updated
     * @return Returns true if successful, else false
     */
    static bool putUser(const String& username, const String& password, const Permission* permissions, const uint8_t numberOfPermissions, const bool updateUser);

    /**
     * Deletes the specified user. Will not automatically be serialized and saved!
     * @param[in] username The user to be deleted
     * @return Returns true if successful, else false
     */
    static bool deleteUser(const String& username);

    /**
     * Serializes the user data
     *
     * @param[out] The output serialized data
     * @return Returns true if successful, else false
     */
    bool serialize(String& serialized) const;

    /**
     * Deserializes the passed data and re-creates user data
     *
     * @param[in] The serialized JSON string data
     * @return Returns true if successful, else false
     */
    bool deserialize(const String& serial);

private:
    /** Specifies the minimum password length in printable characters */
    static const uint8_t MIN_PASSWORD_CHARS = 8;

    /** Specifies the maximum password length in printable characters */
    static const uint8_t MAX_PASSWORD_CHARS = 128;

    /** Specifies the minimum username length in printable characters */
    static const uint8_t MIN_USERNAME_CHARS = 2;

    /** Specifies the maximum username length in printable characters */
    static const uint8_t MAX_USERNAME_CHARS = 16;

    /** Specifies how many users can be registered at max */
    static const uint8_t MAX_REGISTERED_USERS = 8;

    /** Specifies how many permisssions one user can have */
    static const uint8_t MAX_PERMISSIONS_PER_USER = 32;

    /** Specifies the default admin username */
    static const char* DEFAULT_ADMIN_USERNAME;

    /** Specifies the default admin password */
    static const char* DEFAULT_ADMIN_PASSWORD;

    /** Specifies the default user username */
    static const char* DEFAULT_USER_USERNAME;

    /** Specifies the default user password */
    static const char* DEFAULT_USER_PASSWORD;

    /** Stores how many users are currently registered */
    static uint8_t m_numberOfRegisteredUsers;

    /** Stores pointers to all registered users */
    static User* m_registeredUsers[];

    /** Mutex which is used to control access to the registered websocket sessions */
    static SemaphoreHandle_t m_usersMutex;

    /** Instance of CryptoServices */
    static CryptoServices m_crypto;

    /** The username of the current user */
    String m_username;

    /** The hashed password of the current user */
    String m_hashedPassword;

    /** The random password salt of the current user */
    String m_passwordSalt;

    /** Permissions of the current user */
    Permission m_permissions[MAX_PERMISSIONS_PER_USER];

    /** The number of permissions the current user has */
    uint8_t m_numberOfPermissions;

    /**
     * Returns the array index of the user with the specified username
     *
     * @param[in] username to the username string
     * @return Returns index if user has been found, returns -1 if user is not existing
     */
    static int8_t getUserIdx(const String& username);
};
#endif /** __USER_H__ */
