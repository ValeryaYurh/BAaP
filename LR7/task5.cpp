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



// Основная функция O(n)
void sum() {
    const int slaves = 5;
    const int maxBarrels = 240;

    bool* died1 = new bool[slaves];
    bool* died2 = new bool[slaves];

    for (int i = 0; i < slaves; i++)
    {
        died1[i] = false;
        died2[i] = false;
    }

    getExperimentalResults(died1, died2, slaves);

    int result = decodeBarrel(died1, died2, slaves);

    cout << GREEN << "\nОтравленная бочка: " << result << RESET << endl;

    if (result < 0 || result > maxBarrels)
        cout << BRED << "Ошибка! Номер бочки вне диапазона!" << RESET << endl;

    delete[] died1;
    delete[] died2;
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
       << BYELLOW << "Определение отравленной бочки. У Патриция 240 бочек вина и 5 рабов. Недоброжелатель отравил одну из бочек. " << RESET << endl
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