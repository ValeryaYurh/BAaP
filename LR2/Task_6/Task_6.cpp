#include <iostream>
#include <cmath>
using namespace std;

int main(){
  double x, p, A, B, z, C, D, K, Y;
  cout << "Ввести x, p, z, D, K, C: ";
  cin >> x >> p >> z >> D >> K >> C;
  A = sin(x) - z;
  B = abs(p-x);
  Y = pow(A+B, 2) - (K/(C*D));
  cout << "Y = " << Y;
  return 0;
}
  