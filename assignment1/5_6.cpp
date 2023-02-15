// Include header file
#include "5_6.h"

// Include assertions
#include <assert.h>

#include <iostream>
// Define function that handles matrix-matrix multiplication
void Multiply(double **res, double **A, double **B, int ARows, int ACols, int BRows, int BCols){

    // Only possible when A of shape (l x m) and B of shape (m x n), remember: (rows x cols)
    assert(ACols == BRows);

    // Loop over rows in res of shape (l x n)
    for (int i=0; i<ARows; i++){
        // Loop over cols in res
        for (int j=0; j<BCols; j++){
            // Initialise result at zero
            res[i][i] = 0;
        }
    }

    //std::cout << "I AM HERE" << std::endl;

    // Loop over rows in res
    for (int i=0; i<ARows; i++){
        // Loop over cols in res
        for (int j=0; j<BCols; j++){
            // Loop over number of terms that go into the calculation of each elements
            for (int k=0; k<ACols; k++){
                // Sum the terms and store in res
                //std::cout << i << std::endl;
                res[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Returns result of shape (l x n)
    return;
}


// Define function that handles vector-matrix multiplication
void Multiply(double *res, double *A, double **B, int ACols, int BRows, int BCols){

    // Only possible when A of shape (1 x m) and B of shape (m x n), remember: (rows x cols)
    assert(ACols == BRows);

    // Loop over cols in res of shape (1 x n)
    for (int j=0; j<BCols; j++){
        // Initialise result at zero
        res[j] = 0;
    }

    // Loop over columns in B
    for (int j=0; j<BCols; j++){
        // Loop over the terms that go into the calculation of a result element
        for (int k=0; k<ACols; k++){
            // Sum the terms and store in res
            res[j] += A[k] * B[k][j];
        }
    }

    // Returns result of shape (1 x n)
    return;
}


// Define function that handles matrix-vector multiplication
void Multiply(double *res, double **A, double *B, int ARows, int ACols, int BRows){

    // Only possible when A of shape (m x n) and B of shape (n x 1), remember: (rows x cols)
    assert(ACols == BRows);

    // Loop over rows in res of shape (n x 1)
    for (int i=0; i<BRows; i++){
        // Initialise result at zero
        res[i] = 0;
    }

    // Loop over rows in A
    for (int i=0; i<ARows; i++){
        // Loop over the terms that go into the calculation of a result element
        for (int k=0; k<BRows; k++){
            // Sum the terms and store in res
            res[i] += A[i][k] * B[k];
        }
    }

    // Returns result of shape (1 x n)
    return;
}


// Define function that handles scalar-matrix multiplication
void Multiply(double **res, double scalar, double **B, int BRows, int BCols){

    // Loop over rows in B
    for (int i=0; i<BRows; i++){
        // Loop over cols
        for (int j=0; j<BCols; j++){
            // Calculate result
            res[i][j] = B[i][j] * scalar;
        }
    }

    // Returns result the shape of B
    return;
}


// Define function that handles matrix-scalar multiplication
void Multiply(double **res, double **B, double scalar, int BRows, int BCols){

    // Loop over rows in B
    for (int i=0; i<BRows; i++){
        // Loop over cols
        for (int j=0; j<BCols; j++){
            // Calculate result
            res[i][j] = scalar * B[i][j];
        }
    }

    // Returns result the shape of B
    return;
}
