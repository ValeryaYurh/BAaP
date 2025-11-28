#include <iostream>
#include <string>
#include <limits>
#include "include/tools.h"
using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

//O(logn)
void sum()
{
    int size = 0;
    int s = 0;
    int q;
    cout << "Введите разряд(2, 8, 10, 16): ";
    cin >> q;

    while(q!=2 and q!=10 and q!=8 and q!=16) 
    {
        cout << BRED << "Работаем только с 2, 8, 10, 16 системами. Введите заново: " << RESET;
        cin >> q;
    }

    int num1;
    cout << "Введите первое число(в десятичной): ";
    cin >> num1;

    int num2;
    cout << "Введите второе число(в десятичной): ";
    cin >> num2;

    int *num1_bin_int = binary(num1, size);
    char *num1_bin_char = bin_char(num1_bin_int, size);

    int *num2_bin_int = binary(num2, size);
    char *num2_bin_char = bin_char(num2_bin_int, size);

    switch (q)
    {
    case 16:
    {
        int size1 = 0;
        int size2 = 0;
        char *num1_hex = dec_to_hex_char(num1, size1);

        cout << GREEN << "Числа в шестнадцатеричной системе:\n";
        for (int i = 0; i < size1; i++)
        {
            cout << num1_hex[i];
        }
        cout << endl;

        char *num2_hex = dec_to_hex_char(num2, size2);

        cout << GREEN << "Числа в шестнадцатеричной системе:\n";
        for (int i = 0; i < size2; i++)
        {
            cout << num2_hex[i];
        }
        cout << endl;

        int sum = num1+num2;
        int dif = abs(num1-num2);

        cout << GREEN << "Сумма: ";
        char *res1 = dec_to_hex_char(sum, size);
        for(int i = 0; i < size; i++)
        {
            cout << res1[i];
        }
        cout << endl;

        cout << GREEN << "Разность: ";
        char *res2 = dec_to_hex_char(dif, size);
        for(int i = 0; i < size; i++)
        {
            cout << res2[i];
        }
        cout << RESET << endl;

        delete[] res1;
        delete[] res2;
        delete[] num2_hex;
        delete[] num1_hex;

        break;
    }
    case 10:
    {
        cout << GREEN << "Сумма: " << num1 + num2 << endl
             << "Разность: " << num1 - num2 << RESET << endl;
        break;
    }
    case 8:
    {
        int size1 = 0;
        int size2 = 0;
        char *num1_oct = dec_to_oct_char(num1, size1);

        cout << GREEN << "Числа в восьмеричной системе:\n";
        for (int i = 0; i < size; i++)
        {
            cout << num1_oct[i];
        }
        cout << endl;

        char *num2_oct = dec_to_oct_char(num2, size2);

        for (int i = 0; i < size; i++)
        {
            cout << num2_oct[i];
        }
        cout << endl;

        size = size1 > size2 ? size1 : size2;

        cout << "Сумма: ";

        char *res1 = sum_oct(num1, num2, size);

        for (int i = 0; i < size; i++)
        {
            cout << res1[i];
        }
        cout << endl;

        cout << "Разность: ";

        char *res2 = dif_oct(num1, num2, size);

        for (int i = 0; i < size; i++)
        {
            cout << res2[i];
        }
        cout << endl;

        delete[] res1;
        delete[] res2;
        delete[] num1_oct;
        delete[] num2_oct;

        break;
    }
    case 2:
    {
        int size1 =0;
        int size2 =0;
        int *num1_bin = binary(num1, size1);

        cout << GREEN << "Первое число: ";
        for(int i = 0; i < size1; i++)
        {
            cout << num1_bin[i]; 
        }
        cout << RESET << endl;

        int *num2_bin = binary(num2, size2);

        cout << GREEN << "Второе число: ";
        for(int i = 0; i < size2; i++)
        {
            cout << num2_bin[i]; 
        }
        cout << RESET << endl;

        int *res1 = summy(num1_bin_int, num2_bin_int, size);

        cout << GREEN << "Сумма: ";
        for (int i = 0; i < size; i++)
        {
            cout << res1[i];
        }
        cout << RESET << endl;

        cout << GREEN << "Разность: ";
        int dif = abs(num1 - num2);

        int *difference = binary(dif, size);
        for (int i = 0; i < size; i++)
        {
            cout << difference[i];
        }
        cout << RESET << endl;

        delete[] res1;
        delete[] difference;
        delete[] num2_bin;
        delete[] num1_bin;

        break;
    }
    default:
        break;
    }
      
        delete[] num1_bin_int;
        delete[] num2_bin_int;
        delete[] num1_bin_char;
        delete[] num2_bin_char;

        return;
    }

    void help()
    {
        cout << GREEN << "1\tвыводит значение\n"
             << BYELLOW << "2\tвыводит дополнительную информацию\n"
             << BRED << "3 или 4\tвыходит из проекта" << endl;
    }

    int main()
    {
        cout << BBLUE << "Добро пожаловать!" << endl
             << "Данный проект подготовлен Юргилевич Валерией" << RESET << endl
             << BYELLOW << "Пользователь вводит основание системы счисления. Осуществить сложение и вычитание чисел в заданной системе счисления. В другую систему счисления не переводить. В системах счисления больших десятичной использовать буквы по аналогии с шестнадцатеричной системой. Разработать функции для выполнения операции сложения и функции для выполнения операции вычитания. Предусмотреть ввод положительных и отрицательных чисел. " << RESET << endl
             << "Введите" << BBLUE << " 1" << RESET << ", если хотите вывести значение;" << BBLUE << " 2" << RESET << ", если нужна дополнительная информация" << endl
             << "Если хотитие закончить проект, введите" << BBLUE << " 3 или 4" << endl;
        while (true)
        {
            int command;
            cout << BYELLOW << "Введите команду: " << RESET;
            cin >> command;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (command == 1)
            {
                sum();
            }
            else if (command == 2)
            {
                help();
            }
            else if (command == 3 || command == 4)
            {
                return 0;
            }
            else
            {
                cout << BRED << "Данная команда не найдена" << RESET << endl;
            }
        }
        return 0;
    }