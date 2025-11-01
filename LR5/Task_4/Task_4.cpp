#include <iostream>
#include "search_switch.h"
using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

void sum()
{
  int n;
  cout << BBLUE << "Введите количество строк в массиве: ";
  cin >> n;
  if (n <= 0)
  {
    cout << BRED << "Число должно быть строго больше нуля. Измените значение: ";
    cin >> n;
  }

  int k;
  cout << BBLUE << "Введите количество столбцов в массиве: ";
  cin >> k;
  if (k <= 0)
  {
    cout << BRED << "Число должно быть строго больше нуля. Измените значение: ";
    cin >> k;
  }

  double **array_A = new double *[n];
  for (int i = 0; i < n; i++)
  {
    array_A[i] = new double[k];
  }

  cout << "Ввести элементы массива: ";

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < k; j++)
    {
      cout << "a[" << i << "][" << j << "] = ";
      cin >> array_A[i][j];
      cout << "\n";
    }
  }

  cout << "Итоговый массив А: " << endl;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < k; j++)
    {
      cout << array_A[i][j] << " ";
    }
    cout << "\n";
  }
  cout << "\n";

  search(array_A, n, k);

  switch_el(array_A, n, k);

 
  for (int i = 0; i < n; i++)
    delete[] array_A[i];
  delete[] array_A;

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
       << BYELLOW << "Создать двумерный динамический массив вещественных чисел. Определить, встречаются ли среди них элементы с нулевым значением. Если встречаются такие элементы, то определить их индексы и общее количество. Переставить элементы этого массива в обратном порядке и вывести на экран. Использовать функции." << RESET << endl
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