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
 * @file HexConvert.ts
 * @author Luis Moser
 * @brief HexConvert class
 * @date 09/17/2021
 *
 * @{
 */

/** HexConvert class */
export class HexConvert {
  /**
   * Converts a binary buffer to a hex string with leading zeros
   *
   * @param binary The binary to be converted to hex
   * @returns The output hex string with leading zeros if byte < 16
   */
  public static binaryToHexString(binary: Uint8Array): string {
    let hexString = "";
    for (let byteIdx = 0; byteIdx < binary.length; byteIdx++) {
      let hex = (+binary[byteIdx]).toString(16);
      if (hex.length < 2) {
        hex = "0" + hex;
      }
      hexString += hex;
    }
    return hexString;
  }

  /**
   * Converts a hex string with leading zeros to binary buffer
   *
   * @param hexString The hex string with leading zeros if byte < 16
   * @returns Returns the output binary buffer
   */
  public static hexStringToBinary(hexString: string): Uint8Array {
    let byteIdx = 0;
    const binaryBuffer = new Uint8Array(hexString.length / 2);

    for (let charIdx = 0; charIdx < hexString.length; charIdx += 2) {
      binaryBuffer[byteIdx] = parseInt(
        hexString[charIdx] + hexString[charIdx + 1],
        16
      );
      byteIdx++;
    }
    return binaryBuffer;
  }
}
