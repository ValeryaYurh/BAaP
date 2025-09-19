#include <iostream>
using namespace std;

int main() {
    int X, Y, K;
    double A, B, C;
    cout << "Ввести X, Y, A, B, C, K: ";
    cin >> X >> Y >> A >> B >> C >> K;
    if(X==Y){
        Y=0;
        X=0;
    }else if (X>Y)
    {
        Y=0;
    }else if (Y>X)
    {
        X=0;
    }
    if(A>B and A>C){
        A = A - K;
    }else if(B>A and B>C){
        B = B - K;
    }else if(C>A and C>B){
        C = C - K;
    }
    cout << X << " " << Y << " " << A << " " << B << " " << C;
    return 0;
}