#include "data.h"
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

void menu()
{
    cout << BBLUE << "===============Меню===============\n"
         << "0. Вывести меню\n"
         << "1. Ввести данные по звонкам\n"
         << "2. Просмотр звонков\n"
         << "3. Добавить звонок\n"
         << "4. Найти сумму звонков по городам\n"
         << "5. Удалить или изменить данные по звонку\n"
         << "6. Записать файл\n"
         << "7. Читать файл\n"
         << RESET;
    return;
}

void allInfCalls(InfCall *&call, int &size)
{
    int n;
    cout << BYELLOW << "Введите количество звонков: " << RESET;
    cin >> n;

    call = new InfCall[n];
    size = n;

    for (int i = 0; i < n; i++)
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string command;

        cout << GREEN << "============Звонок №" << i + 1 << "============\n"
             << RESET;
        cout << "Введите в каком виде будет писаться дата(n/s): ";
        getline(cin, command);
        if (command == "n")
        {
            call[i].isNumericDate = true;
            cout << BYELLOW << "Дата звонка(введите 0, если хотите закончить): " << RESET;
            cin >> call[i].date.number;
        }
        else if (command == "s")
        {
            call[i].isNumericDate = false;
            cout << BYELLOW << "Дата звонка(введите 0, если хотите закончить): " << RESET;
            cin.getline(call[i].date.fullDate, 20);
        }
        while (command != "s" and command != "n")
        {
            cout << BRED << "Такой команды не найдено. Попробуйте снова: " << RESET;
            getline(cin, command);
            cout << "\n";
        }

        cout << BYELLOW << "Код города: " << RESET;
        cin >> call[i].code;
        cout << "\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << BYELLOW << "Название города: " << RESET;
        getline(cin, call[i].city);
        cout << "\n";

        cout << BYELLOW << "Тариф(стоимоть звонка за минуту): " << RESET;
        cin >> call[i].tariff;
        cout << "\n";

        cout << BYELLOW << "Время звонка: " << RESET;
        cin >> call[i].lengthOfConversation;
        cout << "\n";

        cout << BYELLOW << "Номер телефона в этом городе: " << RESET;
        cin >> call[i].telephoneInCity;
        cout << "\n";

        cout << BYELLOW << "Номер телефона абонента: " << RESET;
        cin >> call[i].telephone;
        cout << "\n";
    }

    string answer;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << RESET << "Есть ли ещё звонки(y/n): ";
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
        cout << "Введите сколько ещё будет звонков: ";
        cin >> k;
        InfCall *newArr = new InfCall[size + k];

        for (int i = 0; i < size; i++)
            newArr[i] = call[i];

        delete[] call;
        call = newArr;

        for (int i = size; i < size + k; i++)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string command;

            cout << GREEN << "============Звонок №" << i + 1 << "============\n"
                 << RESET;
            cout << "Введите в каком виде будет писаться дата(n/s): ";
            getline(cin, command);
            if (command == "n")
            {
                call[i].isNumericDate = true;
                cout << BYELLOW << "Дата звонка(введите 0, если хотите закончить): " << RESET;
                cin >> call[i].date.number;
            }
            else if (command == "s")
            {
                call[i].isNumericDate = false;
                cout << BYELLOW << "Дата звонка(введите 0, если хотите закончить): " << RESET;
                cin.getline(call[i].date.fullDate, 20);
            }
            while (command != "s" and command != "n")
            {
                cout << BRED << "Такой команды не найдено. Попробуйте снова: " << RESET;
                getline(cin, command);
                cout << "\n";
            }

            cout << BYELLOW << "Код города: " << RESET;
            cin >> call[i].code;
            cout << "\n";

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << BYELLOW << "Название города: " << RESET;
            getline(cin, call[i].city);
            cout << "\n";

            cout << BYELLOW << "Тариф(стоимоть звонка за минуту): " << RESET;
            cin >> call[i].tariff;
            cout << "\n";

            cout << BYELLOW << "Время звонка: " << RESET;
            cin >> call[i].lengthOfConversation;
            cout << "\n";

            cout << BYELLOW << "Номер телефона в этом городе: " << RESET;
            cin >> call[i].telephoneInCity;
            cout << "\n";

            cout << BYELLOW << "Номер телефона абонента: " << RESET;
            cin >> call[i].telephone;
            cout << "\n";
        }

        size += k;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RESET << "Есть ли ещё звонки(y/n): ";
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

