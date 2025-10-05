#include <iostream>
#include <string>

using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

double mySin(double x)
{
    double term = x;
    double sum = 0.0;
    int sign = 1;

    for (int n = 1; n <= 10; ++n)
    {
        sum += sign * term;
        term = term * x * x / ((2 * n) * (2 * n + 1));
        sign = -sign;
    }

    return sum;
}

double myAbs(double x)
{
    return (x < 0) ? -x : x;
}

double myLn(double x)
{
    if (x <= 0)
        return -1e9;

    int k = 0;
    while (x > 2.0)
    {
        x /= 2.718281828;
        k++;
    }
    while (x < 0.5)
    {
        x *= 2.718281828;
        k--;
    }

    double y = x - 1;
    double term = y;
    double sum = 0.0;
    int sign = 1;

    for (int n = 1; n <= 20; ++n)
    {
        sum += sign * term / n;
        term *= y;
        sign = -sign;
    }

    return sum + k;
}

double myCos(double x)
{

    const double PI = 3.141592653589793;
    while (x > PI)
        x -= 2 * PI;
    while (x < -PI)
        x += 2 * PI;

    double sum = 0.0;
    int sign = 1;

    for (int n = 0; n < 10; ++n)
    {
        double term = 1;

        for (int i = 1; i <= 2 * n; ++i)
            term *= x / i;
        sum += sign * term;
        sign = -sign;
    }

    return sum;
}

double sum()
{
    double a, b, c, x;
    cout << BBLUE << "Ввести x: " << RESET;
    cin >> x;
    a = mySin(x);
    b = myCos(x);
    c = myLn(myAbs(x));
    if (a < b and a < c)
    {
        cout << GREEN << "При x= " << x << "\tМинимальное значение равно = " << a << endl;
    }
    else if (b < a and b < c)
    {
        cout << GREEN << "При x= " << x << "\tМинимальное значение равно = " << b << endl;
    }
    else if (c < b and c < a)
    {
        cout << GREEN << "При x= " << x << "\tМинимальное значение равно = " << c << endl;
    }
    return 0;
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
         << BYELLOW << "Из величин, определяемых выражениями a = sinx, b = cosx, c = ln|x| при заданном х, определить и вывести на экран дисплея минимальное значение." << RESET << endl
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