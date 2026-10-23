#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
using namespace std;

double f_prime_centrally(double (*f)(double), double x) {
    double h = 1e-6;
    return (f(x + h) - f(x - h)) / (2 * h);
}

double findRoot_bisection(double (*f)(double), double a, double b, int maxIter, bool save_error, bool iter_mode) {
    double tol = 1e-6;
    double c;
    ofstream outFile("output_bisection.dat", ios::app);
    if(save_error) {
        outFile << "Iteration Root Error" << endl;
    }
    for (int i = 0; i < maxIter; ++i) {
        c = (a + b) / 2;
        if (fabs(f(c)) < tol && !iter_mode) {
            return c;
        }
        if (f(a) * f(c) < 0) {
            b = c;
        } else {
            a = c;
        }
        if (save_error) {
            // Append fabs(f(c)) for debugging or analysis to .dat
            outFile << i << " " << -c << " " << fabs(f(c)) << endl;
        }        
    }
    outFile.close();
    return c;
}

double findRoot_secant(double (*f)(double), int maxIter, double xa, double xb, bool save_error, bool iter_mode) {
    // Secant method implementation
    double tol = 1e-6;
    double x2 = xb;
    ofstream outFile("output_secant.dat", ios::app);
    if(save_error) {
        outFile << "Iteration Root Error" << endl;
    }
    for (int i = 0; i < maxIter; ++i) {
        // Converged to machine precision: further steps would be 0/0
        if (xb == xa && not iter_mode) {
            break;
        }
        x2 =  (xb != xa) ? xb - f(xb) * (xb - xa) / (f(xb) - f(xa)): x2; // Division by zero check
        if (fabs(x2 - xb) < tol && !iter_mode) {
            return x2;
        }
        if (save_error) {
            // Append fabs(f(x2)) for debugging or analysis to .dat
            outFile << i << " " << -x2 << " " << fabs(f(x2)) << endl;
        }
        xa = xb;
        xb = x2;
    }
    outFile.close();
    return x2;
}

double findRoot_Newton_Raphson(double (*f)(double), double x0, int maxIter, bool save_error, bool iter_mode) {
    double tol = 1e-6;
    double x1;
    for (int i = 0; i < maxIter; ++i) {
        x1 = x0 - f(x0) / f_prime_centrally(f, x0);
        if (fabs(x1 - x0) < tol && !iter_mode) {
            return x1;
        }
        if (save_error) {
            // Append fabs(f(x1)) for debugging or analysis to .dat
            static ofstream outFile("output_newton_raphson.dat", ios::app);
            if (i == 0) {
                outFile << "Iteration Root Error" << endl;
            }
            outFile << i << " " << -x1 << " " << fabs(f(x1)) << endl;
        }
        x0 = x1;
    }
    return x1;
}