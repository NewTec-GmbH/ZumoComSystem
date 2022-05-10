"""

BSD 3-Clause License

Copyright (c) 2021-2022, Gabryel Reyes <gabryelrdiaz@gmail.com>
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

"""

Import("env")

from os.path import exists, getsize
import subprocess

def buildSignedFirmware() :
    ID_SIZE_BYTE = 16
    TARGET_SIZE_BYTE = 16
    VERSION_SIZE_BYTE = 1
    HASH_ALG_SIZE_BYTE = 16
    SIGN_ALG_SIZE_BYTE = 32
    SIGNATURE_SIZE_BYTE = 256
    HEADER_SIZE_BYTE = ID_SIZE_BYTE + TARGET_SIZE_BYTE + VERSION_SIZE_BYTE + HASH_ALG_SIZE_BYTE + SIGN_ALG_SIZE_BYTE + SIGNATURE_SIZE_BYTE

    ID = "CPSFW"
    TARGET = "ZUMO"
    VERSION = "\1"
    HASH_ALG = "SHA256"
    SIGN_ALG = "RSA2048PKCS#1v15"

    ID_ARR = list(ID) + (['\0'] * (ID_SIZE_BYTE - len(ID)))
    TARGET_ARR = list(TARGET) + (['\0'] * (TARGET_SIZE_BYTE - len(TARGET)))
    VERSION_ARR = list(VERSION)
    HASH_ALG_ARR = list(HASH_ALG) + (['\0'] * (HASH_ALG_SIZE_BYTE - len(HASH_ALG)))
    SIGN_ALG_ARR = list(SIGN_ALG) + (['\0'] * (SIGN_ALG_SIZE_BYTE - len(SIGN_ALG)))

    HEADER_ARR = ID_ARR + TARGET_ARR + VERSION_ARR + HASH_ALG_ARR + SIGN_ALG_ARR

    if(HEADER_SIZE_BYTE != (len(HEADER_ARR) + SIGNATURE_SIZE_BYTE)) :
        raise RuntimeError("Error at Building of Header")

    outputFile = open("./outputFirmware.cpsfw", "w")

    for byte in HEADER_ARR :
        outputFile.write("%c" % byte)

    outputFile.close()

    outputFile = open("./outputFirmware.cpsfw", "ab")
    signatureFile = open("./signature.sign", "rb")
    firmwareFile = open("./firmware.bin", "rb")

    if(getsize("./signature.sign") != SIGNATURE_SIZE_BYTE) :
        raise RuntimeError ("Error in length of Signature File")
    
    outputFile.write(signatureFile.read())
    outputFile.write(firmwareFile.read())

    outputFile.close()
    signatureFile.close()
    firmwareFile.close()

def sign_firmware (source, target, env) :

    # Check for Private Key in top directory
    if not exists("./privateKey.pem"):
        print("Private Key is missing!")
        Exit(1)
    
    # Convert .hex into .bin using objcopy.
    if 0 != env.Execute("objcopy -I ihex \"${BUILD_DIR}\\${PROGNAME}.hex\" -O binary ./firmware.bin") :
        print("objcopy failed!")
        Exit(1) # Exit the building process

    try:
        # Sign using OpenSSL included with Git for Windows. Assumed that user is working in Windows and has Git installed in default path (Program Files)
        subprocess.run("openssl.exe dgst -sha256 -sign privateKey.pem -out signature.sign firmware.bin", check=True, timeout=5, capture_output=True, shell=True)
        
        # Build the Signed Firmware file
        buildSignedFirmware()

        # Clean temporary files
        subprocess.run("rm firmware.bin signature.sign", check=True, timeout=5, capture_output=True, shell=True)

    except subprocess.CalledProcessError :
        # Print the error
        print(f"\033[93mIs OpenSSL/Git for Windows installed? Please check installation and add OpenSSL to Path\033[0m")
        # Exit the building process
        Exit(1)

    except subprocess.TimeoutExpired :
        # Print the error
        print(f"\033[93mSigning Process timed-out\033[0m")
        # Exit the building process
        Exit(1)

    except Exception as err:
        # Other error
        print(f"\033[93m{err}\033[0m")
        # Exit the building process
        Exit(1)
    else:
        print("Successfully signed the firmware!")

# Always build .hex file. Assume it is always out-of-date
env.AlwaysBuild("${BUILD_DIR}\\${PROGNAME}.hex")

# Register the callback to the creation of the .hex file
env.AddPostAction("${BUILD_DIR}\\${PROGNAME}.hex", sign_firmware)
