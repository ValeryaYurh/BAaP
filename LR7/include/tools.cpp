#include "tools.h"
#include <cmath>
#include <iostream>

#define RESET "\033[0m"
#define GREEN "\033[32m"

int *binary(int a, int &size)
{
    bool isNegative = a < 0;
    a = abs(a);

    size = 0;
    int *bi_code = nullptr;

    if (a == 0)
    {
        bi_code = new int[1];
        bi_code[0] = 0;
        size = 1;
        return bi_code;
    }


    while (a > 0)
    {
        int k = a % 2;
        a /= 2;

        int *tmp = new int[size + 1];
        for (int i = 0; i < size; i++)
            tmp[i] = bi_code[i];

        tmp[size] = k;

        delete[] bi_code;
        bi_code = tmp;
        size++;
    }

    int *tmp = new int[size + 1];
    for (int i = 0; i < size; i++)
        tmp[i] = bi_code[i];

    tmp[size] = isNegative ? 1 : 0;

    delete[] bi_code;
    bi_code = tmp;
    size++;

    for (int i = 0; i < size / 2; i++)
    {
        int temp = bi_code[i];
        bi_code[i] = bi_code[size - 1 - i];
        bi_code[size - 1 - i] = temp;
    }

    return bi_code;
}

int *complement(int *arr, int size, int a)
{
    int* c = new int[size];

    if (a >= 0)
    {
        for (int i = 0; i < size; i++)
        {
            c[i] = arr[i];
        }
    }
    else
    {
        c[0] = arr[0];

        for (int i = 1; i < size; i++)
            c[i] = arr[i] == 0 ? 1 : 0;
    }

    return c;
}
