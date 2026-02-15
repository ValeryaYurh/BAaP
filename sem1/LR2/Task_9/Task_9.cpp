#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int n, x, z, f, a, d;
    double y;
    cout << "Ввести n, z, a, d: ";
    cin >> n >> z >> a >> d;
    y = 2 * f * (a*sin(x) + (d*exp(-x-3)));
    if(z>0){
       x = -3 * z;
    }else{
        x = pow(z, 2);
    }
    switch(n){
      case 1:
        f = 2 * x;
        cout << "При f(x) = 2x y = " << y;
        break;
      case 2:
        f = pow(x, 3);
        cout << "При f(x) = x^3 y = " << y;
        break;
      case 3:
        f =  x/3;
        cout << "При f(x) = x/3 y = " << y;
        break;
      default:
        break;
    }
    return 0;
}