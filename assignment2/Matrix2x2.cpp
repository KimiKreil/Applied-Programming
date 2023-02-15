#include "Matrix2x2.hpp"
#include <cassert>
#include <iostream>

// ----- 6.2.0: Get methods for the private variables -----
// I THINK THIS IS ALREADY IMPLEMENTED???

// ----- 6.2.1: default constructor that initialises all entries of the matrix to zero -----
Matrix2x2::Matrix2x2(){
    // Initialise all elements at zero
    val00 = 0;
    val01 = 0;
    val10 = 0;
    val11 = 0;
}

// ----- 6.2.2: An overridden copy constructor. -----
Matrix2x2::Matrix2x2(const Matrix2x2& other){
    // Initialise all elements as the elements of input M
    val00 = other.Getval00();
    val01 = other.Getval01();
    val10 = other.Getval10();
    val11 = other.Getval11();
}

// ----- 6.2.3: A constructor that specifies the four entries -----
Matrix2x2::Matrix2x2(double a, double b, double c, double d){
    // Allocates the doubles a,b,c and d to the entries 00, 01, 10 and 11 respectively
    val00 = a;
    val01 = b;
    val10 = c;
    val11 = d;
}

// ----- 6.2.4: method (function) that returns the determinant of the matrix. -----
double Matrix2x2::CalcDeterminant() const{
    // Calculates the determinant by |A| = ad - bc
    return val00 * val11 - val01 * val10;
}

// ----- 6.2.5: A method that returns the inverse of the matrix, if it exists. -----
Matrix2x2 Matrix2x2::CalcInverse() const{
    // Calculates the inverse with the formula for a 2x2 matrix found here: https://www.cuemath.com/algebra/inverse-of-2x2-matrix/

    // Determinant
    double det = CalcDeterminant();

    // Adjoint of matrix
    Matrix2x2 Inv(val11/det, -val01/det, -val10/det, val00/det);

    return Inv;
}

// ----- 6.2.6: Overloading of the assignment operator, allowing us to write code such as A = B -----
Matrix2x2& Matrix2x2::operator=(const Matrix2x2& z){
    // Define the matrix elements from the elements of z
    val00 = z.Getval00();
    val01 = z.Getval01();
    val10 = z.Getval10();
    val11 = z.Getval11();
    return *this;
}

// ----- 6.2.7: Overloading of the unary subtraction operator, allowing us to write code such as A = -B -----
Matrix2x2 Matrix2x2::operator-() const{
    // Return a matrix with all elements with inverted sign
    return Matrix2x2(-val00, -val01, -val10, -val11);

}

// ----- 6.2.8: Overloading of the binary addition and subtraction operators, allowing us to write code such as A = B + C or A = B - C -----
Matrix2x2 Matrix2x2::operator+(const Matrix2x2& z) const{
    // Add each element valXX with the corresponding of the matrix behind the + sign z
    double a = val00 + z.Getval00();
    double b = val01 + z.Getval01();
    double c = val10 + z.Getval10();
    double d = val11 + z.Getval11();
    return Matrix2x2(a,b,c,d);
}

Matrix2x2 Matrix2x2::operator-(const Matrix2x2& z) const{
    // Subtract from each element valXX the corresponding of the matrix behind the + sign z
    double a = val00 - z.Getval00();
    double b = val01 - z.Getval01();
    double c = val10 - z.Getval10();
    double d = val11 - z.Getval11();
    return Matrix2x2(a,b,c,d);
}

// ----- 6.2.9: A method that multiplies a matrix by a specified double precision floating point variable. -----
void Matrix2x2::MultScalar(double scalar){
    val00 *= scalar;
    val01 *= scalar;
    val10 *= scalar;
    val11 *= scalar;
}

// Extra
void Matrix2x2::Print() const{
    std::cout << val00 << " " << val01 << "\n" << val10 << " " << val11 <<"\n";
}






