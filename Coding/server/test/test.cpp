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
#include <Log.h>

#define ARRAY_NUM(__arr)    (sizeof(__arr) / sizeof((__arr)[0]))

/**
 * Logging interface for testing purposes.
 * It provides all relevant methods from the Print class, which are used.
 */
class TestLogger : public Print
{
public:

    /**
     * Constructs a logging interface for testing purposes.
     */
    TestLogger():
        m_buffer()
    {
        uint16_t index = 0U;

        for(index = 0U; index < ARRAY_NUM(m_buffer); ++index)
        {
            m_buffer[index] = 0;
        }
    }

    /**
     * Write a single byte.
     *
     * @param[in] data The byte to be written.
     *
     * @return 1.
     */
    size_t write(uint8_t data)
    {
        (void)data;

        /* Method is not used at all, because the write(const uint8_t*, size_t size)
         * is overwritten, which doesn't use the single byte write method.
         */

        return 0;
    }

    /**
     * Write a single byte.
     *
     * @param[in] buffer Pointer to the data to be written.
     * @param[in] size the size of the data to be written.
     *
     * @return The size of the written data.
     */
    size_t write(const uint8_t* buffer, size_t size)
    {
        uint16_t index = 0U;

        for(index = 0U; index < ARRAY_NUM(m_buffer); ++index)
        {
            m_buffer[index] = static_cast<char>(buffer[index]);
        }

        return size;
    }

    /**
     * Get the Write buffer.
     *
     * @return Write buffer
     */
    const char* getBuffer()
    {
        return m_buffer;
    }

    /**
     * Clear internal buffer.
     */
    void clear()
    {
        m_buffer[0] = '\0';
    }

    /**
     * Destroys the logging interface.
     */
    ~TestLogger( )
    {
    }

private:
    char m_buffer[1024]; /**< Write buffer, containing the logMessage. */
};

static void test_Logging();

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_Logging);
    UNITY_END();

    return 0;
}

/**
 * Test the logging functionality
 */
static void test_Logging()
{
    Log&        logger      = Log::getInstance();
    TestLogger  testLogger;

    logger.setOutput(&testLogger);

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
}
