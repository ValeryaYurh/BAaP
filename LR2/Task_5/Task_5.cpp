#include <iostream>
using namespace std;

int main(){
    double X, Y;
    cout << "Ввести X, Y: ";
    cin >> X >> Y;
    if(X>Y){ 
        cout << "Х - максималльное значение"; 
    }else{
      cout << "Y - максимальное значение";
    }
    return 0;
}