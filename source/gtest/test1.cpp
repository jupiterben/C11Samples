

int Foo(int a, int b)
{
    if (a == 0 || b == 0)
    {
        throw "don't do that";
    }
    int c = a % b;
    if (c == 0)
        return b;
    return Foo(b, c);
}

#include <gtest/gtest.h>

TEST(FooTest, HandleNoneZeroInput)
{
    EXPECT_EQ(1, Foo(4, 10));
    EXPECT_EQ(6, Foo(30, 18));
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
