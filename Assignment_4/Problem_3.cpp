#include <iostream>
using namespace std;

class MonteCarloFunction {
    public:
        double approximate(double (*func)(double), double a, double b, double num_samples) {
            double sum = 0;
            for (int i = 0; i < num_samples; i++) {
                double x = (double)rand() / RAND_MAX * (b - a) + a;
                sum += func(x);
            }
            return (b - a) * sum / num_samples;
        }
};