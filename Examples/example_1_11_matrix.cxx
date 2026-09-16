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
  int i,j; // Simple integer variable
  double matrix [length_array][length_array]; // Array of integers
  
  i = 0; // set first counter variable
  j = 0; // set 2nd counter variable
  while (i < length_array) // first loop
    {
     while (j < length_array) // 2nd loop
     {
      matrix[i][j] = i+j; // Initalize matrix with values
      j=j+1;  // increment counter j
     } 
    j=0; // set counter j to 0 to start go back into j loop!
    i = i+1; // increment i
  //  cout << i << " " << j << "\n";
    }
  // Output of array vector
  cout << "\nOutput of array matrix:\n";
  j = 0; // start at 0
  i = 0; // start at 0
  while (i < length_array) // first loop
    {
     while (j< length_array) // 2nd loop
     {
      cout << matrix[i][j] << " "; // write out each element
      j = j+1; // increment j
     }
     cout << "\n"; // start new line
     j=0; // set j to 0 to start with j=0 in 2nd loop
     i = i + 1; // increment i
    }
  
     cout << "\n"; // start new line


  // alternative structure
  for(i=0; i<length_array; i++)  // for loop, needs running variable, here "i"
  {
   for(j=0; j<length_array; j++){ // for loop, increment inside bracket!
      matrix[i][j] = i*j;   // operation
   }
  j=0; // we still need to set j=0 to do what we want to do!
  }

  for(i=0; i<length_array; i++) // same loop, but now we write the result on the screen
  {
   for(j=0; j<length_array; j++){
      cout << matrix[i][j] << " ";
   }
     cout << "\n"; // start new line
     j=0; // set j to 0 to start with j=0 in 2nd loop
  }

  return 0;
}

