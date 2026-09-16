/*
  PY 2105: Introduction in Computational Physics

  Example 1.8: functions
*/

// Header
#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
using namespace std;

double cube(double x);
double power4th(double x);

// Main program
int main ()
{  // start main program
  // Declaration of variables
  double x;
  x=4.;
  // write out  
  cout << "The cube of x is " << cube(x) << "\n";
  cout << "The 4th power of x is " << power4th(x) << "\n";
} // end main program

// simple function
double cube(double y){
 return y*y*y;
} // end simple function
// more complex function
double power4th(double y){
 double value; 
  value = y*y*y*y;
 return value;
} // end more complex function
