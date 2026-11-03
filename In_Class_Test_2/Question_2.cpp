#include <cmath>

class function_manipulation {
public:
    double findRoot(double (*f)(double), double a, double b, int maxIter) {
        double tol = 1e-6;
        double c;
        for (int i = 0; i < maxIter; ++i) {
            c = (a + b) / 2;
            // cout << c << ":" << f(c) << endl; Debuggin
            if (fabs(f(c)) < tol) {
                return c;
            }
            if (f(a) * f(c) < 0) {
                b = c;
            } else {
                a = c;
            }     
        }
        return c;
    }

    double trapesium_rule(double (*f)(double), double a, double b, int n) {
        double integral = 0.0;
        double h = (b - a) / n;
        for (double x = a; x < (b-h); x += h) {
            integral += (f(x) + f(x+h)) / 2 * h;
        }
        return integral;
    }
};