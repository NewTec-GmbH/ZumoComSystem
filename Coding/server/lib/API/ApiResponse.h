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
 * @file ApiResponse.h
 * @author Luis Moser
 * @brief ApiResponse header
 * @date 07/14/2021
 * @addtogroup API
 * @{
 */

#ifndef __APIRESPONSE_H__
#define __APIRESPONSE_H__

#include <Arduino.h>
#include <ResponseCode.h>

 /** Data structure for returning information about the invoked websocket API service to the client.
  * Contains status code and additional/optional json payload
  */
class ApiResponse
{
public:
    /**
     * Default Constructor
     */
    ApiResponse();

    /**
     * Destructor
     */
    ~ApiResponse();

    /**
     * Serializes this instance to JSON object. Omits jsonPayload field if passed payload equals empty string
     *
     * @param[out] serial The serialized JSON output string
     * @return Returns true if successful, else false
     */
    bool serialize(String& serial);

    /**
     * Sets the JSON payload of this APIRequest
     *
     * @param[in] jsonPayload The JSON object string
     */
    void setJsonPayload(const String& jsonPayload);

    /**
     * Sets the status code of this APIRequest
     *
     * @param[in] statusCode The status code
     */
    void setStatusCode(const ResponseCode& statusCode);

    /**
     * Returns the current Status Code set in in the Request
     */
    ResponseCode getStatusCode();

private:
    /** Specifies the status code of the response */
    ResponseCode m_statusCode;

    /** Specifies optional/additional payload required for this command */
    String m_jsonPayload;
};
#endif /** __APIRESPONSE_H__ */

/**
 *  @}
 */