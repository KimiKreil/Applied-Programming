// Include header file
#include "5_4.h"

// Include cmath to get sqrt function
#include <math.h>

// Define function to calculate the mean
double calc_mean(double a[], int length){

    // Initialise sum of elements at 0
    double sum = 0;

    // Loop over elements
    for (int i=0; i<length; i++){

        // Sum elements by adding them to the sum
        sum += a[i];
    }

    // Calculate the mean by dividing sum with length
    double mean = sum / length;
    return mean;
}


// Define function to calculate the standard deviation
double calc_std(double a[], int length){

    // Ensure no division with zero (if length=1, N-1=0 in the denominator)
    if (length == 1){

        // If there is only one element, we define the std as 0
        return 0.0;
    }

    // Calculate the mean
    double mean = calc_mean(a, length);

    // Initialise the sum in the numerator as 0
    double sum = 0;

    // Loop over elements
    for (int i=0; i<length; i++){

        // Add to sum
        sum += pow(a[i] - mean,2);
    }

    // Divide by denominator and take sqrt to get std
    double std = sqrt( sum / (length-1) );
    return std;
}