#include <iostream>
#include <cmath>
#include <string>
using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

void sum()
{
    double m = 20.0;
    double a = 0.0;
    double b = M_PI / 2;
    double h = (b - a) / m;
    double y;
    for (double i = 0; a + i * h <= b; i++)
    {
        double x = a + i * h;
        y = sin(x) - cos(x);
        cout << GREEN << "Результат вычислений равен: " << y << "\t" << "при x: " << x << RESET << endl;
    }

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
         << BYELLOW << "В данном проекте нужно используя цикл for составить программу вычисления значений функции y = sin(x) - cos(x) на отрезке [A, B] в точках 𝑋𝑖 = 𝐴 + 𝑖 ∗ 𝐻,где H = (B - A) / M, M = 20, A = 0, B = π/2 " << endl
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