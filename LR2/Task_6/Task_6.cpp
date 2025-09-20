#include <iostream>
#include <cmath>
using namespace std;

int main(){
  double A, B, C, D, K, p, x, Y;
  cout << "Ввести x, p, K, C, D: ";
  cin >> x >> p >> K >> C >> D;
  A = x + sin(p);
  B = exp(K);
  Y = 1 + (pow(K, 2)/2*A*B) -B + (D*C);
  cout << "Y = " << Y;
  return 0;
}