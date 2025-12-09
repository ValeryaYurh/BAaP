#include "customer.h"
#include <iostream>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

void allCustomers(Customer *&person, int &size)
{
    int n;
    cout << BYELLOW << "Введите количество клиентов: " << RESET;
    cin >> n;

    person = new Customer[n];
    size = n;

    for (int i = 0; i < n; i++)
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << GREEN;

        cout << "============Клиент №" << i + 1 << "============\n";
        cout << BYELLOW << "ФИО(или 's' для остановки): " << RESET;
        getline(cin, person[i].name);
        if (person[i].name == "s")
        {
            size = i;
            return;
        }
        cout << "\n";

        cout << BYELLOW << "Домашний адрес: " << RESET;
        getline(cin, person[i].address);
        cout << "\n";

        cout << BYELLOW << "Размер предоставляемой скидки(%): " << RESET;
        cin >> person[i].discount.percent;
        cout << "\n";
    }

    string answer;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << RESET << "Есть ли ещё клиенты(y/n): ";
    getline(cin, answer);
    while (answer != "y" and answer != "n")
    {
        cout << BRED << "Вы ввели неверную команду. Попробуйте заново: ";
        getline(cin, answer);
    }
    cout << "\n";

    while (answer == "y")
    {
        int k;
        cout << "Введите сколько ещё будет клиентов: ";
        cin >> k;
        Customer *newArr = new Customer[size + k];

        for (int i = 0; i < size; i++)
            newArr[i] = person[i];

        delete[] person;
        person = newArr;

        for (int i = size; i < size + k; i++)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << GREEN;

            cout << "============Клиент №" << i + 1 << "============\n";
            cout << BYELLOW << "ФИО(или 's' для остановки): " << RESET;
            getline(cin, person[i].name);
            if (person[i].name == "s")
                return;
            cout << "\n";

            cout << BYELLOW << "Домашний адрес: " << RESET;
            getline(cin, person[i].address);
            cout << "\n";

            cout << BYELLOW << "Размер предоставляемой скидки(%): " << RESET;
            cin >> person[i].discount.percent;
            cout << "\n";
        }

        size += k;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RESET << "Есть ли ещё клиенты(y/n): ";
        getline(cin, answer);
        while (answer != "y" and answer != "n")
        {
            cout << BRED << "Вы ввели неверную команду. Попробуйте заново: ";
            getline(cin, answer);
        }
        cout << "\n";
    }

    return;
}

void printArr(Customer *&person, int &size)
{
    cout << GREEN << "Данные по клиентам: " << "\n";
    for (int i = 0; i < size; i++)
    {
        cout << GREEN << "============Клиент №" << i + 1 << "============\n";
        cout << "ФИО: " << person[i].name;
        cout << "\n";

        cout << "Домашний адрес: " << person[i].address;
        cout << "\n";

        cout << "Размер предоставляемой скидки(%): " << person[i].discount.percent << RESET;
        cout << "\n";
    }
    return;
}

void addCustomers(Customer *&person, int &size)
{
    int n;
    cout << "Введите, сколько клиентов хотите добавить: ";
    cin >> n;
    cout << "\n";

    Customer *newArr = new Customer[size + n];

    for (int i = 0; i < size; i++)
        newArr[i] = person[i];

    delete[] person;
    person = newArr;

    for (int i = size; i < size + n; i++)
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << GREEN;

        cout << "============Клиент №" << i + 1 << "============\n";
        cout << BYELLOW << "ФИО(или 's' для остановки): " << RESET;
        getline(cin, person[i].name);
        if (person[i].name == "s")
        {
            size = i;
            return;
        }
        cout << "\n";

        cout << BYELLOW << "Домашний адрес: " << RESET;
        getline(cin, person[i].address);
        cout << "\n";

        cout << BYELLOW << "Размер предоставляемой скидки(%): " << RESET;
        cin >> person[i].discount.percent;
        cout << "\n";
    }

    size += n;

    return;
}

