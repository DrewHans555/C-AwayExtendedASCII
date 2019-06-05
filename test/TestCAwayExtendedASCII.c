#include "unity.h"
#include "CAwayExtendedASCII.h"

void test_compressFile__with_invalid_file__should_return_1(void)
{
    TEST_ASSERT_EQUAL(1, CAwayExtendedASCII(NULL));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_compressFile__with_invalid_file__should_return_1);

    return UNITY_END();
}
