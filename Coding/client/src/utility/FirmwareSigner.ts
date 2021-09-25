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
 * @file FirmwareSigner.ts
 * @author Luis Moser
 * @brief FirmwareSigner class
 * @date 09/17/2021
 *
 * @{
 */

import { KJUR } from "jsrsasign";
import { HexConvert } from "./HexConvert";

/** FirmwareSigner class */
export class FirmwareSigner {
  /**
   * Signs the provided firmware with the provided private RSA2048 key according to PKCS#1v15
   * @param rsaKey The private RSA2048 key used for signing the firmware
   * @param firmware The firmware to be signed
   * @returns The resulting signature binary buffer
   */
  public static sign(rsaKey: string, firmware: Uint8Array): Uint8Array {
    const SIGN_ALGORITHM = "SHA256withRSA";
    const jsRSA = new KJUR.crypto.Signature({ alg: SIGN_ALGORITHM });

    /* Set the private RSA2048 key */
    jsRSA.init(rsaKey);

    /* Set the firmware payload for signing */
    jsRSA.updateHex(HexConvert.binaryToHexString(firmware));

    /* Get the signature result */
    return HexConvert.hexStringToBinary(jsRSA.sign());
  }
}
