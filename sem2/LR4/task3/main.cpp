#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

std::vector<int> b(std::vector<int> arr)
{

    std::vector<int> newArr;
    int i = 0;
    while (i + 2 < arr.size())
    {
        std::vector<int> triple = {arr[i], arr[i + 1], arr[i + 2]};
        std::sort(triple.begin(), triple.end());
        newArr.push_back(triple[1]);
        i += 3;
    }
    int remain = arr.size() - i;
    if (remain == 1)
    {
        newArr.push_back(arr[i]);
    }
    else if (remain == 2)
    {
        int m = (arr[i] + arr[i + 1]) / 2;
        newArr.push_back(m);
    }

    return newArr;
}

void runTests()
{
    cout << "==============================================" << endl;
    cout << "     ФУНКЦИОНАЛЬНОЕ ТЕСТИРОВАНИЕ" << endl;
    cout << "     function b" << endl;
    cout << "==============================================" << endl;

    int passedTests = 0;
    int totalTests = 0;

    // =========================================================================
    // ТЕСТ 1: Пустой массив
    // =========================================================================
    cout << "\nТЕСТ 1: Пустой массив" << endl;
    totalTests++;
    vector<int> arr1 = {};
    vector<int> result1 = b(arr1);
    cout << "До: {}" << endl;
    cout << "После: {}" << endl;
    cout << "Ожидаемый результат: {}" << endl;

    if (result1.size() == 0)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 2: Массив из 3 элементов (одна тройка)
    // =========================================================================
    cout << "\nТЕСТ 2: Массив из 3 элементов (одна тройка)" << endl;
    totalTests++;
    vector<int> arr2 = {5, 1, 3};
    vector<int> result2 = b(arr2);
    cout << "До: {5, 1, 3}" << endl;
    cout << "После: {";
    for (int i = 0; i < result2.size(); i++)
    {
        cout << result2[i];
        if (i < result2.size() - 1) cout << ", ";
    }
    cout << "}" << endl;
    cout << "Ожидаемый результат: {3} (медиана из 1,3,5)" << endl;

    if (result2.size() == 1 && result2[0] == 3)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 3: Массив из 6 элементов (две тройки)
    // =========================================================================
    cout << "\nТЕСТ 3: Массив из 6 элементов (две тройки)" << endl;
    totalTests++;
    vector<int> arr3 = {1, 5, 3, 10, 6, 8};
    vector<int> result3 = b(arr3);
    cout << "До: {1, 5, 3, 10, 6, 8}" << endl;
    cout << "После: {";
    for (int i = 0; i < result3.size(); i++)
    {
        cout << result3[i];
        if (i < result3.size() - 1) cout << ", ";
    }
    cout << "}" << endl;
    cout << "Ожидаемый результат: {3, 8} (медианы из 1,3,5 и 6,8,10)" << endl;

    if (result3.size() == 2 && result3[0] == 3 && result3[1] == 8)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 4: Массив из 4 элементов (одна тройка + 1 остаток)
    // =========================================================================
    cout << "\nТЕСТ 4: Массив из 4 элементов (тройка + 1)" << endl;
    totalTests++;
    vector<int> arr4 = {2, 8, 5, 10};
    vector<int> result4 = b(arr4);
    cout << "До: {2, 8, 5, 10}" << endl;
    cout << "После: {";
    for (int i = 0; i < result4.size(); i++)
    {
        cout << result4[i];
        if (i < result4.size() - 1) cout << ", ";
    }
    cout << "}" << endl;
    cout << "Ожидаемый результат: {5, 10} (медиана 2,5,8 = 5, остаток 10)" << endl;

    if (result4.size() == 2 && result4[0] == 5 && result4[1] == 10)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 5: Массив из 5 элементов (одна тройка + 2 остатка)
    // =========================================================================
    cout << "\nТЕСТ 5: Массив из 5 элементов (тройка + 2)" << endl;
    totalTests++;
    vector<int> arr5 = {3, 1, 4, 10, 20};
    vector<int> result5 = b(arr5);
    cout << "До: {3, 1, 4, 10, 20}" << endl;
    cout << "После: {";
    for (int i = 0; i < result5.size(); i++)
    {
        cout << result5[i];
        if (i < result5.size() - 1) cout << ", ";
    }
    cout << "}" << endl;
    cout << "Ожидаемый результат: {3, 15} (медиана 1,3,4 = 3, среднее 10,20 = 15)" << endl;

    if (result5.size() == 2 && result5[0] == 3 && result5[1] == 15)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 6: Массив из 2 элементов (только остаток)
    // =========================================================================
    cout << "\nТЕСТ 6: Массив из 2 элементов (только остаток)" << endl;
    totalTests++;
    vector<int> arr6 = {7, 13};
    vector<int> result6 = b(arr6);
    cout << "До: {7, 13}" << endl;
    cout << "После: {";
    for (int i = 0; i < result6.size(); i++)
    {
        cout << result6[i];
        if (i < result6.size() - 1) cout << ", ";
    }
    cout << "}" << endl;
    cout << "Ожидаемый результат: {10} (среднее 7,13 = 10)" << endl;

    if (result6.size() == 1 && result6[0] == 10)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    cout << "\n==============================================" << endl;
    cout << "               ИТОГИ ТЕСТИРОВАНИЯ" << endl;
    cout << "==============================================" << endl;
    cout << "Пройдено тестов: " << passedTests << " из " << totalTests << endl;

    if (passedTests == totalTests)
    {
        cout << "Все тесты успешно пройдены!" << endl;
    }
    else
    {
        cout << "Внимание! Некоторые тесты не пройдены." << endl;
    }
    cout << "==============================================" << endl;
}

int main(int argc, char const *argv[])
{
    while (true)
    {
        int answer;
        std::cout << "MENU\n1-run program\n2-run tests\n0-end program\n";
        std::cin >> answer;

        switch (answer)
        {
        case 1:
        {
            int cnt;
            std::cout << "Enter count of items in array: ";
            std::cin >> cnt;

            std::vector<int> arr(cnt);
            std::cout << "Enter items of array:\n";
            for (int i = 0; i < cnt; i++)
                std::cin >> arr[i];
            std::vector<int> bArr;
            bArr = b(arr);
            for (int i = 0; i < bArr.size(); i++)
            {
                std::cout << bArr[i] << " ";
            }
            continue;
        }

        case 2:
        {
            runTests();
            continue;
        }

        case 0:
            return 0;

        default:
        {
            cout << "Wrong input";
            continue;
        }
        }
    }
}
