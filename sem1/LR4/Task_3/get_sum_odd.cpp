#include "get_sum_odd.h"

int get_sum(int *array, int m, int n)
{
    int sum_even = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i >= j or i + j >= n - 1)
            {
                sum_even += array[i * n + j];
            }
        }
    }
    return sum_even;
}

int get_odd(int *array, int m, int n)
{
    long long product_odd = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i >= j or i + j >= n - 1)
            {
                product_odd *= array[i * n + j];
            }
        }
    }
    return product_odd;
}