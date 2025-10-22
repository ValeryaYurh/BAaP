#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

void sum()
{
  int n;
  printf(BBLUE "Введите порядок квадрата N(нечётное число): " RESET);
  scanf("%d", &n);

  if (n <= 0 || n > (pow(2, 32) - 1) || n % 2 == 0)
  {
    while(n<=0 || n%2==0){
    printf(BRED "Число должно быть нечётное и строго больше нуля. Измените значение: " RESET);
    scanf("%d", &n);
    }
  }

  int **array = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++)
  {
    array[i] = (int *)malloc(n * sizeof(int));
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      array[i][j] = 0;
    }
  }

  int i = n / 2;
  int j = n - 1;

  for (int num = 1; num <= n * n;)
  {
    if (i == -1 && j == n)
    {
      i = 0;
      j = n - 2;
    }
    else
    {
      if (i < 0)
        i = n - 1;
      if (j == n)
        j = 0;
    }

    if (array[i][j] != 0)
    {
      i += 1;
      j -= 2;
      continue;
    }
    else
    {
      array[i][j] = num++;
      i -= 1;
      j += 1;
    }
  }

  printf(GREEN "\nМагический квадрат:\n" RESET);
  for (int x = 0; x < n; x++)
  {
    for (int y = 0; y < n; y++)
    {
      printf("%4d ", array[x][y]);
    }
    printf("\n");
  }

  for (int i = 0; i < n; i++)
  {
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
  printf(BYELLOW "Построить магический квадрат. Порядок квадрата задаётся пользователем. Максимальный размер магического квадрата не превышает 2^32 - 1.\n" RESET);
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
