#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BRED "\033[91m"
#define GREEN "\033[32m"
#define BBLUE "\033[94m"
#define RESET "\033[0m"
#define BYELLOW "\033[93m"

void sum() {
    int n;
    printf(BBLUE "Введите порядок массива N: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf(BRED "Число должно быть строго больше нуля. Измените значение: ");
        scanf("%d", &n);
    }
    
    // Выделение памяти для 3D массива
    int ***array = (int ***)malloc(n * sizeof(int **));
    for (int i = 0; i < n; ++i) {
        array[i] = (int **)malloc(n * sizeof(int *));
        for (int j = 0; j < n; ++j) {
            array[i][j] = (int *)malloc(n * sizeof(int));
        }
    }
    
    printf(BYELLOW "Ввести элементы подмассива: \n");
    for (int i = 0; i < n; i++) {
        printf("Слой %d: \n", i + 1);
        for (int j = 0; j < n; j++) {
            printf("Строка %d: ", j + 1);
            for (int k = 0; k < n; k++) {
                scanf("%d", &array[i][j][k]);
            }
        }
    }

    printf(GREEN "Итоговый массив: ");
    for (int i = 0; i < n; i++) {
        printf("\nCлой %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            printf("\nCтрока %d: ", j + 1);
            for (int k = 0; k < n; k++) {
                printf("%d ", array[i][j][k]);
            }
        }
    }

    long long max_diag = 0;
    int sum_diag = 0;
    for (int i = 0; i < n; i++) {
        sum_diag += array[i][i][i];
    }

    int sum_diag2 = 0;
    for (int i = 0; i < n; i++) {
        sum_diag2 += array[i][i][n - 1 - i];
    }

    int sum_diag3 = 0;
    for (int i = 0; i < n; i++) {
        sum_diag3 += array[i][n - 1 - i][i];
    }

    int sum_diag4 = 0;
    for (int i = 0; i < n; i++) {
        sum_diag4 += array[n - 1 - i][i][i];
    }

    int *diags = (int *)malloc(4 * sizeof(int));
    diags[0] = sum_diag;
    diags[1] = sum_diag2;
    diags[2] = sum_diag3;
    diags[3] = sum_diag4;

    max_diag = diags[0];
    for (int i = 1; i < 4; i++) {
        if (diags[i] > max_diag) {
            max_diag = diags[i];
        }
    }

    printf(GREEN "\nНаибольшая диагональ равна: %lld\n", max_diag);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            free(array[i][j]);
        }
        free(array[i]);
    }
    free(array);
    free(diags);
}

void help() {
    printf(GREEN "calc\tвыводит значение\n");
    printf(BYELLOW "help\tвыводит дополнительную информацию\n");
    printf(BRED "quit,exit\tвыходит из проекта\n");
}

int main() {
    printf(BBLUE "Добро пожаловать!\n");
    printf(RESET "Данный проект подготовлен Юргилевич Валерией\n");
    printf(BYELLOW "Дан трёхмерный динамический массив размером n^3 целых неотрицательных чисел. Необходимо определить диагональ с наибольшей суммой чисел. Для обхода диагоналей нельзя использовать вложенные циклы.\n" RESET);
    printf("Введите " BBLUE "calc" RESET ", если хотите вывести значение;" BBLUE " help" RESET ", если нужна дополнительная информация\n");
    printf("Если хотитие закончить проект, введите" BBLUE " quit или exit\n");
    
    while (1) {
        char command[10];
        printf(BYELLOW "Введите команду: " RESET);
        scanf("%s", command);
        
        if (strcmp(command, "calc") == 0) {
            sum();
        }
        else if (strcmp(command, "help") == 0) {
            help();
        }
        else if (strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0) {
            return 0;
        }
        else {
            printf(BRED "Данная команда не найдена\n" RESET);
        }
    }
    
    return 0;
}