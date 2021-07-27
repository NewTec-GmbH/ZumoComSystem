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
 * @file Command.h
 * @author Luis Moser
 * @brief Command header
 * @date 07/16/2021
 *
 * @{
 */

#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <Arduino.h>
#include <Permission.h>
#include <ApiRequest.h>
#include <ApiResponse.h>
#include <ResponseCode.h>

 /** Simple class which defines the mandatory members of any API services */
class Command
{
public:
    /**
     * Constructor
     *
     * @param[in] serviceID The service id of the API service
     * @param[in] reqPermission The required permission for this service
     */
    Command(const String& serviceID, const Permission& reqPermission);

    /**
     * Destructor
     */
    virtual ~Command();

    /**
     * Returns the mnemonic service ID of the API service
     *
     * @return Return the service name
     */
    const String& getServiceID() const;

    /**
     * Returns the permissions required for invoking the API service
     *
     * @return Returns the required permission
     */
    const Permission& getReqPermission() const;

    /**
     * Implements the API service business logic
     *
     * @param[in] request Reference to the incoming ApiRequest
     * @param[out] response Reference to the outgoing ApiResponse
     */
    virtual void run(const ApiRequest& request, ApiResponse& response) const = 0;

private:
    /** Specifies the unique mnemonic name of the API service which is used to call the service remotely */
    String m_serviceID;

    /** Specifies the permissions required to invoke the API service */
    Permission m_reqPermission;
};
#endif
