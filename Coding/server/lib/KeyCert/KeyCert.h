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
 * @file KeyCert.h
 * @author Luis Moser
 * @brief KeyCert header
 * @date 06/22/2021
 * 
 * @{
 */

#ifndef __KEYCERT_H__
#define __KEYCERT_H__

#include <SSLCert.hpp>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Logger.h>

using namespace httpsserver;

/** Data structure for HTTPS/WSS server which supports JSON serialization */
class KeyCert
{
public:
   /**
    * Default Constructor
    */
   KeyCert()
   {
      m_Cert = new SSLCert();
   }

   /**
    * Constructor
    * 
    * @param[in] certificate The
    * certificate to be saved
    */
   KeyCert(SSLCert *certificate)
   {
      m_Cert = certificate;
   }

   /**
    * Destructor
    */
   ~KeyCert()
   {
      delete m_Cert;
   }

   /**
    * Generates a new SSLCert
    * for this class instance
    */
   bool generateNewCert();

   /**
    * Sets a new certificate and private key
    * 
    * @param[in] certificate The certificate
    * to be saved
    */
   void setCert(SSLCert *certificate);

   /**
    * Returns the certificate and private key
    * 
    * @return Returns the SSLCert
    */
   SSLCert *getCert();

   /** Returns JSON string
     * 
     * @return Returns the serialized object
     * in JSON string
     */
   String serialize();

   /** Re-creates object from serialized JSON string
     * 
     * @param serial The serialized JSON string
     * @return Returns false in case of failure,
     * true in case of success
     */
   bool deserialize(String serial);

private:
   /** 
    * The DER-X509 certificate
    * which stores the private RSA key
    * as well as the public certificate.
    * This data structure is used by
    * the HTTPs/WSS servers
    */
   SSLCert *m_Cert;
};
#endif