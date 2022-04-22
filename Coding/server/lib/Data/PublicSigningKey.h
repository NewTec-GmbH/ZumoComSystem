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
 * @file PublicSigningKey.h
 * @author Luis Moser
 * @brief PublicSigningKey header
 * @date 07/30/2021
 *
 * @{
 */

#ifndef __PUBLICSIGNINGKEY_H__
#define __PUBLICSIGNINGKEY_H__

#include <Arduino.h>

/** Stores the public RSA2048 key to be used for firmware signature verification */
namespace PublicSigningKey
{
    static const char* PUB_RSA_SIGN_KEY = 
    "-----BEGIN PUBLIC KEY-----\n"
"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAwO80BNFKnza1OApkT68F"
"+q1hi434TDhcyl0Wq5c9uZOAakEUV7dU+QuBrP+mMjAoQCUBSezO/jV+dI7Gibau"
"hITUXVxw1UhgRWaucUu2veE81v+0jVrZis2rrhXJ32Wr4hKP8z7ZwKe2cQ1RGnb9"
"y7nz5jD8wlGkywxLDlQzgyhvajiHFw4D8vjVEsAP+wPj5vh+J4SMM8OphjiRbs4s"
"SONm3ENF/U1KcfYcf2xXgVI/ohkBWbz2vISbpHQD6r+brUEzMkLlC7cP9j/9jeZx"
"dp8hLrIiDl+t3qstiT7RvQev/yVE6+D1iRwWY4lmZf51L0pZluvOyPmAN9waPX1e"
"nQIDAQAB"
"-----END PUBLIC KEY-----\n";

    static const uint16_t KEY_LENGTH_BYTES = strlen(PUB_RSA_SIGN_KEY) + 1;
};
#endif /** __PUBLICSIGNINGKEY_H__ */

/**
 *  @}
 */