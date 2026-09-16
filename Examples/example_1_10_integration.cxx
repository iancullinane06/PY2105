/*
  PY 2105: Introduction in Computational Physics

  Example 1.10: integration
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

  double deltat,a,b,n,low, upper, midpoint,distance;
// Calculate 
 
  a=8.0;
  b=30.0;
  deltat=1.; //corresponds to h in the lecture notes
  n=(b-a)/deltat; // number of segments
  distance=0.0; // initialise the distance
// Now distance of the rocket via midpoint rule
  for(int i=0;i<n;i++){
    // calculate (a+b)/2
    low = a+i*deltat;
    upper = a+(i+1)*deltat;
    midpoint = (low+upper)/2.;
    distance = distance + deltat*velocity(midpoint);
    cout << i << " " << distance << "\n";
  }
  cout << "distance of the rocket " << distance << "\n";
} // end program


// Function of velocity
double velocity(double t){
 double value; 
  value = 2000.*log(14.*pow(10.,4.)/(14.*pow(10.,4.)-2100.*t))-9.8*t;
 return value;
}


