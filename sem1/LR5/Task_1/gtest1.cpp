#include <gtest/gtest.h>
#include "sum_sol.h"

// Краевой тест 1: a = 0
TEST(ResultTest, AIsZero) {
    EXPECT_EQ(result(0.0, 5.0), 0.0);
    EXPECT_EQ(result(0.0, -3.2), 0.0);
}

// Краевой тест 2: b = 0, a != 0
TEST(ResultTest, BIsZero) {
    EXPECT_EQ(result(5.0, 0.0), 0.0);
    EXPECT_EQ(result(-2.0, 0.0), 0.0);
}

// Тест с обычными значениями
TEST(ResultTest, NormalValues) {
    EXPECT_DOUBLE_EQ(result(2.0, 4.0), -2.0);
    EXPECT_DOUBLE_EQ(result(-3.0, 6.0), 2.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
