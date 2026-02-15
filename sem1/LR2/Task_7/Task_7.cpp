#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double a = -13.8, b = 8.9, c = 25;
    double Y = 0;
    int N;
    cout << "Ввести N: ";
    cin >> N;
    switch (N) {
        case 2: 
            Y = b * c - a * a;
            break;
        case 56: 
            Y = b * c;
            break;
        case 7:
            Y = pow(a, 7) + c;
            break;
        case 3:
            Y = a - b * c;
            break;
        default:
            Y = pow(a + b, 3);
    }
    cout << Y << "\n";
    return 0;
}