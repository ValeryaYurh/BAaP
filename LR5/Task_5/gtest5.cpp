#include <gtest/gtest.h>
#include "arr_average.h"

// ---------- ТЕСТЫ ДЛЯ ФУНКЦИИ count ----------

// Тест: нет нечётных элементов в чётных столбцах
TEST(ArrAverageTest, CountNoOddInEvenCols) {
    int n = 2, k = 3;
    int **a = new int*[n];
    a[0] = new int[k]{2, 4, 6};
    a[1] = new int[k]{8, 10, 12};

    EXPECT_EQ(count(a, n, k), 0);

    for (int i = 0; i < n; i++) delete[] a[i];
    delete[] a;
}

// Тест: есть нечётные в чётных столбцах
TEST(ArrAverageTest, CountSomeOddInEvenCols) {
    int n = 2, k = 4;
    int **a = new int*[n];
    a[0] = new int[k]{1, 3, 2, 7};
    a[1] = new int[k]{2, 5, 4, 9};

    // Чётные столбцы — 2 и 4 → значения 3,7,5,9 → все нечётные → 4 элемента
    EXPECT_EQ(count(a, n, k), 4);

    for (int i = 0; i < n; i++) delete[] a[i];
    delete[] a;
}

// ---------- ТЕСТЫ ДЛЯ ФУНКЦИИ new_arr ----------

TEST(ArrAverageTest, NewArrCorrectExtraction) {
    int n = 2, k = 4;
    int **a = new int*[n];
    a[0] = new int[k]{1, 3, 2, 7};
    a[1] = new int[k]{2, 5, 4, 9};

    int p = count(a, n, k);
    int *x = new int[p];

    new_arr(a, x, n, k);

    int expected[] = {3, 7, 5, 9};
    for (int i = 0; i < p; i++)
        EXPECT_EQ(x[i], expected[i]);

    for (int i = 0; i < n; i++) delete[] a[i];
    delete[] a;
    delete[] x;
}

// ---------- ТЕСТЫ ДЛЯ ФУНКЦИИ average ----------

TEST(ArrAverageTest, AverageSimpleCase) {
    int arr[] = {3, 1, 3};
    testing::internal::CaptureStdout();
    average(arr, 3);
    std::string output = testing::internal::GetCapturedStdout();

    // Проверяем, что число 2.33 есть в выводе (примерно)
    EXPECT_NE(output.find("2.3"), std::string::npos);
}

TEST(ArrAverageTest, AverageEmptyArray) {
    int *arr = nullptr;
    testing::internal::CaptureStdout();
    average(arr, 0);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Ошибка"), std::string::npos);
}

// ---------- MAIN ДЛЯ ЗАПУСКА ВСЕХ ТЕСТОВ ----------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
