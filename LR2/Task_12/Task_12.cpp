#include <iostream>

int main() {
    double a, b, c;
    std::cout << "Enter a b c: ";
    std::cin >> a >> b >> c;

    double A = 1;
    double B = b / a;
    double C = c / a - 2;

    double D = B*B - 4*A*C;

    if (D < 0) {
        std::cout << "No real solutions\n";
        return 0;
    }

    double y1 = (-B + sqrt(D)) / (2*A);
    double y2 = (-B - sqrt(D)) / (2*A);

    for (int i = 0; i < 2; ++i) {
        double y = (i == 0) ? y1 : y2;
        double disc = y*y - 4;
        if (disc < 0) continue;

        double x1 = (y + sqrt(disc)) / 2;
        double x2 = (y - sqrt(disc)) / 2;

        std::cout << "x = " << x1 << " and x = " << x2 << "\n";
    }

    return 0;
}