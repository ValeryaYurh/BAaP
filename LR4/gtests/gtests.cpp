#include <gtest/gtest.h>
#include "../Task_1/dubelems.h"
#include "../Task_2/sumodd.h"
#include "../Task_3/get_sum_odd.h"
#include "../LabWork4_PartC/Task_4/max_diag.h"
extern "C" {
#include "../LabWork4_PartC/Task_5/num_mine.h"
}

#include "../LabWork4_PartC/Task_6/magic_square.h"


// Test 1: Remove duplicates from a normal array
TEST(RemoveDuplicatesTest, RemovesDuplicates) {
    int arr[] = {1, 2, 2, 3, 3, 4};
    int n = 6;

    int newSize = removeDuplicates(arr, n);

    int expected[] = {1, 2, 3, 4};

    EXPECT_EQ(newSize, 4);
    for (int i = 0; i < newSize; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

// Test 2: Remove duplicates when array has all identical elements
TEST(RemoveDuplicatesTest, AllIdentical) {
    int arr[] = {7, 7, 7, 7, 7};
    int n = 5;

    int newSize = removeDuplicates(arr, n);

    EXPECT_EQ(newSize, 1);
    EXPECT_EQ(arr[0], 7);
}

// Тест 1: массив 2x2
TEST(MatrixTest, SmallMatrix)
{
    const int m = 2, n = 2;
    int array[m][n]{{1, 2}, {3, 4}};


    EXPECT_EQ(get_even_sum(*array, m, n), 2 + 4);   // 6
    EXPECT_EQ(get_odd_product(*array, m, n), 1 * 3); // 3
}

// Тест 2: массив 3x3
TEST(MatrixTest, LargerMatrix)
{
    const int m = 3, n = 3;
    int array[m][n]{{2, 4, 6}, {1, 3, 5}, {7, 8, 9}};

    EXPECT_EQ(get_even_sum(*array, m, n), 2+4+6+8);          // 20
    EXPECT_EQ(get_odd_product(*array, m, n), 1*3*5*7*9);     // 945
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//Tест 1
// Тест суммы для 3x3 матрицы
TEST(MatrixFunctionsTest, Sum3x3)
{
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int* flat = &matrix[0][0];
    int result = get_sum(flat, 3, 3);
    // Заштрихованная часть: элементы i>=j || i+j>=2
    // Вычислим вручную: 1,3,4,5,6,7,8,9 = 43
    EXPECT_EQ(result, 43);
}

// Тест для 2x2 матрицы
TEST(MatrixFunctionsTest, SumAndProduct2x2)
{
    int matrix[2][2] = {
        {2, 3},
        {4, 5}
    };
    int* flat = &matrix[0][0];
    EXPECT_EQ(get_sum(flat, 2, 2), 2 + 3 + 4 + 5);      // 14
    EXPECT_EQ(get_odd(flat, 2, 2), 2 * 3 * 4 * 5);     // 120
}

// Тест для матрицы с нулями
TEST(MatrixFunctionsTest, ZeroElements)
{
    int matrix[2][2] = {
        {0, 0},
        {0, 0}
    };
    int* flat = &matrix[0][0];
    EXPECT_EQ(get_sum(flat, 2, 2), 0);
    EXPECT_EQ(get_odd(flat, 2, 2), 0);
}

//Tecm 4
TEST(MaxDiagTest, RegularValues) {
    int diags[4] = {10, 20, 15, 5};
    int max = max_d(diags, 4);
    EXPECT_EQ(max, 20);
}

TEST(MaxDiagTest, AllEqualValues) {
    int diags[4] = {7, 7, 7, 7};
    int max = max_d(diags, 4);
    EXPECT_EQ(max, 7);
}

TEST(MaxDiagTest, NegativeValues) {
    int diags[4] = {-1, -5, -3, -4};
    int max = max_d(diags, 4);
    EXPECT_EQ(max, -1);
}



//test 5 

// Тест 1: пустое поле, никакой мины
TEST(MinesweeperTest, NoMines) {
    int n = 3, m = 3;
    char* field[3];
    char row0[] = {'.', '.', '.'};
    char row1[] = {'.', '.', '.'};
    char row2[] = {'.', '.', '.'};
    field[0] = row0;
    field[1] = row1;
    field[2] = row2;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            EXPECT_EQ(num_mine(field, m, n, i, j), 0);
}

// Тест 2: одна мина в центре
TEST(MinesweeperTest, SingleMineCenter) {
    int n = 3, m = 3;
    char* field[3];
    char row0[] = {'.', '.', '.'};
    char row1[] = {'.', '*', '.'};
    char row2[] = {'.', '.', '.'};
    field[0] = row0;
    field[1] = row1;
    field[2] = row2;

    EXPECT_EQ(num_mine(field, m, n, 0, 0), 1);
    EXPECT_EQ(num_mine(field, m, n, 0, 1), 1);
    EXPECT_EQ(num_mine(field, m, n, 0, 2), 1);
    EXPECT_EQ(num_mine(field, m, n, 1, 0), 1);
    EXPECT_EQ(num_mine(field, m, n, 1, 2), 1);
    EXPECT_EQ(num_mine(field, m, n, 2, 0), 1);
    EXPECT_EQ(num_mine(field, m, n, 2, 1), 1);
    EXPECT_EQ(num_mine(field, m, n, 2, 2), 1);
    EXPECT_EQ(num_mine(field, m, n, 1, 1), 0); // сама мина
}

// Тест 3: мины по диагонали
TEST(MinesweeperTest, DiagonalMines) {
    int n = 3, m = 3;
    char* field[3];
    char row0[] = {'*', '.', '.'};
    char row1[] = {'.', '*', '.'};
    char row2[] = {'.', '.', '*'};
    field[0] = row0;
    field[1] = row1;
    field[2] = row2;

    EXPECT_EQ(num_mine(field, m, n, 0, 1), 2);
    EXPECT_EQ(num_mine(field, m, n, 1, 0), 2);
    EXPECT_EQ(num_mine(field, m, n, 1, 2), 2);
    EXPECT_EQ(num_mine(field, m, n, 2, 1), 2);
}

// Тест 4: все клетки — мины
TEST(MinesweeperTest, AllMines) {
    int n = 2, m = 2;
    char* field[2];
    char row0[] = {'*', '*'};
    char row1[] = {'*', '*'};
    field[0] = row0;
    field[1] = row1;

    EXPECT_EQ(num_mine(field, m, n, 0, 0), 0);
    EXPECT_EQ(num_mine(field, m, n, 0, 1), 0);
    EXPECT_EQ(num_mine(field, m, n, 1, 0), 0);
    EXPECT_EQ(num_mine(field, m, n, 1, 1), 0);
}

// Тест 5: поле с краевыми минами
TEST(MinesweeperTest, EdgeMines) {
    int n = 3, m = 3;
    char* field[3];
    char row0[] = {'*', '.', '*'};
    char row1[] = {'.', '.', '.'};
    char row2[] = {'*', '.', '*'};
    field[0] = row0;
    field[1] = row1;
    field[2] = row2;

    EXPECT_EQ(num_mine(field, m, n, 1, 1), 4);
    EXPECT_EQ(num_mine(field, m, n, 0, 1), 2);
    EXPECT_EQ(num_mine(field, m, n, 1, 0), 2);
    EXPECT_EQ(num_mine(field, m, n, 1, 2), 2);
    EXPECT_EQ(num_mine(field, m, n, 2, 1), 2);
}

//tests 6

// Проверка корректного размера квадрата
TEST(MagicSquareTest, CorrectSize) {
    int n = 3;
    int **square = magic_square(n);
    ASSERT_NE(square, nullptr);

    for (int i = 0; i < n; i++)
        ASSERT_NE(square[i], nullptr);

    // Освобождаем память
    for (int i = 0; i < n; i++)
        free(square[i]);
    free(square);
}

// Проверка магического свойства (суммы строк, столбцов и диагоналей)
TEST(MagicSquareTest, MagicProperty3x3) {
    int n = 3;
    int **square = magic_square(n);
    ASSERT_NE(square, nullptr);

    int magic_sum = n * (n * n + 1) / 2;

    // Сумма строк
    for (int i = 0; i < n; i++) {
        int row_sum = 0;
        for (int j = 0; j < n; j++)
            row_sum += square[i][j];
        EXPECT_EQ(row_sum, magic_sum);
    }

    // Сумма столбцов
    for (int j = 0; j < n; j++) {
        int col_sum = 0;
        for (int i = 0; i < n; i++)
            col_sum += square[i][j];
        EXPECT_EQ(col_sum, magic_sum);
    }

    // Сумма главной диагонали
    int diag1 = 0;
    for (int i = 0; i < n; i++)
        diag1 += square[i][i];
    EXPECT_EQ(diag1, magic_sum);

    // Сумма побочной диагонали
    int diag2 = 0;
    for (int i = 0; i < n; i++)
        diag2 += square[i][n - i - 1];
    EXPECT_EQ(diag2, magic_sum);

    // Освобождаем память
    for (int i = 0; i < n; i++)
        free(square[i]);
    free(square);
}

// Проверка корректного возврата при чётном n
TEST(MagicSquareTest, EvenOrderReturnsNull) {
    int n = 4;
    int **square = magic_square(n);
    EXPECT_EQ(square, nullptr);
}

// Проверка корректного возврата при отрицательном n
TEST(MagicSquareTest, NegativeOrderReturnsNull) {
    int n = -5;
    int **square = magic_square(n);
    EXPECT_EQ(square, nullptr);
}

