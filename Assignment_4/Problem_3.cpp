#include <cmath>
#include <cstdlib>
#include <stdexcept>

class MonteCarloFunction {
public:
    double approximate(
        double (*func)(double),
        double a,
        double b,
        double y_min,
        double y_max,
        long long num_samples
    ) const {
        if (b <= a || y_max <= y_min || num_samples <= 0) {
            throw std::invalid_argument("Invalid Monte Carlo integration bounds or sample count.");
        }

        long long points_under_curve = 0;
        for (long long i = 0; i < num_samples; i++) {
            const double x = a + static_cast<double>(std::rand()) / RAND_MAX * (b - a);
            const double y = y_min + static_cast<double>(std::rand()) / RAND_MAX * (y_max - y_min);
            const double function_value = func(x);
            if (function_value < y_min || function_value > y_max) {
                throw std::runtime_error("The integration boundary does not enclose the function.");
            }
            if (y <= function_value) {
                points_under_curve++;
            }
        }
        return (b - a) * (y_max - y_min) *
            static_cast<double>(points_under_curve) / num_samples;
    }
};

double trapezoidal_integral(double (*func)(double), double a, double b, long long intervals) {
    const double step = (b - a) / intervals;
    double integral = (func(a) + func(b)) / 2.0;
    for (long long i = 1; i < intervals; i++) {
        integral += func(a + i * step);
    }
    return integral * step;
}

long long trapezoid_intervals_for_tolerance(
    double (*func)(double),
    double a,
    double b,
    double reference,
    double relative_tolerance
) {
    long long intervals = 1;
    while (true) {
        const double estimate = trapezoidal_integral(func, a, b, intervals);
        const double relative_error = std::fabs(estimate - reference) / std::fabs(reference);
        if (relative_error < relative_tolerance) {
            return intervals;
        }
        intervals++;
    }
}
