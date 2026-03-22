#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void interpolationSort(std::vector<int> &arr)
{
    int n = arr.size();
    if (n <= 1)
        return;

    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int l = 0;
        int r = i - 1;

        while (l <= r && (arr[r] != arr[l]))
        {
            int pos = l + ((key - arr[l]) * (r - l)) / (arr[r] - arr[l]);

            if (pos < l)
                pos = l;
            if (pos > r)
                pos = r;

            if (arr[pos] == key)
            {
                l = pos + 1;
                break;
            }
            else if (arr[pos] < key)
            {
                l = pos + 1;
            }
            else
            {
                r = pos - 1;
            }
        }
        int j = i - 1;
        while (j >= l)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[l] = key;
        std::cout << "Шаг " << i << ": ";
        for (int x : arr)
            std::cout << x << " ";
        std::cout << "\n";
    }
}

void runTests()
{
    cout << "==============================================" << endl;
    cout << "     ФУНКЦИОНАЛЬНОЕ ТЕСТИРОВАНИЕ" << endl;
    cout << "     interpolationSort" << endl;
    cout << "==============================================" << endl;

    int passedTests = 0;
    int totalTests = 0;

    // =========================================================================
    // ТЕСТ 1: Пустой массив
    // =========================================================================
    cout << "\nТЕСТ 1: Пустой массив" << endl;
    totalTests++;
    vector<int> arr1 = {};
    cout << "До: {}" << endl;

    interpolationSort(arr1);

    cout << "После: {}" << endl;

    if (arr1.size() == 0)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 2: Один элемент
    // =========================================================================
    cout << "\nТЕСТ 2: Один элемент" << endl;
    totalTests++;
    vector<int> arr2 = {42};
    cout << "До: {42}" << endl;

    interpolationSort(arr2);

    cout << "После: {" << arr2[0] << "}" << endl;

    if (arr2.size() == 1 && arr2[0] == 42)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 3: Уже отсортированный массив
    // =========================================================================
    cout << "\nТЕСТ 3: Уже отсортированный массив" << endl;
    totalTests++;
    vector<int> arr3 = {1, 2, 3, 4, 5};
    cout << "До: {1, 2, 3, 4, 5}" << endl;

    interpolationSort(arr3);

    cout << "После: {";
    for (int i = 0; i < arr3.size(); i++)
    {
        cout << arr3[i];
        if (i < arr3.size() - 1) cout << ", ";
    }
    cout << "}" << endl;

    bool test3Pass = true;
    for (int i = 0; i < arr3.size() - 1; i++)
    {
        if (arr3[i] > arr3[i + 1]) test3Pass = false;
    }

    if (test3Pass)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 4: Обратно отсортированный массив
    // =========================================================================
    cout << "\nТЕСТ 4: Обратно отсортированный массив" << endl;
    totalTests++;
    vector<int> arr4 = {9, 7, 5, 3, 1};
    cout << "До: {9, 7, 5, 3, 1}" << endl;

    interpolationSort(arr4);

    cout << "После: {";
    for (int i = 0; i < arr4.size(); i++)
    {
        cout << arr4[i];
        if (i < arr4.size() - 1) cout << ", ";
    }
    cout << "}" << endl;

    bool test4Pass = true;
    for (int i = 0; i < arr4.size() - 1; i++)
    {
        if (arr4[i] > arr4[i + 1]) test4Pass = false;
    }

    if (test4Pass)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 5: Неотсортированный массив
    // =========================================================================
    cout << "\nТЕСТ 5: Неотсортированный массив" << endl;
    totalTests++;
    vector<int> arr5 = {34, 7, 23, 32, 5, 62};
    cout << "До: {34, 7, 23, 32, 5, 62}" << endl;

    interpolationSort(arr5);

    cout << "После: {";
    for (int i = 0; i < arr5.size(); i++)
    {
        cout << arr5[i];
        if (i < arr5.size() - 1) cout << ", ";
    }
    cout << "}" << endl;

    bool test5Pass = true;
    for (int i = 0; i < arr5.size() - 1; i++)
    {
        if (arr5[i] > arr5[i + 1]) test5Pass = false;
    }

    if (test5Pass)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 6: Массив с дубликатами
    // =========================================================================
    cout << "\nТЕСТ 6: Массив с дубликатами" << endl;
    totalTests++;
    vector<int> arr6 = {5, 2, 8, 2, 9, 1, 5};
    cout << "До: {5, 2, 8, 2, 9, 1, 5}" << endl;

    interpolationSort(arr6);

    cout << "После: {";
    for (int i = 0; i < arr6.size(); i++)
    {
        cout << arr6[i];
        if (i < arr6.size() - 1) cout << ", ";
    }
    cout << "}" << endl;

    bool test6Pass = true;
    for (int i = 0; i < arr6.size() - 1; i++)
    {
        if (arr6[i] > arr6[i + 1]) test6Pass = false;
    }
    // Проверка что все элементы на месте (1,2,2,5,5,8,9)
    int expected6[] = {1, 2, 2, 5, 5, 8, 9};
    for (int i = 0; i < 7; i++)
    {
        if (arr6[i] != expected6[i]) test6Pass = false;
    }

    if (test6Pass)
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

int main()
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
            std::cout << "Enter cnt of nums:";
            std::cin >> cnt;
            std::vector<int> data(cnt);
            for (int i = 0; i < cnt; i++)
            {
                std::cin >> data[i];
            }

            std::cout << "До сортировки: ";
            for (int x : data)
                std::cout << x << " ";
            std::cout << "\n";

            interpolationSort(data);

            std::cout << "После сортировки: ";
            for (int x : data)
                std::cout << x << " ";
            std::cout << "\n";
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