#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include "Problem_1.cpp"
#include "Problem_2.cpp"
#include "Problem_3.cpp"
using namespace std;

Matrix A = {{
    {13, 4, 7, 9},
    {10, 6, 5, 12},
    {1, 8, 2, 16},
    {3, 14, 15, 11}
}};

Vector b = {{111, 118, 114, 163}};

double exponential_function(double x) {
    return 300.0 * x / (1.0 + exp(x));
}

int main() {
    cout << setprecision(10);

    cout << "Problem 1: Gaussian elimination with partial pivoting" << endl;
    Matrix_solver_Gauss gaussian_solver;
    Matrix_solver_Gauss::Result gaussian = gaussian_solver.solve(A, b);
    cout << "Upper triangular matrix U:" << endl;
    gaussian.A.print();
    cout << "Forward-eliminated b:" << endl;
    gaussian.b.print();
    cout << "Solution x:" << endl;
    gaussian.x.print();
    cout << "det(A): " << gaussian.determinant << endl;

    cout << "\nProblem 1: LU decomposition" << endl;
    Matrix_solver_LU lu_solver;
    Matrix_solver_LU::Result lu = lu_solver.solve(A, b);
    cout << "L:" << endl;
    lu.L.print();
    cout << "U:" << endl;
    lu.U.print();
    cout << "Solution x:" << endl;
    lu.x.print();
    cout << "Inverse of A:" << endl;
    lu.inverse.print();

    cout << "\nProblem 2: Monte Carlo estimate of pi" << endl;
    MonteCarloPi pi_estimator;
    const double pi_approximation =
        pi_estimator.write_convergence_data("output/pi_convergence.csv", 10000000);
    cout << "Pi estimate (10000000 samples): " << pi_approximation << endl;
    cout << "Precision data written to output/pi_convergence.csv" << endl;

    cout << "\nProblem 3: Monte Carlo integration" << endl;
    const double lower_x = 0.0;
    const double upper_x = 10.0;
    const double lower_y = 0.0;
    const double upper_y = 100.0;
    const double relative_tolerance = 0.0001;
    const double reference = trapezoidal_integral(
        exponential_function, lower_x, upper_x, 1000000
    );
    const double hit_probability =
        reference / ((upper_x - lower_x) * (upper_y - lower_y));
    const double z_score_95_percent = 1.96;
    const long long monte_carlo_samples = static_cast<long long>(ceil(
        z_score_95_percent * z_score_95_percent * (1.0 - hit_probability) /
        (hit_probability * relative_tolerance * relative_tolerance)
    ));

    MonteCarloFunction function_estimator;
    const auto monte_carlo_start = chrono::steady_clock::now();
    const double monte_carlo_integral = function_estimator.approximate(
        exponential_function,
        lower_x,
        upper_x,
        lower_y,
        upper_y,
        monte_carlo_samples
    );
    const auto monte_carlo_end = chrono::steady_clock::now();
    const double monte_carlo_seconds =
        chrono::duration<double>(monte_carlo_end - monte_carlo_start).count();
    const double monte_carlo_error_percent =
        100.0 * fabs(monte_carlo_integral - reference) / fabs(reference);

    cout << "Bounding rectangle: x = [0, 10], y = [0, 100]" << endl;
    cout << "Reference integral (1,000,000-interval trapezoid): " << reference << endl;
    cout << "Monte Carlo samples (estimated for 95% confidence): "
         << monte_carlo_samples << endl;
    cout << "Monte Carlo integral: " << monte_carlo_integral << endl;
    cout << "Monte Carlo relative error: " << monte_carlo_error_percent << "%" << endl;
    cout << "Monte Carlo runtime: " << monte_carlo_seconds << " s" << endl;

    const long long trapezoid_intervals = trapezoid_intervals_for_tolerance(
        exponential_function,
        lower_x,
        upper_x,
        reference,
        relative_tolerance
    );
    const double trapezoid_step = (upper_x - lower_x) / trapezoid_intervals;
    const auto trapezoid_start = chrono::steady_clock::now();
    const double trapezoid_estimate = trapezoidal_integral(
        exponential_function, lower_x, upper_x, trapezoid_intervals
    );
    const auto trapezoid_end = chrono::steady_clock::now();
    const double trapezoid_seconds =
        chrono::duration<double>(trapezoid_end - trapezoid_start).count();
    const double trapezoid_error_percent =
        100.0 * fabs(trapezoid_estimate - reference) / fabs(reference);

    cout << "Trapezoid intervals for relative error below 0.01%: "
         << trapezoid_intervals << endl;
    cout << "Trapezoid step size: " << trapezoid_step << endl;
    cout << "Trapezoid integral: " << trapezoid_estimate << endl;
    cout << "Trapezoid relative error: " << trapezoid_error_percent << "%" << endl;
    cout << "Trapezoid runtime: " << trapezoid_seconds << " s" << endl;

    return 0;
}
