#include "dubelems.h"

int removeDuplicates(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                for (int l = j; l < n - 1; l++)
                {
                    arr[l] = arr[l + 1];
                }
                n--;
                j--;
            }
        }
    }
    return n;
}
