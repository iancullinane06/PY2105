/*
  PY 2105: Introduction in Computational Physics

  Example 1.7: functions
*/

// Header

#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
using namespace std;


double velocity(double t); //alternatively you can declare your function completely above the main program

// Main program
int main ()
{  // start main program
  // Declaration of variables

  double t,deltat,vel,a;
// Calculate 
 
  t=16.;
  deltat=2.;
  vel=velocity(t);
  
  cout << "Velocity of the rocket at t=" << t << " is " << vel << "\n";
// Now calculate forward differentiation
  a = (velocity(t+deltat)-velocity(t))/deltat;

  cout << "Acceleration of the rocket at t=" << t << " is " << a << "\n";

} // end program


// Function of velocity
double velocity(double t){
 double value; 
  value = 2000.*log(14.*pow(10.,4.)/(14.*pow(10.,4.)-2100.*t))-9.8*t;
 return value;
}


