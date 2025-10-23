#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "magic_square.h"

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

// Функция для ввода n и вывода магического квадрата
void sum()
{
  int n;
  printf(BBLUE "Введите порядок квадрата N(нечётное число): " RESET);
  scanf("%d", &n);

  while (n <= 0 || n % 2 == 0)
  {
    printf(BRED "Число должно быть нечётное и строго больше нуля. Измените значение: " RESET);
    scanf("%d", &n);
  }

  int **array = magic_square(n);
  if (!array)
  {
    printf(BRED "Ошибка при создании магического квадрата.\n" RESET);
    return;
  }

  printf(GREEN "\nМагический квадрат:\n" RESET);
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      printf("%4d ", array[i][j]);
    printf("\n");
    free(array[i]);
  }
  free(array);
}

void help()
{
  printf(GREEN "calc\t" RESET "выводит значение\n");
  printf(BYELLOW "help\t" RESET "выводит дополнительную информацию\n");
  printf(BRED "quit, exit\t" RESET "выходит из проекта\n");
}

int main()
{
  printf(BBLUE "Добро пожаловать!\n" RESET);
  printf("Данный проект подготовлен Юргилевич Валерией\n");
  printf(BYELLOW "Построить магический квадрат. Порядок квадрата задаётся пользователем.\n" RESET);
  printf("Введите " BBLUE "calc" RESET ", если хотите вывести значение; ");
  printf(BBLUE "help" RESET ", если нужна дополнительная информация\n");
  printf("Если хотите закончить проект, введите " BBLUE "quit" RESET " или " BBLUE "exit\n" RESET);

  while (1)
  {
    char command[20];
    printf(BYELLOW "Введите команду: " RESET);
    scanf("%s", command);

    if (strcmp(command, "calc") == 0)
    {
      sum();
    }
    else if (strcmp(command, "help") == 0)
    {
      help();
    }
    else if (strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0)
    {
      return 0;
    }
    else
    {
      printf(BRED "Данная команда не найдена\n" RESET);
    }
  }

  return 0;
}
