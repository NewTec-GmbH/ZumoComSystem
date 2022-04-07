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
 * @file BinaryCommand.h
 * @author Luis Moser
 * @brief BinaryCommand header
 * @date 08/11/2021
 * @addtogroup API
 * @{
 */

#ifndef __BINARYCOMMAND_H__
#define __BINARYCOMMAND_H__

#include <Arduino.h>
#include <Permission.h>
#include <ApiResponse.h>

class Session;

/** Simple class which defines the mandatory members of any API services */
class BinaryCommand
{
public:
    /**
     * Constructor
     *
     * @param[in] serviceID The service id of the API service
     * @param[in] reqPermission The required permission for this service
     */
    BinaryCommand(const String& serviceID, const Permission& reqPermission);

    /**
     * Destructor
     */
    virtual ~BinaryCommand();

    /**
     * Returns the mnemonic service ID of the API service
     *
     * @return Return the service name
     */
    const String& getBinaryServiceID() const;

    /**
     * Returns the permissions required for invoking the API service
     *
     * @return Returns const reference of Permission
     */
    const Permission& getBinaryReqPermission() const;

    /**
     * Implements the API service business logic
     *
     * @param[out] response Reference to the outgoing ApiResponse
     * @param[in] connectionCtx Pointer to Session class instance
     */
    virtual void run(ApiResponse& response, Session* connectionCtx) = 0;

    /**
     * Implements the API serive reset logic to clean up resources
     */
    virtual void reset() = 0;

private:
    /**
     * Default Constructor
     */
    BinaryCommand();

    /**
     * Copy Constructor
     */
    BinaryCommand(const BinaryCommand&);

    /**
     * Assignment operator
     */
    BinaryCommand& operator =(const BinaryCommand&);

    /** Specifies the unique mnemonic name of the API service which is used to call the service remotely */
    String m_binaryServiceID;

    /** Specifies the permissions required to invoke the API service */
    Permission m_binaryReqPermission;
};
#endif /** __BINARYCOMMAND_H__ */

/**
 *  @}
 */