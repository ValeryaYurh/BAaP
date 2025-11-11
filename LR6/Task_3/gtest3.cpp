#include <gtest/gtest.h>
#include "res.h"

// =======================
// Тестирование sum_el
// =======================
TEST(SumElTest, EmptyWord) {
    char* arr[1];
    arr[0] = new char[1]{'\0'};
    int* sums = sum_el(arr, 1);
    EXPECT_EQ(sums[0], 0);
    delete[] sums;
    delete[] arr[0];
}

TEST(SumElTest, SingleLetter) {
    char* arr[1];
    arr[0] = new char[2]{'A','\0'};
    int* sums = sum_el(arr, 1);
    EXPECT_EQ(sums[0], 'A');
    delete[] sums;
    delete[] arr[0];
}

TEST(SumElTest, TwoWords) {
    char* arr[2];
    arr[0] = new char[6]{'H','e','l','l','o','\0'};
    arr[1] = new char[6]{'W','o','r','l','d','\0'};
    int* sums = sum_el(arr, 2);
    EXPECT_EQ(sums[0], 'H'+'e'+'l'+'l'+'o');
    EXPECT_EQ(sums[1], 'W'+'o'+'r'+'l'+'d');
    delete[] sums;
    delete[] arr[0];
    delete[] arr[1];
}

TEST(SumElTest, MixedCase) {
    char* arr[1];
    arr[0] = new char[6]{'A','b','C','d','E','\0'};
    int* sums = sum_el(arr, 1);
    EXPECT_EQ(sums[0], 'A'+'b'+'C'+'d'+'E');
    delete[] sums;
    delete[] arr[0];
}

// =======================
// Тестирование res
// =======================
TEST(ResTest, EvenAsciiWord) {
    char* arr[1];
    arr[0] = new char[5]{'a','b','c','d','\0'}; // сумма четная
    res(arr, 1);
    EXPECT_STREQ(arr[0], "dcba");
    delete[] arr[0];
}

TEST(ResTest, OddAsciiWord) {
    char* arr[1];
    arr[0] = new char[4]{'a','b','d','\0'}; // сумма нечетная
    res(arr, 1);
    EXPECT_STREQ(arr[0], "abd"); // не меняется
    delete[] arr[0];
}

TEST(ResTest, MultipleWords) {
    char* arr[3];
    arr[0] = new char[5]{'t','e','s','t','\0'};
    arr[1] = new char[6]{'w','o','r','d','s','\0'};
    arr[2] = new char[2]{'x','\0'};
    res(arr, 3);
    // проверяем побайтно
    delete[] arr[0];
    delete[] arr[1];
    delete[] arr[2];
}

TEST(ResTest, OneLetterWord) {
    char* arr[1];
    arr[0] = new char[2]{'A','\0'};
    res(arr,1);
    EXPECT_STREQ(arr[0], "A"); // не переворачивается
    delete[] arr[0];
}

TEST(ResTest, EmptyWord) {
    char* arr[1];
    arr[0] = new char[1]{'\0'};
    res(arr,1);
    EXPECT_STREQ(arr[0], ""); // пустое слово
    delete[] arr[0];
}

TEST(ResTest, EvenAndOddWords) {
    char* arr[2];
    arr[0] = new char[5]{'a','b','c','d','\0'}; // четная
    arr[1] = new char[4]{'x','y','z','\0'};     // нечетная
    res(arr,2);
    EXPECT_STREQ(arr[0], "dcba");
    EXPECT_STREQ(arr[1], "xyz");
    delete[] arr[0];
    delete[] arr[1];
}

// main для запуска тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
