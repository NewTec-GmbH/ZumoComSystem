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
 * @addtogroup API
 * @{
 */

#ifndef __APIREQUEST_H__
#define __APIREQUEST_H__

#include <Arduino.h>

 /** Data structure for specifying the requested websocket API service as well as passing additional
  * arguments to API service implementations using the websocket service API
  */
class ApiRequest
{
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
     * Deserializes passed JSON object and re-creates internal state. It automatically checks the shapeliness of the incoming request
     * according to the defined request structure design.
     *
     * @param[in] serial The serialized JSON string
     * @return Returns true if successul, else false
     */
    bool deserialize(const String& serial);

    /**
     * Returns the command id of the current ApiRequest
     *
     * @return Returns the command id
     */
    const String& getCommandId() const;

    /**
     * Returns the JSON object
     *
     * @return Returns the JSON object string
     */
    const String& getJsonPayload() const;

private:
    /** Specifies the mnemonic command string name to identify the requested API service implementation */
    String m_commandId;

    /** Specifies optional/additional payload required for the requested API service implementation */
    String m_jsonPayload;
};
#endif /** __APIREQUEST_H__ */

/**
 *  @}
 */