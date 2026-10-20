#include <iostream>
#include <cmath>
using namespace std;

double sin_radians(double angle) {
    return static_cast<double>(sin(angle));
}

double quadratic(double x) {
    return x*x - x + 1;
}

double centrally_differentiate(double (*f)(double), double x, double h) {
    return (f(x + h) - f(x - h)) / (2 * h);
}

double forward_differentiate(double (*f)(double), double x, double h) {
    return (f(x + h) - f(x)) / h;
}

double backward_differentiate(double (*f)(double), double x, double h) {
    return (f(x) - f(x - h)) / h;
}

double exponential_function(double x) {
    return 300 * x / (1 + exp(x));
}

double integrate_function(double (*f)(double), double a, double b, double n) {
    double integral = 0.0;
    double h = (b - a) / n;
    for (double x = a; x < b; x += h) {
        integral += f(x) * h;
    }
    return integral;
}

int main() {
    // Problem 1 a
    double residual;
    double part_b_residual;
    
    for (double i = 0; i < 0.5; i += 0.001) {
        residual = 100.0*(i - sin_radians(i))/i;
        if (residual >= 1) {
            cout << "i: " << i << ", residual: " << residual << endl;
            part_b_residual = i;
            break;
        }
    }

    //part c
    residual = 100.0*abs(part_b_residual - pow(part_b_residual, 3)/6 - sin_radians(part_b_residual))/part_b_residual;
    cout << "i: " << part_b_residual << ", residual: " << residual << " Residual for second order taylor approximation \n";

    //part c
    for (double i = 0; i < 2; i += 0.001) {
        residual = 100.0*abs(i - pow(i, 3)/6 - sin_radians(i))/sin_radians(i);
        if (residual >= 1) {
            cout << "i: " << i << ", residual: " << residual << endl;
            break;
        }
    }

    // Problem 2: Centrally differentiate the quadratic function
    double h = 0.001;
    double x = 2.0;
    double derivative = centrally_differentiate(quadratic, x, h);
    cout << "x: " << x << ", derivative: " << derivative << endl;

    // Absolute error
    double exact_derivative = 2*x - 1;
    double absolute_error = abs(derivative - exact_derivative);
    cout << "x: " << x << ", absolute error: " << absolute_error << endl;

    // Forward and backward differentiation
    double forward_derivative = forward_differentiate(quadratic, x, h);
    double backward_derivative = backward_differentiate(quadratic, x, h);
    cout << "x: " << x << ", forward derivative: " << forward_derivative << endl;
    cout << "x: " << x << ", backward derivative: " << backward_derivative << endl;

    // Absolute errors for forward and backward differentiation
    double forward_absolute_error = abs(forward_derivative - exact_derivative);
    double backward_absolute_error = abs(backward_derivative - exact_derivative);
    cout << "x: " << x << ", forward absolute error: " << forward_absolute_error << endl;
    cout << "x: " << x << ", backward absolute error: " << backward_absolute_error << endl;

    // Problem 3: Integrate the exponential function
    double a = 0.0;
    double b = 10.0;
    double n = 64;
    double integral = integrate_function(exponential_function, a, b, n);
    cout << "Integral of exponential function from " << a << " to " << b << " with n = " << n << " is: " << integral << endl;

    // Analysis of trapezoidal rule for higher n found in Python version

    return 0;
}