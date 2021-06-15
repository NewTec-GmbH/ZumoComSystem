#include <unity.h>
#include <Logger.h>

/** The baud rate which is used to write to serial port */
static const uint32_t BAUD_RATE = 9600;

void test_logInstance(void)
{
    Log &log = Log::getInstance();
}

int main()
{
    Serial.begin(BAUD_RATE);
    UNITY_BEGIN();

    RUN_TEST(test_logInstance);

    UNITY_END();
    Serial.end();

    return 0;
}