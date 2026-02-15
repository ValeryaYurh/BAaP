#include <iostream>
using namespace std;
int main() {
    int x, y, z;
    cout << "Enter x: ";
    cin >> x;
    cout << "Enter y: ";
    cin >> y;
    cout << "Enter z: ";
    cin >> z;
    if(x + y > z and x + z > y and y + z > x) cout << "Треугольник существует";
    else cout << "Треугольник не существует";
    return 0;
}