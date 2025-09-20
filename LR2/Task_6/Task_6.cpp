#include <iostream>
#include <cmath>
using namespace std;

int main(){
  int A, Y, C, x, y;
  double D, K, S;
  cout << "Ввести x, y, C, K: ";
  cin >> x >> y >> C >> K;
  A = x + y;
  D = abs(C-A);
  S = 10.1 + (A/C) + D/pow(K, 2);
  cout << "S = " << S;
  return 0;
}
  