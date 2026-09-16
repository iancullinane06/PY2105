/*
  PY 2105: Introduction in Computational Physics

  Example 1.6: Plot
*/

// Header

#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
using namespace std;
#include <stdlib.h> // new headers to be included for reading in file
#include <stdarg.h>
#include <assert.h>
#include <fstream>
std::ifstream infile("data1.dat"); // name of datafile

// Declaration of constants and assigning values

const int number_points = 25; // length of the array, predefined

// Main program

int main ()
{
  //Declaration of variables	
  double x [number_points]; // Array of x values of plot
  double y [number_points]; // Array of y values of plot
  int nr, ny;
  double a,b;
  
  nr=0;
  while (infile >> a >> b)
   {
    x[nr] = a;
    y[nr] = b;
    nr = nr+1;
   }

  ny=0;
  while (ny < nr)
  {
   cout << x[ny] << " " << y[ny] << "\n";
   ny=ny+1;
  }

  return 0;
}
