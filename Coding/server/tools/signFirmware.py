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
    '''
    Builds the .cpsfw file using the created binary file and its signature, including the respective header.
    '''

    ID_SIZE_BYTE = 16
    TARGET_SIZE_BYTE = 16
    VERSION_SIZE_BYTE = 1
    HASH_ALG_SIZE_BYTE = 16
    SIGN_ALG_SIZE_BYTE = 32
    SIGNATURE_SIZE_BYTE = 256
    HEADER_SIZE_BYTE = ID_SIZE_BYTE + TARGET_SIZE_BYTE + VERSION_SIZE_BYTE + HASH_ALG_SIZE_BYTE + SIGN_ALG_SIZE_BYTE + SIGNATURE_SIZE_BYTE

    ID = b'CPSFW'
    TARGET = b'ZUMO'
    VERSION = b'\1'
    HASH_ALG = b'SHA256'
    SIGN_ALG = b'RSA2048PKCS#1v15'

    HEADER = b''
    HEADER += ID + (b'\0' * (ID_SIZE_BYTE - len(ID)))
    HEADER += TARGET + (b'\0' * (TARGET_SIZE_BYTE - len(TARGET)))
    HEADER += VERSION + (b'\0' * (VERSION_SIZE_BYTE - len(VERSION)))
    HEADER += HASH_ALG + (b'\0' * (HASH_ALG_SIZE_BYTE - len(HASH_ALG)))
    HEADER += SIGN_ALG + (b'\0' * (SIGN_ALG_SIZE_BYTE - len(SIGN_ALG)))

    
    if(HEADER_SIZE_BYTE != (len(HEADER) + getsize("./signature.sign"))) :
        raise RuntimeError("Error on Header Length")
    else:
        outputFile = open("./outputFirmware.cpsfw", "wb")
        signatureFile = open("./signature.sign", "rb")
        firmwareFile = open("./firmware.bin", "rb")
        
        outputFile.write(HEADER)
        outputFile.write(signatureFile.read())
        outputFile.write(firmwareFile.read())

        outputFile.close()
        signatureFile.close()
        firmwareFile.close()
    
    return

def sign_firmware (source, target, env) :
    """
    This function is called after the file "firmware.hex" is built.
    - Checks that the private signing key is in the root directory.
    - Converts the .hex file into a .bin file
    - Creates a Signature for the binary file
    - Calls "buildSignedFirmware" to create the final .cpsfw file.
    - Cleans the temporary files.

    Args:
        source (SCons.Node.FS.File): Source file as file object
        target (SCons.Node.Alias.Alias): Alias object
        env (SCons.Script.SConscript.SConsEnvironment): Environment object
    """
    
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
    
    return

# Always build .hex file. Assume it is always out-of-date
env.AlwaysBuild("${BUILD_DIR}\\${PROGNAME}.hex")

# Register the callback to the creation of the .hex file
env.AddPostAction("${BUILD_DIR}\\${PROGNAME}.hex", sign_firmware)
