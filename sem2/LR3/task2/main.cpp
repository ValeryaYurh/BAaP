#include <iostream>

int A(int m, int n)
{
    if (m == 0)
    {
        return n + 1;
    }
    else if (n == 0)
    {
        return A(m - 1, 1);
    }
    else
    {
        return A(m - 1, A(m, n - 1));
    }
}

int main(int argc, char const *argv[])
{
    int m, n;
    std::cout << "Enter m:";
    std::cin >> m;
    std::cout << "Enter n:";
    std::cin >> n;
    std::cout << "Akkerman function result: " << A(m, n) << std::endl;
    return 0;
}