void printArr(InfCall *&call, int &size)
{
    cout << GREEN << "Данные по звонкам: " << "\n";
    for (int i = 0; i < size; i++)
    {

        cout << GREEN << "\n============Звонок №" << i + 1 << "============\n"
             << "Дата звонка: ";
        if (call[i].isNumericDate)
            cout
                << call[i].date.number << "\n";
        else
            cout << call[i].date.fullDate << "\n";

        cout << GREEN << "Код города: " << call[i].code
             << "\n"

             << "Название города: " << call[i].city
             << "\n"

             << "Тариф(стоимоть звонка за минуту): " << call[i].tariff
             << "\n"

             << "Время звонка: " << call[i].lengthOfConversation << " минут"
             << "\n"

             << "Номер телефона в этом городе: " << call[i].telephoneInCity
             << "\n"

             << "Номер телефона абонента: " << call[i].telephone
             << "\n";
    }
    return;
}

void addInfCalls(InfCall *&call, int &size)
{
    int n;
    cout << "Введите, сколько звонков хотите добавить: ";
    cin >> n;
    cout << "\n";

    InfCall *newArr = new InfCall[size + n];

    for (int i = 0; i < size; i++)
        newArr[i] = call[i];

    delete[] call;
    call = newArr;

    for (int i = size; i < size + n; i++)
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string command;

        cout << GREEN << "============Звонок №" << i + 1 << "============\n"
             << RESET;
        cout << "Введите в каком виде будет писаться дата(n/s): ";
        getline(cin, command);
        if (command == "n")
        {
            cout << BYELLOW << "Дата звонка(введите 0, если хотите закончить): " << RESET;
            cin >> call[i].date.number;
        }
        else if (command == "s")
        {
            cout << BYELLOW << "Дата звонка(введите 0, если хотите закончить): " << RESET;
            cin.getline(call[i].date.fullDate, 20);
        }
        while (command != "s" and command != "n")
        {
            cout << BRED << "Такой команды не найдено. Попробуйте снова: " << RESET;
            getline(cin, command);
            cout << "\n";
        }

        cout << BYELLOW << "Код города: " << RESET;
        cin >> call[i].code;
        cout << "\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << BYELLOW << "Название города: " << RESET;
        getline(cin, call[i].city);
        cout << "\n";

        cout << BYELLOW << "Тариф(стоимоть звонка за минуту): " << RESET;
        cin >> call[i].tariff;
        cout << "\n";

        cout << BYELLOW << "Время звонка: " << RESET;
        cin >> call[i].lengthOfConversation;
        cout << "\n";

        cout << BYELLOW << "Номер телефона в этом городе: " << RESET;
        cin >> call[i].telephoneInCity;
        cout << "\n";

        cout << BYELLOW << "Номер телефона абонента: " << RESET;
        cin >> call[i].telephone;
        cout << "\n";
    }

    size += n;

    return;
}

void sumCallsForCities(InfCall *&call, int &size)
{
    bool *processed = new bool[size]{false};

    double *sumArr = new double[size];
    int *lengthArr = new int[size];

    for (int i = 0; i < size; i++)
    {
        if (processed[i])
            continue;

        int length = 0;
        double sum = 0;

        for (int j = 0; j < size; j++)
        {
            if (call[i].city == call[j].city)
            {
                double aSum = call[j].tariff * call[j].lengthOfConversation;
                double aLength = call[j].lengthOfConversation;
                length += aLength;
                sum += aSum;
                processed[j] = true;
            }
        }
        sumArr[i] = sum;
        lengthArr[i] = length;

        cout << GREEN << "Длинна звонков по городу " << call[i].city << ": " << lengthArr[i] << " минут\n"
             << "Сумма за звонки по городу" << call[i].city << ": " << sumArr[i] << " рублей\n"
             << RESET;
    }

    delete[] sumArr;
    delete[] lengthArr;
    delete[] processed;

    return;
}

