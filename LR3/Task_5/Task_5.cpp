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
    int n;
    cout << BBLUE << "Ввести на сколько частей разделить область поиска корня(n>0): ";
    cin >> n;
    double min_y = 1000;
    double min_x = -2;
    double i = -2;
    for (;i <= 2;)
    {
        double y = acos(exp(-pow(i + 1, 2))) + sin(i);
        double abs_y = abs(y);
        if (abs_y < min_y)
        {
            min_y = abs_y;
            min_x = i;
        }
        double step = 4.0 / n;
        i += step;
    }
    cout << GREEN << "При x: " << min_x << "\tМинимальное значение y: " << min_y << endl;
    return min_y;
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
         << BYELLOW << "Необходимо приближенно найти корень уравнения f(x) = 0 для функции из своего варианта. Корень нужно найти по следующему алгоритму: перебираем значения от начала до конца интервала с некоторым шагом и ищем значение функции, минимальное по модулю." << RESET << endl
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