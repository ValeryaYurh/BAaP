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

// Основная функция O(1)
void sum()
{
    int num;
    cout << "Введите число, которое будем проверять на делимость на 3, 37, 89: ";
    cin >> num;

    if (isDivisibleBy(num, 3) == true)
        cout << GREEN << "Число " << num << " делится на 3" << RESET << endl;
    else
        cout << BRED << "Число " << num << " не делится на 3" << RESET << endl;

    if (isDivisibleBy(num, 37) == true)
        cout << GREEN << "Число " << num << " делится на 37" << RESET << endl;
    else
        cout << BRED << "Число " << num << " не делится на 37" << RESET << endl;

    if (isDivisibleBy(num, 89) == true)
        cout << GREEN << "Число " << num << " делится на 89" << RESET << endl;
    else
        cout << BRED << "Число " << num << " не делится на 89" << RESET << endl;

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
         << "Вариант 1" << endl
         << BYELLOW << "Проверить, делится ли введенное пользователем число на заданное простое. " << RESET << endl
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