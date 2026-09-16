/*
  PY 2105: Introduction in Computational Physics

  Example 1.5: Numerical arrays
*/

// Header

#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
using namespace std;


// Declaration of constants and assigning values

const int length_array = 10;


// Main program

int main ()
{
  // Declaration of variables
  int nr; // Simple integer variable
  int vector [length_array]; // Array of integers
  
  // Input of values of the array vector
  cout << "Please enter the values of the array vector:\n";
  nr = 0;
  while (nr < length_array)
    {
      cout << "entry " << nr << ": ";
      cin >> vector [nr];
      nr = nr + 1;
    }
  
  // Output of array vector
  cout << "\nOutput of array vector:\n";
  nr = 0;
  while (nr < length_array)
    {
      cout << "entry " << nr << ": " << vector [nr] << "\n";
      nr = nr + 1;
    }
  
  return 0;
}
