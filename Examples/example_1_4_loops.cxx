/*
  PY 2105: Introduction in Computational Physics

  Example 1.4: Loops
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
      cout << sum << "\n";  // writes out the current sum and starts new line
      nr = nr + 1;  // increments nr by 1
    }  // end of while loop
    cout << "The sum from 1 to " << nr-1 << " is " << sum << "\n";


//---------------------------------------------------
// Now only sum over the even numbers
   nr=1;  // setting counter to 1 again
   sum=0;  // setting sum to 0, otherwise previous sum will be carried!
   while (nr <= 10) // while loop
   {
    if(nr % 2 ==0) // modulo command: checks if the rest after division by 2 is 0
     sum += nr; // what to do in the if statement: longer if statements can be done
//		   with { and }, like in the while loop
     
   nr = nr+1;
   }

    cout << "The even sum from 1 to " << nr-1 << " is  " << sum << "\n";   



//---------------------------------
// sum to x for odd numbers
  nr = 1;  // setting counter to 1
  sum = 0; // setting sum to 0
  while (sum <= 50) // loop until sum reaches at least 50
  {
   if(nr % 2 == 1) // only do things if number is odd
    sum += nr;  // sum up the odd numbers
  
   nr = nr+1; // increase the increment by 1
  }

  cout << "We need to sum all odd numbers up to " << nr-1 <<" to reach at least 50 \n";


} // end program
