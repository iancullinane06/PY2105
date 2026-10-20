#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

double f_prime_centrally(double (*f)(double), double x) {
    double h = 1e-6;
    return (f(x + h) - f(x - h)) / (2 * h);
}

double f(double x) {
    return pow(x, 2) - 2;
}

double f2(double x) {
    return cos(x) - (1.0/4.0);
}

double f3(double x) {
    return -pow(x, 4)  + 7*pow(x, 3) - 5*pow(x, 2) + 15;
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
        if (xb == xa) {
            break;
        }
        x2 =  xb - f(xb) * (xb - xa) / (f(xb) - f(xa));
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

class least_squares_fit {
public:
    least_squares_fit(vector<pair<double, double>> v, int n) {
    double sum_x = 0;
    double sum_y = 0;
    double sum_x2 = 0;
    double sum_xy = 0;
    for (int i = 0; i < n; i++) {
        double x = v[i].first;
        double y = v[i].second;
        sum_x += x;
        sum_y += y;
        sum_x2 += x * x;
        sum_xy += x * y;
    }
    double slope = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    double intercept = (sum_y - slope * sum_x) / n;
    m_slope = slope;
    m_intercept = intercept;
    }
    double get_slope() const { return m_slope; }
    double get_intercept() const { return m_intercept; }
private:
    double m_slope;
    double m_intercept;
};

int main() {
    
    // Problem 1 Finding the roots
    bool save_error = false;
    bool iter_mode = false;
    cout << "Bisection method root: " << findRoot_bisection(f, 0, 2, 100, save_error, iter_mode) << endl;
    cout << "Secant method root: " << findRoot_secant(f, 100, 0, 2, save_error, iter_mode) << endl;
    cout << "Newton-Raphson method root: " << findRoot_Newton_Raphson(f, 1.0, 100, save_error, iter_mode) << endl;

    // b)
    save_error = false;
    iter_mode = false;
    cout << "Bisection method root for f2: " << findRoot_bisection(f2, 0, M_PI/2, 100, save_error, iter_mode) << endl;
    cout << "Secant method root for f2: " << findRoot_secant(f2, 100, 0, M_PI/2, save_error, iter_mode) << endl;
    cout << "Newton-Raphson method root for f2: " << findRoot_Newton_Raphson(f2, M_PI/2, 100, save_error, iter_mode) << endl;

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