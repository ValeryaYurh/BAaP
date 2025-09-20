#include <iostream>
#include <cmath>
using namespace std;

int main(){
  int n, m;
  double A, D, x, K, Y;
  cout << "Ввести x, n, m, K: ";
  cin >> x >> n >> m >> K;
  D = tan(x);
  A = abs(n + m);
  Y = 1.29 + (K/A) + pow(D, 2);
  cout << "Y = " << Y;
  return 0;
}