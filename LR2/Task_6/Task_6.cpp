#include <iostream>
#include <cmath>
using namespace std;

int main(){
  double x, d, A, B, C, K, Y;
  cout << "Ввести x, d, K, C: ";
  cin >> x >> d >> K >> C;
  A = log10(x);
  B = x + exp(d);
  Y = A+B - (pow(C, 2)/K);
  cout << "Y = " << Y;
  return 0;
}
  