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
 * @file SessionManager.cpp
 * @author Luis Moser
 * @brief SessionManager class
 * @date 07/16/2021
 *
 * @{
 */

#include <SessionManager.h>

SessionManager::SessionManager()
{
}

SessionManager::~SessionManager()
{
}

bool SessionManager::checkSession(Command* command, Session* connectionCtx)
{
    bool sessionAuthenticated = connectionCtx->isAuthenticated();

    uint8_t numberOfPermissions = 0;
    const Permission* permissions = connectionCtx->getPermissions(numberOfPermissions);
    bool permissionAvailable = false;

    if (nullptr != permissions)
    {
        for (uint8_t permIdx = 0; permIdx < numberOfPermissions; permIdx++)
        {
            /* Check if linked user has required permission or has full priviliges */
            if ((permissions[permIdx] == ANY) || (command->getReqPermission() == permissions[permIdx]))
            {
                permissionAvailable = true;
                break;
            }
        }
    }

    return (sessionAuthenticated && permissionAvailable);
}

void SessionManager::aquireSession(ApiRequest& request, ApiResponse& response, Session* connectionCtx)
{
    UserCredentials credentials;
    credentials.deserialize(request.getJsonPayload());

    if (true == User::checkCredentials(credentials.getUsername(), credentials.getPassword()))
    {
        User* linkedUser = User::getUser(credentials.getUsername());
        connectionCtx->authenticateSession(linkedUser);

        response.setStatusCode(SUCCESS);
    }
    else
    {
        response.setStatusCode(ERROR);
    }
}
