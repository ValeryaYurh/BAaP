#include <gtest/gtest.h>
#include "result_sum_arr.h"

// Тест count_el
TEST(ResultSumArrTest, CountElEmpty) {
    int n = 2;
    int **arr = new int*[n];
    for(int i=0;i<n;i++){
        arr[i] = new int[n]{1,3};
    }
    EXPECT_EQ(count_el(arr, n, n), 0);
    for(int i=0;i<n;i++) delete[] arr[i];
    delete[] arr;
}

TEST(ResultSumArrTest, CountElMixed) {
    int n = 3;
    int **arr = new int*[n];
    arr[0] = new int[3]{2, 1, 3};
    arr[1] = new int[3]{5, 4, 6};
    arr[2] = new int[3]{7, 9, 8};
    EXPECT_EQ(count_el(arr, n, n), 3); // 2,4,8 на диагонали чётные
    for(int i=0;i<n;i++) delete[] arr[i];
    delete[] arr;
}

// Тест product
TEST(ResultSumArrTest, ProductArray) {
    int arr[4] = {2,3,4,5};
    EXPECT_EQ(product(arr, 4), 2*3*4*5);
}

TEST(ResultSumArrTest, ProductEmpty) {
    int arr[0] = {};
    EXPECT_EQ(product(arr, 0), 1);
}

// main для запуска тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
