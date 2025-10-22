#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

void sum(void)
{
    int n, m;
    printf(BBLUE "Введите количество строк n: ");
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("n должен быть строго больше\nВведите n: ");
        scanf("%d", &n);
    }

    printf(BBLUE "Введите количество столбцов m: ");
    scanf("%d", &m);
    if (m <= 0)
    {
        printf("m должен быть строго больше\nВведите m: ");
        scanf("%d", &m);
    }

    char **array = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        array[i] = (char *)malloc(m * sizeof(char));
    }

    printf(BYELLOW "Ввести игровое поле('*' - бомба, '.' - пустая клетка): \n");

    for (int i = 0; i < n; i++)
    {
        printf("\nСтрока %d: ", i + 1);
        for (int j = 0; j < m; j++)
        {
            scanf(" %c", &array[i][j]);
            if (array[i][j] != '.' && array[i][j] != '*')
            {
                printf(BRED "Данный символ не является элементом игрового поля\n" BYELLOW "Введите заново: ");
                scanf(" %c", &array[i][j]);
            }
        }
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int k = 0; // количество мин
            if (array[i][j] == '.')
            {
                if (j + 1 < m && array[i][j + 1] == '*')
                    ++k;
                if (i + 1 < n && j + 1 < m && array[i + 1][j + 1] == '*')
                    ++k;
                if (i + 1 < n && array[i + 1][j] == '*')
                    ++k;
                if (i - 1 >= 0 && j - 1 >= 0 && array[i - 1][j - 1] == '*')
                    ++k;
                if (j - 1 >= 0 && array[i][j - 1] == '*')
                    ++k;
                if (i - 1 >= 0 && j + 1 < m && array[i - 1][j + 1] == '*')
                    ++k;
                if (i - 1 >= 0 && array[i - 1][j] == '*')
                    ++k;
                if (i + 1 < n && j - 1 >= 0 && array[i + 1][j - 1] == '*')
                    ++k;
            }
            if (k > 0)
                array[i][j] = k + '0';
        }
    }

    printf(GREEN "Схема сапёра: \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%c", array[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++)
    {
        free(array[i]);
    }
    free(array);
}

void help(void)
{
    printf(GREEN "calc\tвыводит значение\n" BYELLOW "help\tвыводит дополнительную информацию\n" BRED "quit,exit\tвыходит из проекта\n");
}

int main(void)
{
    printf(BBLUE "Добро пожаловать!\n"
                 "Данный проект подготовлен Юргилевич Валерией" RESET "\n" BYELLOW "На вход подаётся поле для игры в 'сапёр' размером n*m символов, где символ '.' означает пустое место, а символ '*' - бомбу. Требуется дополнить это поле числами, как в оригинальной игре." RESET "\n"
                 "Введите" BBLUE " calc" RESET ", если хотите вывести значение;" BBLUE " help" RESET ", если нужна дополнительная информация\n"
                 "Если хотите закончить проект, введите" BBLUE " quit или exit\n" RESET);

    while (1)
    {
        char command[10]; 
        printf(BYELLOW "Введите команду: " RESET);
        scanf("%9s", command);

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