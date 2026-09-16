/*
  PY 2105: Introduction in Computational Physics
  Euler method for cooling ball
*/
// Header
#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
using namespace std;

// Constants
const int max_number_steps = 10000; // maximal number of steps

// Main programme
int main ()
{
    double t_end, dt; // initialize end time and time step
    int number_steps; // number of steps
    double value_theta [max_number_steps]; // array to store theta
    double value_f [max_number_steps]; // array to store f

    number_steps=16; //number of time steps
    t_end=480; // end time
    dt = t_end / number_steps; // calculate time step
    cout << "dt = " << dt << "\n"; // write out time step size

    // Numerical Simulation using Euler method
    value_theta[0]=1200; // theta_0 = 1200
    // value_f[0]=-2.2067*pow(10,-12)*(pow(value_theta[0],4)-81*pow(10,8)); // f(0,1200)
    for (int j = 0; j <= number_steps; j++) // loop over time
    {
      value_f [j] = - 2.2067*pow(10.,-12.)*(pow(value_theta[j],4)-81.*pow(10.,8.)); // calculate f(t,theta)
      value_theta [j+1] = value_theta [j] + dt * value_f [j]; // calculate new temperature
      cout << j*dt << " , " << value_theta[j] << " , " << value_f[j] << "\n"; // write out results
    } 
}
