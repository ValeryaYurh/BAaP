#include <iostream>
#include <cmath>
using namespace std;

int main(){
  int h;
  double x, p, A, B, C, D, K, Y;
  cout << "Ввести x, p, h, K, C, D: ";
  cin >> x >> p >> h >> K >> C >> D;
  A = x - p;
  B = log(h);
  Y = 0.78 * B + pow(A, 3)/(K*C*D);
  cout << "Y = " << Y;
  return 0;
}
  