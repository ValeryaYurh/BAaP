#include <iostream>
#include <cmath>
using namespace std;


int binpow(int digit, int power, int mod)
{
    int result = 1;
    digit = digit % mod;
    while (power > 0)
    {
        if (power % 2 == 1)
            result = (1LL * result * digit) % mod;
        digit = (1LL * digit * digit) % mod;
        power /= 2;
    }
    return result;
}

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
        if (arr[mid] > target)
        {
            right = mid - 1;
        }
    }
    return -1;  
}



void runTests()
{
    cout << "==============================================" << endl;
    cout << "     ФУНКЦИОНАЛЬНОЕ ТЕСТИРОВАНИЕ" << endl;
    cout << "     binpow и binSearch" << endl;
    cout << "==============================================" << endl;

    int passedTests = 0;
    int totalTests = 0;

    // =========================================================================
    // ТЕСТ 1: binpow - степень 0
    // =========================================================================
    cout << "\nТЕСТ 1: binpow (степень 0)" << endl;
    totalTests++;
    int result1 = binpow(5, 0, 1000);
    cout << "5^0 mod 1000 = " << result1 << endl;
    cout << "Ожидаемый результат: 1" << endl;

    if (result1 == 1)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 2: binpow - большая степень с модулем
    // =========================================================================
    cout << "\nТЕСТ 2: binpow (2^10 mod 1000)" << endl;
    totalTests++;
    int result2 = binpow(2, 10, 1000);
    cout << "2^10 mod 1000 = " << result2 << endl;
    cout << "Ожидаемый результат: 24" << endl;

    if (result2 == 24)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 3: binpow - степень 1
    // =========================================================================
    cout << "\nТЕСТ 3: binpow (степень 1)" << endl;
    totalTests++;
    int result3 = binpow(7, 1, 100);
    cout << "7^1 mod 100 = " << result3 << endl;
    cout << "Ожидаемый результат: 7" << endl;

    if (result3 == 7)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 4: binSearch - элемент в середине массива
    // =========================================================================
    cout << "\nТЕСТ 4: binSearch (элемент в середине)" << endl;
    totalTests++;
    int arr4[] = {1, 3, 5, 7, 9};
    int n4 = 5;
    int result4 = binSearch(arr4, 5, n4);
    cout << "Массив: {1, 3, 5, 7, 9}, Искомое: 5" << endl;
    cout << "Результат: индекс " << result4 << endl;
    cout << "Ожидаемый результат: 2" << endl;

    if (result4 == 2)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 5: binSearch - элемент не найден
    // =========================================================================
    cout << "\nТЕСТ 5: binSearch (элемент не найден)" << endl;
    totalTests++;
    int arr5[] = {2, 4, 6, 8, 10};
    int n5 = 5;
    int result5 = binSearch(arr5, 5, n5);
    cout << "Массив: {2, 4, 6, 8, 10}, Искомое: 5" << endl;
    cout << "Результат: индекс " << result5 << endl;
    cout << "Ожидаемый результат: -1" << endl;

    if (result5 == -1)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТ 6: binSearch - первый элемент массива
    // =========================================================================
    cout << "\nТЕСТ 6: binSearch (первый элемент)" << endl;
    totalTests++;
    int arr6[] = {10, 20, 30, 40, 50};
    int n6 = 5;
    int result6 = binSearch(arr6, 10, n6);
    cout << "Массив: {10, 20, 30, 40, 50}, Искомое: 10" << endl;
    cout << "Результат: индекс " << result6 << endl;
    cout << "Ожидаемый результат: 0" << endl;

    if (result6 == 0)
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
            int cnt, target, mod;
            std::cout << "Enter count of items in array: ";
            std::cin >> cnt;

            int *arr = new int[cnt];
            std::cout << "Enter items of array:\n";
            for (int i = 0; i < cnt; i++)
                std::cin >> arr[i];

            std::cout << "Enter target value to find in array: ";
            std::cin >> target;

            std::cout << "Enter mod value: ";
            std::cin >> mod;

            int index = binSearch(arr, target, cnt);
            if (index == -1)
            {
                std::cout << "Target not found\n";
            }
            else
            {
                int result = binpow(index, cnt, mod);
                std::cout << "Index^length_of_array % mod = " << result << "\n";
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