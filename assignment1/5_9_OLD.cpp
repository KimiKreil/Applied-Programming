// Include the header file
#include "5_9.h"

// Assertion library
#include <assert.h>

// Math library
#include <math.h>
#include <iostream>

////////////////////
//   Solve Ax=b   //
////////////////////

// Define function to solve Au = b using LU-factorization, forward- and back-substitution
// A is the coefficient matrix, b is the dependent variable values and x is the solution vector
void solve3by3(double **A, double *b , double *x){
    
    
    // Define dimension
    int n = 3;

    /////////////////////////////////////
    //          Partial Pivot          //
    /////////////////////////////////////
    /* 
    Partial pivoting is only row-interchanging and should be stable for most examples.
    It ensures that the largest (absolute) value of each column gets onto the diagonal.
    */

    // Declare variables to use later
    double swap_value;
    double current_piv;
    int current_row;

    // Loop over columns
    for (int k=0; k<n; k++){

        // Find current pivot (for the given column)
        current_piv = fabs( A[k][k] );
        // Note the current row
        current_row = k;

        // Loop over rows below current_row
        for (int r=k; r<n; r++){

            // Check if elements below the pivot for that column is larger
            if (fabs(A[r][k]) > current_piv){

                // Update pivot if element below is larger
                current_piv = fabs(A[r][k]);
                // Update which row it is in
                current_row = r;
            }

            // Check if pivot is needed (if current_piv is not on the diagonal)
            if (current_row != k){
                
                // Loop over columns
                for (int j=0; j<n; j++){

                    // Permute A by swapping rows (for all columns) so current_piv is in the diagonal position
                    swap_value = A[current_row][j]; // current diagonal element
                    A[current_row][j] = A[k][j];
                    A[k][j] = swap_value;
                }

                // Permute B accordingly
                swap_value = b[current_row];
                b[current_row] = b[k];
                b[k] = swap_value;
            }
        }
    }

    ////////////////////////////////////////
    //          LU-decomposition          //
    ////////////////////////////////////////
    /* 
    Perform LU-decommposition, where L is the lower triangular matrix and U is the upper triangular matrix,
    such that A=LU, or in case of pivoting PA=LU where P is a permutation matrix (not explicitly present in the code)
    */

    // -------- Initialise L and U -------- //

    // Dynamically allocate memory for L and U
    double** L;
    L = new double* [n];
    double** U;
    U = new double* [n];
    // This could be done for irregular matrices more ifficiently, see the book p. 65, but for a 3x3 system this is simpler
    for (int i=0; i<n; i++){
        L[i] = new double[n];
        U[i] = new double[n];
    }
    // Loop over rows and columns within n
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            // Make L an identity matrix
            L[i][j] = 0;
            if (i == j){
                L[i][j] = 1;
            }
            // Make U a zero matrix
            U[i][j] = 0;
        }
    } 

    // -------- Compute L -------- //

    // Loop over all columns except the last one
    for (int k = 0; k<n-1; k++){
        // Loop over the subdiagonal rows in the given column
        for (int i=k+1; i<n; i++){
            // Find the value for all subdiagonal elements in L
            L[i][k] = A[i][k] / A[k][k];
        }  

        // -------- Compute U -------- //

        // Loop again, combinations of j,i,k will give us elements of the submatrix in bottom right    
        for (int j=k+1; j<n; j++){
            for (int i=k+1; i<n; i++)
            // Apply transformation to the remaining submatrix
            A[i][j] = A[i][j] - L[i][k] * A[k][j];
        }
        // Loop over the superdiagonal rows
        for (int r=0; r<=k; r++){
            // Assign upper triangular part of the transformed A to U for the given column
            U[r][k] = A[r][k];
        }
    }

    // Assign the upper triangular part of the transformed A to U for the last column (all rows)
    for (int r=0; r<n; r++){
        U[r][n-1] = A[r][n-1];
    }

    ////////////////////////////////////////////
    //          Forward Substitution          //
    ////////////////////////////////////////////
    /*
    Perform forward substitution, computing the solution y to Ly=b
    */

    // Declare the solution vector y (dynamically)
    double* y;
    y = new double [n];

    // Loop over columns in L or rows in b
    for (int j=0; j<n; j++){

        if (L[j][j] == 0){
            std::cout << "ENCOUNTERED SINGULAR MATRIX" << std::endl;
        }

        // Compute the solution component, i.e. the solution to the i'th linear equation
        y[j] = b[j] / L[j][j];

        // Update right hand side (b), looping over the rows in L
        for (int i=j+1; i<n; i++){
            b[i] = b[i] - L[i][j] * y[j];
        }
    }

    /////////////////////////////////////////
    //          Back Substitution          //
    /////////////////////////////////////////
    /*
    Perform back-substitution, computing the solution x to Ux=y
    */

    // Loop backwards over columns
    for (int j=n-1; j>=0; j--){

        if (U[j][j] == 0){
            std::cout << "ENCOUNTERED SINGULAR MATRIX" << std::endl;
        }

        // Compute solution component
        x[j] = y[j] / U[j][j];

        // Update right hand side, y
        for (int i=0; i<j; i++){
            y[i] = y[i] - U[i][j] * x[j];
        }
    }

    /////////////////////////////////////////////////////////////
    //          Free Memory Used for Dynamical Memory          //
    /////////////////////////////////////////////////////////////

    // Delete L and U, no longer needed
    for (int i=0; i<n; i++){
        delete[] L[i];
        delete[] U[i];
    }
    delete[] L;
    delete[] U;

    // Delete y no longer needed
    delete[] y;

    return;
}