#include <iostream>
#include <iomanip> 
#include "receipt_calc.h"
using namespace std;

int calcWords(char *arr)
{
    int count = 0;
    for (int i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] != ' ' and (arr[i + 1] == ' ' or arr[i + 1] == '\0'))
            count++;
    }
    return count;
}

double costReceipt(char *arr)
{
    double costForOneWord = 0.065;
    int count = calcWords(arr);
    double cost = count * costForOneWord;

    return cost;
}

void receipt(char *arr)
{
    cout << "===================================" << endl
         << "             КВИТАНЦИЯ" << endl
         << "===================================" << endl
         << endl
         << endl
         << "Текст телеграммы:" << endl;
    for (int i = 0; arr[i] != '\0'; i++)
    {
        cout << arr[i];
    }
    cout << endl
         << endl
         << "Количество слов в телеграмме: " << calcWords(arr) << endl
         << "Cтоимость одного слова: 0.065 бел.рублей" << endl
         << "Cтоимость телеграммы: " << fixed << setprecision(2) << costReceipt(arr) << " бел.рублей" << endl
         << "===================================" << endl;

    return;
}