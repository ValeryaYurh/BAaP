#include <iostream>
#include "arr_average.h"
using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

int count(int **array, int n, int k)
{
     int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (array[i][j] % 2 and (j+1) % 2 == 0)
                count += 1;
        }
    }
    return count;
}

void new_arr(int **array1, int *array2, int n, int k)
{
    cout << GREEN << "Итоговый новый массив: ";
    
    int m = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (array1[i][j] % 2 and (j + 1) % 2 == 0)
            {

                array2[m] = array1[i][j];
                cout << array2[m] << " ";
                m++;
            }
        }
    }

    cout << RESET << endl;

    return;
}

void average(int *array, int n)
{
    if(n==0) 
    {
        cout << BRED << "Ошибка: нет подходящих элементов. Попробуйте заново." << endl;
        return;
    }
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += array[i];
    }
    double average = (double)sum / n;

    cout << GREEN << "Среднее арифметическое значений: " << average << RESET << endl;

    return;
}