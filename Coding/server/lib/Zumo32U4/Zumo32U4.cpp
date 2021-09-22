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
 * @file Zumo32U4.cpp
 * @author Luis Moser
 * @brief Zumo32U4 class
 * @date 08/23/2021
 *
 * @{
 */

#include <Zumo32U4.h>
#include <FirmwareChecker.h>
#include <Log.h>
#include <GPIOPins.h>

USB Zumo32U4::m_usb;
ACMAsyncOper Zumo32U4::m_asyncOper;
ACM Zumo32U4::m_acm(&m_usb, &m_asyncOper);

const uint8_t Zumo32U4::AWAIT_RESPONSE_DELAY_MS = 50;
const uint8_t Zumo32U4::NEXT_SERIAL_SEND_DELAY_MS = 10;
const uint16_t Zumo32U4::USB_TIMEOUT_MS = 10000;
const uint8_t Zumo32U4::USB_RETRY_DELAY_MS = 10;
const uint8_t Zumo32U4::USB_MAX_PACKET_READ_BYTES = 64;
const uint16_t Zumo32U4::USB_MAX_PACKET_WRITE_BYTES = 64;
const uint16_t Zumo32U4::PAGE_SIZE_BYTES = 128;
const uint16_t Zumo32U4::MAX_FIRMWARE_BUFFER_BYTES;

uint8_t ACMAsyncOper::OnInit(ACM* pacm)
{
    uint8_t rcode;

    LINE_CODING lineCoding;
    lineCoding.dwDTERate = BAUD_RATE;
    lineCoding.bCharFormat = CHAR_FORMAT;
    lineCoding.bParityType = PARITY_TYPE;
    lineCoding.bDataBits = NUMBER_OF_DATA_BITS;

    rcode = pacm->SetLineCoding(&lineCoding);
    if (rcode)
    {
        ErrorMessage<uint8_t>(PSTR("SetLineCoding"), rcode);
    }
    return rcode;
}

Zumo32U4::Zumo32U4() :
    m_stateMachine(),
    m_io(IO::getInstance()),
    m_crypto(),
    firmwareWriteBuffer(),
    m_writtenFirmwareBytes(0),
    m_currWriteMemAddr(0),
    m_currReadMemAddr(0),
    m_expectedFirmwareSize(0),
    m_expectedHashValue()
{
}

Zumo32U4::~Zumo32U4()
{
    close();
}

Zumo32U4& Zumo32U4::getInstance()
{
    static Zumo32U4 instance;
    return instance;
}

bool Zumo32U4::open()
{
    bool retCode = false;
    if (true == m_stateMachine.setState(OPENED))
    {
        /* Clear all driver data*/
        reset();
        retCode = true;
    }
    else
    {
        LOG_ERROR("Could not open device driver. Current state does not allow transition!");
    }
    return retCode;
}

bool Zumo32U4::close()
{
    bool retCode = ((FLASHING != m_stateMachine.getState()) && (true == m_stateMachine.setState(CLOSED)));
    if (true == retCode)
    {
        LOG_INFO("Successfully closed the Zumo32U4 driver!");
    }
    else
    {
        LOG_ERROR("Could not close the Zumo32U4 driver!");
    }
    return retCode;
}

void Zumo32U4::handleUSBDriver()
{
    m_usb.Task();
}

ZumoStates Zumo32U4::getState()
{
    return m_stateMachine.getState();
}

template<int size>
bool Zumo32U4::sendCommand(const ZumoCommand<size>& command, const uint8_t* commandData, const uint16_t* commandDataSize, uint8_t* retData, uint16_t* retDataSize)
{
    uint8_t retCode = true;
    uint8_t resCode = 1;

    /* Temporary buffer for both the command OpCode as well as the command data */
    const uint16_t WRITE_BUFFER_SIZE = 256;
    uint8_t writeBuffer[WRITE_BUFFER_SIZE];
    uint16_t bytesToWrite = 0;

    uint8_t* pWriteBuffer = nullptr;
    uint8_t* pReadBuffer = nullptr;

    uint16_t totalReadBytes = 0;
    unsigned long startInitTime = 0L;

    /* Copy the command OpCode into buffer */
    memcpy(writeBuffer, command.commandData, command.commandSize);
    bytesToWrite = command.commandSize;

    /* If any command data has been passed, append that data to the buffer */
    if ((nullptr != commandData) && (0 < *commandDataSize))
    {
        pWriteBuffer = &writeBuffer[bytesToWrite];
        memcpy(pWriteBuffer, commandData, *commandDataSize);
        bytesToWrite += *commandDataSize;
    }

    /* Await ACM initialization */
    startInitTime = millis();
    while ((false == m_acm.isReady()) && (USB_TIMEOUT_MS >= (millis() - startInitTime)))
    {
        LOG_WARN("Trying to initialize the ACM instance!");
        delay(USB_RETRY_DELAY_MS);
        handleUSBDriver();
    }

    if (true == m_acm.isReady())
    {
        /* Send the OpCode and command data to Zumo robot */
        resCode = m_acm.SndData(bytesToWrite, const_cast<uint8_t*>(writeBuffer));
        if (0 == resCode)
        {
            /* Await response */
            delay(AWAIT_RESPONSE_DELAY_MS);

            uint16_t readBytes = 0;

            /* Read all response data */
            do
            {
                readBytes = PAGE_SIZE_BYTES;
                pReadBuffer = &retData[totalReadBytes];

                resCode = m_acm.RcvData(&readBytes, pReadBuffer);
                if (resCode && resCode != hrNAK)
                {
                    retCode = false;
                    ErrorMessage<uint8_t>(PSTR("Ret"), resCode);
                    LOG_ERROR("Could not receive data from Zumo robot!");
                    break;
                }
                totalReadBytes += readBytes;
            } while (readBytes != 0);

            *retDataSize = totalReadBytes;
        }
        else
        {
            ErrorMessage<uint8_t>(PSTR("SndData"), resCode);
            LOG_ERROR("Could not send data packet to Zumo robot. Aborting now");
            retCode = false;
        }
        /* Wait until next serial send */
        delay(NEXT_SERIAL_SEND_DELAY_MS);
    }
    else
    {
        LOG_ERROR("Aborting sendCommand() because ACM could not be initialized!");
        retCode = false;
    }
    return retCode;
}

template<int size>
bool Zumo32U4::sendCommand(const ZumoCommand<size>& command, uint8_t* retData, uint16_t* retDataSize)
{
    return sendCommand(command, nullptr, 0, retData, retDataSize);
}

void Zumo32U4::restart()
{
    const uint16_t HIGH_TIME_MS = 500;

    /* Pull down RESET to GND once to restart in normal mode */
    m_io.writeGPIO(GPIOPins::PIN_ROBOT_RESET, LOW);
    delay(HIGH_TIME_MS);
    m_io.writeGPIO(GPIOPins::PIN_ROBOT_RESET, HIGH);
}

void Zumo32U4::enterBootloaderMode()
{
    const uint8_t LOW_TIME_MS = 50;
    const uint8_t WAIT_TIME_MS = 100;

    /* Set control GPIO as output */
    m_io.setPinMode(GPIOPins::PIN_ROBOT_RESET, OUTPUT);

    /* Pull down RESET to GND twice in under 750ms to enter bootloader mode */
    m_io.writeGPIO(GPIOPins::PIN_ROBOT_RESET, LOW);
    delay(LOW_TIME_MS);
    m_io.writeGPIO(GPIOPins::PIN_ROBOT_RESET, HIGH);

    delay(WAIT_TIME_MS);

    m_io.writeGPIO(GPIOPins::PIN_ROBOT_RESET, LOW);
    delay(LOW_TIME_MS);
    m_io.writeGPIO(GPIOPins::PIN_ROBOT_RESET, HIGH);
}

bool Zumo32U4::exitBootloaderMode()
{
    bool retCode = false;

    const uint8_t BUFFER_SIZE = 64;
    uint8_t readBuffer[BUFFER_SIZE];
    uint16_t readBytes = 0;

    /* Check the software ID */
    retCode = sendCommand(Zumo32U4Specification::EXIT_BOOTLOADER_MODE, readBuffer, &readBytes);
    if (true == retCode)
    {
        retCode = (0 == memcmp(readBuffer, Zumo32U4Specification::RET_OK.data, Zumo32U4Specification::RET_OK.dataSize));
        if (true == retCode)
        {
            LOG_INFO("Successfully exited bootloader mode!");
        }
        else
        {
            LOG_ERROR("Could not exit bootloader mode!");
        }
    }
    else
    {
        LOG_ERROR("Could not send exit bootloader mode command!");
    }
    return retCode;
}

bool Zumo32U4::enterProgrammerMode()
{
    bool retCode = false;

    const uint8_t BUFFER_SIZE = 64;
    uint8_t readBuffer[BUFFER_SIZE];
    uint16_t readBytes = 64;

    /* Check the software ID */
    retCode = sendCommand(Zumo32U4Specification::ENTER_PROGRAMMING_MODE, readBuffer, &readBytes);
    if (true == retCode)
    {
        retCode = (0 == memcmp(readBuffer, Zumo32U4Specification::RET_OK.data, Zumo32U4Specification::RET_OK.dataSize));
        if (true == retCode)
        {
            LOG_INFO("Successfully entered programmer mode!");
        }
        else
        {
            LOG_ERROR("Could not enter programmer mode!");
        }
    }
    else
    {
        LOG_ERROR("Could not send enter programmer mode command!");
    }
    return retCode;
}

bool Zumo32U4::exitProgrammerMode()
{
    bool retCode = false;

    const uint8_t BUFFER_SIZE = 64;
    uint8_t readBuffer[BUFFER_SIZE];
    uint16_t readBytes = 64;

    /* Check the software ID */
    retCode = sendCommand(Zumo32U4Specification::EXIT_PROGRAMMING_MODE, readBuffer, &readBytes);
    if (true == retCode)
    {
        retCode = (0 == memcmp(readBuffer, Zumo32U4Specification::RET_OK.data, Zumo32U4Specification::RET_OK.dataSize));
        if (true == retCode)
        {
            LOG_INFO("Successfully exited programmer mode!");
        }
        else
        {
            LOG_ERROR("Could not exited programmer mode!");
        }
    }
    else
    {
        LOG_ERROR("Could not send exit programmer mode command!");
    }
    return retCode;
}

bool Zumo32U4::checkPlatform()
{
    bool validSwID = false;
    bool validSwVersion = false;
    bool validHwVersion = false;
    bool validProgrType = false;
    bool supportsAutoInc = false;
    bool supportsBlockFlash = false;
    bool supportsDeviceCodes = false;

    const uint8_t BUFFER_SIZE = 64;
    uint8_t readBuffer[BUFFER_SIZE];
    uint16_t readBytes = 64;

    /* Check the software ID */
    if (true == sendCommand(Zumo32U4Specification::READ_SW_ID, readBuffer, &readBytes))
    {
        validSwID = (0 == memcmp(readBuffer, Zumo32U4Specification::EXPECTED_SOFTWARE_ID.data, Zumo32U4Specification::EXPECTED_SOFTWARE_ID.dataSize));
    }
    else
    {
        LOG_ERROR("Could not fetch software ID!");
    }

    /* Check the software version */
    if (true == sendCommand(Zumo32U4Specification::READ_SW_VERSION, readBuffer, &readBytes))
    {
        validSwVersion = (0 == memcmp(readBuffer, Zumo32U4Specification::EXPECTED_SW_VERSION.data, Zumo32U4Specification::EXPECTED_SW_VERSION.dataSize));
    }
    else
    {
        LOG_ERROR("Could not fetch software version!");
    }

    /* Check the hardware version */
    if (true == sendCommand(Zumo32U4Specification::READ_HW_VERSION, readBuffer, &readBytes))
    {
        validHwVersion = (0 == memcmp(readBuffer, Zumo32U4Specification::EXPECTED_HW_VERSION.data, Zumo32U4Specification::EXPECTED_HW_VERSION.dataSize));
    }
    else
    {
        LOG_ERROR("Could not fetch hardware version!");
    }

    /* Check programmer type */
    if (true == sendCommand(Zumo32U4Specification::READ_PROGRAMMER_TYPE, readBuffer, &readBytes))
    {
        validProgrType = (0 == memcmp(readBuffer, Zumo32U4Specification::EXPECTED_PROGRAMMER_TYPE.data, Zumo32U4Specification::EXPECTED_PROGRAMMER_TYPE.dataSize));
    }
    else
    {
        LOG_ERROR("Could not fetch the programmer type!");
    }

    /* Check auto memory address increment support */
    if (true == sendCommand(Zumo32U4Specification::CHECK_AUTO_MEM_ADDR_INC_SUPPORT, readBuffer, &readBytes))
    {
        supportsAutoInc = (0 == memcmp(readBuffer, Zumo32U4Specification::EXPECTED_SUPPORTS_AUTO_MEM_ADDR_INC.data, Zumo32U4Specification::EXPECTED_SUPPORTS_AUTO_MEM_ADDR_INC.dataSize));
    }
    else
    {
        LOG_ERROR("Could not fetch the auto memory address increment support information!");
    }

    /* Check block flash support */
    if (true == sendCommand(Zumo32U4Specification::CHECK_BLOCK_FLASH_SUPPORT, readBuffer, &readBytes))
    {
        supportsBlockFlash = (0 == memcmp(readBuffer, Zumo32U4Specification::EXPECTED_BLOCK_BUFFER_SIZE.data, Zumo32U4Specification::EXPECTED_BLOCK_BUFFER_SIZE.dataSize));
    }
    else
    {
        LOG_ERROR("Could not fetch the auto memory address increment support information!");
    }

    /* Check supported device codes */
    if (true == sendCommand(Zumo32U4Specification::READ_SUPPORTED_DEVICE_CODE, readBuffer, &readBytes))
    {
        supportsDeviceCodes = (0 == memcmp(readBuffer, Zumo32U4Specification::EXPECTED_DEVICE_CODE.data, Zumo32U4Specification::EXPECTED_DEVICE_CODE.dataSize));
    }
    else
    {
        LOG_ERROR("Could not fetch the auto memory address increment support information!");
    }

#ifdef ACTIVATE_LOGGING
    if (true == validSwID)
    {
        LOG_INFO("Received software ID is valid!");
    }
    else
    {
        LOG_ERROR("Received software ID is invalid!");
    }

    if (true == validSwVersion)
    {
        LOG_INFO("Received software version is valid!");
    }
    else
    {
        LOG_ERROR("Received software version is invalid!");
    }

    if (true == validHwVersion)
    {
        LOG_INFO("Received hardware version is valid!");
    }
    else
    {
        LOG_ERROR("Received hardware version is invalid!");
    }

    if (true == validProgrType)
    {
        LOG_INFO("Received programmer type is valid!");
    }
    else
    {
        LOG_ERROR("Received programmer type is invalid!");
    }

    if (true == supportsAutoInc)
    {
        LOG_INFO("Automatic memory address increment supported");
    }
    else
    {
        LOG_ERROR("Automatic memory address increment not supported");
    }

    if (true == supportsBlockFlash)
    {
        LOG_INFO("Block flash with 128 bytes blocks is supported");
    }
    else
    {
        LOG_ERROR("Block flash with 128 bytes blocks is not supported");
    }

    if (true == supportsDeviceCodes)
    {
        LOG_INFO("Supports all device codes!");
    }
    else
    {
        LOG_ERROR("Does not support all device codes!");
    }
#endif

    return (validSwID
        && validSwVersion
        && validHwVersion
        && validProgrType
        && supportsAutoInc
        && supportsBlockFlash
        && supportsDeviceCodes);
}

bool Zumo32U4::verifyFuses()
{
    const uint8_t BUFFER_SIZE = 64;
    uint8_t readBuffer[BUFFER_SIZE];
    uint16_t readBytes = 64;

    bool retCode = false;
    bool lsbFuseValid = false;
    bool msbFuseValid = false;
    bool extFuseValid = false;

    /* Check the LSB fuse */
    retCode = sendCommand(Zumo32U4Specification::READ_LSB_FUSE, readBuffer, &readBytes);
    if (true == retCode)
    {
        lsbFuseValid = (0 == memcmp(readBuffer, Zumo32U4Specification::EXPECTED_LSB_FUSE_VALUE.data, Zumo32U4Specification::EXPECTED_LSB_FUSE_VALUE.dataSize));
        if (true == lsbFuseValid)
        {
            LOG_INFO("LSB fuse value is valid!");
        }
        else
        {
            LOG_INFO("LSB fuse value is invalid!");
        }
    }
    else
    {
        LOG_ERROR("Could not read LSB fuse!");
    }

    /* Check the MSB fuse */
    retCode = sendCommand(Zumo32U4Specification::READ_MSB_FUSE, readBuffer, &readBytes);
    if (true == retCode)
    {
        msbFuseValid = (0 == memcmp(readBuffer, Zumo32U4Specification::EXPECTED_MSB_FUSE_VALUE.data, Zumo32U4Specification::EXPECTED_MSB_FUSE_VALUE.dataSize));
        if (true == msbFuseValid)
        {
            LOG_INFO("MSB fuse value is valid!");
        }
        else
        {
            LOG_INFO("MSB fuse value is invalid!");
        }
    }
    else
    {
        LOG_ERROR("Could not read MSB fuse!");
    }

    /* Check the extended fuse */
    retCode = sendCommand(Zumo32U4Specification::READ_LSB_FUSE, readBuffer, &readBytes);
    if (true == retCode)
    {
        extFuseValid = (0 == memcmp(readBuffer, Zumo32U4Specification::EXPECTED_EXTENDED_FUSE_VALUE.data, Zumo32U4Specification::EXPECTED_EXTENDED_FUSE_VALUE.dataSize));
        if (true == extFuseValid)
        {
            LOG_INFO("Extended fuse value is valid!");
        }
        else
        {
            LOG_INFO("Extended fuse value is invalid!");
        }
    }
    else
    {
        LOG_ERROR("Could not read extended fuse!");
    }
    return (lsbFuseValid && msbFuseValid && extFuseValid);
}

bool Zumo32U4::verifySignature()
{
    bool retCode = false;

    const uint8_t BUFFER_SIZE = 64;
    uint8_t readBuffer[BUFFER_SIZE];
    uint16_t readBytes = 64;

    /* Check the LSB fuse */
    retCode = sendCommand(Zumo32U4Specification::READ_SIGNATURE, readBuffer, &readBytes);
    if (true == retCode)
    {
        retCode = (0 == memcmp(readBuffer, Zumo32U4Specification::EXPECTED_SIGNATURE.data, Zumo32U4Specification::EXPECTED_SIGNATURE.dataSize));
        if (true == retCode)
        {
            LOG_INFO("Signature value is valid!");
        }
        else
        {
            LOG_INFO("Signature value is invalid!");
        }
    }
    else
    {
        LOG_ERROR("Could not read Signature value");
    }
    return retCode;
}

bool Zumo32U4::configurePlatform()
{
    bool retCode = false;

    const uint8_t BUFFER_SIZE = 64;
    uint8_t readBuffer[BUFFER_SIZE];
    uint16_t readBytes = 64;

    const uint8_t DEVICE_CODE = 0x44;
    const uint16_t DATA_SIZE = 1;

    /* Set device type */
    if (true == sendCommand(Zumo32U4Specification::SET_DEVICE_TYPE, &DEVICE_CODE, &DATA_SIZE, readBuffer, &readBytes))
    {
        retCode = (0 == memcmp(readBuffer, Zumo32U4Specification::RET_OK.data, Zumo32U4Specification::RET_OK.dataSize));
        if (true == retCode)
        {
            LOG_INFO("Successfully set the device code!");
        }
        else
        {
            LOG_ERROR("Could not set the device code!");
        }
    }
    else
    {
        LOG_ERROR("Could not send set device code command!");
    }
    return retCode;
}

bool Zumo32U4::flashPages(uint8_t* dataChunk, const uint16_t chunkSize)
{
    bool retCode = false;

    /* Temporary buffer for response data */
    const uint8_t READ_BUFFER_SIZE_BYTES = 64;
    uint8_t readBuffer[READ_BUFFER_SIZE_BYTES];
    uint16_t readBytes = 64;

    /* Temporary buffer for setting the current block base memory address */
    const uint16_t ADDR_BUFFER_SIZE_BYTES = 2;
    uint8_t addrBuffer[ADDR_BUFFER_SIZE_BYTES];

    uint8_t* pWriteBuffer = nullptr;
    uint16_t arrSize = 0;
    const uint8_t FILLER_VALUE = 0xFF;

    uint16_t numberOfPages = 0;
    uint16_t fillBytes = 0;

    /* Check if one block is not full. Only write fully packaged pages. Perform byte stuffing with '0xFF' as filler value */
    if (0 != (chunkSize % PAGE_SIZE_BYTES))
    {
        fillBytes = PAGE_SIZE_BYTES - (chunkSize % PAGE_SIZE_BYTES);
        for (uint32_t idx = chunkSize; idx < chunkSize + fillBytes; idx++)
        {
            dataChunk[idx] = FILLER_VALUE;
        }
        LOG_INFO(String("Added ") + fillBytes + String(" 0xFF stuffing bytes to only write full pages"));
    }
    arrSize = chunkSize + fillBytes;
    LOG_INFO(String("Total firmware(chunk) size: ") + arrSize + String(" bytes"));

    /* Determine how many pages have to be flashed */
    numberOfPages = arrSize / PAGE_SIZE_BYTES;
    LOG_INFO(String("Writing ") + numberOfPages + String(" pages with ") + PAGE_SIZE_BYTES + String(" bytes each"));

    if (FirmwareChecker::MAX_ZUMO_FW_BLOB_SIZE_BYTE >= ((m_currWriteMemAddr * 2) + arrSize))
    {
        for (uint16_t pageIdx = 0; pageIdx < numberOfPages; pageIdx++)
        {
            /* Write lower and higher byte of current address into address buffer */
            addrBuffer[0] = (m_currWriteMemAddr >> 8) & 0xFF;
            addrBuffer[1] = (m_currWriteMemAddr) & 0xFF;

            /* Get pointer to next page base address */
            pWriteBuffer = &dataChunk[pageIdx * PAGE_SIZE_BYTES];

            /* Set base memory address of current page for writing */
            if (true == sendCommand(Zumo32U4Specification::SET_MEMORY_ADDR, addrBuffer, &ADDR_BUFFER_SIZE_BYTES, readBuffer, &readBytes))
            {
                retCode = (0 == memcmp(readBuffer, Zumo32U4Specification::RET_OK.data, Zumo32U4Specification::RET_OK.dataSize));
                if (true == retCode)
                {
                    /* Write the memory page */
                    if (true == sendCommand(Zumo32U4Specification::WRITE_MEMORY_PAGE, pWriteBuffer, &PAGE_SIZE_BYTES, readBuffer, &readBytes))
                    {
                        retCode = (0 == memcmp(readBuffer, Zumo32U4Specification::RET_OK.data, Zumo32U4Specification::RET_OK.dataSize));
                        if (true == retCode)
                        {
                            LOG_INFO(String("Successfully flashed page with ") + PAGE_SIZE_BYTES + " bytes into Zumo robot memory!");
                        }
                        else
                        {
                            LOG_ERROR("Could not write data into Zumo robot memory!");
                            break;
                        }
                    }
                    else
                    {
                        LOG_ERROR("Could not write to memory!");
                    }
                }
                else
                {
                    LOG_ERROR("Aborted writing to memory because memory address could not be set!");
                    break;
                }
            }
            else
            {
                LOG_ERROR("Could not send set memory address for writing command!");
                break;
            }

            /* Each address addresses one WORD with 2(!) bytes, this is why one page consists of 64 addresses but 128 bytes memory */
            m_currWriteMemAddr += (PAGE_SIZE_BYTES / 2);
        }
    }
    else
    {
        LOG_ERROR("Could not write to memory. Either memory is full, nullptr, too big or empty array has been passed");
    }
    return retCode;
}

bool Zumo32U4::readMemoryPage(uint8_t* dataChunk, uint16_t& chunkSize)
{
    bool retCode = false;

    /* Temporary buffer for response data */
    const uint8_t READ_BUFFER_SIZE_BYTES = 64;
    uint8_t readBuffer[READ_BUFFER_SIZE_BYTES];
    uint16_t readBytes = 64;

    /* Temporary buffer for setting the current block base memory address */
    const uint16_t ADDR_BUFFER_SIZE_BYTES = 2;
    uint8_t addrBuffer[ADDR_BUFFER_SIZE_BYTES];

    /* Write lower and higher byte of current base address into address buffer */
    addrBuffer[0] = (m_currReadMemAddr >> 8) & 0xFF;
    addrBuffer[1] = (m_currReadMemAddr) & 0xFF;

    if (FirmwareChecker::MAX_ZUMO_FW_BLOB_SIZE_BYTE >= ((m_currWriteMemAddr * 2) + PAGE_SIZE_BYTES))
    {
        /* Set base memory address of current page for writing */
        if (true == sendCommand(Zumo32U4Specification::SET_MEMORY_ADDR, addrBuffer, &ADDR_BUFFER_SIZE_BYTES, readBuffer, &readBytes))
        {
            retCode = (0 == memcmp(readBuffer, Zumo32U4Specification::RET_OK.data, Zumo32U4Specification::RET_OK.dataSize));
            if (true == retCode)
            {
                /* Read the memory page */
                if (true == sendCommand(Zumo32U4Specification::READ_MEMORY_PAGE, dataChunk, &chunkSize))
                {
                    retCode = true;
                    LOG_INFO(String("Successfully read ") + chunkSize + " bytes from Zumo robot memory");
                }
                else
                {
                    LOG_ERROR("Could not read from memory!");
                }
            }
            else
            {
                LOG_ERROR("Aborted reading from memory because memory address could not be set!");
            }

            /* Each address addresses one WORD with 2(!) bytes, this is why one page consists of 64 addresses but 128 bytes memory */
            m_currReadMemAddr += (PAGE_SIZE_BYTES / 2);
        }
        else
        {
            LOG_ERROR("Could not send set memory address for writing command!");
        }
    }
    else
    {
        LOG_ERROR("Already read entire data! Call reset() if all pages should be read from beginning again");
    }
    return retCode;
}

bool Zumo32U4::readSerialBuffer(uint8_t* dataBuffer, uint32_t& chunkSize)
{
    bool retCode = false;
    uint8_t resCode = 1;

    uint16_t readBytes = 0;
    uint32_t totalReadBytes = 0;
    uint8_t* pReadBuffer = nullptr;

    unsigned long startInitTime = 0L;

    if (true == m_stateMachine.setState(READING_SERIAL))
    {
        /* Await ACM initialization */
        startInitTime = millis();
        while ((false == m_acm.isReady()) && (USB_TIMEOUT_MS >= (millis() - startInitTime)))
        {
            LOG_WARN("Trying to initialize the ACM instance!");
            delay(USB_RETRY_DELAY_MS);
            handleUSBDriver();
        }

        if (true == m_acm.isReady())
        {
            /* Wait for buffer to fill. Wait here until at least one byte arrives in serial buffer */
            do
            {
                readBytes = PAGE_SIZE_BYTES;
                pReadBuffer = &dataBuffer[totalReadBytes];

                resCode = m_acm.RcvData(&readBytes, pReadBuffer);
                if (resCode && resCode != hrNAK)
                {
                    retCode = false;
                    ErrorMessage<uint8_t>(PSTR("Ret"), resCode);
                    LOG_ERROR("Could not receive data from Zumo robot!");
                }
                totalReadBytes += readBytes;
            } while (readBytes == 0);

            /* Read all data in serial buffer until buffer is empty */
            do
            {
                readBytes = PAGE_SIZE_BYTES;
                pReadBuffer = &dataBuffer[totalReadBytes];

                resCode = m_acm.RcvData(&readBytes, pReadBuffer);
                if (resCode && resCode != hrNAK)
                {
                    retCode = false;
                    ErrorMessage<uint8_t>(PSTR("Ret"), resCode);
                    LOG_ERROR("Could not receive data from Zumo robot!");
                    break;
                }
                totalReadBytes += readBytes;
            } while (readBytes != 0);

            chunkSize = totalReadBytes;
            retCode = true;
            LOG_DEBUG(String("Successfully read entire serial buffer. Read ") + totalReadBytes + String(" bytes"));
        }
        else
        {
            LOG_ERROR("Aborting because ACM could not be initialized!");
        }
    }
    else
    {
        LOG_ERROR("Could not read serial port of Zumo robot because driver is in invalid state!");
    }
    return retCode;
}

bool Zumo32U4::writeSerialBuffer(uint8_t* dataBuffer, const uint16_t chunkSize)
{
    uint8_t resCode = 1;
    unsigned long startInitTime = 0L;

    if (true == m_stateMachine.setState(WRITING_SERIAL))
    {
        /* Await ACM initialization */
        startInitTime = millis();
        while ((false == m_acm.isReady()) && (USB_TIMEOUT_MS >= (millis() - startInitTime)))
        {
            LOG_WARN("Trying to initialize the ACM instance!");
            delay(USB_RETRY_DELAY_MS);
            handleUSBDriver();
        }

        if (true == m_acm.isReady())
        {
            /* Send the entire buffer data to serial output.
            USB driver automatically splits buffer into
            multiple data packets
            */
            resCode = m_acm.SndData(chunkSize, const_cast<uint8_t*>(dataBuffer));
            if (0 == resCode)
            {
                LOG_DEBUG(String("Successfully wrote buffer with ") + chunkSize + String(" bytes to serial output!"));
            }
            else
            {
                ErrorMessage<uint8_t>(PSTR("SndData"), resCode);
                LOG_ERROR("Could not write buffer to serial output. Aborting now");
            }

            /* Wait until next serial send */
            delay(NEXT_SERIAL_SEND_DELAY_MS);
        }
        else
        {
            LOG_ERROR("Aborting because ACM could not be initialized!");
        }
    }
    else
    {
        LOG_ERROR("Could not write to serial port of Zumo robot because driver is in invalid state!");
    }
    return (0 == resCode);
}

bool Zumo32U4::beginWriteFirmware(uint16_t firmwareSize, const String& expectedHash)
{
    bool retCode = false;
    bool validPlatform = false;
    bool validSignature = false;

    if ((0 < firmwareSize) && (false == expectedHash.isEmpty()))
    {
        if (true == m_stateMachine.setState(FLASHING))
        {
            /* Clean up driver and data */
            reset();

            if (true == resetUSBDriver())
            {
                /* Switch/reboot into bootloader mode */
                enterBootloaderMode();

                m_expectedFirmwareSize = firmwareSize;
                m_expectedHashValue = expectedHash;

                validPlatform = checkPlatform();

                if (true == configurePlatform())
                {
                    if (true == enterProgrammerMode())
                    {
                        validSignature = verifySignature();
                        verifyFuses();

                        retCode = (validPlatform && validSignature);
                        if (true == retCode)
                        {
                            LOG_INFO("All checks for writing Zumo firmware have been passed!");
                        }
                        else
                        {
                            LOG_ERROR("At least one Zumo platform check failed. Could not start firmware flashing!");
                        }
                    }
                    else
                    {
                        LOG_ERROR("Could not start firmware flashing because Zumo robot could not be switched into bootloader mode!");
                    }
                }
                else
                {
                    LOG_ERROR("Could not start firmware flashing because Zumo robot could not be configured!");
                }
            }
            else
            {
                LOG_ERROR("Could not reset USB driver!");
            }
        }
        else
        {
            LOG_ERROR("Could not start firmware flashing because driver is in invalid state!");
        }
    }
    else
    {
        LOG_ERROR("Either expected firmware size is 0 byte or passed hash value is empty!");
    }
    return retCode;
}

bool Zumo32U4::writeFirmwareChunk(uint8_t* dataChunk, const uint16_t chunkSize)
{
    bool retCode = false;
    bool isLastChunk = (m_expectedFirmwareSize == (m_writtenFirmwareBytes + chunkSize));

    if (true == m_stateMachine.setState(FLASHING))
    {
        if ((nullptr != dataChunk) && (0 < chunkSize))
        {
            if (FirmwareChecker::MAX_ZUMO_FW_BLOB_SIZE_BYTE >= (m_writtenFirmwareBytes + chunkSize))
            {
                /* Check if the data chunk, which is not the last page, fills the page buffer(s) entirely,
                if not, this would cause byte stuffing in the middle of the firmware payload, which
                is not wanted.
                */
                if ((false == isLastChunk) && (0 != chunkSize % PAGE_SIZE_BYTES))
                {
                    LOG_ERROR("The current data chunk is too small! It should fully fill one or more pages with PAGE_SIZE_BYTES!. Did not write the page!");
                }
                else
                {
                    retCode = flashPages(dataChunk, chunkSize);
                    m_writtenFirmwareBytes += chunkSize;
                    LOG_DEBUG("Successfully flashed passed data chunk into Zumo robot memory");
                }
            }
            else
            {
                LOG_ERROR("Passed data chunk is too big to be flashed onto the Zumo robot!");
            }
        }
        else
        {
            LOG_ERROR("Passed buffer pointer is nullptr or size of array is 0 bytes!");
        }
    }
    else
    {
        LOG_ERROR("Could not flash Zumo robot because driver is in invalid state!");
    }
    return retCode;
}

bool Zumo32U4::verifyWrittenFirmware()
{
    bool retCode = true;
    uint8_t pageBuffer[PAGE_SIZE_BYTES];
    uint16_t readBytes = 0;

    String actualHashValue = "";

    uint32_t expectedPages = m_expectedFirmwareSize / PAGE_SIZE_BYTES;
    uint32_t remainingBytes = m_expectedFirmwareSize % PAGE_SIZE_BYTES;

    m_crypto.resetSHA256Hash();

    /* Hash all fully packed pages */
    for (uint32_t pageNo = 0; pageNo < expectedPages; pageNo++)
    {
        if (true == readMemoryPage(pageBuffer, readBytes))
        {
            if (false == m_crypto.updateSHA256Hash(pageBuffer, readBytes))
            {
                retCode = false;
                LOG_ERROR("Could not hash firmware data. Aborting now");
                break;
            }
        }
        else
        {
            retCode = false;
            LOG_ERROR("Could not read the memory page. Aborting now");
            break;
        }
    }

    /* Hash the last page which is (not) fully packed */
    if ((true == retCode) && (true == readMemoryPage(pageBuffer, readBytes)))
    {
        if (remainingBytes <= readBytes)
        {
            if (true == m_crypto.updateSHA256Hash(pageBuffer, remainingBytes))
            {
                if (true == m_crypto.getSHA256String(actualHashValue))
                {
                    retCode = (actualHashValue == m_expectedHashValue);
                }
                else
                {
                    retCode = false;
                }
            }
            else
            {
                retCode = false;
                LOG_ERROR("Could not hash firmware data. Aborting now");
            }
        }
        else
        {
            retCode = false;
            LOG_ERROR("Could not read the memory page. Aborting now");
        }
    }
    else
    {
        retCode = false;
        LOG_ERROR("Could not read the memory page. Aborting now");
    }
    return retCode;
}

bool Zumo32U4::finalizeWriteFirmware()
{
    bool retCode = false;

    if (true == m_stateMachine.setState(CLOSED))
    {
        retCode = verifyWrittenFirmware();
        verifyFuses();

        if (true == exitProgrammerMode())
        {
            if (true == exitBootloaderMode())
            {
                /* Restart the Zumo robot */
                restart();
            }
            else
            {
                LOG_ERROR("Could not exit bootloader mode!");
            }
        }
        else
        {
            LOG_ERROR("Could not exit programmer mode!");
        }
    }
    else
    {
        LOG_ERROR("Could not finish flashing of Zumo robot because driver is in invalid state!");
    }
    return retCode;
}

void Zumo32U4::reset()
{
    /* Rest the crypto lib and the calculated hash */
    m_crypto.resetSHA256Hash();

    m_currWriteMemAddr = 0;
    m_currReadMemAddr = 0;

    m_writtenFirmwareBytes = 0;
    m_expectedFirmwareSize = 0;
    m_expectedHashValue = "";

    LOG_DEBUG("Successfully cleared all Zumo32U4 driver data");
}

bool Zumo32U4::resetUSBDriver()
{
    bool retCode = false;

    /* Restart the USB Host Shield µC to begin from a clean and defined state */
    LOG_DEBUG("Resetting USB Host Shield now!");
    m_usb.reset();

    /* Unregister CDC device instance */
    LOG_DEBUG("De-Registering ACM/CDC device instance now!");
    m_acm.Release();

    LOG_DEBUG("Fully re-set the USB HOST Shield and cleared ACM!");

    if (0 == m_usb.Init())
    {
        LOG_DEBUG("USB driver has been successfully initialized!");
        retCode = true;
    }
    else
    {
        LOG_ERROR("Could not initialize USB driver!");
    }
    return retCode;
}
