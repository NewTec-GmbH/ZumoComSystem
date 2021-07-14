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
 * @file ApiRequest.h
 * @author Luis Moser
 * @brief ApiRequest header
 * @date 07/14/2021
 *
 * @{
 */

#ifndef __APIREQUEST_H__
#define __APIREQUEST_H__

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Log.h>

 /* Data structure for data exchange using the Api */
class ApiRequest
{
private:
    /** Specifies the command to be executed */
    String m_commandId;

    /** Specifies optional/additional payload required for this command */
    String m_jsonPayload;

public:
    /**
     * Default Constructor
     */
    ApiRequest();

    /**
     * Destructor
     */
    ~ApiRequest();

    /**
     * Deserializes passed JSON object and re-creates internal state
     *
     * @param[in] serial The serialized JSON string
     * @return Returns true if successul, else false
     */
    bool deserialize(String serial);

    /**
     * Returns the command id
     *
     * @return Returns the command id 
     */
    String getCommandId();

    /**
     * Returns the JSON object
     *
     * @return Returns the JSON object string
     */
    String getJsonPayload();
};
#endif /** __APIREQUEST_H__ */
