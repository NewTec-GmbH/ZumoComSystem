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

import subprocess
from os.path import exists, getsize

# pylint: disable=undefined-variable
Import("env")  # type: ignore

# pylint: disable=too-many-locals
def build_signed_firmware():
    '''
    Builds the .cpsfw file using the created binary file
    and its signature, including the respective header.
    '''

    id_size_byte = 16
    target_size_byte = 16
    version_size_byte = 1
    hash_alg_size_byte = 16
    sign_alg_size_byte = 32
    signature_size_byte = 256
    header_size_byte = id_size_byte + target_size_byte + \
        version_size_byte + hash_alg_size_byte + \
        sign_alg_size_byte + signature_size_byte

    firmware_id = b'CPSFW'
    firmware_target = b'ZUMO'
    firmware_version = b'\1'
    firmware_hash_alg = b'SHA256'
    firmware_sign_alg = b'RSA2048PKCS#1v15'

    header = b''
    header += firmware_id + (b'\0' * (id_size_byte - len(firmware_id)))
    header += firmware_target + (b'\0' * (target_size_byte - len(firmware_target)))
    header += firmware_version + (b'\0' * (version_size_byte - len(firmware_version)))
    header += firmware_hash_alg + (b'\0' * (hash_alg_size_byte - len(firmware_hash_alg)))
    header += firmware_sign_alg + (b'\0' * (sign_alg_size_byte - len(firmware_sign_alg)))

    if header_size_byte != (len(header) + getsize("./signature.sign")):
        raise RuntimeError("Error on Header Length")

    with open("./outputFirmware.cpsfw", "wb") as output_file :
        output_file.write(header)

        with open("./signature.sign", "rb") as signature_file :
            output_file.write(signature_file.read())

        with open("./firmware.bin", "rb") as firmware_file :
            output_file.write(firmware_file.read())

def sign_firmware(source, target, env):  # pylint: disable=unused-argument
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
        # pylint: disable=undefined-variable
        Exit(1)  # type: ignore

    # Convert .hex into .bin using objcopy.
    if 0 != env.Execute("${OBJCOPY} -I ihex \
            \"${BUILD_DIR}\\${PROGNAME}.hex\" -O binary ./firmware.bin"):
        print("objcopy failed!")
        # pylint: disable=undefined-variable
        Exit(1)  # type: ignore

    try:
        # Sign using OpenSSL included with Git for Windows.
        subprocess.run("openssl.exe dgst -sha256 -sign privateKey.pem \
                -out signature.sign firmware.bin",
                       check=True, timeout=5, capture_output=True, shell=True)

        # Build the Signed Firmware file
        build_signed_firmware()

        # Clean temporary files
        subprocess.run("rm firmware.bin signature.sign", check=True,
                       timeout=5, capture_output=True, shell=True)

    except subprocess.CalledProcessError:
        # Print the error
        # pylint: disable=f-string-without-interpolation
        print(f"\033[93mIs OpenSSL/Git for Windows installed? \
            Please check installation and add OpenSSL to Path\033[0m")

        # Exit the building process
        # pylint: disable=undefined-variable
        Exit(1)  # type: ignore

    except subprocess.TimeoutExpired:
        # Print the error
        # pylint: disable=f-string-without-interpolation
        print(f"\033[93mSigning Process timed-out\033[0m")

        # Exit the building process
        # pylint: disable=undefined-variable
        Exit(1)  # type: ignore

    except Exception as err:  # pylint: disable=broad-except
        # Other error
        print(f"\033[93m{err}\033[0m")

        # Exit the building process
        # pylint: disable=undefined-variable
        Exit(1)  # type: ignore

    else:
        print("Successfully signed the firmware!")


# Always build .hex file. Assume it is always out-of-date
# pylint: disable=undefined-variable
env.AlwaysBuild("${BUILD_DIR}\\${PROGNAME}.hex")  # type: ignore

# Register the callback to the creation of the .hex file
# pylint: disable=undefined-variable
env.AddPostAction("${BUILD_DIR}\\${PROGNAME}.hex", sign_firmware)  # type: ignore
