#include <iostream>
#include <cmath>
#include "Question_1.cpp"
#include "Question_2.cpp"
#include "Question_3.cpp"
using namespace std;

double function(double x) {
    return log(x + exp(x - 1)) - sin(2*x);
}

double gravity(double x) {
    return 9.8;
}

int main() {
    // Question 1 - double die
    cout << "Question 1" << endl;
    double_die question_1;
    int num_values;
    cout << "how many rolls : ";
    cin >> num_values;
    vector<double_die::Result> results = question_1.dices(num_values, 6);
    for (int i = 0; i < num_values; i++) {
        cout << "Roll : " << (i + 1) << " dice 1: " << results[i].dice_1 << " dice 2: " << results[i].dice_2 << " sum : " << results[i].sum << endl;
    }

    // Question 2 - function manipulation
    cout << "Question 2" << endl;
    function_manipulation question_2;
    double root = question_2.findRoot(function, 0, 5, 100);
    cout << "root : " << root << endl;

    double stepsizes[4] = {10, 20, 40, 80};

    double true_value = question_2.trapesium_rule(function, root, 5, 100000);

    for (int i = 0; i < 4; i++) {
        double integral = question_2.trapesium_rule(function, root, 5, stepsizes[i]);
        cout << "area for stepsize : " << stepsizes[i] << " : " << integral << " true error : " << integral - true_value << endl;
    }

    cout << " As the area increases, the error decreased logarithmically. Each true error is approximately half the previous." << endl;
    
    // Question 3 - Euler's method for solving ODE
    cout << "Question 3" << endl;
    Euler_Solver solver;
    double dt = 0.5;
    double y0 = 0.0;
    double endTime = 1.0;
    cout << "dt = 0.5" << endl;
    double result = solver.solve_ODE(gravity, dt, y0, endTime);
    cout << "Solution at t = " << endTime << " : " << result << endl;

    dt = 0.1;
    cout << "dt = 0.1" << endl;
    result = solver.solve_ODE(gravity, dt, y0, endTime);
    cout << "Solution at t = " << endTime << " : " << result << endl;

    cout << "Because the question at hand has a constant function, g = 9.8, which is invariant of time. The two results return the same value. The error for the euler method is in f prime which is - in the context of this question - 0." << endl;
    return 0;
}

