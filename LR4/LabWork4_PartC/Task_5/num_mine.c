#include "num_mine.h"

int num_mine(char **array, int m, int n, int i, int j)
{
    int k = 0;
    if (array[i][j] == '.') {
        if (j + 1 < m && array[i][j + 1] == '*') ++k;
        if (i + 1 < n && j + 1 < m && array[i + 1][j + 1] == '*') ++k;
        if (i + 1 < n && array[i + 1][j] == '*') ++k;
        if (i - 1 >= 0 && j - 1 >= 0 && array[i - 1][j - 1] == '*') ++k;
        if (j - 1 >= 0 && array[i][j - 1] == '*') ++k;
        if (i - 1 >= 0 && j + 1 < m && array[i - 1][j + 1] == '*') ++k;
        if (i - 1 >= 0 && array[i - 1][j] == '*') ++k;
        if (i + 1 < n && j - 1 >= 0 && array[i + 1][j - 1] == '*') ++k;
    }
    return k;
}