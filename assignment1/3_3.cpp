// Include the header file
#include "3_3.h"

// Include library to make assertion
#include <assert.h>

// Include library to write to file
#include <iostream>
#include <fstream>

// Define the implicit Euler function where n is the number of gridpoints
void implicit_Euler(int N){

    // Check that the number of grid points is greater than 1
    assert(N>1);

    // Calculate the step_size h, casting the integer n to a double to not perform integer division
    double h = 1 / ( (double)(N) - 1 );

    // Initialise arrays to contain the results for x and y
    double X[N];
    double Y[N];

    // Store initial values y(0)=1
    X[0] = 0;
    Y[0] = 1;

    // Loop over the next gridpoints (ommiting the initial value)
    for (int i=1; i<N; i++){

        // Perform one iteration of implicit euler
        // (isolating y_n in the given difference relation)
        Y[i] = Y[i-1] / (1+h);

        // Update values of x according to x_n=n*h
        X[i] = i*h;
    }

    // Create/open a file for output
    std::ofstream write_output("xy.dat");
    // Check that the file is open
    assert( write_output.is_open() );

    // Loop over the gridpoints
    for (int i=0; i<N; i++){

        // Write output
        write_output << X[i] << "," << Y[i] << "\n";
    }

    // Close the file
    write_output.close();

    return;
}