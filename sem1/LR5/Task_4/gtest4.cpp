#include <gtest/gtest.h>
#include "search_switch.h"

// ---------- ТЕСТЫ ДЛЯ ФУНКЦИИ search ----------

// Тест: нет нулевых элементов
TEST(SearchSwitchTest, SearchNoZeros) {
    int n = 2, k = 3;
    double **a = new double*[n];
    for (int i = 0; i < n; i++) {
        a[i] = new double[k]{1, 2, 3};
    }

    EXPECT_EQ(search(a, n, k), 0);

    for (int i = 0; i < n; i++) delete[] a[i];
    delete[] a;
}

// Тест: несколько нулей
TEST(SearchSwitchTest, SearchSomeZeros) {
    int n = 2, k = 3;
    double **a = new double*[n];
    a[0] = new double[k]{0, 2, 3};
    a[1] = new double[k]{0, 5, 0};

    EXPECT_EQ(search(a, n, k), 3);

    for (int i = 0; i < n; i++) delete[] a[i];
    delete[] a;
}

// Тест: все элементы равны нулю
TEST(SearchSwitchTest, SearchAllZeros) {
    int n = 2, k = 2;
    double **a = new double*[n];
    a[0] = new double[k]{0, 0};
    a[1] = new double[k]{0, 0};

    EXPECT_EQ(search(a, n, k), 4);

    for (int i = 0; i < n; i++) delete[] a[i];
    delete[] a;
}

// ---------- ТЕСТЫ ДЛЯ ФУНКЦИИ switch_el ----------

// Тест: разворот 2×3
TEST(SearchSwitchTest, SwitchElRectangular) {
    int n = 2, k = 3;
    double **a = new double*[n];
    a[0] = new double[k]{1, 2, 3};
    a[1] = new double[k]{4, 5, 6};

    switch_el(a, n, k);

    double expected[2][3] = {{6, 5, 4}, {3, 2, 1}};
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < k; ++j)
            EXPECT_DOUBLE_EQ(a[i][j], expected[i][j]);

    for (int i = 0; i < n; i++) delete[] a[i];
    delete[] a;
}

// Тест: разворот квадратной матрицы
TEST(SearchSwitchTest, SwitchElSquare) {
    int n = 3, k = 3;
    double **a = new double*[n];
    a[0] = new double[k]{1, 2, 3};
    a[1] = new double[k]{4, 5, 6};
    a[2] = new double[k]{7, 8, 9};

    switch_el(a, n, k);

    double expected[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < k; ++j)
            EXPECT_DOUBLE_EQ(a[i][j], expected[i][j]);

    for (int i = 0; i < n; i++) delete[] a[i];
    delete[] a;
}

// Тест: 1×1 (ничего не меняется)
TEST(SearchSwitchTest, SwitchElSingle) {
    int n = 1, k = 1;
    double **a = new double*[n];
    a[0] = new double[k]{42};

    switch_el(a, n, k);

    EXPECT_DOUBLE_EQ(a[0][0], 42);

    delete[] a[0];
    delete[] a;
}

// main для запуска тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