void delete_changeInfCall(InfCall *&call, int &size)
{
    int n;
    cout << "Введите номер звонка, у которого нужно изменить или удалить данные: ";
    cin >> n;
    cout << "\n";
    while (n > size)
    {
        cout << BRED << "Такого звонка нет. Всего " << size << " звоноков. Попробуйте снова: " << RESET;
        cin >> n;
    }

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
        string command;

        cout << GREEN << "============Звонок №" << n - 1 << "============\n"
             << RESET;
        cout << "Введите в каком виде будет писаться дата(n/s): ";
        getline(cin, command);
        if (command == "n")
        {
            cout << BYELLOW << "Дата звонка(введите 0, если хотите закончить): " << RESET;
            cin >> call[n - 1].date.number;
        }
        else if (command == "s")
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << BYELLOW << "Дата звонка(введите 0, если хотите закончить): " << RESET;
            cin.getline(call[n - 1].date.fullDate, 20);
        }
        while (command != "s" and command != "n")
        {
            cout << BRED << "Такой команды не найдено. Попробуйте снова: " << RESET;
            getline(cin, command);
            cout << "\n";
        }

        cout << BYELLOW << "Код города: " << RESET;
        cin >> call[n - 1].code;
        cout << "\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << BYELLOW << "Название города: " << RESET;
        getline(cin, call[n - 1].city);
        cout << "\n";

        cout << BYELLOW << "Тариф(стоимоть звонка за минуту): " << RESET;
        cin >> call[n - 1].tariff;
        cout << "\n";

        cout << BYELLOW << "Время звонка: " << RESET;
        cin >> call[n - 1].lengthOfConversation;
        cout << "\n";

        cout << BYELLOW << "Номер телефона в этом городе: " << RESET;
        cin >> call[n - 1].telephoneInCity;
        cout << "\n";

        cout << BYELLOW << "Номер телефона абонента: " << RESET;
        cin >> call[n - 1].telephone;
        cout << "\n";
    }
    else if (restriction == "d")
    {
        InfCall *newArr = nullptr;
        if (size - 1 > 0)
        {
            newArr = new InfCall[size - 1];
            int idx = 0;
            for (int i = 0; i < size; i++)
            {
                if (i == n - 1)
                    continue;
                newArr[idx++] = call[i];
            }
        }

        delete[] call;
        call = newArr;
        size = size - 1;
        cout << GREEN << "Звонок удалён.\n"
             << RESET;
    }
}

void writeFile(InfCall *&call, int &size)
{
    ofstream outFile("../Task_2/InfCalls.txt", ios::out | ios::trunc);

    if (!outFile.is_open())
    {
        cout << BRED << "Ошибка: не удалось создать/открыть файл InfCalls.txt\n"
             << RESET;

        return;
    }

    for (int i = 0; i < size; i++)
    {
        outFile << (call[i].isNumericDate ? "n" : "s") << "\n";

        if (call[i].isNumericDate)
            outFile << call[i].date.number << "\n";
        else
            outFile << call[i].date.fullDate << "\n";

        outFile << call[i].code << endl;
        outFile << call[i].city << endl;
        outFile << call[i].tariff << endl;
        outFile << call[i].lengthOfConversation << endl;
        outFile << call[i].lengthOfConversation << endl;
        outFile << call[i].telephoneInCity << endl;
        outFile << call[i].telephone << endl;
    }
    outFile.close();

    ifstream check("../Task_2/InfCalls.txt");
    if (check.good() && size > 0)
    {
        cout << GREEN << "Данные (" << size << " записей) сохранены в InfCalls.txt\n"
             << RESET;
    }
    else if (size == 0)
    {
        cout << GREEN << "Файл создан, но данных для сохранения нет\n"
             << RESET;
    }
    else
    {
        cout << BRED << "Ошибка: файл не был создан\n"
             << RESET;
    }
    check.close();
}

void readFile(InfCall *&call, int &size)
{
    ifstream inFile("../Task_2/InfCalls.txt");
    if (!inFile)
    {
        cout << "Ошибка открытия InfCalls.txt\n";
        size = 0;
        call = nullptr;
        return;
    }

    size = 0;
    call = nullptr;
    InfCall temp;

    string type;

    while (true)
    {
        if (!getline(inFile, type))
            break;

        if (type == "n")
        {
            temp.isNumericDate = true;
            inFile >> temp.date.number;
            inFile.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (type == "s")
        {
            temp.isNumericDate = false;
            inFile.getline(temp.date.fullDate, 20);
        }
        else
            break;

        inFile >> temp.code;
        inFile.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!getline(inFile, temp.city))
            break;

        inFile >> temp.tariff;
        inFile >> temp.lengthOfConversation;
        inFile >> temp.lengthOfConversation;
        inFile >> temp.telephoneInCity;
        inFile >> temp.telephone;
        inFile.ignore(numeric_limits<streamsize>::max(), '\n');

        InfCall *newArr = new InfCall[size + 1];
        for (int i = 0; i < size; i++)
            newArr[i] = call[i];

        newArr[size] = temp;

        delete[] call;
        call = newArr;
        size++;
    }

    inFile.close();
    cout << "Количество звонков: " << size << "\n";

    return;
}