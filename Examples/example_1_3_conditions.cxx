/*
  PY 2105: Introduction in Computational Physics

  Example 1.3: Conditions
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
{
  // Declaration of variable;
  int b;

  // Input of variable
  cout << "Value of b: ";
  cin >> b;

//------------------------------------------------
    
  cout << "Example 1:\n";

  if (b < 0)
    cout << "b is less than zero\n";

//------------------------------------------------
  
  cout << "\nExample 2:\n";

  if (b < 0)
    cout << "b is less than zero\n";
  else
    cout << "b is greater than or equal to zero\n";

//------------------------------------------------

//------------------------------------------------
  
  cout << "\nExample 3:\n";

  if ((b > 0) && (b < 10))
    cout << "b is greater than zero and less than 10\n";
    
  if ((b < 0) || (b > 10))
    cout << "b is less than zero or greater than 10\n";
    
  return 0;
}
