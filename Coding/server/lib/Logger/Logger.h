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
 * @file Logger.h
 * @author Luis Moser
 * @brief Loggging header
 * @date 06/14/2021
 * 
 * @{
 */

#ifndef __LOGGING_H__
#define __LOGGING_H__

#ifdef TESTFAKE
#include "ArduinoFake.h"
#else
#include "Arduino.h"
#endif

#ifdef DEBUGCOM
/** Macro for logging debug messages */
#define LOG_DEBUG(msg) ((Log::getInstance().writeLog(Log::LEVEL_DEBUG, msg)))

/** Macro for logging info messages */
#define LOG_INFO(msg) ((Log::getInstance().writeLog(Log::LEVEL_INFO, msg)))

/** Macro for logging warning messages */
#define LOG_WARN(msg) ((Log::getInstance().writeLog(Log::LEVEL_WARN, msg)))

/** Macro for logging error messages */
#define LOG_ERROR(msg) ((Log::getInstance().writeLog(Log::LEVEL_ERROR, msg)))
#else
#define LOG_DEBUG(msg) do{}while(0)
#define LOG_INFO(msg) do{}while(0)
#define LOG_WARN(msg) do{}while(0)
#define LOG_ERROR(msg) do{}while(0)
#endif

/** Singleton logging class used for logging events */
class Log
{
public:
   /**
    * Enumeration to specify granularity of events
    */
   enum LogLevel
   {
      LEVEL_DEBUG = 3,
      LEVEL_INFO = 2,
      LEVEL_WARN = 1,
      LEVEL_ERROR = 0
   };

   /** Get the singleton instance of Log class
    * 
    * @return Returns the Log class instance
    */
   static Log &getInstance()
   {
      static Log instance;
      return instance;
   }

   /** Get the currently used log level
    * 
    * @return Returns the log level
    */
   LogLevel getLogLevel();

   /** Set the log level to be used 
    * 
    * @param[in] level The log level to be used 
   */
   void setLogLevel(LogLevel level);

   /** Write the passed string message into log
    * 
    * @param[in] level The log level to be used 
    * @param[in] msg The log message to be written
   */
   void writeLog(LogLevel level, String msg);

private:
   /** The log level which is used to determine what to print */
   LogLevel m_LogLevel;

   /** Constructor */
   Log() : m_LogLevel(LEVEL_DEBUG)
   {
   }

   /** Destructor */
   ~Log()
   {
   }
};
#endif /* __LOGGING_H__ */