#include <iostream>
using namespace std;

int main() {
   double b1, n, q, S;
   cout << "Ввести b1: ";
   cin >> b1;
   cout << "Ввести n: ";
   cin >> n;
   q = 1/(n + 1);
   S = b1/(1 - q);
   cout << "Cумма всех членов убывающей геометрической прогрессии = " << S;
return 0; 
}