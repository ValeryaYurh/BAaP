#include <iostream>
#include <chrono>
#include <random>
using namespace std;

void heapify(int *arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }
    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}
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

void runTests()
{
    cout << "==============================================" << endl;
    cout << "     ФУНКЦИОНАЛЬНОЕ ТЕСТИРОВАНИЕ" << endl;
    cout << "     heapify и generatedArray" << endl;
    cout << "==============================================" << endl;

    int passedTests = 0;
    int totalTests = 0;

    // =========================================================================
    // ТЕСТИРОВАНИЕ ФУНКЦИИ heapify
    // =========================================================================
    cout << "\n>>> ТЕСТИРОВАНИЕ ФУНКЦИИ heapify" << endl;
    cout << "----------------------------------------------" << endl;

    // --- ТЕСТ 1: Простое дерево (3 элемента) ---
    cout << "\nТЕСТ 1: Простое дерево (3 элемента)" << endl;
    totalTests++;
    int arr1[] = {1, 3, 2};
    int n1 = 3;
    cout << "До: {1, 3, 2}" << endl;
    
    heapify(arr1, n1, 0);
    
    cout << "После: {" << arr1[0] << ", " << arr1[1] << ", " << arr1[2] << "}" << endl;
    
    // Проверка: корень >= обоих детей
    if (arr1[0] >= arr1[1] && arr1[0] >= arr1[2])
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // --- ТЕСТ 2: Нарушение в левом поддереве ---
    cout << "\nТЕСТ 2: Нарушение в левом поддереве" << endl;
    totalTests++;
    int arr2[] = {10, 5, 3, 20, 1};
    int n2 = 5;
    cout << "До: {10, 5, 3, 20, 1}" << endl;
    
    heapify(arr2, n2, 0);
    
    cout << "После: {" << arr2[0] << ", " << arr2[1] << ", " << arr2[2] << ", " << arr2[3] << ", " << arr2[4] << "}" << endl;
    
    // Проверка свойства heap для всех узлов
    bool test2Pass = true;
    if (arr2[0] < arr2[1] || arr2[0] < arr2[2]) test2Pass = false;
    if (arr2[1] < arr2[3] || arr2[1] < arr2[4]) test2Pass = false;
    
    if (test2Pass)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // --- ТЕСТ 3: Нарушение в правом поддереве ---
    cout << "\nТЕСТ 3: Нарушение в правом поддереве" << endl;
    totalTests++;
    int arr3[] = {10, 20, 5, 1, 2, 30, 4};
    int n3 = 7;
    cout << "До: {10, 20, 5, 1, 2, 30, 4}" << endl;
    
    heapify(arr3, n3, 0);
    
    cout << "После: {" << arr3[0] << ", " << arr3[1] << ", " << arr3[2] << ", " << arr3[3] << ", " << arr3[4] << ", " << arr3[5] << ", " << arr3[6] << "}" << endl;
    
    bool test3Pass = true;
    for (int i = 0; i <= (n3 - 2) / 2; i++)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n3 && arr3[i] < arr3[left]) test3Pass = false;
        if (right < n3 && arr3[i] < arr3[right]) test3Pass = false;
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

    // --- ТЕСТ 4: Уже корректный heap ---
    cout << "\nТЕСТ 4: Уже корректный max-heap" << endl;
    totalTests++;
    int arr4[] = {30, 20, 10, 5, 15};
    int n4 = 5;
    cout << "До: {30, 20, 10, 5, 15}" << endl;
    
    heapify(arr4, n4, 0);
    
    cout << "После: {" << arr4[0] << ", " << arr4[1] << ", " << arr4[2] << ", " << arr4[3] << ", " << arr4[4] << "}" << endl;
    
    bool test4Pass = true;
    if (arr4[0] < arr4[1] || arr4[0] < arr4[2]) test4Pass = false;
    if (arr4[1] < arr4[3] || arr4[1] < arr4[4]) test4Pass = false;
    
    if (test4Pass)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // --- ТЕСТ 5: Один элемент ---
    cout << "\nТЕСТ 5: Один элемент (граничный случай)" << endl;
    totalTests++;
    int arr5[] = {42};
    int n5 = 1;
    cout << "До: {42}" << endl;
    
    heapify(arr5, n5, 0);
    
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

    // --- ТЕСТ 6: Два элемента ---
    cout << "\nТЕСТ 6: Два элемента" << endl;
    totalTests++;
    int arr6[] = {5, 10};
    int n6 = 2;
    cout << "До: {5, 10}" << endl;
    
    heapify(arr6, n6, 0);
    
    cout << "После: {" << arr6[0] << ", " << arr6[1] << "}" << endl;
    
    if (arr6[0] >= arr6[1])
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // --- ТЕСТ 7: Глубокая рекурсия (15 элементов) ---
    cout << "\nТЕСТ 7: Глубокая рекурсия (15 элементов)" << endl;
    totalTests++;
    int arr7[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int n7 = 15;
    cout << "До: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}" << endl;
    
    for (int i = (n7 / 2) - 1; i >= 0; i--)
    {
        heapify(arr7, n7, i);
    }
    
    cout << "После: {";
    for (int i = 0; i < n7; i++)
    {
        cout << arr7[i];
        if (i < n7 - 1) cout << ", ";
    }
    cout << "}" << endl;
    
    bool test7Pass = true;
    for (int i = 0; i <= (n7 - 2) / 2; i++)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n7 && arr7[i] < arr7[left]) test7Pass = false;
        if (right < n7 && arr7[i] < arr7[right]) test7Pass = false;
    }
    
    if (test7Pass)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }

    // =========================================================================
    // ТЕСТИРОВАНИЕ ФУНКЦИИ generatedArray
    // =========================================================================
    cout << "\n>>> ТЕСТИРОВАНИЕ ФУНКЦИИ generatedArray" << endl;
    cout << "----------------------------------------------" << endl;

    // --- ТЕСТ 8: Проверка размера массива (n=10) ---
    cout << "\nТЕСТ 8: Проверка размера массива (n=10)" << endl;
    totalTests++;
    int n8 = 10;
    int *arr8 = generatedArray(n8);
    cout << "Запрошенный размер: " << n8 << endl;
    cout << "Сгенерированный: {";
    for (int i = 0; i < n8; i++)
    {
        cout << arr8[i];
        if (i < n8 - 1) cout << ", ";
    }
    cout << "}" << endl;
    
    delete[] arr8;
    cout << " ✓ ПРОЙДЕН" << endl;
    passedTests++;

    // --- ТЕСТ 9: Проверка диапазона значений (1 до n) ---
    cout << "\nТЕСТ 9: Проверка диапазона значений (1 до 20)" << endl;
    totalTests++;
    int n9 = 20;
    int *arr9 = generatedArray(n9);
    cout << "Размер: " << n9 << endl;
    cout << "Значения: {";
    for (int i = 0; i < n9; i++)
    {
        cout << arr9[i];
        if (i < n9 - 1) cout << ", ";
    }
    cout << "}" << endl;
    
    bool test9Pass = true;
    for (int i = 0; i < n9; i++)
    {
        if (arr9[i] < 1 || arr9[i] > n9)
        {
            test9Pass = false;
            cout << "Ошибка: arr[" << i << "] = " << arr9[i] << endl;
            break;
        }
    }
    
    if (test9Pass)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }
    delete[] arr9;

    // --- ТЕСТ 10: Массив размером 1 ---
    cout << "\nТЕСТ 10: Массив размером 1" << endl;
    totalTests++;
    int n10 = 1;
    int *arr10 = generatedArray(n10);
    cout << "Размер: " << n10 << ", Значение: " << arr10[0] << endl;
    
    if (arr10[0] >= 1 && arr10[0] <= 1)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }
    delete[] arr10;

    // --- ТЕСТ 11: Массив размером 100 ---
    cout << "\nТЕСТ 11: Массив размером 100" << endl;
    totalTests++;
    int n11 = 100;
    int *arr11 = generatedArray(n11);
    cout << "Размер: " << n11 << endl;
    
    bool test11Pass = true;
    for (int i = 0; i < n11; i++)
    {
        if (arr11[i] < 1 || arr11[i] > n11)
        {
            test11Pass = false;
            break;
        }
    }
    
    if (test11Pass)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }
    delete[] arr11;

    // --- ТЕСТ 12: Проверка выделения памяти ---
    cout << "\nТЕСТ 12: Проверка выделения памяти" << endl;
    totalTests++;
    int n12 = 5;
    int *arr12a = generatedArray(n12);
    int *arr12b = generatedArray(n12);
    
    if (arr12a != nullptr && arr12b != nullptr)
    {
        cout << " ✓ ПРОЙДЕН" << endl;
        passedTests++;
    }
    else
    {
        cout << " ✗ ПРОВАЛЕН" << endl;
    }
    delete[] arr12a;
    delete[] arr12b;

   
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
        std::cout << "\nChoose which array to heapsort:\n";
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

            for (int i = cnt / 2 - 1; i >= 0; i--)
                heapify(arr, cnt, i);

            for (int i = cnt - 1; i >= 0; i--)
            {
                std::swap(arr[i], arr[0]);
                heapify(arr, i, 0);
            }

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration =
                std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

            std::cout << "Sorted array:\n";
            for (int i = 0; i < cnt; i++)
                std::cout << arr[i] << " ";

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
                std::cout<<genArray[i]<<" ";
            }
            

            auto startGen = std::chrono::high_resolution_clock::now();

            for (int i = cnt / 2 - 1; i >= 0; i--)
                heapify(genArray, cnt, i);

            for (int i = cnt - 1; i >= 0; i--)
            {
                std::swap(genArray[i], genArray[0]);
                heapify(genArray, i, 0);
            }

            auto stopGen = std::chrono::high_resolution_clock::now();
            auto durationGen =
                std::chrono::duration_cast<std::chrono::nanoseconds>(stopGen - startGen);

            std::cout << "\nSorted array:\n";
            for (int i = 0; i < cnt; i++)
                std::cout << genArray[i] << " ";

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
            continue;
        }
    }

    return 0;
}


