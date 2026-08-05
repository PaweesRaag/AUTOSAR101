#include<gtest/gtest.h>

int Add(int a, int b)
{
    return a + b;
}

TEST(AdditionTest, PositiveNumbers)
{
    EXPECT_EQ(Add(2, 3), 5);
}
