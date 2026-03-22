#include <iostream>
using namespace std;

int binSearch(int *arr, int target, int n)
{
    int left = 0;
    int right = n - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (arr[mid] == target)
        {
            return mid;
        }
        if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}

void runTests()
{
    cout << "==============================================" << endl;
    cout << "     ТЕСТИРОВАНИЕ БИНАРНОГО ПОИСКА" << endl;
    cout << "==============================================" << endl;

    int passedTests = 0;
    int totalTests = 0;

    cout << "\nТЕСТ 1: Поиск элемента в середине" << endl;
    int arr1[] = {1, 3, 5, 7, 9};
    int target1 = 5;
    int n1 = 5;
    int expected1 = 2;
    totalTests++;

    int result1 = binSearch(arr1, target1, n1);
    cout << "Массив: {1, 3, 5, 7, 9}, Искомое: " << target1 << endl;
    cout << "Ожидаемый индекс: " << expected1 << ", Получено: " << result1;

    if (result1 == expected1)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    cout << "\nТЕСТ 2: Поиск первого элемента" << endl;
    int arr2[] = {2, 4, 6, 8, 10};
    int target2 = 2;
    int n2 = 5;
    int expected2 = 0;
    totalTests++;

    int result2 = binSearch(arr2, target2, n2);
    cout << "Массив: {2, 4, 6, 8, 10}, Искомое: " << target2 << endl;
    cout << "Ожидаемый индекс: " << expected2 << ", Получено: " << result2;

    if (result2 == expected2)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    cout << "\nТЕСТ 3: Поиск последнего элемента" << endl;
    int arr3[] = {10, 20, 30, 40, 50};
    int target3 = 50;
    int n3 = 5;
    int expected3 = 4;
    totalTests++;

    int result3 = binSearch(arr3, target3, n3);
    cout << "Массив: {10, 20, 30, 40, 50}, Искомое: " << target3 << endl;
    cout << "Ожидаемый индекс: " << expected3 << ", Получено: " << result3;

    if (result3 == expected3)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    cout << "\nТЕСТ 4: Элемент не найден (меньше минимума)" << endl;
    int arr4[] = {5, 10, 15, 20};
    int target4 = 1;
    int n4 = 4;
    int expected4 = -1;
    totalTests++;

    int result4 = binSearch(arr4, target4, n4);
    cout << "Массив: {5, 10, 15, 20}, Искомое: " << target4 << endl;
    cout << "Ожидаемый индекс: " << expected4 << ", Получено: " << result4;

    if (result4 == expected4)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    cout << "\nТЕСТ 5: Элемент не найден (больше максимума)" << endl;
    int arr5[] = {1, 2, 3, 4, 5};
    int target5 = 100;
    int n5 = 5;
    int expected5 = -1;
    totalTests++;

    int result5 = binSearch(arr5, target5, n5);
    cout << "Массив: {1, 2, 3, 4, 5}, Искомое: " << target5 << endl;
    cout << "Ожидаемый индекс: " << expected5 << ", Получено: " << result5;

    if (result5 == expected5)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    cout << "\nТЕСТ 6: Массив из одного элемента (совпадение)" << endl;
    int arr6[] = {42};
    int target6 = 42;
    int n6 = 1;
    int expected6 = 0;
    totalTests++;

    int result6 = binSearch(arr6, target6, n6);
    cout << "Массив: {42}, Искомое: " << target6 << endl;
    cout << "Ожидаемый индекс: " << expected6 << ", Получено: " << result6;

    if (result6 == expected6)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // --- ТЕСТ 7: Массив из одного элемента (не совпадение) ---
    cout << "\nТЕСТ 7: Массив из одного элемента (не совпадение)" << endl;
    int arr7[] = {10};
    int target7 = 5;
    int n7 = 1;
    int expected7 = -1;
    totalTests++;

    int result7 = binSearch(arr7, target7, n7);
    cout << "Массив: {10}, Искомое: " << target7 << endl;
    cout << "Ожидаемый индекс: " << expected7 << ", Получено: " << result7;

    if (result7 == expected7)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    cout << "\nТЕСТ 8: Отрицательные числа в массиве" << endl;
    int arr8[] = {-10, -5, 0, 5, 10};
    int target8 = -5;
    int n8 = 5;
    int expected8 = 1;
    totalTests++;

    int result8 = binSearch(arr8, target8, n8);
    cout << "Массив: {-10, -5, 0, 5, 10}, Искомое: " << target8 << endl;
    cout << "Ожидаемый индекс: " << expected8 << ", Получено: " << result8;

    if (result8 == expected8)
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
        cout << "Проверьте логику функции binSearch." << endl;
    }
    cout << "==============================================" << endl;
}

int main(int argc, char const *argv[])
{
    while (true)
    {
        int answer;
        std::cout << "MENU\n1-run program\n2-run tests\n3-end program\n";
        std::cin >> answer;

        switch (answer)
        {
        case 1:
        {
            int cnt;
            int target;
            std::cout << "Enter count of items in array:";
            std::cin >> cnt;
            std::cout << "Enter items of array:\n";
            int *arr = new int[cnt];
            for (int i = 0; i < cnt; i++)
            {
                std::cin >> arr[i];
            }
            std::cout << "Enter target value to find in array:";
            std::cin >> target;
            int index = binSearch(arr, target, cnt);
            std::cout << "Target value index: " << index << "\n";
            continue;
        }

        case 2:
        {
            runTests();
            continue;
        }

        case 3:
            return 0;

        default:
        {
            cout << "Wrong input";
            continue;
        }
        }
    }
}
