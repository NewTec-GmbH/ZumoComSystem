#include <unity.h>

void setup()
{
}

void loop()
{
}

void add_test()
{
    uint32_t res = 42 + 31;
    TEST_ASSERT_EQUAL_UINT32(73, res);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(add_test);
    UNITY_END();

    return 0;
}