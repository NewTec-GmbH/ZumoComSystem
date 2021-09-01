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
 * @file Zumo32U4.h
 * @author Luis Moser
 * @brief Zumo32U4 header
 * @date 08/23/2021
 *
 * @{
 */

#ifndef __ZUMO32U4_H__

#include <Arduino.h>
#include <ZumoDriverStateMachine.h>
#include <Zumo32U4Specification.h>
#include <IO.h>
#include <cdcacm.h>
#include <SPI.h>
#include <CryptoServices.h>

class ACMAsyncOper : public CDCAsyncOper
{
public:
    uint8_t OnInit(ACM* pacm);

private:
    static const uint16_t BAUD_RATE = 9800;

    static const uint8_t CHAR_FORMAT = 0;

    static const uint8_t PARITY_TYPE = 0;

    static const uint8_t NUMBER_OF_DATA_BITS = 8;

    static const uint8_t CONTROL_LINE_STATE = 3;
};

class Zumo32U4
{
public:
    static Zumo32U4& getInstance();

    bool open();

    bool close();

    ZumoStates getState();

    bool restart();

    bool readSerialBuffer(uint8_t* dataBuffer, uint32_t& chunkSize);

    bool writeSerialBuffer(uint8_t* dataBuffer, const uint16_t chunkSize);

    bool beginWriteFirmware(uint16_t firmwareSize, const String& expectedHash);

    bool writeFirmwareChunk(uint8_t* dataChunk, const uint16_t chunkSize);

    bool finalizeWriteFirmware();

    void handleUSBDriver();

    Zumo32U4();

    ~Zumo32U4();

private:
    static USB m_usb;

    static ACMAsyncOper m_asyncOper;

    static ACM m_acm;

    static const uint8_t AWAIT_RESPONSE_DELAY_MS;

    static const uint8_t NEXT_SERIAL_SEND_DELAY_MS;

    static const uint16_t USB_TIMEOUT_MS;

    static const uint8_t USB_RETRY_DELAY_MS;

    static const uint8_t USB_MAX_PACKET_READ_BYTES;

    static const uint16_t USB_MAX_PACKET_WRITE_BYTES;

    static const uint16_t PAGE_SIZE_BYTES;

    static const uint16_t MAX_FIRMWARE_BUFFER_BYTES = 4096;

    ZumoDriverStateMachine m_stateMachine;

    IO& m_io;

    CryptoServices m_crypto;

    uint8_t firmwareWriteBuffer[MAX_FIRMWARE_BUFFER_BYTES];

    uint16_t m_writtenFirmwareBytes;

    uint16_t m_currWriteMemAddr;

    uint16_t m_currReadMemAddr;

    uint16_t m_expectedFirmwareSize;

    String m_expectedHashValue;

    template<int size>
    bool sendCommand(const ZumoCommand<size>& command, const uint8_t* commandData, const uint16_t* commandDataSize, uint8_t* retData, uint16_t* retDataSize);

    template<int size>
    bool sendCommand(const ZumoCommand<size>& command, uint8_t* retData, uint16_t* retDataSize);

    void enterBootloaderMode();

    bool exitBootloaderMode();

    bool enterProgrammerMode();

    bool exitProgrammerMode();

    bool checkPlatform();

    bool verifyFuses();

    bool verifySignature();

    bool configurePlatform();

    bool readMemoryPage(uint8_t* dataChunk, uint16_t& chunkSize);

    bool flashPages(uint8_t* dataChunk, const uint16_t chunkSize);

    void reset();

    bool verifyWrittenFirmware();
};
#define __ZUMO32U4_H__
#endif
