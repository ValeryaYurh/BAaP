#include <iostream>
using namespace std;

int main() {
    int x1, y1, r1, x2, y2, r2;
    cout << "Ввести x1, y1, r1, x2, y2, r2: ";
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    double l = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    if(r2>r1+l){
        cout << "Да";
    }else if(r1>r2+l){
        cout << "Да, но справедливо обратное для двух фигур";
    }else if(l<=r1+r2){
        cout << "Фигуры пересекаются";
    }else{
        cout << "Ни одно условие не выполнено";
    }
    return 0;
}