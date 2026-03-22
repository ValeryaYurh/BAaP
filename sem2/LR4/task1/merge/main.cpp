#include <iostream>
#include <chrono>
#include <random>
#include <vector>

using namespace std;

std::vector<int> generatedArray(int n)
{
    std::vector<int> arr;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, n);

    for (int i = 0; i < n; i++)
    {
        arr.push_back(dist(gen));
    }
    return arr;
}
std::vector<int> merge(const std::vector<int> &left, const std::vector<int> &right)
{
    std::vector<int> result;
    int leftInd = 0;
    int rightInd = 0;
    while (leftInd < left.size() && rightInd < right.size())
    {
        if (left[leftInd] < right[rightInd])
        {
            result.push_back(left[leftInd]);
            leftInd++;
        }
        else
        {
            result.push_back(right[rightInd]);
            rightInd++;
        }
    }
    while (leftInd < left.size())
    {
        result.push_back(left[leftInd]);
        leftInd++;
    }
    while (rightInd < right.size())
    {
        result.push_back(right[rightInd]);
        rightInd++;
    }
    return result;
}

std::vector<int> mergeSort(std::vector<int> arr)
{
    if (arr.size() <= 1)
    {
        return arr;
    }
    int midIndex = arr.size() / 2;
    std::vector<int> left;
    std::vector<int> right;
    for (int i = 0; i < midIndex; i++)
    {
        left.push_back(arr[i]);
    }
    for (int i = midIndex; i < arr.size(); i++)
    {
        right.push_back(arr[i]);
    }
    return merge(mergeSort(left), mergeSort(right));
}

void runTests()
{
    cout << "==============================================" << endl;
    cout << "     ФУНКЦИОНАЛЬНОЕ ТЕСТИРОВАНИЕ" << endl;
    cout << "     generatedArray, merge, mergeSort" << endl;
    cout << "==============================================" << endl;

    int passedTests = 0;
    int totalTests = 0;

    // =========================================================================
    // ТЕСТ 1: generatedArray - проверка размера и диапазона
    // =========================================================================
    cout << "\nТЕСТ 1: generatedArray (n=10)" << endl;
    totalTests++;
    vector<int> arr1 = generatedArray(10);
    cout << "Размер: " << arr1.size() << endl;
    cout << "Значения: {";
    for (int i = 0; i < arr1.size(); i++)
    {
        cout << arr1[i];
        if (i < arr1.size() - 1) cout << ", ";
    }
    cout << "}" << endl;

    bool test1Pass = (arr1.size() == 10);
    for (int i = 0; i < arr1.size(); i++)
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

    // =========================================================================
    // ТЕСТ 2: merge - слияние двух отсортированных векторов
    // =========================================================================
    cout << "\nТЕСТ 2: merge (два отсортированных вектора)" << endl;
    totalTests++;
    vector<int> left2 = {1, 3, 5};
    vector<int> right2 = {2, 4, 6};
    vector<int> merged2 = merge(left2, right2);
    cout << "Left: {1, 3, 5}" << endl;
    cout << "Right: {2, 4, 6}" << endl;
    cout << "Result: {";
    for (int i = 0; i < merged2.size(); i++)
    {
        cout << merged2[i];
        if (i < merged2.size() - 1) cout << ", ";
    }
    cout << "}" << endl;

    bool test2Pass = (merged2.size() == 6);
    int expected2[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < 6; i++)
    {
        if (merged2[i] != expected2[i]) test2Pass = false;
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
    // ТЕСТ 3: merge - слияние с пустым вектором
    // =========================================================================
    cout << "\nТЕСТ 3: merge (один пустой вектор)" << endl;
    totalTests++;
    vector<int> left3 = {1, 2, 3};
    vector<int> right3 = {};
    vector<int> merged3 = merge(left3, right3);
    cout << "Left: {1, 2, 3}" << endl;
    cout << "Right: {}" << endl;
    cout << "Result: {";
    for (int i = 0; i < merged3.size(); i++)
    {
        cout << merged3[i];
        if (i < merged3.size() - 1) cout << ", ";
    }
    cout << "}" << endl;

    bool test3Pass = (merged3.size() == 3 && merged3[0] == 1 && merged3[2] == 3);

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
    // ТЕСТ 4: mergeSort - сортировка неотсортированного массива
    // =========================================================================
    cout << "\nТЕСТ 4: mergeSort (неотсортированный массив)" << endl;
    totalTests++;
    vector<int> arr4 = {5, 2, 8, 1, 9, 3};
    vector<int> sorted4 = mergeSort(arr4);
    cout << "До: {5, 2, 8, 1, 9, 3}" << endl;
    cout << "После: {";
    for (int i = 0; i < sorted4.size(); i++)
    {
        cout << sorted4[i];
        if (i < sorted4.size() - 1) cout << ", ";
    }
    cout << "}" << endl;

    bool test4Pass = true;
    for (int i = 0; i < sorted4.size() - 1; i++)
    {
        if (sorted4[i] > sorted4[i + 1]) test4Pass = false;
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
    // ТЕСТ 5: mergeSort - уже отсортированный массив
    // =========================================================================
    cout << "\nТЕСТ 5: mergeSort (уже отсортированный массив)" << endl;
    totalTests++;
    vector<int> arr5 = {1, 2, 3, 4, 5};
    vector<int> sorted5 = mergeSort(arr5);
    cout << "До: {1, 2, 3, 4, 5}" << endl;
    cout << "После: {";
    for (int i = 0; i < sorted5.size(); i++)
    {
        cout << sorted5[i];
        if (i < sorted5.size() - 1) cout << ", ";
    }
    cout << "}" << endl;

    bool test5Pass = true;
    for (int i = 0; i < sorted5.size() - 1; i++)
    {
        if (sorted5[i] > sorted5[i + 1]) test5Pass = false;
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
    // ТЕСТ 6: mergeSort - массив из одного элемента
    // =========================================================================
    cout << "\nТЕСТ 6: mergeSort (один элемент)" << endl;
    totalTests++;
    vector<int> arr6 = {42};
    vector<int> sorted6 = mergeSort(arr6);
    cout << "До: {42}" << endl;
    cout << "После: {" << sorted6[0] << "}" << endl;

    if (sorted6.size() == 1 && sorted6[0] == 42)
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
        std::cout << "\nChoose which array to mergesort:\n";
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

            std::vector<int> arr;

            for (int i = 0; i < cnt; i++)
            {
                int num;
                std::cin >> num;
                arr.push_back(num);
            }
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<int> sortedArr = mergeSort(arr);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration =
                std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

            std::cout << "Sorted array:\n";
            for (int i = 0; i < cnt; i++)
                std::cout << sortedArr[i] << " ";

            std::cout << "\nTime: " << duration.count() << " nanoseconds\n";
            continue;
        }

        case 2:
        {
            int cnt = 10;
            std::vector<int> genArray = generatedArray(cnt);
            for (int i = 0; i < cnt; i++)
            {
                std::cout << genArray[i] << " ";
            }

            auto startGen = std::chrono::high_resolution_clock::now();
            std::vector<int> sortedArrRand = mergeSort(genArray);
            auto stopGen = std::chrono::high_resolution_clock::now();
            auto durationGen =
                std::chrono::duration_cast<std::chrono::nanoseconds>(stopGen - startGen);

            std::cout << "\nSorted array:\n";
            for (int i = 0; i < cnt; i++)
                std::cout << sortedArrRand[i] << " ";

            std::cout << "\nTime: " << durationGen.count() << " nanoseconds\n";
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
