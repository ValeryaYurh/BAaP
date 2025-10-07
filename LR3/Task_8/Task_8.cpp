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
    int n, i, a, k;
    cout << BBLUE << "Ввести количество элементов n: ";
    cin >> n;
    cout << "Ввести последний элемент a: ";
    cin >> a;
    i = a;
    k = n - 1;
    long long int res{};

    for (; i >= a-k ; i-- and n--)
    {
        res += pow(2, (n - 1)) * pow((-1), (n - 1)) * i;
    }
    cout << GREEN << "Результат вычислений равен: " << res << endl;
    return res;
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
         << BYELLOW << "Необходимо Вычислить ao -2a1, +4a2 -8a3+…+2^(n-1)*(-1)^(n-1)*аn-1." << RESET << endl
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