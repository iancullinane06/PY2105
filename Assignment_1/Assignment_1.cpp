#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
using namespace std;

// If you need to edit the location of dice.dat go to line 150

// Decimal to binary conversion function
string decimalToBinary(double decimal) {
    if (decimal == 0) {
        return "0";
    }

    string binary = "";
    int integerPart = static_cast<int>(decimal);
    double fractionalPart = decimal - integerPart;

    while (integerPart > 0) {
        binary = (integerPart % 2 == 0 ? "0" : "1") + binary;
        integerPart /= 2;
    }

    if (fractionalPart > 0) {
        binary += ".";
        for (int i = 0; i < 12 && fractionalPart > 0; i++) {
            fractionalPart *= 2;
            if (fractionalPart >= 1) {
                binary += "1";
                fractionalPart -= 1;
            } else {
                binary += "0";
            }
        }
    }

    return binary;
}

// Binary to decimal conversion function
double binaryToDecimal(string binary) {
    double decimal = 0;
    bool fractionalPart = false;
    double placeValue = 1;

    for (char bit : binary) {
        if (bit == '.') {
            fractionalPart = true;
            placeValue = 0.5;
        } else if (bit == '0' || bit == '1') {
            if (fractionalPart) {
                if (bit == '1') {
                    decimal += placeValue;
                }
                placeValue /= 2;
            } else {
                decimal = decimal * 2 + (bit - '0');
            }
        }
    }

    return decimal;
}

double meanCalc(int delays[], int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += delays[i];
    }
    return sum / size;
}

double standardDeviationCalc(int delays[], int size, double mean) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += (delays[i] - mean) * (delays[i] - mean);
    }
    return sqrt(sum / size);
}

double medianCalc(vector<int> values) {
    std::sort(values.begin(), values.end());
    int size = values.size();
    if (size % 2 == 0) {
        return (values[size / 2 - 1] + values[size / 2]) / 2.0;
    } else {
        return values[size / 2];
    }
}

int main()
{
    // Problem 1: double operations
    // Initialise
    double int1;
    double int2;
    double int3;
    cout << "Enter three numbers: ";
    cin >> int1 >> int2 >> int3;

    double sum = int1 + int2 + int3;
    double product = int1 * int2 * int3;

    cout << "Sum = " << sum << " and Product = " << product;

    //Problem 2: decimal to binary conversion
    double decimalNumber = 15.875;
    string binaryNumber = decimalToBinary(decimalNumber);
    cout << "\nDecimal " << decimalNumber << " is Binary " << binaryNumber;

    // Problem 3: binary to decimal conversion
    string binary = "1001.0011";
    double decimal = binaryToDecimal(binary);
    cout << "\nBinary " << binary << " is Decimal " << decimal;

    // Problem 4: Professor B's delays
    int delays[9] = {4, 10, 12, 55, 22, 15, 8, 7, 9};
    int size = 9;
    // Calculate mean
    double mean = meanCalc(delays, size);
    // Calculate stdev
    double stDev = standardDeviationCalc(delays, size, mean);

    // Print mean and standard deviation
    cout << "\nMean = " << mean << ", Standard Deviation = " << stDev;

    // Remove all outliers
    for (int i = 0; i < size; i++) {
        if (delays[i] > mean + stDev || delays[i] < mean - stDev) {
            for (int j = i; j < size - 1; j++) {
                delays[j] = delays[j + 1];
            }
            i--; // Adjust index after removal
            size--; // Decrease the size of the array after removal
        }

    }

    // Print new mean and it's variation
    double oldMean = mean;
    mean = meanCalc(delays, size);
    cout << "\nOld Mean = " << oldMean << ", New Mean = " << mean << ", Difference = " << (oldMean - mean);

    // Problem 5: Dice
    ifstream file;
    file.open("dice.dat");
    if (!file) {
        cerr << "Unable to open file dice.dat";
        return 1;
    }

    vector<int> rolls;

    // Calculate mean median and standard deviation for dice rolls
    int value;
    bool indexVal = true; 
    while (file >> value) {

        if (!indexVal) {
            rolls.push_back(value);
        }
        indexVal = !indexVal;
    }
    file.close();

    int rolls_size = rolls.size();
    double meanRolls = meanCalc(rolls.data(), rolls_size);
    double stDevRolls = standardDeviationCalc(rolls.data(), rolls_size, meanRolls);
    double medianRolls = medianCalc(rolls);

    cout << "\nDice Rolls - Mean = " << meanRolls << ", Standard Deviation = " << stDevRolls << ", Median = " << medianRolls << ", Relative difference = " << 200*abs(meanRolls - medianRolls)/(meanRolls + medianRolls) << "%";

    return 0;
}