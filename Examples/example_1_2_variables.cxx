/*
  PY 2105: Introduction in Computational Physics

  Example 1.2: Variables
*/

// Header

#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
using namespace std;


// Declaration of constants and assigning values
const int c_int = 9; 
const double c_double = -2.3;

// Main program

int main ()
{
  // Declaration of variables: integer and doubles
  int a; // as the name suggests, variables can vary their value
  int b, c, d; // during the execution of the program
  double r, s, e; 

  // Assigning values to the variables	
  a = -100;
  b = c_int;
  r = 1.5e1; // double
  s = 3.2 + c_double; // adding two doubles
  c = a + b;  // adding two integers
  d = c_int + c_double; // adding integer and double
  e = c_int + c_double; // adding integer and double 

  // Output of the variables
  
  cout << "a = " << a << "\n"; // first part inside the " " gives
  cout << "b = " << b << "\n"; // a writing on the screen
  cout << "c = " << c << "\n"; // << are neccessary to move to the
  cout << "r = " << r << "\n"; // next part that is written out
  cout << "s = " << s << "\n"; // output of variables don't need
  cout << "d = " << d << "\n"; // the " " around
  cout << "e = " << e << "\n"; // \n means that the following part
  cout << "a/d = " << a/d << "\n"; // is written in a new line
  cout << "s*b = " << s*b << "\n";

  return 0;  // end of program
}




