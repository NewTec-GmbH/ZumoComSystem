#include <unity.h>
#include <Logger.h>

void test_logInstance(void)
{
    Log &log = Log::getInstance();
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_logInstance);
    UNITY_END();

    return 0;
}