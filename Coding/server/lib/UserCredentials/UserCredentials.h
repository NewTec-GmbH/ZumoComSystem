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
 * @file UserCredentials.h
 * @author Luis Moser
 * @brief UserCredentials header
 * @date 07/23/2021
 *
 * @{
 */

#ifndef __USERCREDENTIALS_H__
#define __USERCREDENTIALS_H__

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Log.h>

 /** Simple class for specifying User credentials for the API */
class UserCredentials
{
public:
    /**
     * Default Constructor
     */
    UserCredentials();

    /**
     * Destructor
     */
    ~UserCredentials();

    /**
     * Returns the username
     *
     * @return Returns reference to username
     */
    const String& getUsername();

    /**
     * Returns the password
     *
     * @return Returns reference to password
     */
    const String& getPassword();

    /**
     * Deserializes the passed JSON string and re-creates object
     *
     * @param[in] serial The serialized JSON string
     * @return Returns true if successful, else false
     */
    bool deserialize(String serial);

private:
    /** Username of the user */
    String m_username;

    /** Password of the user */
    String m_password;
};
#endif /** __USERCREDENTIALS_H__ */
