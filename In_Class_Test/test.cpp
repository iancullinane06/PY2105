#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
using namespace std;

int factorial(int n) {
    if (n==0) return 1;
    return n * factorial(n - 1);
}

double polynomial(double x) {
    return pow(x, 3) - 3*pow(x, 2) + 3;
}

double differentiate_centrally(double x, double h) {
    return (polynomial(x + h) - polynomial(x - h)) / (2*h);
}

double differentiate_forward(double x, double h) {
    return (polynomial(x + h) - polynomial(x)) / h;
}

double differentiate_backward(double x, double h) {
    return (polynomial(x) - polynomial(x - h)) / h;
}

double true_error(double approximation, double true_value) {
    return 100*abs(approximation- true_value)/true_value;
}

double differentiate_true(double x) {
    return 3*pow(x, 2) - 6*x;
}

int main() {
    // Problem 1
    //----------------------------------------------------
    // Program - Collection of instructions grouped together in a wrapper that we call a program. Necessary for use with a compiler.
    // Compiler - Takes the abstracted language expressed in our programs and breaks them down into machine code which the CPU can read as instructions.
    // Variable and it's value - A variable acts like a container, they can be mutable or immutable. Variables act as pointers to memory which can be accessed and manipulated. Variables in C++ must be assigned a type at initialisation but can dynamically be reassigned values so long as hte type's compatible.

    // Problem 2
    //----------------------------------------------------
    double num1, num2;
    cout << "enter two numbers: ";
    cin >> num1 >> num2;
    double max = (num1 > num2) ? num1 : num2;
    cout << "maximum: " << max << "\n";

    //----------------------------------------------------
    // Problem 3
    int n;
    while (true) {
        cout << "factorial: enter n > 0: ";
        cin >> n;
        if (n >= 0) break;
        cout << "please try again; ";
    }

    cout << "factorial : " << factorial(n) << "\n";

    //----------------------------------------------------
    // Problem 4
    //a) in python
    
    //b)
    double x;
    double h = 0.1;
    cout << "x for derivative: ";
    cin >> x;
    cout << "Derivative : " << differentiate_centrally(x, h) << "\n";

    //c)
    double error_centrally = true_error(differentiate_centrally(x, h), differentiate_true(x));
    cout << "percentage error central method: " << error_centrally << "\n";

    //d)
    double error_forward = true_error(differentiate_forward(x, h), differentiate_true(x));
    cout << "percentage error forward method: " << error_forward << " derivative: " << differentiate_forward(x, h) << "\n";

    double error_backward = true_error(differentiate_backward(x, h), differentiate_true(x));
    cout << "percentage error backward method: " << error_backward << " derivative: " << differentiate_backward(x, h) << "\n";


    return 0;
}