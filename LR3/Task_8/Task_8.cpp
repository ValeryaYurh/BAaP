#include <iostream>
#include <cmath>
#include <string>

using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

double sum()
{
    
}

void help()
{
    cout << GREEN << "calc\tвыводит значение\n"
         << BYELLOW << "help\tвыводит дополнительную информацию\n"
         << BRED << "quit,exit\tвыходит из проекта" << endl;
}

int main()
{
    cout << BBLUE << "Добро пожаловать!" << endl
         << "Данный проект подготовлен Юргилевич Валерией" << RESET << endl
         << BYELLOW << "Необходимо написать программу, которая выводит все числа Армстронга, меньше введённого пользователем числа." << RESET << endl
         << "Введите" << BBLUE << " calc" << RESET << ", если хотите вывести значение;" << BBLUE << " help" << RESET << ", если нужна дополнительная информация" << endl
         << "Если хотитие закончить проект, введите" << BBLUE << " quit или exit" << endl;
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