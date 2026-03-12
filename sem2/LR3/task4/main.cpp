#include <iostream>

void hanoi(int n, char start, char dest, char addit)
{
    if (n>0)
    {
        hanoi(n-1, start, addit, dest);
        std::cout<<"Disk "<<n<<" moved from stick "<<start<<" to "<<dest<<"\n";
        hanoi(n-1, addit, dest, start);
    }
}

int main(int argc, char const *argv[])
{
    int n;
    std::cout << "Enter number of rings: ";
    std::cin>>n;
    hanoi(n, 'A', 'C', 'B');
    return 0;
}
