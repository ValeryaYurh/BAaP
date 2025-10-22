#include <iostream>
using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

void sum()
{
    int n;
    cout << BBLUE << "Введите порядок массива N: ";
    cin >> n;
    if (n <= 0)
    {
        cout << BRED << "Число должно быть строго больше нуля. Измените значение: ";
        cin >> n;
    }
    int ***array = new int **[n];
    for (int i = 0; i < n; ++i)
    {
        array[i] = new int *[n];
        for (int j = 0; j < n; ++j)
        {
            array[i][j] = new int[n];
        }
    }
    cout << BYELLOW << "Ввести элементы подмассива: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Слой " << i + 1 << ": ";
        for (int j = 0; j < n; j++)
        {
            cout << "Строка " << j + 1 << ": ";
            for (int k = 0; k < n; k++)
                cin >> array[i][j][k];
        }
    }

    cout << GREEN << "Итоговый массив: ";
    for (int i = 0; i < n; i++)
    {
        cout << "\n"
             << "Cлой " << i + 1 << ": ";
        for (int j = 0; j < n; j++)
        {
            cout << "\n"
                 << "Cтрока " << j + 1 << ": ";
            for (int k = 0; k < n; k++)
            {
                cout << array[i][j][k];
                cout << " ";
            }
        }
    }

    long long max_diag = 1;
    int sum_diag = 0;
    for (int i = 0; i < n; i++)
    {
        sum_diag += array[i][i][i];
    }

    int sum_diag2 = 0;

    for (int i = 0; i < n; i++)
    {
        sum_diag2 += array[i][i][n - 1 - i];
    }

    int sum_diag3 = 0;

    for (int i = 0; i < n; i++)
    {
        sum_diag3 += array[i][n - 1 - i][i];
    }

    int sum_diag4 = 0;

    for (int i = 0; i < n; i++)
    {
        sum_diag4 += array[n - 1 - i][i][i];
    }

    int *diags = new int[4];
    diags[0]=sum_diag;
    diags[1]=sum_diag2;
    diags[2]=sum_diag3;
    diags[3]=sum_diag4;

    for (int i = 0; i < 4; i++)
    {
        if (diags[i + 1] > diags[i])
        {
            max_diag = diags[i + 1];
        }
    }

    cout << GREEN << endl
         << "Наибольшая диагональ равна: " << max_diag << endl;
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
         << "Вариант 15" << endl
         << BYELLOW << "В данном проекте нужно инициализировать при объявлении статический двумерный массив целых чисел размером MxN. Подсчитать сумму четных элементов и произведение нечётных элементов матрицы и вывести на экран исходные данные и полученный результат." << RESET << endl
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