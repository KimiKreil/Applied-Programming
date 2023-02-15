#include <iostream>
#include "2_6.h"
#include "3_3.h"
#include "5_3.h"
#include "5_4.h"
#include "5_6.h"
#include "5_9.h"
#include "5_10.h"

int main(){

    std::cout << " ------------- Checking 2.6 ------------- \n" << std::endl;
    /*
    Check the Newton Rhapson algorithm solving f(x) = 0, for f(x) = e^x + x^3 - 5
    */

    double initialGuess = 0;
    double epsilon = 0.001; 
    double x = newton_Raphson(initialGuess, epsilon);

    std::cout << "Initial guess = 0, final root = " << x << "\n" << std::endl;
    std::cout << "True root is approximately 1.19367 \n" << std::endl;


    std::cout << " ------------- Checking 3.3 ------------- \n" << std::endl;
    /*
    Checking the Implicit Euler method estimating the solution function to the differential equation dy/dx=-y with y(0)=1
    in the interval 0<x<1. The result is found in the file xy.dat and should be plottet to verify the result, comparing it
    to the true solution y=e^-x.
    */

    int n = 100;
    implicit_Euler(n);

    std::cout << "The result in the xy.dat file should be plotted and compared to y=e^-x to verify the solution. \n" << std::endl;


    std::cout << " ------------- Checking 5.3 ------------- \n" << std::endl;
    /*
    Check the functions that swap values of a and b, using respectively pointers and references.
    */

    double a = 1;
    double b = 2;
    std::cout << "Initialising a and b with values:" << std::endl;
    std::cout << "a = " << a << ", b = " << b << "\n" << std::endl;

    std::cout << "Swapping values with pointers:" << std::endl;
    swap_pointer(&a, &b);
    std::cout << "a = " << a << ", b = " << b << "\n" << std::endl;

    std::cout << "Swapping values with references:" << std::endl;
    swap_ref(a, b);
    std::cout << "a = " << a << ", b = " << b << "\n" << std::endl;


    std::cout << " ------------- Checking 5.4 ------------- \n" << std::endl;
    /*
    Check the functions for calculating respectively the mean and standard deviation of an array.
    */

    double arr[5] = {1., 2., 3., 4., 5.};
    int len = sizeof(arr)/sizeof(arr[0]);
    double mean = calc_mean(arr, len);
    double sigma = calc_std(arr, len);

    std::cout << "The mean and standard deviation of the array [1,2,3,4,5] is found to be respectively \n" << std::endl;
    std::cout << mean << " and " << sigma << "\n" << std::endl;

    std::cout << "The true values are respectively \n" << std::endl;
    std::cout << "3 and 1.5811 \n" << std::endl;


    std::cout << " ------------- Checking 5.6 ------------- \n" << std::endl;
    /*
    Check the function Multiply for various inputs.
    */
    std::cout << "This function performs multiplication between scalar, vectors and matrices." << std::endl;
    std::cout << "We will use the scalar S=5, the vector V=[1,2,3], \nand the matrix M=[ [1,2,3], [4,5,6], [7,8,9] ] \n" << std::endl;

    // Define the scalar and the vector [1,2,3]
    double scalar = 5;
    double vector[] = {1,2,3};

    // Dynamically assign memory to a nxn matrix
    int size = 3;
    double **matrix;
    matrix = new double* [size];
    for (int i=0; i<size; i++){
        matrix[i] = new double [size];
    }
    // Fill the matrix with [ [1,2,3],[4,5,6],[7,8,9] ]
    int fill = 0;
    for (int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            fill += 1;
            matrix[i][j] = fill;
        }
    }

    //////////////////////////////////
    // Matrix-Matrix Multiplication //
    //////////////////////////////////

    // Dynamically assign memory to a result matrix
    double **res_MM;
    res_MM = new double* [size];
    for (int i=0; i<size; i++){
        res_MM[i] = new double[size];
    }
    for (int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            res_MM[i][j] = 0;
        }
    }
    
    // Get results
    Multiply(res_MM, matrix, matrix, 3, 3, 3, 3);
    std::cout << "## MATRIX-MATRIX MULTIPLICATION ##" << std::endl;
    std::cout << "The function found the solution: \nMM =" << std::endl;
    std::cout << "[ [" << res_MM[0][0] << "," << res_MM[0][1] << "," << res_MM[0][2] << "]\n" << std::endl;
    std::cout << " [" << res_MM[1][0] << "," << res_MM[1][1] << "," << res_MM[1][2] << "]\n" << std::endl;
    std::cout << " [" << res_MM[2][0] << "," << res_MM[2][1] << "," << res_MM[2][2] << "] ]\n" << std::endl;

    // Delete res
    for (int i=0; i<size; i++){
        delete[] res_MM[i];
    }
    delete[] res_MM;

    //////////////////////////////////
    // Vector-Matrix Multiplication //
    //////////////////////////////////

    double res_VM[size];

    // Get results
    Multiply(res_VM, vector, matrix, 3, 3, 3);
    std::cout << "## VECTOR-MATRIX MULTIPLICATION ##" << std::endl;
    std::cout << "The function found the solution: VM = [" << res_VM[0] << ", " << res_VM[1] << ", " << res_VM[2] << "]" << std::endl;
    std::cout << "The true solution: VM = [30, 36, 42]\n" << std::endl;

    //////////////////////////////////
    // Scalar-Matrix Multiplication //
    //////////////////////////////////

    // Dynamically assign memory to a result matrix
    double **res_SM;
    res_SM = new double* [size];
    for (int i=0; i<size; i++){
        res_SM[i] = new double[size];
    }
    for (int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            res_SM[i][j] = 0;
        }
    }

    // Get results
    Multiply(res_SM, scalar, matrix, 3, 3);
    std::cout << "## SCALAR-MATRIX MULTIPLICATION ##" << std::endl;
    std::cout << "The function found the solution: \nSM =" << std::endl;
    std::cout << "[ [" << res_SM[0][0] << "," << res_SM[0][1] << "," << res_SM[0][2] << "]\n" << std::endl;
    std::cout << " [" << res_SM[1][0] << "," << res_SM[1][1] << "," << res_SM[1][2] << "]\n" << std::endl;
    std::cout << " [" << res_SM[2][0] << "," << res_SM[2][1] << "," << res_SM[2][2] << "] ]\n" << std::endl;

    // Delete res and matrix
    for (int i=0; i<size; i++){
        delete[] res_SM[i];
        delete[] matrix[i];
    }
    delete[] res_SM;
    delete[] matrix;


    std::cout << " ------------- Checking 5.9 ------------- \n" << std::endl;
    /*
    Check the function for solving the 3x3 linear system Au=b.
    */

    double b_vec[] = {4,-12,17};
    double x_vec[3] = {};

    double **mat3x3;
    mat3x3 = new double* [3];
    for (int i=0; i<3; i++){
        mat3x3[i] = new double [3];
    }

    mat3x3[0][0] = 2;
    mat3x3[0][1] = -1; 
    mat3x3[0][2] = 0;
    mat3x3[1][0] = -6;
    mat3x3[1][1] = 5;
    mat3x3[1][2] = -4;
    mat3x3[2][0] = 3;
    mat3x3[2][1] = 4;
    mat3x3[2][2] = 0;
    
    std::cout << "Finding the solution to Ax=b, where A=[[2,-1,0],[-6,5,-4],[3,4,0]] and b=[4,-12,17] \n" << std::endl;
    solve3by3(mat3x3, b_vec , x_vec);
    std::cout << "The solution vector found is x = [" << x_vec[0] << "," << x_vec[1] << "," << x_vec[2] << "]\n" << std::endl;
    std::cout << "The true solution is x = [3,2,1]\n" << std::endl;

    // Delete matrix
    for (int i=0; i<size; i++){
        delete[] mat3x3[i];
    }
    delete[] mat3x3;

    std::cout << " ------------- Checking 5.10 ------------- \n" << std::endl;
    /*
    Check the function for solving the nxn linear system Au=b using Gaussian elimination with pivoting.
    */

    double b_vector[] = {6,-3,-2,0};
    double x_vector[4] = {};

    double **mat4x4;
    mat4x4 = new double* [4];
    for (int i=0; i<4; i++){
        mat4x4[i] = new double [4];
    }
    mat4x4[0][0] = 1;
    mat4x4[0][1] = 0; 
    mat4x4[0][2] = 1;
    mat4x4[0][3] = 2;

    mat4x4[1][0] = 0;
    mat4x4[1][1] = 1;
    mat4x4[1][2] = -2;
    mat4x4[1][3] = 0;

    mat4x4[2][0] = 1;
    mat4x4[2][1] = 2;
    mat4x4[2][2] = -1;
    mat4x4[2][3] = 0;

    mat4x4[3][0] = 2;
    mat4x4[3][1] = 1;
    mat4x4[3][2] = 3;
    mat4x4[3][3] = -2;

    std::cout << "Finding the solution to Ax=b, where A=[[1,0,1,2],[0,1,-2,0],[1,2,-1,0],[2,1,3,-2]] and b=[6,-3,-2,0] \n" << std::endl;
    guassian_elimination(mat4x4, b_vector , x_vector, 4);
    std::cout << "The solution vector found is x = [" << x_vector[0] << "," << x_vector[1] << "," << x_vector[2] << "," << x_vector[3] << "]\n" << std::endl;
    std::cout << "The true solution is x = [1,-1,1,2]\n" << std::endl;

    // Delete matrix
    for (int i=0; i<size; i++){
        delete[] mat4x4[i];
    }
    delete[] mat4x4;

    return 1;
}
