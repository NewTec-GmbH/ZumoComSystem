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
 * @file SetSTACredentialsCommand.cpp
 * @author Luis Moser
 * @brief SetSTACredentialsCommand class
 * @date 08/19/2021
 *
 * @{
 */

#include <SetSTACredentialsCommand.h>
#include <NetworkCredentials.h>
#include <Permission.h>
#include <Store.h>
#include <Log.h>

SetSTACredentialsCommand::SetSTACredentialsCommand() :
    Command("setstacredentials", CONFIGURE_NETWORK)
{
}

SetSTACredentialsCommand::~SetSTACredentialsCommand()
{
}

void SetSTACredentialsCommand::run(const ApiRequest& request, ApiResponse& response, Session* connectionCtx) const
{
    const bool ARE_STA_CREDENTIALS = true;
    NetworkCredentials staCredentials;

    /* Check if credentials have been set. If not, delete the credentials */
    if (request.getJsonPayload() != "")
    {
        if (true == staCredentials.deserialize(request.getJsonPayload(), ARE_STA_CREDENTIALS))
        {
            /* Credentials are valid. Write them into store and save them in persistent storage */
            Store::getInstance().setSTACredentials(staCredentials);

            if (true == Store::getInstance().saveSTACredentials())
            {
                response.setStatusCode(SUCCESS);
                LOG_INFO("Successfully changed the STA network credentials! Reboot the system for the changes to take effect");
            }
            else
            {
                response.setStatusCode(ERROR);
                LOG_ERROR("Could not save the new STA network credentials to persistent storage!");
            }
        }
        else
        {
            response.setStatusCode(BAD_REQUEST);
            LOG_ERROR("Could not set new STA network credentials because either JSON is malformed or SSID or passphrase do not comply with IEEE 802.11");
        }
    }
    else
    {
        if (true == Store::getInstance().deleteSTACredentials())
        {
            response.setStatusCode(SUCCESS);
            LOG_INFO("Successfully deleted the STA network credentials!");
        }
        else
        {
            response.setStatusCode(ERROR);
            LOG_ERROR("Could not delete the STA network credentials!");
        }
    }
}
