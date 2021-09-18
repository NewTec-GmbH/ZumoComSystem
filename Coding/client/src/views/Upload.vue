<template>
  <div class="upload">
    <FirmwareCard
      :firmwareAvailable="firmwareAvailable"
      :targetSystem="fwInfo.targetSystem"
      :sizeBytes="fwInfo.sizeBytes"
      :payloadHash="fwInfo.payloadHash"
      :isValid="fwInfo.isValid"
    />

    <Dropdown
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
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import FirmwareCard from "@/components/FirmwareCard.vue";
import RequestResponseHandler from "@/api/RequestResponseHandler";
import Log from "@/utility/Log";
import { ApiResponse } from "@/models/ApiResponse";
import { ApiRequest } from "@/models/ApiRequest";
import { ResponseCode } from "@/models/ResponseCode";
import { FirmwareInfo } from "@/models/FirmwareInfo";
import { Firmware } from "@/models/Firmware";
import { FirmwareHeader } from "@/models/FirmwareHeader";
import { FirmwareSigner } from "@/utility/FirmwareSigner";

export default defineComponent({
  name: "Upload",
  watch: {
    "$store.state.seletedDevice.name": function (newValue, oldValue) {
      let targetSystem = "";
      if ("Zumo32U4 Robot" === newValue) {
        targetSystem = "ZUMO";
      } else if ("ComPlatform" === newValue) {
        targetSystem = "COM";
      }

      /* Prepare the API command */
      let request = new ApiRequest();
      request.commandId = "getfirmwareinfo";
      request.jsonPayload = JSON.stringify({ target: targetSystem });

      /* Send the request */
      RequestResponseHandler.getInstance()
        .makeRequest(request, this)
        .then((response: ApiResponse) => {
          if (response.statusCode == ResponseCode.SUCCESS) {
            /* Set the new FirmwareInfo data */
            this.firmwareAvailable = true;
            this.fwInfo = JSON.parse(response.jsonPayload);
          } else {
            this.firmwareAvailable = false;
          }
        });
    },
  },
  components: {
    FirmwareCard,
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
        name: "Upload signed firmware (.cpsfw)",
        key: "cpsfw",
      },

      firmwareAvailable: false,
      fwInfo: new FirmwareInfo(),
    };
  },

  methods: {
    async uploadPackets(firmware: Firmware): Promise<boolean> {
      return new Promise<boolean>(() => {
        let retCode = true;

        /* Binary which inclues header and payload */
        const firmwareBinary = firmware.serialize();

        const uploadBlockSizeBytes = 2048;
        const uploadChunks = Math.floor(
          firmwareBinary.length / uploadBlockSizeBytes
        );
        const remainingBytes = firmwareBinary.length % uploadBlockSizeBytes;

        let byteOffset = 0;
        let chunkBuffer = new Uint8Array(uploadBlockSizeBytes);
        let remainBuffer = new Uint8Array(remainingBytes);

        let uploadRequest = new ApiRequest();

        /* Set the target system */
        if ("ComPlatform" === this.$store.getters.selectedDevice.name) {
          uploadRequest.commandId = "uploadcom";
        } else if (
          "Zumo32U4 Robot" === this.$store.getters.selectedDevice.name
        ) {
          uploadRequest.commandId = "uploadzumo";
        }

        /* Set the payload size */
        uploadRequest.jsonPayload = JSON.stringify({
          fileSizeBytes: firmwareBinary.length,
        });

        /* Switch API into BINARY mode */
        RequestResponseHandler.getInstance()
          .makeRequest(uploadRequest, this)
          .then((response: ApiResponse) => {
            /* Send the chunks */
            if (ResponseCode.SUCCESS === response.statusCode) {
              for (let chunkNo = 0; chunkNo < uploadChunks; chunkNo++) {
                byteOffset = chunkNo * uploadBlockSizeBytes;

                /* Assemble current package */
                for (
                  let byteIdx = 0;
                  byteIdx < uploadBlockSizeBytes;
                  byteIdx++
                ) {
                  chunkBuffer[byteIdx] = firmwareBinary[byteOffset + byteIdx];
                }

                /* Send the current chunk/package */
                RequestResponseHandler.getInstance()
                  .sendBinary(chunkBuffer)
                  .then((response: ApiResponse) => {
                    /* Abort if any upload failed */
                    if (ResponseCode.SUCCESS != response.statusCode) {
                      Log.error(
                        "Could not upload data chunk! Aborting upload now!"
                      );

                      retCode = false;
                    }
                  });
              }

              if (true === retCode) {
                byteOffset = uploadChunks * uploadBlockSizeBytes;

                /* Assemble last package */
                for (let byteIdx = 0; byteIdx < remainingBytes; byteIdx++) {
                  remainBuffer[byteIdx] = firmwareBinary[byteOffset + byteIdx];
                }

                /* Send the remaining bytes */
                RequestResponseHandler.getInstance()
                  .sendBinary(remainBuffer)
                  .then((response: ApiResponse) => {
                    if (ResponseCode.SUCCESS != response.statusCode) {
                      Log.error("Could not upload last data chunk!");
                      retCode = false;
                    }
                  });
              }
            } else {
              retCode = false;
            }
            return retCode;
          });
      });
    },

    async uploadFirmware(data: any) {
      let files: Array<File> = data.files;
      let fileReader = new FileReader();

      let binaryFirmware = new Uint8Array();

      let firmwareHeader = new FirmwareHeader();
      let firmware = new Firmware();

      if ("ComPlatform" === this.$store.getters.selectedDevice.name) {
        firmwareHeader.setTarget("COM");
      } else if ("Zumo32U4 Robot" === this.$store.getters.selectedDevice.name) {
        firmwareHeader.setTarget("ZUMO");
      }

      let binFile: File = files.filter(function (file: File) {
        return file.name.endsWith(".bin")!;
      })[0];

      let sigFile: File = files.filter(function (file: File) {
        return file.name.endsWith(".pem");
      })[0];

      if ("bin" === this.uploadOption.key) {
        /* Read the unsigned firmware binary */
        fileReader.readAsArrayBuffer(binFile);

        /* Called when firmware has been read */
        fileReader.onload = (event: any) => {
          /* Read the firmware */
          binaryFirmware = new Uint8Array(fileReader.result as ArrayBuffer);
          firmware.setFirmware(binaryFirmware);

          /* Read the private RSA2048 key string when firmware has been read */
          fileReader.readAsText(sigFile);

          /* Called when RSA2048 key has been read */
          fileReader.onload = (event: any) => {
            /* Sign the firmware payload */
            const binSig = FirmwareSigner.sign(
              fileReader.result as string,
              binaryFirmware
            );
            firmwareHeader.setSignature(binSig);
            firmware.setHeader(firmwareHeader);

            /* Upload the CPSFW file */
            this.uploadPackets(firmware);
          };
        };
      } else if ("cpsfw" === this.uploadOption.key) {
        // TODO: Implement
      }
    },
  },
});
</script>

<style lang="less" scoped>
@import "~@/styles/global.less";

.upload {
  display: flex;
  flex-direction: column;

  .progress-bar {
    width: 60%;
  }
}
</style>
