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
    double x;
    cout << BYELLOW << "Ввести x(0.1-1): ";
    cin >> x;
    int n;
    cout << BBLUE << "Ввести n: ";
    cin >> n;
    double y = x * atan(x) - log(sqrt(1 + x * x));
    double s = 0;
    for (int i = 1; i <= n; i++)
    {
        s += pow(-1, (i + 1)) * pow(x,(2 * i))/(2 * i * (2 * i - 1));
    }
    cout << GREEN << "При x: " << x << "\tY(x): " << y << "\tS(x): " << s << endl;
    return s;
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
         << BYELLOW << "Необходимо разложить функцию Y(x) из своего варианта в ряд S(x), затем с помощью полученного ряда найти значение функции и сравнить его со значением, вычисленным с помощью стандартных функций. " << RESET << endl
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