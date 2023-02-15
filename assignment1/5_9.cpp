#include <iostream>

// Include the header file
#include "5_9.h"

// Assertion library
#include <assert.h>

// Math library
#include <math.h>

////////////////////
//   Solve Ax=b   //
////////////////////

// Define function to solve Au = b, where A is non-singular and a 3x3 matrix
// A is the coefficient matrix, b is the dependent variable values and x is the solution vector
void solve3by3(double **A, double *b , double *u){

    // Define size of matrix
    int n = 3;

    // Calculate the determinant see here: https://www.mathsisfun.com/algebra/matrix-determinant.html

    // Calculate determinants of submatrices
    double x = A[1][1]*A[2][2] - A[1][2]*A[2][1];
    double y = A[1][0]*A[2][2] - A[1][2]*A[2][0];
    double z = A[1][0]*A[2][1] - A[1][1]*A[2][0];

    // Determinant of full matrix
    double det = A[0][0]*x - A[0][1]*y + A[0][2]*z;

    // Check if matrix is singular (det=0)
    if (det==0){
        std::cout << "WARNING: Determinant is zero => Matrix is singular" << std::endl;
    }

    // Dynamically assign memory to the inverse matrix
    double** inv_mat;
    inv_mat = new double* [n];
    for (int i=0; i<n; i++){
        inv_mat[i] = new double[n];
    }

    // Compute inv. matrix (see "sætning 3.4.1", p. 118, Lineær Algebra, Hesselholt & Wahl)
    inv_mat[0][0] = x * (1/det);
    inv_mat[0][1] = (A[0][2] * A[2][1] - A[0][1] * A[2][2]) * (1/det);
    inv_mat[0][2] = (A[0][1] * A[1][2] - A[0][2] * A[1][1]) * (1/det);

    inv_mat[1][0] = -y * (1/det);
    inv_mat[1][1] = (A[0][0] * A[2][2] - A[0][2] * A[2][0]) * (1/det);
    inv_mat[1][2] = (A[1][0] * A[0][2] - A[0][0] * A[1][2]) * (1/det);

    inv_mat[2][0] = z * (1/det);
    inv_mat[2][1] = (A[2][0] * A[0][1] - A[0][0] * A[2][1]) * (1/det);
    inv_mat[2][2] = (A[0][0] * A[1][1] - A[1][0] * A[0][1]) * (1/det);

    // Compute solution
    for (int i=0; i<n; i++){

        // Initialise solution at zero
        u[i] = 0;

        for (int j=0; j<n; j++){
            u[i] += inv_mat[i][j] * b[j];
        }
    }

    // Delete matrix
    for (int i=0; i<n; i++){
        delete[] inv_mat[i];
    }
    delete[] inv_mat;

    return;
}