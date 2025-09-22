#include <iostream>
using namespace std; 

int main(){
    int a, b, c;
    double x1, x2, x3, x4, y1, y2, D;
    cout << "Ввести a, b, c: ";
    cin >> a >> b >> c;
    D = b*b - 4*a*c;
    if(D>=0){
        y1 = (-b + sqrt(D))/(2*a);
        y2 = (-b - sqrt(D))/(2*a);
         if(y1>=0 or y2>=0){
          x1 = sqrt(y1);
          x2 = -x1;
          x3 = sqrt(y2);
          x4 = -x3;
          cout << "Корни уравнения: " << x1 << " " << x2 << " " << x3 << " " << x4;
          }else{
            cout << "Корней нет"; 
         }
    }else{
        cout << "Корней нет";
    }
    return 0;
}