#include "sumodd.h"

int get_even_sum(int *array, int m, int n)
{
    int sum_even = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (array[i * n + j] % 2 == 0)
            {
                sum_even += array[i * n + j];
            }
        }
    }
    return sum_even;
}

int get_odd_product(int *array, int m, int n)
{
    int product_odd = 1;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (array[i * n + j] % 2 != 0)
            {
                product_odd *= array[i * n + j];
            }
        }
    }
    return product_odd;
}