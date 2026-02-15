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

//O(n)
void sum()
{
    int size;
    cout << "Введите длину чисeл: ";
    cin >> size;
    int *num1 = new int[size];
    for (int i = 0; i < size; i++)
    {
        cout << "Введите первое число в естественной форме(через 0 и 1): ";
        cin >> num1[i];
        while(num1[i] != 0 and num1[i] != 1)
        {
            cout << BRED << "Число должно состоять только из 0 и 1. Введите заново: " << RESET;
            cin >> num1[i];
        }
    }
    cout << endl;

    int *num2 = new int[size];
    for (int i = 0; i < size; i++)
    {
        cout << "Введите втрое число в естественной форме(через 0 и 1): ";
        cin >> num2[i];
        while(num2[i] != 0 and num2[i] != 1)
        {
            cout << BRED << "Число должно состоять только из 0 и 1. Введите заново: " << RESET;
            cin >> num2[i];
        }
    }
    cout << endl;

    cout << GREEN << "Прямой код:\n";
    for (int i = 0; i < size; i++)
    {
        cout << num1[i];
    }
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        cout << num2[i];
    }
    cout << RESET
         << endl;

    int *c1 = complement(num1, size);
    int *c2 = complement(num2, size);
    cout << GREEN << "Обратный код:\n";
    for (int i = 0; i < size; i++)
    {
        cout << c1[i];
    }
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        cout << c2[i];
    }
    cout << RESET
         << endl;

    int *res1 = twos_complement(c1, size);
    int *res2 = twos_complement(c2, size);
    cout << GREEN << "Дополнительный код:\n";
    for (int i = 0; i < size; i++)
    {
        cout << res1[i];
    }
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        cout << res2[i];
    }
    cout << RESET
         << endl;

    int *result = summy(res1, res2, size);
    cout << GREEN << "Итоговая сумма: ";
    for (int i = 0; i < size; i++)
    {
        cout << result[i];
    }
    cout << endl;

    delete[] result;
    delete[] res1;
    delete[] res2;
    delete[] c1;
    delete[] c2;
    delete[] num1;
    delete[] num2;


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
         << "Данный проект подготовлен Юргилевич Валерией" << endl
         << "Вариант 1" << RESET << endl
         << BYELLOW << "Найдите сумму двоичных чисел, заданных в естественной форме. Сложение выполните в дополнительном коде. Ответ выразите в прямом коде. " << RESET << endl
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