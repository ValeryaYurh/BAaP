#include "max_diag.h"

int max_d(int *diags, int n)
{
    int max_diag = diags[0];
    for (int i = 1; i < 4; i++) {
        if (diags[i] > max_diag) {
            max_diag = diags[i];
        }
    }
    return max_diag;
}