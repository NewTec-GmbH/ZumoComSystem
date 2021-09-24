<!--
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
-->

<!--
 * @file Upload.vue
 * @author Luis Moser
 * @brief Upload class
 * @date 09/22/2021
 *
 * @{
-->

<template>
  <div class="upload">
    <TextDialog
      :type="type"
      :showTextDialog="infoDialogVisible"
      :text="infoText"
      @declined="infoDialogVisible = false"
      @accepted="fnPtr"
    />

    <FirmwareCard :update="update" />

    <Dropdown
      class="dropdown"
      v-model="uploadOption"
      :options="options"
      optionLabel="name"
      placeholder="Select an upload option"
    />

    <FileUpload
      v-if="uploadOption.key === 'cpsfw'"
      name="demo[]"
      accept=".cpsfw"
      :customUpload="true"
      :fileLimit="1"
      @uploader="uploadFirmware"
    >
      <template #empty>
        <p>Drag and drop .cpsfw file here to upload it!</p>
      </template>
    </FileUpload>

    <FileUpload
      v-else-if="uploadOption.key === 'bin'"
      name="demo[]"
      accept=".bin,.pem"
      :customUpload="true"
      :fileLimit="2"
      @uploader="uploadFirmware"
    >
      <template #empty>
        <p>
          Drag and drop .bin and .pem files here to sign the firmware and upload
          the generated firmware!
        </p>
      </template>
    </FileUpload>

    <ProgressBar
      class="progressbar"
      v-if="uploadActive === true"
      :value="uploadProgressPercent"
    />
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import FirmwareCard from "@/components/FirmwareCard.vue";
import TextDialog from "@/components/TextDialog.vue";
import RequestResponseHandler from "@/api/RequestResponseHandler";
import Log from "@/utility/Log";
import { ApiResponse } from "@/models/ApiResponse";
import { ApiRequest } from "@/models/ApiRequest";
import { ResponseCode } from "@/models/ResponseCode";
import { Firmware } from "@/models/Firmware";
import { FirmwareHeader } from "@/models/FirmwareHeader";
import { FirmwareSigner } from "@/utility/FirmwareSigner";
import FileSaver from "file-saver";

export default defineComponent({
  name: "Upload",
  components: {
    FirmwareCard,
    TextDialog,
  },

  data() {
    return {
      options: [
        {
          name: "Upload signed firmware (.cpsfw)",
          key: "cpsfw",
        },
        {
          name: "Upload unsigned firmware (.bin) and RSA2048 signing key (.pem)",
          key: "bin",
        },
      ],

      uploadOption: {
        name: "Upload unsigned firmware (.bin) and RSA2048 signing key (.pem)",
        key: "bin",
      },

      uploadProgressPercent: 0,
      uploadActive: false,

      update: false,

      type: "no-yes",
      infoDialogVisible: false,
      infoText: "",
      fnPtr: () => {
        console.log("empty");
      },
    };
  },

  methods: {
    async uploadPackets(firmwareBinary: Uint8Array): Promise<boolean> {
      this.uploadActive = true;
      this.uploadProgressPercent = 0;

      const uploadBlockSizeBytes = 2048;
      const uploadChunks = Math.floor(
        firmwareBinary.length / uploadBlockSizeBytes
      );
      const remainingBytes = firmwareBinary.length % uploadBlockSizeBytes;

      let byteOffset = 0;
      let chunkBuffer = new Uint8Array(uploadBlockSizeBytes);
      let remainBuffer = new Uint8Array(remainingBytes);

      let uploadRequest = new ApiRequest();

      let retCode = true;

      /* Set the target system */
      if ("ComPlatform" === this.$store.getters.selectedDevice.name) {
        uploadRequest.commandId = "uploadcom";
      } else if ("Zumo32U4 Robot" === this.$store.getters.selectedDevice.name) {
        uploadRequest.commandId = "uploadzumo";
      }

      /* Set the payload size */
      uploadRequest.jsonPayload = JSON.stringify({
        fileSizeBytes: firmwareBinary.length,
      });

      /* Switch API into BINARY mode */
      let response = await RequestResponseHandler.getInstance().makeRequest(
        uploadRequest,
        this
      );

      /* Send the chunks */
      if (ResponseCode.SUCCESS === response.statusCode) {
        Log.debug("Successfully switched API into BINARY mode!");

        for (let chunkNo = 0; chunkNo < uploadChunks; chunkNo++) {
          byteOffset = chunkNo * uploadBlockSizeBytes;

          /* Assemble current package */
          for (let byteIdx = 0; byteIdx < uploadBlockSizeBytes; byteIdx++) {
            chunkBuffer[byteIdx] = firmwareBinary[byteOffset + byteIdx];
          }

          /* Send the current chunk/package */
          response = await RequestResponseHandler.getInstance().sendBinary(
            chunkBuffer,
            this
          );

          /* Abort if any upload failed */
          if (ResponseCode.SUCCESS != response.statusCode) {
            Log.error("Could not upload data chunk! Aborting upload now!");
            retCode = false;
            break;
          } else {
            this.uploadProgressPercent = Math.round(
              (chunkNo / uploadChunks) * 100
            );
          }
        }

        if (true === retCode) {
          byteOffset = uploadChunks * uploadBlockSizeBytes;

          /* Assemble last package */
          for (let byteIdx = 0; byteIdx < remainingBytes; byteIdx++) {
            remainBuffer[byteIdx] = firmwareBinary[byteOffset + byteIdx];
          }

          /* Send the remaining bytes */
          response = await RequestResponseHandler.getInstance().sendBinary(
            remainBuffer,
            this
          );

          if (ResponseCode.SUCCESS != response.statusCode) {
            Log.error("Could not upload last data chunk!");
            retCode = false;
          } else {
            this.uploadProgressPercent = 100;
          }
        } else {
          Log.error(
            "Not sending remaining bytes because previous packet could not be sent!"
          );
        }
      } else {
        Log.error("Could not switch API into binary mode!");
      }

      this.uploadActive = false;

      return new Promise<boolean>((resolve) => {
        resolve(retCode);
      });
    },

    upload(firmwareBinary: Uint8Array) {
      /* Upload the CPSFW file */
      this.uploadPackets(firmwareBinary).then((result: boolean) => {
        /* Force the FirmwareCard to update itself */
        this.update = !this.update;

        if (true === result) {
          this.$toast.add({
            severity: "success",
            summary: "Upload Success",
            detail: "Successfully uploaded the firmware!",
            life: 5000,
          });
        } else {
          this.$toast.add({
            severity: "error",
            summary: "Upload Error",
            detail: "Could not upload the firmware!",
            life: 5000,
          });
        }

        /* Ask if firmware should be flashed now */
        this.infoDialogVisible = true;
        this.infoText = "Do you want to flash the uploaded firmware now?";
        this.fnPtr = () => {
          this.infoDialogVisible = false;

          /* Go to flash page */
          this.$router.push({
            name: "Flash",
            query: { autoFlash: "true" },
          });
        };
      });
    },

    save(firmwareBinary: Uint8Array, firmwareHeader: FirmwareHeader) {
      /* Ask if CPSFW file should be saved */
      this.infoDialogVisible = true;
      this.infoText = "Do you want to download the generated CPSFW file?";
      this.fnPtr = () => {
        this.infoDialogVisible = false;

        FileSaver.saveAs(
          new Blob([firmwareBinary.buffer]),
          firmwareHeader.getTarget() + "_firmware_signed.cpsfw"
        );
      };
    },

    async uploadFirmware(data: any) {
      let files: Array<File> = data.files;
      let fileReader = new FileReader();

      let binaryRead = new Uint8Array();
      let firmwareHeader = new FirmwareHeader();
      let firmware = new Firmware();
      let firmwareBinary: Uint8Array;

      let binFiles = files.filter(function (file: File) {
        return file.name.endsWith(".bin");
      });

      let sigFiles = files.filter(function (file: File) {
        return file.name.endsWith(".pem");
      });

      let cpsfwFiles = files.filter(function (file: File) {
        return file.name.endsWith(".cpsfw");
      });

      if ("bin" === this.uploadOption.key) {
        /* Make sure user submitted exactly one .pem and one .bin file */
        if (1 === binFiles.length && 1 === sigFiles.length) {
          if ("ComPlatform" === this.$store.getters.selectedDevice.name) {
            firmwareHeader.setTarget("COM");
          } else if (
            "Zumo32U4 Robot" === this.$store.getters.selectedDevice.name
          ) {
            firmwareHeader.setTarget("ZUMO");
          }

          /* Read the unsigned firmware binary */
          fileReader.readAsArrayBuffer(binFiles[0]);

          /* Called when firmware has been read */
          fileReader.onload = (event: any) => {
            /* Read the firmware */
            binaryRead = new Uint8Array(fileReader.result as ArrayBuffer);
            firmware.setFirmware(binaryRead);

            /* Read the private RSA2048 key string when firmware has been read */
            fileReader.readAsText(sigFiles[0]);

            /* Called when RSA2048 key has been read */
            fileReader.onload = (event: any) => {
              /* Sign the firmware payload */
              const binSig = FirmwareSigner.sign(
                fileReader.result as string,
                binaryRead
              );
              firmwareHeader.setSignature(binSig);
              firmware.setHeader(firmwareHeader);
              firmwareBinary = firmware.serialize();

              /* Upload the CPSFW file */
              this.upload(firmwareBinary);

              /* Ask if CPSFW file should be saved */
              this.save(firmwareBinary, firmwareHeader);
            };
          };
        } else {
          this.$toast.add({
            severity: "error",
            summary: "Selection Error",
            detail: "Please select exactly one *.bin and one *.pem file!",
            life: 5000,
          });
        }
      } else if ("cpsfw" === this.uploadOption.key) {
        if (1 === cpsfwFiles.length) {
          /* Read the signed CPSFW binary */
          fileReader.readAsArrayBuffer(cpsfwFiles[0]);

          /* Called when firmware has been read */
          fileReader.onload = (event: any) => {
            /* Read the CPSFW file */
            binaryRead = new Uint8Array(fileReader.result as ArrayBuffer);

            firmware = new Firmware();
            if (true === firmware.deserialize(binaryRead)) {
              // TODO: Show deserialization result
              console.log(firmware);

              /* Upload the CPSFW file */
              this.upload(binaryRead);
            } else {
              this.$toast.add({
                severity: "error",
                summary: "Deserialization Error",
                detail: "Could not deserialize the provided CPSFW file!",
                life: 5000,
              });
            }
          };
        } else {
          this.$toast.add({
            severity: "error",
            summary: "Selection Error",
            detail: "Please select exactly one *.cpsfw file!",
            life: 5000,
          });
        }
      }
    },

    flashFirmware() {
      this.infoDialogVisible = false;

      /* Go to flash page */
      this.$router.push({ name: "Flash", query: { autoFlash: "true" } });
    },
  },
});
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.upload {
  display: flex;
  flex-direction: column;
  align-items: center;

  .firmware-card {
    width: 80%;
    margin-bottom: 20px;
  }

  .dropdown {
    width: 80%;
    margin-bottom: 20px;
  }

  .p-fileupload {
    width: 80%;
    margin-bottom: 20px;
  }

  .progressbar {
    width: 80%;
    margin-bottom: 20px;
  }
}
</style>
