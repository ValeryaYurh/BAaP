#include <gtest/gtest.h>
#include "check_sin.h"
#include <cmath>

// Краевой тест 1: Пустой массив или некорректные данные
TEST(AnySinPositiveTest, InvalidInput) {
    EXPECT_FALSE(any_sin_positive(nullptr, 5));   // null указатель
    EXPECT_FALSE(any_sin_positive(nullptr, 0));   // null и N = 0
    double arr[1] = {0};
    EXPECT_FALSE(any_sin_positive(arr, 0));       // N = 0
    EXPECT_FALSE(any_sin_positive(arr, -3));      // отрицательный размер
}

// Краевой тест 2: Один элемент
TEST(AnySinPositiveTest, SingleElement) {
    double arr1[1] = {0.0};               // sin(0) = 0
    double arr2[1] = {M_PI / 2};          // sin(pi/2) > 0
    double arr3[1] = {-M_PI / 2};         // sin(-pi/2) < 0

    EXPECT_FALSE(any_sin_positive(arr1, 1));
    EXPECT_TRUE(any_sin_positive(arr2, 1));
    EXPECT_FALSE(any_sin_positive(arr3, 1));
}

// Тест 4: Есть хотя бы один элемент, где sin > 0
TEST(AnySinPositiveTest, AtLeastOnePositive) {
    double arr1[] = {-M_PI, -M_PI/2, M_PI/6};  // sin(pi/6) > 0
    double arr2[] = {M_PI/3, -M_PI, -2*M_PI};  // sin(pi/3) > 0
    EXPECT_TRUE(any_sin_positive(arr1, 3));
    EXPECT_TRUE(any_sin_positive(arr2, 3));
}

// Тест 5: Чётное и нечётное количество элементов
TEST(AnySinPositiveTest, EvenOddLengths) {
    double evenArr[] = {M_PI/6, M_PI/2, M_PI, -M_PI/2};  // sin(pi/6)>0
    double oddArr[] = {-M_PI, -M_PI/2, M_PI/2};          // sin(pi/2)>0
    EXPECT_TRUE(any_sin_positive(evenArr, 4));
    EXPECT_TRUE(any_sin_positive(oddArr, 3));
}

// Тест 6: Все sin равны нулю
TEST(AnySinPositiveTest, AllZeroSin) {
    double arr[] = {0.0, M_PI, -M_PI, 2*M_PI};
    EXPECT_FALSE(any_sin_positive(arr, 4));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
