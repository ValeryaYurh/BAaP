#include <iostream>
using namespace std;

int main(){
    double X, Y;
    cout << "Ввести X, Y: ";
    cin >> X >> Y;
    bool condition = X>Y;
    condition ?  cout << "Х - максималльное значение" : cout << "Y - максимальное значение";
    return 0;
}