/*
  PY 2105: Introduction in Computational Physics

  Example 1.7: errors
*/

// Header

#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
using namespace std;


// Main program

int main ()
{  // start main program
  // Declaration of variables

  double a, b, c, Et, Er;
// Difference between exp(x) and the first 3 or 4 terms of Taylor series at x=0.7
 
  a=exp(0.7); // real function
  b = 1 + 0.7 + pow(0.7,2.)/2.; // pow command for 0.7^2
  c = 1 + 0.7 + pow(0.7,2.)/2. + pow(0.7,3.)/(2*3);
  Et = a - b; // true error
  Er = Et/a; // relative true error

  cout << "real value of exp(0.7) is " << a << "\n";
  cout << "approx value of exp(0.7) is " << b << "\n";
  cout << "true error is " << Et << "\n";
  cout << "relative true error for 3 terms is " << Er << "\n";
  cout << "relative true error for 4 terms is " << (a-c)/a *100. << "%" << "\n";

} // end program
