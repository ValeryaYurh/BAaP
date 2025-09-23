#include <iostream>
using namespace std;

double PI = 3.14159265358979323846;

// Абсолютное значение
double my_abs(double x) {
    return (x < 0) ? -x : x;
}

double my_sqrt(double x) {
    if (x <= 0) return 0;
    double guess = x;
    if (guess < 1) guess = 1; // нормализация
    for (int i = 0; i < 50; i++) {
        double prev = guess;
        guess = 0.5 * (guess + x / guess);
        if (my_abs(guess - prev) < 1e-12) break;
    }
    return guess;
}

double my_acos(double x) {
    if (x <= -1) return PI;
    if (x >= 1) return 0;
    // аппроксимация полиномом (погрешность ~1e-3)
    double negate = (x < 0);
    x = my_abs(x);
    double ret = -0.0187293;
    ret = ret * x;
    ret = ret + 0.0742610;
    ret = ret * x;
    ret = ret - 0.2121144;
    ret = ret * x;
    ret = ret + 1.5707288;
    ret = ret * my_sqrt(1.0 - x);
    if (negate) return PI - ret;
    return ret;
}

int main(){
    int x1, x2, x3, y1, y2, y3;
    double p, P, cr, cR, sfr, sr, sR, s, sfR, l1, l2, l3, m1, m2, m3, h1, h2, h3, b1, b2, b3, r, R, deg1, deg2, deg3, rad1, rad2, rad3;
    cout << "(x1, x2, x3, y1, y2, y3): ";
    cin >>  x1 >> x2 >> x3 >> y1 >> y2 >> y3;
    l1 = my_sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    l3 = my_sqrt((x3-x1)*(x3-x1) + (y3-y1)*(y3-y1));
    l2 = my_sqrt((x3-x2)*(x3-x2) + (y3-y2)*(y3-y2));
    p = (l1 + l2 + l3)/2;
    s = my_sqrt(p*(p-l1)*(p-l2)*(p-l3));
    r = s/p;
    R = l1*l2*l3/(4*s);
    sfr = p*r;
    sfR = l1*l2*l3/(4*R);
    P = p*2;
    sr = PI*PI*r;
    sR = PI*PI*R;
    cr = 2*PI*r;
    cR = 2*PI*R;
    h1 = s*2/l1;
    h2 = s*2/l2;
    h3 = s*2/l3;
    m1 = 0.5*my_sqrt(2*l2*l2 + 2*l3*l3 - l1*l1);
    m2 = 0.5*my_sqrt(2*l1*l1 + 2*l3*l3 - l2*l2);
    m3 = 0.5*my_sqrt(2*l1*l1 + 2*l2*l2 - l3*l3);
    b1 = 2*my_sqrt(l2*l3*p*(p-l1))/(l2+l3);
    b2 = 2*my_sqrt(l1*l3*p*(p-l2))/(l1+l3);
    b3 = 2*my_sqrt(l2*l1*p*(p-l3))/(l2+l1);
    deg1 = my_acos((l2*l2 + l3*l3 - l1*l1) / (2*l2*l3));
    deg2 = my_acos((l1*l1 + l3*l3 - l2*l2) / (2*l1*l3));
    deg3 = my_acos((l2*l2 + l1*l1 - l3*l3) / (2*l2*l1));
    rad1 = deg1*180/PI;
    rad2 = deg2*180/PI;
    rad3 = deg3*180/PI;
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