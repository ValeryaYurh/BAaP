#include <iostream>
using namespace std;

int main(){
  int x;
  cout << "Enter x:";
  cin >> x;
  int x2 = x * x;
  int v1 = 69 * x2 + 8;
  int v2 = x* ( 23 * x2 + 32);
  cout << "v1 + v2 = " << v1 + v2 << "\n";
  cout << "v1 - v2 = " << v1 - v2 << "\n";
  
  return 0;
}