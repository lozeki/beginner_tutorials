#include <gtest/gtest.h>
#include <climits>

// bad function:
// for example: how to deal with overflow?
int add(int a, int b){
    return a + b;
}

TEST(NumberCmpTest, ShouldPass){
    ASSERT_EQ(3, add(1,2));
}

TEST(NumberCmpTest, ShouldPassToo){
    ASSERT_EQ(5, add(4, 1));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

