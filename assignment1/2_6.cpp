// Include the header file
#include "2_6.h"

// Include cmath to get absolute value function for floating type data
#include <math.h>

// Define the function we use newton rhapson on
double f(double x){
    return exp(x) + pow(x,3) -5;
}

// Define the derivative
double f_prime(double x){
    return exp(x) +  3*pow(x,2);
}

// Define a newton rhapson function with nomenclature from the assignment
double newton_Raphson(double initialGuess, double epsilon){

    // The function applies the Newton-Raphson algorithm to the function e^x + x^3 - 5
    // Define that function


    // Initialise the two scalar variables x_prev and x_next
    double x_prev = initialGuess;
    // x_next is defined from newton raphson formula
    double x_next = x_prev - f(x_prev)/f_prime(x_prev);

    // We use the while loop described in subquestion 5 
    // with convergence criterion |x_next-x_prev| < epsilon
    while ( fabs(x_next-x_prev) > epsilon ){

        // Store last iteration as previous
        x_prev = x_next;

        // Perform one iteration of Newton-Rhapson
        x_next = x_prev - f(x_prev)/f_prime(x_prev);
    }

    // Return the result that upholds the criterion
    return x_next;
}
