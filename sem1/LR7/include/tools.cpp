#include "tools.h"
#include <cmath>
#include <iostream>
#include <string> 

using namespace std;

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define BYELLOW "\033[93m"

//O((logn)^2)
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

//O(n)
int *complement(int *arr, int size)
{
    int *c = new int[size];

    if (arr[0] == 0)
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

//O(n)
int *twos_complement(int *arr, int size)
{
    int *res = new int[size];

    for (int i = 0; i < size; i++)
        res[i] = arr[i];

    if (arr[0] == 0)
    {
        for (int i = 0; i < size; i++)
        {
            res[i] = arr[i];
        }
    }
    else
    {
        for (int i = size - 1; i >= 1; i--)
        {
            if (res[i] == 0)
            {
                res[i] = 1;
                break;
            }
            else
            {
                res[i] = 0;
            }
        }
    }

    return res;
}

//O(n)
int *summy(int *arr1, int *arr2, int size)
{
    int *result = new int[size];
    int carry = 0;

    for (int i = size - 1; i >= 0; i--)
    {
        int sum = arr1[i] + arr2[i] + carry;
        result[i] = sum % 2;
        carry = sum / 2;
    }

    return result;
}

//O(n)
char *bin_char(int *arr, int size)
{
    char *bin_char = new char[size + 1];

    for (int i = 0; i < size; i++)
    {
        bin_char[i] = arr[i] + '0';
    }

    bin_char[size] = '\0';

    return bin_char;
}

//O(logn)
char* dec_to_oct_char(int num, int &size)
{
    bool isNegative = num < 0;
    num = abs(num);

    int n = num;
    size = 0;
    while (n > 0)
    {
        n /= 8;
        size++;
    }

    char* oct = new char[size + 1]; 
    oct[size] = '\0';

    for (int i = size - 1; i >= 0; i--)
    {
        oct[i] = '0' + (num % 8);
        num /= 8;
    }

    return oct;
}

//O(logn)
char *sum_oct(int num1, int num2, int size)
{
    int sum = num1+num2;

    char *summy_oct = dec_to_oct_char(sum, size);

    return summy_oct;
}

//O(logn)
char *dif_oct(int num1, int num2, int size)
{
    int dif = num1-num2;

    char *difference_oct = dec_to_oct_char(dif, size);

    return difference_oct;
}


//O(logn)
char* dec_to_hex_char(int num, int &size)
{
    bool isNegative = num < 0;
    num = abs(num);

    int n = num;
    size = 0;
    while (n > 0)
    {
        n /= 16;
        size++;
    }

    char* hex = new char[size + 1];
    hex[size] = '\0';

    for (int i = size - 1; i >= 0; i--)
    {
        int remainder = num % 16;
        if (remainder < 10)
            hex[i] = '0' + remainder;
        else
            hex[i] = 'A' + (remainder - 10); 

        num /= 16;
    }
    
    return hex;
}

//O(n)
int* encodeBase3(int barrel, int size)
{
    int* digits = new int[size];
    for (int i = 0; i < size; i++)
    {
        digits[i] = barrel % 3;
        barrel /= 3;
    }
    return digits;
}

//O(n)
int decodeBarrel(bool* died1, bool* died2, int size)
{
    int barrel = 0;
    int power = 1;

    for (int i = 0; i < size; i++)
    {
        int digit = 0;
        if (died1[i]) digit = 1;
        else if (died2[i]) digit = 2;

        barrel += digit * power;
        power *= 3;
    }
    return barrel;
}

// получение вводимых результатов
//O(n)
void getExperimentalResults(bool* died1, bool* died2, int size)
{
    cout << BYELLOW << "Введите результаты:" << RESET << endl;

    for (int i = 0; i < size; i++)
    {
        char response;
        cout << "Раб " << i + 1 << " умер в День 1? (y/n): ";
        cin >> response;

        died1[i] = (response == 'y' || response == 'Y');

        if (!died1[i])
        {
            cout << "Раб " << i + 1 << " умер в День 2? (y/n): ";
            cin >> response;
            died2[i] = (response == 'y' || response == 'Y');
        }
        else died2[i] = false;
    }
}

//O(n * logn)
bool isDivisibleBy(int n, int d)
{
    int temp = n;
    while (temp >= d)
    {
        int diff = 0, carry;
        int a = temp, b = (~d + 1);
        while (b != 0)
        {
            carry = (a & b) << 1;
            a = a ^ b;
            b = carry;
        }
        temp = a;
    }
    return temp == 0;
}