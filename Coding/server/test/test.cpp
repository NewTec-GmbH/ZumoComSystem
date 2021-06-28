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
 * @file test.cpp
 * @author Luis Moser
 * @brief Test class
 * @date 06/17/2021
 * 
 * @{
 */

#include <unity.h>
#include <ArduinoFake.h>

#include <Log.h>

/**
 * Test the logging functionality
 */

using namespace fakeit;

void test_Logging()
{
    Log &logger = Log::getInstance();

    /* Test if default log level is set to DEBUG */
    Log::LogLevel current = logger.getLogLevel();
    TEST_ASSERT_EQUAL(Log::LEVEL_DEBUG, current);

    /* Test if the log level is set correctly */
    logger.setLogLevel(Log::LEVEL_ERROR);
    current = logger.getLogLevel();
    TEST_ASSERT_EQUAL(Log::LEVEL_ERROR, current);

    /* Test if only valid log levels can be set */
    logger.setLogLevel(Log::LEVEL_INFO);
    logger.setLogLevel(static_cast<Log::LogLevel>(4));
    current = logger.getLogLevel();
    TEST_ASSERT_EQUAL(Log::LEVEL_INFO, current);

    // /* Test if logs are written correctly */
    // const char *testString = "Test";
    // logger.setLogLevel(Log::LEVEL_DEBUG);
    // When(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char *))).AlwaysReturn();
    // LOG_DEBUG(testString);
    // LOG_INFO(testString);
    // LOG_WARN(testString);
    // LOG_ERROR(testString);
    // Verify(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char *)).Using(testString)).Exactly(4);

    // logger.setLogLevel(Log::LEVEL_ERROR);
    // ArduinoFakeReset();
    // When(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char *))).AlwaysReturn();
    // LOG_DEBUG(testString);
    // LOG_INFO(testString);
    // LOG_WARN(testString);
    // LOG_ERROR(testString);
    // Verify(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char *)).Using(testString)).Once();
}

void test_networkCredentials()
{
    /** Test if the network credentials are set correctly **/
    // String ssid = "MyWifi";
    //  String psk = "MySecurePassword21091986";
    // NetworkCredentials net;

    // net.setSSID(ssid);
    // net.setPSK(psk);

    /** Test if network credentials are properly serialized **/

    /** Test if network credentials are properly deserialized **/
}

void setUp()
{
    ArduinoFakeReset();
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_Logging);
    RUN_TEST(test_networkCredentials);
    UNITY_END();

    return 0;
}