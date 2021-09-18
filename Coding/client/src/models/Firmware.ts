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
 * @file Firmware.ts
 * @author Luis Moser
 * @brief Firmware class
 * @date 09/17/2021
 *
 * @{
 */

import { FirmwareHeader } from "@/models/FirmwareHeader";

/** Data model for Firmware */
export class Firmware {
    /** The FirmwareInfo header */
    private m_header = new FirmwareHeader();

    /** The actual firmware */
    private m_firmware = new Uint8Array();

    /**
     * FirmwareHeader getter
     * @returns Returns the FirmwareHeader instance
     */
    public getHeader(): FirmwareHeader {
        return this.m_header;
    }

    /**
     * FirmwareHeader setter
     * @param header The new FirmwareHeader to be set
     */
    public setHeader(header: FirmwareHeader): void {
        this.m_header = header;
    }

    /**
     * Firmware setter
     * @param firmware The firmware to be set 
     */
    public setFirmware(firmware: Uint8Array): void {
        this.m_firmware = firmware;
    }

    /**
     * Serializes firmware to binary data
     * @returns Returns the serialized binary data
     */
    public serialize(): Uint8Array {
        let byteOffset = 0;
        const binaryHeader = this.m_header.serialize();
        const serialBuffer = new Uint8Array(binaryHeader.length + this.m_firmware.length);

        /* Copy the header */
        for (let byteIdx = 0; byteIdx < binaryHeader.length; byteIdx++) {
            serialBuffer[byteIdx] = binaryHeader[byteIdx];
        }
        byteOffset += binaryHeader.length;

        /* Copy the firmware */
        for (let byteIdx = 0; byteIdx < this.m_firmware.length; byteIdx++) {
            serialBuffer[byteOffset + byteIdx] = this.m_firmware[byteIdx];
        }
        return serialBuffer;
    }

    /**
     * Deserializes firmware from binary data
     * @param serial The binary firmware data to be deserialized
     */
    public deserialize(serialBuffer: Uint8Array): boolean {
        let byteOffset = 0;
        let retCode = false;
        const binaryHeader = new Uint8Array(FirmwareHeader.HEADER_SIZE_BYTE);

        /* Copy the header */
        for (let byteIdx = 0; byteIdx < FirmwareHeader.HEADER_SIZE_BYTE; byteIdx++) {
            binaryHeader[byteIdx] = serialBuffer[byteIdx];
        }
        retCode = this.m_header.deserialize(binaryHeader);
        byteOffset += FirmwareHeader.HEADER_SIZE_BYTE;

        /* Copy the firmware */
        for (let byteIdx = 0; byteIdx < (serialBuffer.length - FirmwareHeader.HEADER_SIZE_BYTE); byteIdx++) {
            this.m_firmware[byteIdx] = serialBuffer[byteOffset + byteIdx];
        }
        return retCode;
    }
}
