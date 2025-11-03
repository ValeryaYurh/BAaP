#include "check_sin.h"
#include <cmath> 

const double EPS = 1e-10;

bool any_sin_positive(double* A, int N)
{

    if (A == nullptr || N <= 0)
        return false;

    if (N == 1)
        return std::sin(A[0]) > EPS;

    int mid = N / 2;

    bool left = any_sin_positive(A, mid);                
    bool right = any_sin_positive(A + mid, N - mid);     


    return left || right;
}
