#include <iostream>
#include <string>
#include <limits>
#include "customer.h"
using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

void sum()
{
    int size = 0;
    Customer *person = new Customer[size];
    menu();
    while (true)
    {
        int n;
        cout << BYELLOW << "Введите команду, которую хотите выполнить: " << RESET;
        cin >> n;
        switch (n)
        {
        case 0:
            menu();
            break;
        case 1:
            allCustomers(person, size);
            break;
        case 2:
            printArr(person, size);
            break;
        case 3:
            addCustomers(person, size);
            break;
        case 4:
            findCustomer(person, size);
            break;
        case 5:
            delete_changeCustomer(person, size);
            break;
        case 6:
            writeFile(person, size);
            break;
        case 7:
            readFile(person, size);
            break;
        case 8:
            insertionSortByDiscount(person, size);
            break;
        default:
            cout << BRED << "Данной команды не найдено.\n"
                 << RESET;
            return;
        }
    }

    delete[] person;
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
         << "Данный проект подготовлен Юргилевич Валерией" << RESET << endl
         << "Вариант 1" << RESET << endl
         << BYELLOW << "В магазине сформирован список постоянных клиентов, который включает ФИО, домашний адрес покупателя и размер предоставляемой скидки. Вывести всех покупателей, имеющих 5 % скидку. " << RESET << endl
         << "Введите" << BBLUE << " 1" << RESET << ", если хотите вывести значение;" << BBLUE << " 2" << RESET << ", если нужна дополнительная информация" << endl
         << "Если хотитие закончить проект, введите" << BBLUE << " 3 или 4" << endl;
    while (true)
    {
        int command;
        cout << BYELLOW << "Введите команду: " << RESET;
        cin >> command;
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