/*
  PY 2105: Introduction in Computational Physics
  Example 1.9: Loops 2
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
  int nr;
  int b;
  int sum;
//------------------------------------------------    
  cout << "Example 1:\n";
  nr = 1;  // initialize counter variable to 1
  sum = 0; // initialize sum to 0
  while (nr <= 10)  // loop from 1 to 10
    {  // brackets indicate the length of the while loop
      sum += nr;  // adding nr to sum, equivalent to sum = sum +nr
      nr = nr + 1;  // increments nr by 1
    }  // end of while loop
    cout << "The sum from 1 to " << nr-1 << " is " << sum << "\n";
//-----------------------------
  cout << "Example 1 (for loop):\n";
  sum=0;
  for (nr=1; nr <= 10; nr++){
  sum += nr;
  }
  cout << "The sum from 1 to " << nr-1 << " is " << sum << "\n";
//---------------------------------------------------
// Now only sum over the even numbers
  cout << "Example 2 :\n";
   nr=1;  // setting counter to 1 again
   sum=0;  // setting sum to 0, otherwise previous sum will be carried!
   while (nr <= 10) // while loop
   {
    if(nr % 2 ==0) // modulo command: checks if the rest after division by 2 is 0
     sum += nr; 
     nr = nr+1;
   }
    cout << "The even sum from 1 to " << nr-1 << " is  " << sum << "\n";   
//---------------------------------------
// Example 2: for loop
  cout << "Example 2 (for loop):\n";
 sum=0;
 for (int i=0; i<=10; i+=2){ // i is just declared here and can not be accessed
  sum += i;                  // outside of the loop!
 }
    cout << "The even sum from 1 to 10 is " << sum << "\n";   

} // end program
