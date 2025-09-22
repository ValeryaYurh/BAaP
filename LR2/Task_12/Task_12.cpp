#include <iostream>

int main() {
    double p, q;
    std::cout << "Enter p q: ";
    std::cin >> p >> q;

    double eps = 1e-3;
    bool found = false;

    for (double x = -100; x <= 100; x += 0.001) {
        double val = x*x*x + p*x + q;
        if (val > -eps && val < eps) {
            std::cout << "x = " << x << "\n";
            found = true;
        }
    }

    if (!found) std::cout << "No real solutions found in [-100,100]\n";

    return 0;
}