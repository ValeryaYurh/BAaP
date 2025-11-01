#include <iostream>
#include "search_switch.h"
using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

int search(double **array, int n, int k)
{
    int count = 0;
    cout << GREEN << "Элементы равные нулю: "; 
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (array[i][j] == 0)
            {
                count += 1;
                cout << "a[" << i << "]" << "[" << j << "]" << "   ";
            }
        }
    }
    cout << "\n"
         << "Количество элементов, равных нулю: " << count << RESET << endl;
    return count;
}

void switch_el(double **array, int n, int k)
{
    cout << GREEN << "Обратный порядок элементов: " << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            int i2 = n - 1 - i;
            int j2 = k - 1 - j;

            // Чтобы не обменять один и тот же элемент дважды:
            if (i * k + j >= i2 * k + j2)
                break;

            double temp = array[i][j];
            array[i][j] = array[i2][j2];
            array[i2][j2] = temp;
        }
    }
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
    cout << RESET;

    return;
}