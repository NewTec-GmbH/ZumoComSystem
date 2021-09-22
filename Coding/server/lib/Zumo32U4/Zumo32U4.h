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

 /** Class for configuring the Abstract Control Model used for the USB CDC (Communications Device Class/Serial) */
class ACMAsyncOper : public CDCAsyncOper
{
public:
    /**
     * Initializes the CDC device/Zumo robot when connected
     *
     * @param[in] acm The ACM pointer/instance
     * @return Returns result code
     */
    uint8_t OnInit(ACM* pacm);

private:
    /** Specifies the baud rate used for the serial communication */
    static const uint16_t BAUD_RATE = 57600;

    /** Specifies the character format */
    static const uint8_t CHAR_FORMAT = 0;

    /** Specifies parity check configuration */
    static const uint8_t PARITY_TYPE = 0;

    /** Specifies how many bits are transferred per packet */
    static const uint8_t NUMBER_OF_DATA_BITS = 8;

    /** Specifies RTS/CTS configuration */
    static const uint8_t CONTROL_LINE_STATE = 3;
};

/** Driver class used for serial port R/W, rebooting and flashing the Pololu Zumo32U4 robot */
class Zumo32U4
{
public:
    /**
     * Returns the driver instance
     *
     * @return Zumo32U4 instance/reference
     */
    static Zumo32U4& getInstance();

    /**
     * Open the Zumo driver
     *
     * @return Returns true if successful, else false
     */
    bool open();

    /**
     * Closes the Zumo driver
     *
     * @return Returns true if successful, else false
     */
    bool close();

    /**
     * Returns the current state of the state machine of the driver
     *
     * @return Returns the ZumoStates state of the driver
     */
    ZumoStates getState();

    /**
     * Reboots the Zumo robot with the GPIO reset line
     */
    void restart();

    /**
     * Blocking read of the serial output of the Zumo robot.
     * Waits until new data is received and blocks until the entire serial
     * buffer of the Zumo robot has been read.
     * Writes the result into the specified buffer.
     * There is no upper memory limit for the data to be received
     *
     * @param[in] dataBuffer The binary buffer to be used for saving the read data
     * @param[out] chunkSize Specifies the size of the received data in the dataBuffer
     * @return Returns true if successful, else false
     */
    bool readSerialBuffer(uint8_t* dataBuffer, uint32_t& chunkSize);

    /**
     * Blocking writing of the serial output of the Zumo robot.
     * Waits until all data has been sent to serial buffer of Zumo robot
     *
     * @param[in] dataBuffer The binary data buffer to be written to the serial buffer
     * @param[in] chunkSize The size of the data buffer in bytes
     * @return Returns true if successful, else false
     */
    bool writeSerialBuffer(uint8_t* dataBuffer, const uint16_t chunkSize);

    /**
     * Starts a new firmware flash for the Zumo Pololu Zumo32U4 robot by initializing the driver,
     * initializing the USB Host Shield, booting the robot into the bootloader,
     * checking the signature, fuses and bootloader config
     * of the robot and configuring the bootloader.
     *
     * Always call this method before beginning to write a new firmware to the robot.
     * After this, you can call writeFirmwareChunk() as often as required
     *
     * @param[in] firmwareSize The size of the firmware to be flashed in bytes
     * @param[in] expectedHash The SHA256 hash string of the firmware to be written and to be compared after flashing
     * @return Returns true if all bootloader was entered, checks passed and configuration was successful, else false
     */
    bool beginWriteFirmware(uint16_t firmwareSize, const String& expectedHash);

    /**
     * Writes the passed firmware chunk into the Zumo robot program flash.
     * Always call beginWriteFirmware() first and finish flashing by calling finalizeWriteFirmware()
     *
     * @param[in] dataChunk The binary data buffer to be written to the program flash of the robot
     * @param[in] chunkSize The size of the data buffer in bytes
     * @return Returns true if successful, else false
     */
    bool writeFirmwareChunk(uint8_t* dataChunk, const uint16_t chunkSize);

    /**
     * Finishes the flash process by verifying the written firmware image and exiting the programmer mode and
     * the booatloader and rebooting the Zumo robot.
     * Always call beginWriteFirmware() and writeFirmwareChunk() before.
     *
     * @return Returns true if the read back firmware image is valid and the Zumo robot has been successfully rebooted, else false
     */
    bool finalizeWriteFirmware();

    /**
     * Call this method periodically in the main loop to perform USB device enumration and cleanup tasks
     */
    void handleUSBDriver();

    /**
     * Default Constructor
     */
    Zumo32U4();

    /**
     * Destructor
     */
    ~Zumo32U4();

private:
    /* USB core driver instance for USB Host Shield */
    static USB m_usb;

    /* Instance of the CDC initialization class */
    static ACMAsyncOper m_asyncOper;

    /** Instance of ACM */
    static ACM m_acm;

    /** Specifies time in milliseconds how long it should be waited before reading USB response */
    static const uint8_t AWAIT_RESPONSE_DELAY_MS;

    /** Delay in milliseconds before the next USB packet can be sent */
    static const uint8_t NEXT_SERIAL_SEND_DELAY_MS;

    /** Timeout in milliseconds before attempt to connect to robot with USB is aborted */
    static const uint16_t USB_TIMEOUT_MS;

