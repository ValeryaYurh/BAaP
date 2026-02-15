#include <iostream>
#include "sum_sol.h"

using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

void sum()
{
    int n;
    cout << "Введите размер массивов: ";
    cin >> n;
    if(n<=0) 
    {
        cout << BRED << "Размер должен быть строго больше нуля. Введите заново: " << RESET << endl;
        cin >> n;
    }

    double *array_A = new double[n];

    double *array_B = new double[n];

    for (int i = 0; i < n; i++)
    {
        cout << BBLUE << "Ввести a[" << i << "]: " << RESET;
        cin >> array_A[i];
        cout << endl;
    }
    for (int j = 0; j < n; j++)
    {
        cout << BYELLOW <<  "Ввести b[" << j << "]: " << RESET;
        cin >> array_B[j];
        if(array_B[j] == 0)
        {
            cout << BRED << "На ноль делить нельзя, замените значение." << "\n" << RESET << "Ввести b[" << j << "]: ";
            cin >> array_B[j];
        }
        cout << endl;
    }
    for (int i = 0; i < n; i++)
    {
        double x = result(array_A[i], array_B[i]);
        cout << GREEN << "Значение x[" << i << "]: " << x << RESET << endl;
    }

    delete[] array_A;
    delete[] array_B;
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
         << "Данный проект подготовлен Юргилевич Валерией"  << endl
         << "Вариант 1" << RESET << endl
         << BYELLOW << "Составить программу для решения уравнения 𝑎𝑖𝑥+𝑏𝑗 =0, , где 𝑎𝑖 и 𝑏𝑗 – элементы динамических массивов, а при 𝑎𝑖 =0 переменной x присвоить значение 0, которое также вывести на экран. Использовать функции, размерность массивов ввести с клавиатуры, исходные данные ввести с клавиатуры." << RESET << endl
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