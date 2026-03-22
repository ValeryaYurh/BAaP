#include <iostream>
#include <chrono>
#include <random>
#include <vector>

using namespace std;

int *generatedArray(int n)
{
    int *arr = new int[n];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, n);

    for (int i = 0; i < n; i++)
    {
        arr[i] = dist(gen);
    }
    return arr;
}

int *quickSort(int n, int *arr)
{
    if (n <= 1)
    {
        return arr;
    }
    int pivot = arr[n / 2];
    std::vector<int> left;
    std::vector<int> right;
    std::vector<int> equal;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < pivot)
        {
            left.push_back(arr[i]);
        }
        else if (arr[i] > pivot)
        {
            right.push_back(arr[i]);
        }
        else
        {
            equal.push_back(arr[i]);
        }
    }
    quickSort(left.size(), left.data());
    quickSort(right.size(), right.data());

    int index = 0;
    for (int x : left)
    {
        arr[index++] = x;
    }
    for (int x : equal)
    {
        arr[index++] = x;
    }
    for (int x : right)
    {
        arr[index++] = x;
    }
    return arr;
}

void runTests()
{
    cout << "==============================================" << endl;
    cout << "     ФУНКЦИОНАЛЬНОЕ ТЕСТИРОВАНИЕ" << endl;
    cout << "     generatedArray и quickSort" << endl;
    cout << "==============================================" << endl;

    int passedTests = 0;
    int totalTests = 0;

    // =========================================================================
    // ТЕСТ 1: generatedArray - проверка размера и диапазона
    // =========================================================================
    cout << "\nТЕСТ 1: generatedArray (n=10)" << endl;
    totalTests++;
    int *arr1 = generatedArray(10);
    cout << "Размер: 10" << endl;
    cout << "Значения: {";
    for (int i = 0; i < 10; i++)
    {
        cout << arr1[i];
        if (i < 9) cout << ", ";
    }
    cout << "}" << endl;

    bool test1Pass = true;
    for (int i = 0; i < 10; i++)
    {
        if (arr1[i] < 1 || arr1[i] > 10) test1Pass = false;
    }

    if (test1Pass)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }
    delete[] arr1;

    // =========================================================================
    // ТЕСТ 2: quickSort - сортировка неотсортированного массива
    // =========================================================================
    cout << "\nТЕСТ 2: quickSort (неотсортированный массив)" << endl;
    totalTests++;
    int arr2[] = {5, 2, 8, 1, 9, 3};
    int n2 = 6;
    cout << "До: {5, 2, 8, 1, 9, 3}" << endl;

    quickSort(n2, arr2);

    cout << "После: {";
    for (int i = 0; i < n2; i++)
    {
        cout << arr2[i];
        if (i < n2 - 1) cout << ", ";
    }
    cout << "}" << endl;

    bool test2Pass = true;
    for (int i = 0; i < n2 - 1; i++)
    {
        if (arr2[i] > arr2[i + 1]) test2Pass = false;
    }

    if (test2Pass)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 3: quickSort - уже отсортированный массив
    // =========================================================================
    cout << "\nТЕСТ 3: quickSort (уже отсортированный массив)" << endl;
    totalTests++;
    int arr3[] = {1, 2, 3, 4, 5};
    int n3 = 5;
    cout << "До: {1, 2, 3, 4, 5}" << endl;

    quickSort(n3, arr3);

    cout << "После: {";
    for (int i = 0; i < n3; i++)
    {
        cout << arr3[i];
        if (i < n3 - 1) cout << ", ";
    }
    cout << "}" << endl;

    bool test3Pass = true;
    for (int i = 0; i < n3 - 1; i++)
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
    // ТЕСТ 4: quickSort - обратно отсортированный массив
    // =========================================================================
    cout << "\nТЕСТ 4: quickSort (обратно отсортированный массив)" << endl;
    totalTests++;
    int arr4[] = {9, 7, 5, 3, 1};
    int n4 = 5;
    cout << "До: {9, 7, 5, 3, 1}" << endl;

    quickSort(n4, arr4);

    cout << "После: {";
    for (int i = 0; i < n4; i++)
    {
        cout << arr4[i];
        if (i < n4 - 1) cout << ", ";
    }
    cout << "}" << endl;

    bool test4Pass = true;
    for (int i = 0; i < n4 - 1; i++)
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
    // ТЕСТ 5: quickSort - один элемент
    // =========================================================================
    cout << "\nТЕСТ 5: quickSort (один элемент)" << endl;
    totalTests++;
    int arr5[] = {42};
    int n5 = 1;
    cout << "До: {42}" << endl;

    quickSort(n5, arr5);

    cout << "После: {" << arr5[0] << "}" << endl;

    if (arr5[0] == 42)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 6: quickSort - массив с дубликатами
    // =========================================================================
    cout << "\nТЕСТ 6: quickSort (массив с дубликатами)" << endl;
    totalTests++;
    int arr6[] = {3, 1, 3, 2, 1, 3};
    int n6 = 6;
    cout << "До: {3, 1, 3, 2, 1, 3}" << endl;

    quickSort(n6, arr6);

    cout << "После: {";
    for (int i = 0; i < n6; i++)
    {
        cout << arr6[i];
        if (i < n6 - 1) cout << ", ";
    }
    cout << "}" << endl;

    bool test6Pass = true;
    for (int i = 0; i < n6 - 1; i++)
    {
        if (arr6[i] > arr6[i + 1]) test6Pass = false;
    }
    int expected6[] = {1, 1, 2, 3, 3, 3};
    for (int i = 0; i < n6; i++)
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


int main(int argc, char const *argv[])
{
    int choice;

    while (true)
    {
        std::cout << "\nChoose which array to quicksort:\n";
        std::cout << "Enter 1 - your\n";
        std::cout << "Enter 2 - generate\n";
        std::cout << "Enter 3 - run tests\n";
        std::cout << "Enter 0 - exit\n";

        std::cin >> choice;

        if (choice == 0)
            break;

        switch (choice)
        {
        case 1:
        {
            int cnt;
            std::cout << "Enter cnt of nums: ";
            std::cin >> cnt;

            int *arr = new int[cnt];

            for (int i = 0; i < cnt; i++)
                std::cin >> arr[i];

            auto start = std::chrono::high_resolution_clock::now();
            int *sortedArr = quickSort(cnt, arr);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration =
                std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

            std::cout << "Sorted array:\n";
            for (int i = 0; i < cnt; i++)
                std::cout << sortedArr[i] << " ";

            std::cout << "\nTime: " << duration.count() << " nanoseconds\n";

            delete[] arr;
            continue;
        }

        case 2:
        {
            int cnt = 10;
            int *genArray = generatedArray(cnt);
            for (int i = 0; i < cnt; i++)
            {
                std::cout << genArray[i] << " ";
            }

            auto startGen = std::chrono::high_resolution_clock::now();
            int *sortedArrRand = quickSort(cnt,genArray);
            auto stopGen = std::chrono::high_resolution_clock::now();
            auto durationGen =
                std::chrono::duration_cast<std::chrono::nanoseconds>(stopGen - startGen);

            std::cout << "\nSorted array:\n";
            for (int i = 0; i < cnt; i++)
                std::cout << sortedArrRand[i] << " ";

            std::cout << "\nTime: " << durationGen.count() << " nanoseconds\n";

            delete[] genArray;
            continue;
        }

        case 3: 
        {
            runTests();
            continue;
        }

        default:
            std::cout << "Wrong choice!\n";
        }
    }
    return 0;
}
