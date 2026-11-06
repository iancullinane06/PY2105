#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdexcept>

const double PI_REFERENCE = 3.14159265358979323846;

struct RandSeed {
    RandSeed() { std::srand(static_cast<unsigned int>(std::time(nullptr))); }
} randSeed;

class MonteCarloPi {
public:
    double a = 2.0;

    double approximate(long long num_samples) const {
        if (num_samples <= 0 || a <= 0.0) {
            throw std::invalid_argument("The side length and sample count must be positive.");
        }

        long long inside_circle = 0;
        const double half_side = a / 2.0;
        for (long long i = 0; i < num_samples; i++) {
            const double x = (static_cast<double>(std::rand()) / RAND_MAX - 0.5) * a;
            const double y = (static_cast<double>(std::rand()) / RAND_MAX - 0.5) * a;
            if (x * x + y * y <= half_side * half_side) {
                inside_circle++;
            }
        }
        return 4.0 * static_cast<double>(inside_circle) / num_samples;
    }

    double write_convergence_data(const char *filename, long long max_samples) const {
        if (max_samples <= 0 || a <= 0.0) {
            throw std::invalid_argument("The side length and sample count must be positive.");
        }

        std::ofstream output(filename);
        if (!output) {
            throw std::runtime_error("Could not open the pi convergence output file.");
        }
        output << "samples,estimate,relative_error_percent\n";

        const long long checkpoints[] = {
            100, 1000, 10000, 100000, 1000000, 10000000
        };
        const int checkpoint_count = sizeof(checkpoints) / sizeof(checkpoints[0]);
        const double half_side = a / 2.0;
        long long inside_circle = 0;
        int checkpoint = 0;

        for (long long i = 1; i <= max_samples; i++) {
            const double x = (static_cast<double>(std::rand()) / RAND_MAX - 0.5) * a;
            const double y = (static_cast<double>(std::rand()) / RAND_MAX - 0.5) * a;
            if (x * x + y * y <= half_side * half_side) {
                inside_circle++;
            }

            if (checkpoint < checkpoint_count && i == checkpoints[checkpoint]) {
                const double estimate = 4.0 * static_cast<double>(inside_circle) / i;
                const double relative_error =
                    100.0 * std::fabs(estimate - PI_REFERENCE) / PI_REFERENCE;
                output << i << "," << estimate << "," << relative_error << "\n";
                checkpoint++;
            }
        }

        if (checkpoint == 0 || checkpoints[checkpoint - 1] != max_samples) {
            const double estimate = 4.0 * static_cast<double>(inside_circle) / max_samples;
            const double relative_error =
                100.0 * std::fabs(estimate - PI_REFERENCE) / PI_REFERENCE;
            output << max_samples << "," << estimate << "," << relative_error << "\n";
        }
        return 4.0 * static_cast<double>(inside_circle) / max_samples;
    }
};
