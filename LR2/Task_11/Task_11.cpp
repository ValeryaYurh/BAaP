#include <iostream>
using namespace std;

int main(){
    int h1, h2, h, min1, min2, min;
    cout << "h1 = ";
    cin >> h1; 
    cout << "min1 = ";
    cin >> min1;
    cout << "Cколько времени показывали часы: " << h1 << ":" << min1 << "\n";
    cout << "h2 = "; 
    cin >> h2;
    cout << "min2 = ";
    cin >> min2;
    cout << "Время окончани: " << h2 << ":" << min2 << "\n";
    if(h2>=h1){
        h = h2 - h1;
    }else if(h1>h2){
        h = 24 - h1 + h2;
    }
    if(min2>=min1){
        min = min2 - min1;
    }else if(min1>min2){
        min = 60 - min1 + min2;
        h = h2 - h1 -1; 
    }
    cout << "Общее потраченное время: " << h << ":" << min;
    return 0;
}