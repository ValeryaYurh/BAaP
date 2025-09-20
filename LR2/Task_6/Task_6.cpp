#include <iostream>
#include <cmath>
using namespace std;

int main(){
  double A, B, D, C, x, y, K, z, T;
  cout << "Ввести x, y, z, K, C, D: ";
  cin >> x >> y >> z >> K >> C >> D;
  B = sqrt(z);
  A = x - y;
  T = cos(x) + pow(A, 2)/(K - (C*D)) - B;
  cout << "T = " << T;
  return 0;
}