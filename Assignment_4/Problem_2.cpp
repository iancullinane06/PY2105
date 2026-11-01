#include <cstdlib> // for rand() and RAND_MAX
#include <ctime>   // for time() to seed rand()

// Seed the random number generator
struct RandSeed {
    RandSeed() { std::srand(std::time(nullptr)); }
} randSeed;

class MonteCarloPi {
public:
    double a = 1.0; // radius of the circle
    
    double approximate(double num_samples) {
        double inside_circle = 0;
        for (int i = 0; i < num_samples; i++) {
            double x = (double)rand() / RAND_MAX * a;
            double y = (double)rand() / RAND_MAX * a;
            if (x * x + y * y <= a * a) {
                inside_circle++;
            }
        }

        return 4.0 * static_cast<double>(inside_circle / num_samples);
    }
};