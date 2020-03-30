#include "gtest/gtest.h"

class RedisConnectionTesting : public ::testing::Test
{
protected:
    void SetUp()
    {
        foo = new int;
        *foo = 5;
    }
    void TearDown()
    {
        delete foo;
    }
    int *foo;
};

TEST_F(RedisConnectionTesting, test_name)
{
    ASSERT_EQ(*foo, 5) << "1 is not equal 0";
}

TEST_F(RedisConnectionTesting, test_name_2)
{
    ASSERT_EQ(*foo, 5) << "1 is not equal 0";
}