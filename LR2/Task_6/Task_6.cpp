#include <iostream>
#include <cmath>
using namespace std;

int main(){
  double x, k, A, B, z, C, D, Y;
  cout << "Ввести x, k, z, D, C: ";
  cin >> x >> k >> z >> D >> C;
  A = log(x) - k;
  B = sqrt(z);
  Y = pow(D, 2) + (pow(C, 2)/(0.75*A)) + B;
  cout << "Y = " << Y;
  return 0;
}
  