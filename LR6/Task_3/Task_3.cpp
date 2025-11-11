#include <iostream>
#include <cstdio>
#include <limits>
#include "res.h"
using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

void sum()
{
    int n;
    cout << "Количество слов в массиве: ";
    cin >> n;
    while (n <= 0)
    {
        cout << BRED << "Количество слов должно быть строго положительное. Введите заново: ";
        cin >> n;
    }
    int m = 20;
    char **str = new char *[n];
    for (int i = 0; i < n; i++)
    {
        str[i] = new char[m];
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Введите " << n << " слов(-а): ";
    for(int i =0; i < n; i++)
    {
        cin.getline(str[i], m);
    }

    cout << GREEN << "Исходный массив: ";
    for (int i = 0; i < n; i++)
    {
        cout << str[i] << " ";
    }
    cout << RESET << endl;

    res(str, n);

    for (int i = 0; i < n; i++)
        delete[] str[i];
    delete[] str;

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
         << BYELLOW << "В строке, состоящей из групп нулей и единиц, разделенных пробелами, найти количество групп с пятью цифрами. " << RESET << endl
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