    /** Delay in milliseconds before connecting to robot is tried again */
    static const uint8_t USB_RETRY_DELAY_MS;

    /** Specifies the max size in bytes of incoming USB packets */
    static const uint8_t USB_MAX_PACKET_READ_BYTES;

    /** Specifies the max size in bytes of outgoing USB packets */
    static const uint16_t USB_MAX_PACKET_WRITE_BYTES;

    /** Specifies the number of bytes stored in one Zumo bootloader/flash memory page */
    static const uint16_t PAGE_SIZE_BYTES;

    /** Specifies the size of the firmware buffer, used for flashing, in bytes */
    static const uint16_t MAX_FIRMWARE_BUFFER_BYTES = 4096;

    /** State machine of the driver which keeps track of the state of the driver */
    ZumoDriverStateMachine m_stateMachine;

    /** Instance/Reference to IO class for GPIO access */
    IO& m_io;

    /** Instance of CryptoServices for firmware verification */
    CryptoServices m_crypto;

    /** Binary buffer used for writing the firmware */
    uint8_t firmwareWriteBuffer[MAX_FIRMWARE_BUFFER_BYTES];

    /** Specifies how many bytes have already been written to Zumo program flash */
    uint16_t m_writtenFirmwareBytes;

    /** Specifies the current memory/page address for flashing the firmware of the Zumo program flash */
    uint16_t m_currWriteMemAddr;

    /** Specifies the current memory/page address for reading the firmware of the Zumo program flash */
    uint16_t m_currReadMemAddr;

    /** Specifies the expected firmware size of the firmware to be flashed */
    uint16_t m_expectedFirmwareSize;

    /** Specifies the expected SHA256 hash string of the firmware to be flashed */
    String m_expectedHashValue;

    /**
     * Sends a Zumo robot bootloader command with additional payload to the robot and returns the response from the robot
     *
     * @param[in] command The ZumoCommand instance/command to be sent to the CATERIN/Zumo robot bootloader
     * @param[in] commandData Optional payload data to be used for the specified command
     * @param[in] commandDataSize The size of the passed command data in bytes
     * @param[out] retData The response data buffer to be used for writing the Zumo robot response
     * @param[out] retDataSize The size of the response data in bytes
     * @return Returns true if successful, else false
     */
    template<int size>
    bool sendCommand(const ZumoCommand<size>& command, const uint8_t* commandData, const uint16_t* commandDataSize, uint8_t* retData, uint16_t* retDataSize);

    /**
    * Sends a Zumo robot bootloader command to the robot and returns the response from the robot
    *
    * @param[in] command The ZumoCommand instance/command to be sent to the CATERIN/Zumo robot bootloader
    * @param[out] retData The response data buffer to be used for writing the Zumo robot response
    * @param[out] retDataSize The size of the response data in bytes
    * @return Returns true if successful, else false
    */
    template<int size>
    bool sendCommand(const ZumoCommand<size>& command, uint8_t* retData, uint16_t* retDataSize);

    /**
     * Boots the Zumo robot into the bootloader
     */
    void enterBootloaderMode();

    /**
     * Exits the Zumo robot from the bootlaoder
     *
     * @return Returns true if successful, else false
     */
    bool exitBootloaderMode();

    /**
     * Enters the Zumo robot's bootloader into the programmer mode
     *
     * @return Returns true if successful, else false
     */
    bool enterProgrammerMode();

    /**
     * Exits the Zumo robot's bootloader from the programmer mode
     *
     * @return Returns true if successful, else false
     */
    bool exitProgrammerMode();

    /**
     * Checks Zumo robot's bootloader and device configuration
     *
     * @return Returns true if checks passed, else false
     */
    bool checkPlatform();

    /**
     * Verifies the value of the Zumo robot's/AVR µC fuses
     *
     * @return Returns true if valid, else false
     */
    bool verifyFuses();

    /**
     * Verifies the device signature
     *
     * @return Returns true if valid, else false
     */
    bool verifySignature();

    /**
     * Configures the Zumo robot's CATERIN bootloader for flashing
     *
     * @return Returns true if successful, else false
     */
    bool configurePlatform();

    /**
     * Reads single memory page with at max 128 bytes from the Zumo robot program flash
     * at the current memory address
     *
     * @param[out] dataChunk The read content of the memory page
     * @param[out] chunkSize The size of the read memory page
     * @return Returns true if successful, else false
     */
    bool readMemoryPage(uint8_t* dataChunk, uint16_t& chunkSize);

    /**
     * Flashes the specifies data chunk into one or more program memory pages of the Zumo robot flash
     *
     * @param[in] dataChunk The binary buffer to be written into program flash
     * @param[in] chunkSize The size of the data chunk buffer
     * @return Returns true if successful, else false
     */
    bool flashPages(uint8_t* dataChunk, const uint16_t chunkSize);

    /**
     * Resets/clears the driver data
     */
    void reset();

    /**
     * Resets the USB Host Shield driver and re-initializes it
     *
     * @return Returns true if successful, else false
     */
    bool resetUSBDriver();

    /**
     * Verifies the integrity of the written firmware image by calculating
     * the SHA256 hash of the read image and comparing it with the expected
     * SHA256 hash value
     *
     * @return Returns true if firmware is valid, else false
     */
    bool verifyWrittenFirmware();
};
#define __ZUMO32U4_H__
#endif
