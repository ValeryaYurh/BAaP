#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int x1, x2, x3, y1, y2, y3;
    double p, P, cr, cR, sfr, sr, sR, s, sfR, l1, l2, l3, m1, m2, m3, h1, h2, h3, b1, b2, b3, r, R, deg1, deg2, deg3, rad1, rad2, rad3;
    cout << "(x1, x2, x3, y1, y2, y3): ";
    cin >>  x1 >> x2 >> x3 >> y1 >> y2 >> y3;
    l1 = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
    l3 = sqrt(pow(x3-x1, 2) + pow(y3-y1, 2));
    l2 = sqrt(pow(x3-x2, 2) + pow(y3-y2, 2));
    p = (l1 + l2 + l3)/2;
    s = sqrt(p*(p-l1)*(p-l2)*(p-l3));
    r = s/p;
    R = l1*l2*l3/(4*s);
    sfr = p*r;
    sfR = l1*l2*l3/(4*R);
    P = p*2;
    sr = M_PI*M_PI*r;
    sR = M_PI*M_PI*R;
    cr = 2*M_PI*r;
    cR = 2*M_PI*R;
    h1 = s*2/l1;
    h2 = s*2/l2;
    h3 = s*2/l3;
    m1 = 0.5*sqrt(2*pow(l2, 2) + 2*pow(l3, 2) - pow(l1, 2));
    m2 = 0.5*sqrt(2*pow(l1, 2) + 2*pow(l3, 2) - pow(l2, 2));
    m3 = 0.5*sqrt(2*pow(l1, 2) + 2*pow(l2, 2) - pow(l3, 2));
    b1 = 2*sqrt(l2*l3*p*(p-l1))/(l2+l3);
    b2 = 2*sqrt(l1*l3*p*(p-l2))/(l1+l3);
    b3 = 2*sqrt(l2*l1*p*(p-l3))/(l2+l1);
    deg1 = acos((l2*l2 + l3*l3 - l1*l1) / (2*l2*l3));
    deg2 = acos((l1*l1 + l3*l3 - l2*l2) / (2*l1*l3));
    deg3 = acos((l2*l2 + l1*l1 - l3*l3) / (2*l2*l1));
    rad1 = deg1*180/M_PI;
    rad2 = deg2*180/M_PI;
    rad3 = deg3*180/M_PI;
    cout << "Длины всех сторон треугольника: " << "l1 = " << l1 << " " << "l2 = " << l2 << " " << "l3 = " << l3 << endl;
    cout << "Длины всех высот треугольника: " << "h1 = " << h1 << " " << "h2 = " << h2 << " " << "h3 = " << h3 << endl;
    cout << "Длины всех медиан треугольника: " << "m1 = " << m1 << " " << "m2 = " << m2 << " " << "m3 = " << m3 << endl;
    cout << "Длины всех биссектрис треугольника: "<< "b1 = " << b1 << " " << "b2 = " << b2 << " " << "b3 = " << b3 << endl;
    cout << "Градусная и радианная мера углов треугольника: "<< "deg1, rad1 = " << deg1 << ", " << rad1 << " " << "deg2, rad2 = " << deg2 << ", " << rad2 << " " <<"deg3, rad3 = " << deg3 << ", " << rad3 << endl;
    cout << "Радиусы вписанной и описанной окружностей треугольника: "<< "r, R = " << r << ", " << R << endl;
    cout << "Площадь и длина этих окружностей: " << "sr, cr = " << sr << ", " << cr << " " << "sR, cR = " << sR << ", " << cR << endl;
    cout << "Площадь и периметр треугольника: " << "s = " << s << " " << "sfr = " << sfr << " " << "sfR = " << sfR << " " << "P = " << P << endl ;
    return 0;
}