#include "sum_sol.h"

double result(double a, double b)
{
    double x{};
    if(a==0)
    {
        x = 0;
    }else if(a!=0)
    {
        x = -b/a;
    }
    return x;
}