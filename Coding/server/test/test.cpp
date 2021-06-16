#include <unity.h>
#include <Logger.h>
#include <Arduino.h>

/**
 * Test the logging functionality
 */

using namespace fakeit;

void test_Logging()
{
    Log &logger = Log::getInstance();

    /* Test if default log level is set to DEBUG */
    Log::LogLevel actual = logger.getLogLevel();
    TEST_ASSERT_EQUAL(Log::LEVEL_DEBUG, actual);

    /* Test if the log level is set correctly */
    logger.setLogLevel(Log::LEVEL_ERROR);
    actual = logger.getLogLevel();
    TEST_ASSERT_EQUAL(Log::LEVEL_ERROR, actual);

    /* Test if only valid log levels can be set */
    logger.setLogLevel(Log::LEVEL_INFO);
    logger.setLogLevel(static_cast<Log::LogLevel>(4));
    actual = logger.getLogLevel();
    TEST_ASSERT_EQUAL(Log::LEVEL_INFO, actual);

    /* Test if logs are written correctly */
    const char *testString = "Test";
    logger.setLogLevel(Log::LEVEL_DEBUG);
    When(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char *))).AlwaysReturn();
    LOG_DEBUG(testString);
    LOG_INFO(testString);
    LOG_WARN(testString);
    LOG_ERROR(testString);
    Verify(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char *)).Using(testString)).Exactly(4);

    logger.setLogLevel(Log::LEVEL_ERROR);
    ArduinoFakeReset();
    When(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char *))).AlwaysReturn();
    LOG_DEBUG(testString);
    LOG_INFO(testString);
    LOG_WARN(testString);
    LOG_ERROR(testString);
    Verify(OverloadedMethod(ArduinoFake(Serial), println, size_t(const char *)).Using(testString)).Once();
}

void setUp()
{
    ArduinoFakeReset();
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_Logging);
    UNITY_END();

    return 0;
}