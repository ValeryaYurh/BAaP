#include "magic_square.h"
#include <stdlib.h>

int** magic_square(int n)
{
    
    int **array = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        array[i] = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            array[i][j] = 0;

    int i = n / 2;
    int j = n - 1;

    for (int num = 1; num <= n * n;)
    {
        if (i == -1 && j == n)
        {
            i = 0;
            j = n - 2;
        }
        else
        {
            if (i < 0) i = n - 1;
            if (j == n) j = 0;
        }

        if (array[i][j] != 0)
        {
            i += 1;
            j -= 2;
            continue;
        }
        else
        {
            array[i][j] = num++;
            i -= 1;
            j += 1;
        }
    }

    return array;
}