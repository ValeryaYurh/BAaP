#include <iostream>
void intToBin(int n){
    if (n>1)
    {
       intToBin(n/2);
    }
    std::cout<<n%2;
    
}
void fracToBinary(double frac) {
    if ( frac == 0.0) {
        return;
    }
    frac *= 2;
    int bit = static_cast<int>(frac);
    std::cout << bit;
    fracToBinary(frac - bit);
}
int main(){
    double num;
     if (!(std::cin >> num)) {
        std::cerr << "Ошибка: введите корректное число.\n";
        return 1;
    }
    intToBin(static_cast<int>(num));
    std::cout<<".";
    fracToBinary(num-static_cast<int>(num));
    return 0;
}