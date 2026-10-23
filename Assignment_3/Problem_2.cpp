#include <cmath>
#include <iostream>
using namespace std;

double Simpsons_1_3(double (*f)(double), double a, double b, int n) {
    if (n % 2 != 0) {
        n++; // Make sure n is even
    }
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    for (int i = 1; i < n; i++) {
        if (i % 2 == 0) {
            sum += 2 * f(a + i * h);
        } else {
            sum += 4 * f(a + i * h);
        }
    }
    return sum * h / 3;
}