#include <iostream>
#include <cstdio>
#include <limits>
#include "find.h"
using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

void sum()
{
  char str[81];
  char ch;
  int i =0;
  cout << BBLUE << "Ввести элементы массива, это должны быть группы из 0 и 1, разделенных пробелами: " << RESET;
  while((ch = getchar()) != '\n' and i<80)
  {
    while(ch != '0' and ch != '1' and ch != ' ')
    {
      cout << BRED << "Элемент должен быть либо 0, либо 1. Введите элемент заново: " << RESET;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      ch = getchar();
    }
    str[i] = ch;
    i++;
  }
  int n = i;
  str[i] = '\0'; 
  cout << BYELLOW << "Исходный массив: ";
  for(int j = 0; j < n; j++)
  {
    cout << str[j];
  }
  cout << endl;
  cout << GREEN << "Количество групп с пятью цифрами: " << find(str, n) << RESET << endl;
  
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
       << BYELLOW << "В строке, состоящей из групп нулей и единиц, разделенных пробелами, найти количество групп с пятью цифрами. " << RESET << endl
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