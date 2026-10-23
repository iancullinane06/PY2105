#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>
#include "Problem_1.cpp"
#include "Problem_2.cpp"
#include "Problem_3.cpp"

using namespace std;


double f(double x) {
    return pow(x, 2) - 2;
}

double f2(double x) {
    return cos(x) - (1.0/4.0);
}

double f3(double x) {
    return -pow(x, 4)  + 7*pow(x, 3) - 5*pow(x, 2) + 15;
}


int main() {
    // Problem 1 Finding the roots
    // a )
    bool save_error = false;
    bool iter_mode = false;
    cout << "Bisection method root: " << findRoot_bisection(f, 0, 2, 100, save_error, iter_mode) << endl;
    cout << "Secant method root: " << findRoot_secant(f, 100, 0, 2, save_error, iter_mode) << endl;
    cout << "Newton-Raphson method root: " << findRoot_Newton_Raphson(f, 1.0, 100, save_error, iter_mode) << endl;

    // b)
    save_error = true;
    iter_mode = true;
    cout << "Bisection method root for f2: " << findRoot_bisection(f2, 0, M_PI/2, 50, save_error, iter_mode) << endl;
    cout << "Secant method root for f2: " << findRoot_secant(f2, 50, 0, M_PI/2, save_error, iter_mode) << endl;
    cout << "Newton-Raphson method root for f2: " << findRoot_Newton_Raphson(f2, M_PI/2, 50, save_error, iter_mode) << endl;

    // Problem 2: Integration using Simpson's 1/3 rule
    // Chose to use secant method for finding the roots as it would bound the roots as found in the plot.
    double bound_1 = findRoot_secant(f3, 100, -2.0, -1.0, false, false);
    double bound_2 = findRoot_secant(f3, 100, 6.0, 7.0, false, false);

    save_error = true;
    double integral = Simpsons_1_3(f3, bound_1, bound_2, 10000);
    cout << "Integral of f3 between bounds " << bound_1 << " and " << bound_2 << " is " << integral << endl;
    ofstream outFile("output_simpsons.dat", ios::app);
    outFile << std::fixed;
    outFile << std::setprecision(16);
    if (save_error) outFile << "n Integral" << endl;
    for (int i = 0; i < 20 && save_error; i++){
        int n = pow(2, i+1);
        integral = Simpsons_1_3(f3, bound_1, bound_2, n);
        if (outFile) outFile << n << " " << integral << endl;
    }

    outFile.close();

    // Problem 3: Least squares fit
    // Read form file
    ifstream inFile("data1.dat");
    double x, y;
    vector<pair<double, double>> v;
    while (inFile >> x >> y) {
        v.push_back({x, y});
    }
    least_squares_fit fit(v, v.size());
    cout << "Slope: " << fit.get_slope() << ", Intercept: " << fit.get_intercept() << endl;

    return 0;
}