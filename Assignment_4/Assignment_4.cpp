#include <iostream>
#include <cmath>
#include "Problem_1.cpp"
#include "Problem_2.cpp"
#include "Problem_3.cpp"
using namespace std;

// Ax = b

Matrix A = {{
    {13, 4, 7, 9},
    {10, 6, 5, 12},
    {1, 8, 2, 16},
    {3, 14, 15, 11}
}};

Vector b = {{111, 118, 114, 163}};

double exponential_function(double x) {
    return 300 * x / (1 + exp(x));
}

int main() {
    // Problem 1 - Solve Ax = b using Gaussian Elimination and LU Decomposition
    Matrix_solver_Gauss solver;
    Matrix_solver_Gauss::Result result = solver.solve(A, b);

    Matrix_solver_LU solver_LU;
    Matrix_solver_LU::Result result_LU = solver_LU.solve(A, b);

    cout << "Solution:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "x[" << i << "] = " << result.x.data[i] << endl;
    }
    cout << "Original Matrix A:" << endl;
    A.print();

    cout << "Original Vector b:" << endl;
    b.print();

    cout << "Resulting Matrix A after solving Gauss:" << endl;
    result.A.print();

    cout << "Resulting Matrix A after solving LU:" << endl;
    result_LU.A.print();

    cout << "Solution Vector x (Gauss):" << endl;
    result.x.print();

    cout << "Solution Vector x (LU):" << endl;
    result_LU.x.print();

    cout << "L Matrix:" << endl;
    result_LU.L.print();

    cout << "U Matrix:" << endl;
    result_LU.U.print();

    // Problem 2
    MonteCarloPi monteCarloSim;
    monteCarloSim.a = 2.0;
    double pi_approx = monteCarloSim.approximate(10000000);

    cout << "Approximate value of pi: " << pi_approx << endl;

    // Problem 3 - Monte Carlo integration for the exponential function
    MonteCarloFunction monteCarloFunc;
    double integral_approx = monteCarloFunc.approximate(exponential_function, 0, 10, 1000000);

    cout << "Approximate value of the integral: " << integral_approx ;

    return 0;
}
