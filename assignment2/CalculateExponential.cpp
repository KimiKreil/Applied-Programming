#include "CalculateExponential.hpp"
#include "ComplexNumber.hpp"
#include <cmath>

// First we create a few helper function that can help us with Complex matrix operations
//Complex_Matrix_Multiplication(Last_term, A, Current_term);
void Complex_Matrix_Multiplication(ComplexNumber **A, ComplexNumber **B, ComplexNumber **Result){
    /*
    Performs multiplication of complex matrices A and B and saves it to complex matrix Result: Result = AB
    It works for two 3x3 matrices and thus follows the general rule (nxm) X (pxq) = (nxq) if m==p
    */

    // Define the size of the dimension
    int N = 3;
    
    // Loop over rows in A
    for (int i=0; i<N; i++){
        // Loop over columns in B
        for (int j=0; j<N; j++){

            // Set scalar-product to zero for that element in the result matrix
            ComplexNumber scalar_prod = ComplexNumber();

            // Loop over m, i.e. elements in one row/column
            for (int k=0; k<N; k++){
                
                // Add the k'th term to the scalar product
                // The operator * is overloaded for the Complex Number Class
                scalar_prod = scalar_prod + A[i][k] * B[k][j];
            }

            // Update the i,j element of the result matrix to the scalar product of the A-row and the B-col
            Result[i][j] = scalar_prod;
        }
    }

    return;
}


void Complex_Matrix_Addition(ComplexNumber **A, ComplexNumber **B, ComplexNumber **Result){
    /*
    Performs addition of two complex 3x3 matrices A and B, and saves it to complex matrix Result: Result = A + B
    */

   // Define the size of the dimension
   int N = 3;

   // Loop over rows in A
   for (int i=0; i<N; i++){
       // Loop over cols in A
       for (int j=0; j<N; j++)

       // Perform addition (+ operator is overloaded in complexnumber class)
       Result[i][j] = A[i][j] + B[i][j];
   }
}

void Complex_Matrix_Division_by_Scalar(ComplexNumber **A, ComplexNumber b, ComplexNumber **Result){
    /*
    Performs division of a complex 3x3 matrix A by a scalar b (possibly complex) and saves it to complex matrix Result: Result = A/b
    */

    // Define the size of the dimension
    int N = 3;

    // Loop over rows in A
    for (int i=0; i<N; i++){
        // Loop over cols in A
        for (int j=0; j<N; j++){

            // The operator / is overloaded for the complex number class
            Result[i][j] = A[i][j] / b;
        }
    }
}


void CalculateExponential(ComplexNumber **A, int nMax, ComplexNumber **res){
    /*
    The exponential of a matrix A is given by the series expansion: exp(A) = sum_{n=0}^{nMax} (A^n)/(n!)
    
    We will calculate one term at a time and add to the result matrix "res", thus summing them up to nMax.
    The n'th term is calculated from the (n-1) term: x_n = (A^{n-1} * A) / (n * (n-1)!)  = x_{n-1} * (A/n)

    We start out with the identiy matrix since this is the first term. The series starts as: I + A + AA/2! + AAA/3! ...
    */

    // Define the size of the dimension
    int N = 3;

    // Dynamically assign memory to current_term and last_term 3x3 complex matrices
    ComplexNumber **Current_term = new ComplexNumber* [3];
    ComplexNumber **Last_term = new ComplexNumber* [3];
    for (int i=0; i<N; i++){
        Current_term[i] = new ComplexNumber[3];
        Last_term[i] = new ComplexNumber[3];

        // Loop over cols
        for (int j=0; j<N; j++){
            // Initialise Current_term as a zero matrix
            Current_term[i][j] = ComplexNumber();

            // Initialise Last_term as A (2nd term)
            Last_term[i][j] = A[i][j];

            // Initialise res as an identity matrix (1st term)
            res[i][j] = ComplexNumber();
        }
        res[i][i] = ComplexNumber(1);
    }

    // Update res to be the sum of the two first terms
    Complex_Matrix_Addition(res, A, res); // A, B, Result

    // Loop over remaining n's up to nMax
    for (int n=2; n<=nMax; n++){

        // Calculate current term from last term x_n = x_{n-1} * (A/n)
        
        // Multiply with A
        Complex_Matrix_Multiplication(Last_term, A, Current_term); // A, B, Result - is this the right way or should it be A,current_term??

        // Divide by n
        Complex_Matrix_Division_by_Scalar(Current_term, n, Current_term); // A, b, Result
        //printMatrix(Current_term,3,3);
        // Add current_term to result (compute the sum)
        Complex_Matrix_Addition(res, Current_term, res); // A, B, Result

        // Update Last term to be the current term
        ComplexNumber** temp = Last_term;
        Last_term = Current_term;
        Current_term = temp;
    }

    // Free up memory from current_term
    for (int i=0; i<N; i++){
        delete[] Current_term[i];
        delete[] Last_term[i];
    }
    delete[] Current_term;
    delete[] Last_term;

    return;
}

//non mandatory
void printMatrix(ComplexNumber **A, int rows, int cols){
    
    // Loop over rows
    for (int i = 0; i < rows; i++){
        // Loop over cols
        for (int j = 0; j < cols; j++){

            // Print element with a space after
            std::cout << A[i][j] << " ";
        }
        // Skip line for next row
        std::cout << std::endl;
    }
}