void findCustomer(Customer *&person, int &size)
{
    int num;
    int a = 0;
    cout << "Введите процент, по которому будем искать: ";
    cin >> num;
    cout << "\n";

    for (int i = 0; i < size; i++)
    {
        if (num == person[i].discount.percent)
        {
            cout << GREEN << "Клиент найден!\n";
            cout << GREEN << "============Клиент №" << i + 1 << "============\n";
            cout << "ФИО: " << person[i].name;
            cout << "\n";

            cout << "Домашний адрес: " << person[i].address;
            cout << "\n";

            cout << "Размер предоставляемой скидки(%): " << person[i].discount.percent << RESET;
            cout << "\n";
            a += 1;
        }
    }
    if (a == 0)
    {
        cout << BRED << "Таких клиентов нет.";
        cout << "\n";
    }
    else
    {
        cout << GREEN << "Таких клиентов: " << a;
        cout << "\n";
    }
    return;
}

void delete_changeCustomer(Customer *&person, int &size)
{
    int n;
    cout << "Введите номер клиента, у которого нужно изменить или удалить данные: ";
    cin >> n;
    cout << "\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string restriction;
    cout << "Введите указания(c/d): ";
    getline(cin, restriction);
    while (restriction != "c" and restriction != "d")
    {
        cout << BRED << "Вы ввели неверную команду. Попробуйте заново: ";
        getline(cin, restriction);
    }
    cout << "\n";

    if (restriction == "c")
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << BYELLOW << "ФИО: " << RESET;
        getline(cin, person[n - 1].name);
        cout << "\n";

        cout << BYELLOW << "Домашний адрес: " << RESET;
        getline(cin, person[n - 1].address);
        cout << "\n";

        cout << BYELLOW << "Размер предоставляемой скидки(%): " << RESET;
        cin >> person[n - 1].discount.percent;
        cout << "\n";
    }
    else if (restriction == "d")
    {
        Customer *newArr = nullptr;
        if (size - 1 > 0)
        {
            newArr = new Customer[size - 1];
            int idx = 0;
            for (int i = 0; i < size; i++)
            {
                if (i == n - 1)
                    continue;
                newArr[idx++] = person[i];
            }
        }

        delete[] person;
        person = newArr;
        size = size - 1;
        cout << GREEN << "Клиент удалён.\n"
             << RESET;
    }
}

void writeFile(Customer *&person, int &size)
{
    ofstream outFile("customers.txt");
    for (int i = 0; i < size; i++)
    {
        outFile << person[i].name << endl;
        outFile << person[i].address << endl;
        outFile << person[i].discount.percent << endl;
    }
    outFile.close();
    cout << GREEN << "Данные сохранены в customers.txt\n"
         << RESET;
}

void readFile(Customer *&person, int &size)
{
    ifstream inFile("customers.txt");

    if (!inFile)
    {
        cout << BRED << "Ошибка открытия customers.txt\n"
             << RESET;
        size = 0;
        person = nullptr;
        return;
    }

    Customer temp;
    size = 0;
    person = nullptr;

    while (true)
    {
        if (!getline(inFile, temp.name))
            break;
        if (temp.name.empty())
            break;

        getline(inFile, temp.address);
        inFile >> temp.discount.percent;
        inFile.ignore(numeric_limits<streamsize>::max(), '\n');

        Customer *newArr = new Customer[size + 1];

        for (int i = 0; i < size; i++)
            newArr[i] = person[i];

        newArr[size] = temp;

        delete[] person;
        person = newArr;

        size++;
    }

    inFile.close();
    cout << GREEN << "Количество клиентов: " << size << RESET << "\n";

    return;
}

void insertionSortByDiscount(Customer *&person, int &size)
{
    for (int i = 1; i < size; ++i)
    {
        Customer key = person[i];
        int keyDiscount = key.discount.percent;
        int j = i - 1;

        while (j >= 0 && person[j].discount.percent > keyDiscount)
        {
            person[j + 1] = person[j];
            j--;
        }

        person[j + 1] = key;
    }

    cout << GREEN << "Итоговые данные: \n";

    for (int i = 0; i < size; i++)
    {
        cout << GREEN << "============Клиент №" << i + 1 << "============\n";
        cout << "ФИО: " << person[i].name;
        cout << "\n";

        cout << "Домашний адрес: " << person[i].address;
        cout << "\n";

        cout << "Размер предоставляемой скидки(%): " << person[i].discount.percent << RESET;
        cout << "\n";
    }

    return;
}