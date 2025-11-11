#include "res.h"
#include <iostream>
#define GREEN "\033[32m"
#define RESET "\033[0m"
using namespace std;


int *sum_el(char **arr,  int n)
{
    int *sums = new int[n];
    for(int i = 0; i < n; i++)
    {
        int sum = 0;
        for(int j =0; arr[i][j]!='\0'; j++)
        {
           sum+=(int)arr[i][j];
        }
        sums[i] = sum;
    }
    return sums;
}

void res(char **arr, int n)
{
    int *sum = sum_el(arr, n);
    for(int i = 0; i < n ; i++)
    {
        if(sum[i]%2 == 0)
        {
            int len = 0;
            while(arr[i][len]!='\0') len++;
            for(int j = 0; j < len/2; j++)
            {
                char temp = arr[i][j];
                arr[i][j] = arr[i][len-j -1];
                arr[i][len -j -1] = temp;
            }
        }
    }

    cout << GREEN << "Итоговый массив: ";
    for(int  i=0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << RESET << endl;

    delete[] sum;
}