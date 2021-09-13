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
 * @file Log.ts
 * @author Luis Moser
 * @brief Log class
 * @date 09/13/2021
 *
 * @{
 */

/** Enumeration to specify granularity of events */
enum LogLevel {
    LEVEL_INVALID = 4,
    LEVEL_DEBUG = 3,
    LEVEL_INFO = 2,
    LEVEL_WARN = 1,
    LEVEL_ERROR = 0
};

/** Logging class */
export default class Log {

    /** The log level which is used to determine what to print */
    private static m_logLevel = LogLevel.LEVEL_DEBUG;

    public static setLogLevel(level: LogLevel): void {
        this.m_logLevel = level;
    }

    public static getLogLevel(level: LogLevel): LogLevel {
        return this.m_logLevel;
    }

    public static debug(msg: string): void {
        Log.writeLog(LogLevel.LEVEL_DEBUG, "[+]\t" + msg);
    }

    public static info(msg: string): void {
        Log.writeLog(LogLevel.LEVEL_INFO, "[i]\t" + msg);
    }


    public static warn(msg: string): void {
        Log.writeLog(LogLevel.LEVEL_WARN, "[!]\t" + msg);
    }


    public static error(msg: string): void {
        Log.writeLog(LogLevel.LEVEL_ERROR, "[-]\t" + msg);
    }

    private static writeLog(level: LogLevel, msg: string): void {
        if ((level <= this.m_logLevel) && (0 < msg.length)) {
            console.log(msg);
        }
    }
}
