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
 * @file KeyCert.cpp
 * @author Luis Moser
 * @brief KeyCert class
 * @date 06/22/2021
 * 
 * @{
 */

#include <KeyCert.h>
#include <base64.hpp>

bool KeyCert::generateNewCert()
{
   int retCode = createSelfSignedCert(
       *m_Cert,
       KEYSIZE_2048,
       "CN=complatform.local,O=ComPlatform,C=DE",
       "20210101000000",
       "20310101000000");

   if (0 != retCode)
   {
      LOG_ERROR("Could not generate a new certificate");
   }
   return (0 == retCode);
}

void KeyCert::setCert(SSLCert *certificate)
{
   m_Cert = certificate;
}

SSLCert *KeyCert::getCert()
{
   return m_Cert;
}

String KeyCert::serialize()
{
   /*
   Convert the binary-encoded
   private key and certificate to Base64 to
   store the private key and certificate
   as ASCII strings
   */
   unsigned char *binaryKey = m_Cert->getPKData();
   uint16_t keyLength = m_Cert->getPKLength();

   unsigned char *binaryCert = m_Cert->getCertData();
   uint16_t certLength = m_Cert->getCertLength();

   uint16_t keyBase64StringLength = encode_base64_length(keyLength) + 1;
   uint16_t certBase64StringLength = encode_base64_length(certLength) + 1;

   unsigned char *keyBase64String = new unsigned char[keyBase64StringLength];
   unsigned char *certBase64String = new unsigned char[certBase64StringLength];

   uint32_t writtenKeyBase64StringBytes = encode_base64(binaryKey, keyLength, keyBase64String) + 1;
   uint32_t writtenCertBase64StringBytes = encode_base64(binaryCert, certLength, certBase64String) + 1;

   if (writtenKeyBase64StringBytes == keyBase64StringLength && writtenCertBase64StringBytes == certBase64StringLength)
   {
      const uint8_t size = JSON_OBJECT_SIZE(4);
      StaticJsonDocument<size> jsonDocument;

      /*
      Pass the const/non-volatile char*
      pointers to ArduinoJson so that
      ArduinoJson will not copy/duplicate
      the string values
      */
      jsonDocument["keyLength"] = (const uint16_t)keyLength;
      jsonDocument["certLength"] = (const uint16_t)certLength;
      jsonDocument["keyData"] = (const char *)keyBase64String;
      jsonDocument["certData"] = (const char *)certBase64String;

      String serialized;
      serializeJson(jsonDocument, serialized);

      delete[] keyBase64String;
      delete[] certBase64String;
      return serialized;
   }
   else
   {
      delete[] keyBase64String;
      delete[] certBase64String;

      LOG_ERROR("Could not serialize key and certificate");
      return "null";
   }
}

bool KeyCert::deserialize(String serial)
{
   /*
   Reserve memory on stack for JSON structure
   which consists of two key-value pairs
   */
   StaticJsonDocument<64> jsonDocument;

   uint32_t bufferSize = strlen(serial.c_str()) + 1;
   char *buffer = new char[bufferSize];
   serial.toCharArray(buffer, bufferSize);

   DeserializationError retCode = deserializeJson(jsonDocument, buffer);
   // retCode > 0 in case of arbitrary error */
   if (DeserializationError::Ok == retCode)
   {
      uint16_t keyLength = jsonDocument["keyLength"];
      uint16_t certLength = jsonDocument["certLength"];
      const char *keyBase64String = jsonDocument["keyData"];
      const char *certBase64String = jsonDocument["certData"];

      // Do not free these variables as pointers will be passed to SSLCert!
      unsigned char *binaryKey = new unsigned char[keyLength];
      unsigned char *binaryCert = new unsigned char[certLength];

      uint32_t writtenKeyBytes = decode_base64((unsigned char *)keyBase64String, binaryKey);
      uint32_t writtenCertBytes = decode_base64((unsigned char *)certBase64String, binaryCert);

      delete[] buffer;

      if (writtenKeyBytes == keyLength && writtenCertBytes == certLength)
      {
         m_Cert->setPK(binaryKey, keyLength);
         m_Cert->setCert(binaryCert, certLength);
         return true;
      }
      else
      {
         LOG_ERROR("Error on decoding the KeyCert Base64 string");
         return false;
      }
      return true;
   }
   else
   {
      delete[] buffer;
      LOG_ERROR("Error on deserializing the KeyCert JSON object");
      LOG_ERROR(retCode.c_str());
      return false;
   }
}