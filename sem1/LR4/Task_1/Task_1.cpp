#include <iostream>
#include "dubelems.h"

using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

void sum()
{
    int k;
    cout << BBLUE << "Введите количество элементов массива: ";
    cin >> k;

    int array[100];
    cout << BBLUE << "Введите элементы массива: ";
    for (int i = 0; i < k; i++)
    {
        cin >> array[i];
    }

    cout << GREEN << "Исходный массив: ";
    for (int i = 0; i < k; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;

    k = removeDuplicates(array, k);

    cout << GREEN << "Итоговый массив: ";
    for (int i = 0; i < k; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

void help()
{
    cout << GREEN << "calc\tвыводит значение\n"
         << BYELLOW << "help\tвыводит дополнительную информацию\n"
         << BRED << "quit,exit\tвыходит из проекта" << RESET << endl;
}

int main()
{
    cout << BBLUE << "Добро пожаловать!" << endl
         << "Данный проект подготовлен Юргилевич Валерией" << RESET << endl
         << "Вариант 15" << endl
         << BYELLOW << "В данном проекте нужно Ввести одномерный статический массив из k чисел. Удалить из массива повторяющиеся элементы и вывести на экран исходные данные и полученный результат." << RESET << endl
         << "Введите" << BBLUE << " calc" << RESET << ", если хотите вывести значение;" 
         << BBLUE << " help" << RESET << ", если нужна дополнительная информация" << endl
         << "Если хотите закончить проект, введите" << BBLUE << " quit или exit" << RESET << endl;

    while (true)
    {
        string command;
        cout << BYELLOW << "Введите команду: " << RESET;
        cin >> command;

        if (command == "calc")
        {
            sum();
        }
        else if (command == "help")
        {
            help();
        }
        else if (command == "quit" || command == "exit")
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
