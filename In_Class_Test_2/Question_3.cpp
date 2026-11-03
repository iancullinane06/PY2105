class Euler_Solver {
public:
    double solve_ODE(double (*f)(double), double dt, double y0, double endTime) {
        double y1 = y0;
        for (double t = 0; t < (endTime-0.001); t += dt) {
            y1 = y1 + dt * f(y1);
        }
        return y1;
    }
};