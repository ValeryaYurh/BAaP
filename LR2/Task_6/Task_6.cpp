#include <iostream>
#include <cmath>
using namespace std;

int main(){
  double B, C, D, K, p, n, x, Q;
  cout << "Ввести p, n, x, D, K: ";
  cin >> p >> n >> x >> D >> K;
  B = cos(x);
  C = p - n;
  Q = pow(B, 2)/(K*D) + (B*pow(C, 3));
  cout << "Q = " << Q;
  return 0;
}