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
 * @file System.cpp
 * @author Luis Moser
 * @brief System class
 * @date 06/22/2021
 * 
 * @{
 */

#include <IO.h>
#include <Logger.h>
#include <Store.h>
#include <KeyCert.h>
#include <System.h>

void System::init()
{
   // Register an ISR for ComPlatform reset on Reset key push
   IO::getInstance().registerSystemReset();
   LOG_DEBUG("Reset-ISR registered");

   // Read WiFi key if AP should be spawned
   bool useAP = IO::getInstance().blockingCheckWifiKeyLongPress();

   Store &store = Store::getInstance();

   // Generate and save a new KeyCert
   bool retCode = store.loadKeyCert();
   if (false == retCode)
   {
      LOG_DEBUG("Missing KeyCert. Generating new SSLCert...");
      KeyCert keycert = store.getKeyCert();
      keycert.generateNewCert();
      store.setKeyCert(keycert);
      LOG_DEBUG("New KeyCert created");

      store.saveKeyCert();
      LOG_DEBUG("New KeyCert saved");
   }

   if (true == useAP)
   {
      // Init AP
      LOG_DEBUG("AP spawned");
   }
   else
   {
      // Load NetworkCredentials
      if (true == store.loadNetworkCredentials())
      {
         // Init STA
         LOG_DEBUG("STA mode initialized");
      }
      else
      {
         LOG_ERROR("No NetworkCredentials available");
         // Init AP
         LOG_DEBUG("AP spwaned because there are no network credentials available");
      }
   }

   // Load Users
   // Load Permissions
   // Init HTTPs Server
   // Init WSS Server
}

void System::reset()
{
   LOG_DEBUG("ComPlatform will be restarted");
   ESP.restart();
}