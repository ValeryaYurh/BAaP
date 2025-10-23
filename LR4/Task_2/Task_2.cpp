#include <iostream>
#include "sumodd.h"
using namespace std;

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

void sum()
{
  int m, n;
  cout << BBLUE << "Введите M(количесиво элементов массива): ";
  cin >> m;
  if(m<=0) 
  {
    cout << BRED << "Число должно быть строго больше нуля. Измените значение: ";
    cin >> m;
  }
  cout << BBLUE << "Введите N(количество элементов подмассива): ";
  cin >> n;
  if(n<=0) 
  {
    cout << BRED << "Число должно быть строго больше нуля. Измените значение: ";
    cin >> n;
  }
  int array[100][100];
  cout << BYELLOW << "Ввести элементы подмассива: " << endl; 
  for(int i = 0; i < m; i++)
  {
    cout << "Подмассив " << i+1 << ": ";
    for(int j=0; j < n; j++)
    {
        cin >> array[i][j];
    }
  }
  cout << GREEN << "Итоговый массив: ";
  for(int i = 0; i < m; i++)
  {
    cout << "\n";
    for(int j=0; j < n; j++)
    {
       cout << array[i][j] << " ";
    }
  }

  cout << GREEN << "\n"
       <<"Сумма чётных элементов равна: " << get_even_sum(*array, m, n) << endl
       << "Произведение нечётных равно: " << get_odd_product(*array, m, n) << endl;

  return;
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