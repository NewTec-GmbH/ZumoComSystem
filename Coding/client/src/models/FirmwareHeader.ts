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
 * @file FirmwareHeader.ts
 * @author Luis Moser
 * @brief FirmwareHeader class
 * @date 09/17/2021
 *
 * @{
 */

/** Data model for FirmwareHeader */
export class FirmwareHeader {
  /** Specifies the file id/magic number field size in bytes */
  public static readonly ID_SIZE_BYTE = 16;

  /** Specifies the target system field size in bytes */
  public static readonly TARGET_SIZE_BYTE = 16;

  /** Specifies the file version field size in bytes */
  public static readonly VERSION_SIZE_BYTE = 1;

  /** Specifies the hash algorithm field size in bytes */
  public static readonly HASH_ALG_SIZE_BYTE = 16;

  /** Specifies the signing algorithm field size in bytes */
  public static readonly SIGN_ALG_SIZE_BYTE = 32;

  /** Specifies the signature field size in bytes */
  public static readonly SIGNATURE_SIZE_BYTE = 256;

  /** Specifies the total firmware header field size in bytes */
  public static readonly HEADER_SIZE_BYTE =
    FirmwareHeader.ID_SIZE_BYTE +
    FirmwareHeader.TARGET_SIZE_BYTE +
    FirmwareHeader.VERSION_SIZE_BYTE +
    FirmwareHeader.HASH_ALG_SIZE_BYTE +
    FirmwareHeader.SIGN_ALG_SIZE_BYTE +
    FirmwareHeader.SIGNATURE_SIZE_BYTE;

  /** Stores the id field of the header */
  private m_idBuffer: Uint8Array;

  /** Stores the target system field of the header */
  private m_targetBuffer: Uint8Array;

  /** Stores the file version field of the header */
  private m_versionBuffer: Uint8Array;

  /** Stores the hash algorithm field of the header */
  private m_hashAlgBuffer: Uint8Array;

  /** Stores the signing algorithm field of the header */
  private m_signAlgBuffer: Uint8Array;

  /** Stores the signature field of the header */
  private m_signatureBuffer: Uint8Array;

  /**
   * Default Constructor
   */
  constructor() {
    this.m_idBuffer = new Uint8Array(FirmwareHeader.ID_SIZE_BYTE);
    this.m_targetBuffer = new Uint8Array(FirmwareHeader.TARGET_SIZE_BYTE);
    this.m_versionBuffer = new Uint8Array(FirmwareHeader.VERSION_SIZE_BYTE);
    this.m_hashAlgBuffer = new Uint8Array(FirmwareHeader.HASH_ALG_SIZE_BYTE);
    this.m_signAlgBuffer = new Uint8Array(FirmwareHeader.SIGN_ALG_SIZE_BYTE);
    this.m_signatureBuffer = new Uint8Array(FirmwareHeader.SIGNATURE_SIZE_BYTE);
  }

  /**
   * Converts an ASCII String to binary
   * @param msg The string to be converted
   * @returns Returns the binary data
   */
  private static stringToBinary(msg: string): Uint8Array {
    const binaryBuffer = new Uint8Array(msg.length);
    for (let charIdx = 0; charIdx < msg.length; charIdx++) {
      binaryBuffer[charIdx] = msg.charCodeAt(charIdx);
    }
    return binaryBuffer;
  }

  /**
   * Converts binary data to an ASCII String
   * @param binary The binary data to be converted
   * @returns Returns the string
   */
  private static binaryToString(binary: Uint8Array): string {
    return String.fromCharCode(...binary);
  }

  /**
   * Returns the target system
   * @returns Returns the target
   */
  public getTarget(): string {
    return FirmwareHeader.binaryToString(this.m_targetBuffer);
  }

  /**
   * Sets the target system
   * @param target The target system to be set
   * @returns Returns true if successful, else false
   */
  public setTarget(target: string): boolean {
    let retCode = false;
    if (FirmwareHeader.TARGET_SIZE_BYTE >= target.length) {
      this.m_targetBuffer = FirmwareHeader.stringToBinary(target);
      retCode = true;
    }
    return retCode;
  }

  /**
   * Sets the firmware signature
   * @param signature The signature to be set
   * @returns Returns true if successful, else false
   */
  public setSignature(signature: Uint8Array): boolean {
    let retCode = false;
    if (FirmwareHeader.SIGNATURE_SIZE_BYTE === signature.length) {
      this.m_signatureBuffer = signature;
      retCode = true;
    }
    return retCode;
  }

  /**
   * Returns the ID string
   * @returns Returns the ID
   */
  public getID(): string {
    return FirmwareHeader.binaryToString(this.m_idBuffer);
  }

  /**
   * Sets the ID string
   * @param id The ID to be set
   * @returns Returns true if successful, else false
   */
  private setID(id: string): boolean {
    let retCode = false;
    if (FirmwareHeader.ID_SIZE_BYTE >= id.length) {
      this.m_idBuffer = FirmwareHeader.stringToBinary(id);
      retCode = true;
    }
    return retCode;
  }

  /**
   * Returns the version number
   * @returns Returns the version
   */
  public getVersion(): number {
    return this.m_versionBuffer[0];
  }

  /**
   * Sets the version number
   * @param version The version to be set
   */
  private setVersion(version: number): void {
    this.m_versionBuffer[0] = version;
  }

  /**
   * Returns the used hashing algorithm string
   * @returns Returns the hash algorithm
   */
  public getHashAlg(): string {
    return FirmwareHeader.binaryToString(this.m_hashAlgBuffer);
  }

  /**
   * Sets the hashing algorithm string
   * @param hashAlg The algorithm string to be set
   * @returns Returns true if successful, else false
   */
  private setHashAlg(hashAlg: string): boolean {
    let retCode = false;
    if (FirmwareHeader.HASH_ALG_SIZE_BYTE >= hashAlg.length) {
      this.m_hashAlgBuffer = FirmwareHeader.stringToBinary(hashAlg);
      retCode = true;
    }
    return retCode;
  }

  /**
   * Returns the used signature algorithm string
   * @returns Returns the signature algorithm
   */
  public getSignAlg(): string {
    return FirmwareHeader.binaryToString(this.m_signAlgBuffer);
  }

  /**
   * Sets the signature algorithm string
   * @param signAlg The signature algorithm to be set
   * @returns Returns true if successful, else false
   */
  private setSignAlg(signAlg: string): boolean {
    let retCode = false;
    if (FirmwareHeader.SIGN_ALG_SIZE_BYTE >= signAlg.length) {
      this.m_signAlgBuffer = FirmwareHeader.stringToBinary(signAlg);
      retCode = true;
    }
    return retCode;
  }

  /**
   * Serializes the instance to binary data
   * @returns Returns the binary data
   */
  public serialize(): Uint8Array {
    const serialBuffer = new Uint8Array(FirmwareHeader.HEADER_SIZE_BYTE);
    let byteOffset = 0;

    /* Set the header configuration */
    this.setID("CPSFW");
    this.setVersion(1);
    this.setHashAlg("SHA256");
    this.setSignAlg("RSA2048PKCS#1v15");

    /* Copy the ID */
    for (let byteIdx = 0; byteIdx < FirmwareHeader.ID_SIZE_BYTE; byteIdx++) {
      serialBuffer[byteIdx] = this.m_idBuffer[byteIdx];
    }
    byteOffset += FirmwareHeader.ID_SIZE_BYTE;

    /* Copy the target */
    for (
      let byteIdx = 0;
      byteIdx < FirmwareHeader.TARGET_SIZE_BYTE;
      byteIdx++
    ) {
      serialBuffer[byteOffset + byteIdx] = this.m_targetBuffer[byteIdx];
    }
    byteOffset += FirmwareHeader.TARGET_SIZE_BYTE;

    /* Copy the version */
    serialBuffer[byteOffset] = this.m_versionBuffer[0];
    byteOffset += 1;

    /* Copy the hashing algorithm */
    for (
      let byteIdx = 0;
      byteIdx < FirmwareHeader.HASH_ALG_SIZE_BYTE;
      byteIdx++
    ) {
      serialBuffer[byteOffset + byteIdx] = this.m_hashAlgBuffer[byteIdx];
    }
    byteOffset += FirmwareHeader.HASH_ALG_SIZE_BYTE;

    /* Copy the signing algorithm */
    for (
      let byteIdx = 0;
      byteIdx < FirmwareHeader.SIGN_ALG_SIZE_BYTE;
      byteIdx++
    ) {
      serialBuffer[byteOffset + byteIdx] = this.m_signAlgBuffer[byteIdx];
    }
    byteOffset += FirmwareHeader.SIGN_ALG_SIZE_BYTE;

    /* Copy the signature */
    for (
      let byteIdx = 0;
      byteIdx < FirmwareHeader.SIGNATURE_SIZE_BYTE;
      byteIdx++
    ) {
      serialBuffer[byteOffset + byteIdx] = this.m_signatureBuffer[byteIdx];
    }
    return serialBuffer;
  }

  /**
   * Deserializes the binary data and re-creates instance
   * @param serialBuffer The binary data to be used for deserialization
   * @returns Returns true if successful, else false
   */
  public deserialize(serialBuffer: Uint8Array): boolean {
    let retCode = false;
    if (FirmwareHeader.HEADER_SIZE_BYTE === serialBuffer.length) {
      let byteOffset = 0;

      /* Copy the ID */
      for (let byteIdx = 0; byteIdx < FirmwareHeader.ID_SIZE_BYTE; byteIdx++) {
        this.m_idBuffer[byteIdx] = serialBuffer[byteIdx];
      }
      byteOffset += FirmwareHeader.ID_SIZE_BYTE;

      /* Copy the target */
      for (
        let byteIdx = 0;
        byteIdx < FirmwareHeader.TARGET_SIZE_BYTE;
        byteIdx++
      ) {
        this.m_targetBuffer[byteIdx] = serialBuffer[byteOffset + byteIdx];
      }
      byteOffset += FirmwareHeader.TARGET_SIZE_BYTE;

      /* Copy the version */
      this.m_versionBuffer[0] = serialBuffer[byteOffset];
      byteOffset += 1;

      /* Copy the hashing algorithm */
      for (
        let byteIdx = 0;
        byteIdx < FirmwareHeader.HASH_ALG_SIZE_BYTE;
        byteIdx++
      ) {
        this.m_hashAlgBuffer[byteIdx] = serialBuffer[byteOffset + byteIdx];
      }
      byteOffset += FirmwareHeader.HASH_ALG_SIZE_BYTE;

      /* Copy the signing algorithm */
      for (
        let byteIdx = 0;
        byteIdx < FirmwareHeader.SIGN_ALG_SIZE_BYTE;
        byteIdx++
      ) {
        this.m_signAlgBuffer[byteIdx] = serialBuffer[byteOffset + byteIdx];
      }
      byteOffset += FirmwareHeader.SIGN_ALG_SIZE_BYTE;

      /* Copy the signature */
      for (
        let byteIdx = 0;
        byteIdx < FirmwareHeader.SIGNATURE_SIZE_BYTE;
        byteIdx++
      ) {
        this.m_signatureBuffer[byteIdx] = serialBuffer[byteOffset + byteIdx];
      }

      retCode = true;
    }
    return retCode;
  }
}
