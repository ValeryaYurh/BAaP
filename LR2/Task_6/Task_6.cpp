#include <iostream>
#include <cmath>
using namespace std;

int main(){
  double A, D, x, b, S;
  cout << "Ввести D, x: ";
  cin >> D >> x;
  b = x + D;
  A = D*x/b;
  S = (pow(A, 2) + b*cos(x))/(pow(D, 3) + (A + D - b));
  cout << "S = " << S;
}