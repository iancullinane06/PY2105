/*
  PY 2105: Introduction in Computational Physics
  Example: Random numbers
*/

// Header
#include <iostream> // iostream needed to write data
#include <fstream> // needed to write out data
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <ctime> // needed for time(NULL)
#include <math.h>
#include <cstdlib> // needed for random number generation
using namespace std;

// Main program

int main ()
{  // start main program

	double randomNumd; // random number
	double lifetime; // lifetime of disc
	ofstream datafile; // define data file
	// Get a different random number each time the program runs
	srand(time(NULL)); // Seeding of random number generator srand()
	//	srand(1);	// using instead srand(1) will always return the same sequence!

	// print 10 random integers between 0 and 100
	for (int i=0; i< 10; i++){
		int randomNum = rand() % 101; // Integer random number between 0 and 100
		cout << randomNum << "\n"; // writing out of random number
	}

	// print 10 random numbers between 0 and 1
	for (int i=0; i< 10; i++){
		randomNumd = (double) rand()/RAND_MAX; // double random number between 0 and 1
		cout <<  randomNumd << "\n"; // writing out of random number
	}

	// disc lifetime with exponential decay of 2.5 Myr, meaning lambda = 1/2.5e6
	datafile.open ("data.txt"); // open data file and define its name
	for (int i=0; i <1000; i++){  // loop over number of points
		randomNumd = (double) rand()/RAND_MAX; // Random Number between 0 and 1
		lifetime = -2.5e6*log(1.-randomNumd); // Exponetial function with 2.5 decay
		datafile << lifetime << "\n"; // write out and multiply by 1e6 to get lifetime in Myr
	}
	datafile.close(); // close of data file

} // end program
