#include <iostream>
#include <string>
#include <limits>
#include "include/tools.h"
using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

void sum()
{
  int num;
  cout << "Введите число: ";
  cin >> num;
  int size = 0;
  int *bin = binary(num, size);

  cout << GREEN << "Прямой код: ";
  for (int i = 0; i < size; i++)
  {
    cout << bin[i];
  }
  cout << endl;

  int *c = complement(bin, size);
  cout << GREEN << "Обратный код: ";
  for (int i = 0; i < size; i++)
  {
    cout << c[i];
  }
  cout << RESET
       << endl;


  delete[] bin;
  delete[] c;

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
       << "Данный проект подготовлен Юргилевич Валерией" << endl
       << "Вариант 1" << RESET << endl
       << BYELLOW << "Из прямого кода в обратный. " << RESET << endl
       << "Введите" << BBLUE << " 1" << RESET << ", если хотите вывести значение;" << BBLUE << " 2" << RESET << ", если нужна дополнительная информация" << endl
       << "Если хотитие закончить проект, введите" << BBLUE << " 3 или 4" << endl;
  while (true)
  {
    int command;
    cout << BYELLOW << "Введите команду: " << RESET;
    cin >> command;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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