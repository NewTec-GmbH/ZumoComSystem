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
 * @file Zumo32U4Specification.h
 * @author Luis Moser
 * @brief Zumo32U4Specification header
 * @date 08/23/2021
 *
 * @{
 */

#ifndef __ZUMO32U4Specification_H__
#define __ZUMO32U4Specification_H__

#include <Arduino.h>

 /** Simple struct for specifying Zumo commands */
template <int size>
struct ZumoCommand
{
    /** The binary buffer for the command data */
    uint8_t commandData[size];

    /** Size of command data buffer in bytes */
    uint8_t commandSize;
};

/** Simple struct for specifying Zumo data */
template <int size>
struct ZumoData
{
    /** The binary buffer for the response Zumo data */
    uint8_t data[size];

    /** Size of the response data in bytes */
    uint8_t dataSize;
};

/** Namespace for specifying all used Zumo32U4 commands, return codes and expected return values */
namespace Zumo32U4Specification
{
    /** Command for reading the software ID */
    static const struct ZumoCommand<1> READ_SW_ID = {{0x53}, 1};

    /** Command for reading the software version */
    static const struct ZumoCommand<1> READ_SW_VERSION = {{0x56}, 1};

    /** Command for reading the hardware version */
    static const struct ZumoCommand<1> READ_HW_VERSION = {{0x76}, 1};

    /** Command for getting the programmer type */
    static const struct ZumoCommand<1> READ_PROGRAMMER_TYPE = {{0x70}, 1};

    /** Command for getting the supported bootlaoder device codes */
    static const struct ZumoCommand<1> READ_SUPPORTED_DEVICE_CODE = {{0x74}, 1};

    /** Command for reading the signature */
    static const struct ZumoCommand<1> READ_SIGNATURE = {{0x73}, 1};

    /** Command for reading the low byte AVR fuse */
    static const struct ZumoCommand<1> READ_LSB_FUSE = {{0x46}, 1};

    /** Command for reading the high byte AVR fuse */
    static const struct ZumoCommand<1> READ_MSB_FUSE = {{0x4E}, 1};

    /** Command for reading the extended byte AVR fuse */
    static const struct ZumoCommand<1> READ_EXTENDED_FUSE = {{0x51}, 1};

    /** Command for checking if the bootloader supports block/page flashing */
    static const struct ZumoCommand<1> CHECK_BLOCK_FLASH_SUPPORT = {{0x62}, 1};

    /** Command for setting the current R/W flash memory/page address */
    static const struct ZumoCommand<1> SET_MEMORY_ADDR = {{0x41}, 1};

    /** Command for checking if the bootloader supports automatically incrementing byte addresses when flashing a page */
    static const struct ZumoCommand<1> CHECK_AUTO_MEM_ADDR_INC_SUPPORT = {{0x61}, 1};

    /** Command for setting the device type for flashing */
    static const struct ZumoCommand<1> SET_DEVICE_TYPE = {{0x54}, 1};

    /** Command for switching the bootloader into the programmer mode */
    static const struct ZumoCommand<1> ENTER_PROGRAMMING_MODE = {{0x50}, 1};

    /** Command for leaving the bootloader from the programmer mode */
    static const struct ZumoCommand<1> EXIT_PROGRAMMING_MODE = {{0x4C}, 1};

    /** Command for exiting the bootloader */
    static const struct ZumoCommand<1> EXIT_BOOTLOADER_MODE = {{0x45}, 1};

    /** Command for writing a memory page with 128 bytes into the flash/program memory */
    static const struct ZumoCommand<4> WRITE_MEMORY_PAGE = {{0x42, 0x00, 0x80, 0x46}, 4};

    /** Command for reading a memory page with 128 bytes from the flash/program memory */
    static const struct ZumoCommand<4> READ_MEMORY_PAGE = {{0x67, 0x00, 0x80, 0x46}, 4};

    /** Carriage return for successful return code */
    static const struct ZumoData<1> RET_OK = {{0x0D}, 1};

    /** The expected bootloader ID string */
    static const struct ZumoData<7> EXPECTED_SOFTWARE_ID = {{'C', 'A', 'T', 'E', 'R', 'I', 'N'}, 7};

    /** The expected bootloader version */
    static const struct ZumoData<2> EXPECTED_SW_VERSION = {{0x31, 0x30}, 2};

    /** The expected hardware version */
    static const struct ZumoData<1> EXPECTED_HW_VERSION = {{0x3F}, 1};

    /** The expected programmer type */
    static const struct ZumoData<1> EXPECTED_PROGRAMMER_TYPE = {{0x53}, 1};

    /** The expected supported device code */
    static const struct ZumoData<1> EXPECTED_DEVICE_CODE = {{0x44}, 1};

    /** The expected result when checking if bootloader supports auto incrementing page byte addresses */
    static const struct ZumoData<1> EXPECTED_SUPPORTS_AUTO_MEM_ADDR_INC = {{0x59}, 1};

    /** The expected block size result in bytes when checking if bootloader supports page/block flashing */
    static const struct ZumoData<1> EXPECTED_BLOCK_BUFFER_SIZE = {{0x59}, 1};

    /** The expected AVR low byte fuse value */
    static const struct ZumoData<1> EXPECTED_LSB_FUSE_VALUE = {{0xFF}, 1};

    /** The expected AVR high byte fuse value */
    static const struct ZumoData<1> EXPECTED_MSB_FUSE_VALUE = {{0xD0}, 1};

    /** The expected AVR extended byte fuse value */
    static const struct ZumoData<1> EXPECTED_EXTENDED_FUSE_VALUE = {{0xC8}, 1};

    /** The expected signature value */
    static const struct ZumoData<3> EXPECTED_SIGNATURE = {{0x87, 0x95, 0x1E}, 3};
};
#endif /** __ZUMO32U4Specification_H__ */
