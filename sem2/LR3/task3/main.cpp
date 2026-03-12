#include <iostream>

int reverseNum(int n, int &m)
{
    if (n/10==0)
    {
        return n%10;
    }
    int t=reverseNum(n/10, m);
    m*=10;
    return t+(n%10)*m;
}

int main(int argc, char const *argv[])
{
    int number;
    int m=1;
    std::cout << "Enter number to reverse:";
    std::cin>>number;

    std::cout << "Reversed number: " << reverseNum(number, m) << std::endl;
    return 0;
}
