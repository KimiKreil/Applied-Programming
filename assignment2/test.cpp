#include <iostream>
#include "ComplexNumber.hpp"
#include "CalculateExponential.hpp"
#include "Matrix2x2.hpp"
#include "Student.hpp"
#include "GraduateStudent.hpp"
#include "PhdStudent.hpp"
#include "Exercise82.hpp"
#include "Exception.hpp"
#include "OutOfRangeException.hpp"
#include "FileNotOpenException.hpp"

int main(){

    std::cout << " ------------- Checking 6.1.1-6 ------------- \n" << std::endl;

    // Define a complex number to use
    ComplexNumber z(1,2);

    // Check we can get real and imaginary part
    std::cout << "Checking 6.1.1-2: access to private members real and imaginary part. We use the complex number z = " << z << ".\n" << std::endl;

    std::cout << "Using the method .GetRealPart() and .GetImaginaryPart():" << std::endl;
    std::cout << "The real part is " << z.GetRealPart() << " and the imaginary part is " << z.GetImaginaryPart() << "\n" << std::endl;

    std::cout << "Using the friend functions RealPart(z) and ImaginaryPart(z):" << std::endl;
    std::cout << "The real part is " << RealPart(z) << " and the imaginary part is " << ImaginaryPart(z) << "\n\n" << std::endl;

    // Check copy constructor
    std::cout << "Checking 6.1.3-4: overidden constructors\n"<< std::endl;

    ComplexNumber z_copy = ComplexNumber(z);
    std::cout << "Using the copy constructor, we construct a copy of z = " << z << "." << std::endl;
    std::cout << "The copy is: " << z_copy << ".\n" << std::endl;

    ComplexNumber z_real = ComplexNumber(1);
    std::cout << "Constructing the complex number with only a real part of z, it becomes: " << z_real << ".\n" << std::endl;

    std::cout << "Checking 6.1.5-6: calculate the conjugate of z.\n" << std::endl;
    std::cout << "The conjugate of z is " << z.CalculateConjugate() << " using CalculateConjugate().\n" << std::endl;
    z.SetConjugate();
    std::cout << "The conjugate of z is " <<  z << " using SetConjugate() (This changes z).\n" << std::endl;  


    std::cout << " ------------- Checking 6.1.7 ------------- \n" << std::endl;   

    // Check calculate exponential

    // Define variables
    int power = 100;
    ComplexNumber **A_mat = new ComplexNumber* [3];
    ComplexNumber **Result = new ComplexNumber* [3];
    for (int i=0; i<3; i++){
        A_mat[i] = new ComplexNumber[3];
        Result[i] = new ComplexNumber[3];
    }
    A_mat[0][0] = ComplexNumber(0);
    A_mat[0][1] = ComplexNumber(1);
    A_mat[0][2] = ComplexNumber(0);

    A_mat[1][0] = ComplexNumber(1);
    A_mat[1][1] = ComplexNumber(0);
    A_mat[1][2] = ComplexNumber(0,-1);

    A_mat[2][0] = ComplexNumber(0);
    A_mat[2][1] = ComplexNumber(0,1);
    A_mat[2][2] = ComplexNumber(0);

    std::cout << "We will calculate exp(A) through its series expansion where the infinite sum is truncated at n = " << power << std::endl;
    std::cout << "The matrix A in this example is given by:" << std::endl;
    printMatrix(A_mat,3,3);
    std::cout << std::endl;

    CalculateExponential(A_mat, power, Result);
    std::cout << "The function finds the solution matrix to be:" << std::endl;
    printMatrix(Result,3,3);
    std::cout << std::endl;

    std::cout << "The true solution (from wolfram alpha) is:" << std::endl;
    std::cout << 1.58909 << " " << 1.3683 << " " << -0.589092 << "i " << std::endl;
    std::cout << 1.3683 << " " << 2.1781 << " " << -1.3683 << "i " << std::endl;
    std::cout << 0.58909 << "i " << 1.3683 << "i " << 1.58909 << " " << std::endl;
    std::cout << std::endl;
    
    
    std::cout << " ------------- Checking 6.2 ------------- " << std::endl; 
    std::cout << "Matrix2x2 class\n" << std::endl;

    std::cout << "6.2.1: Check default constructor - all elements should be zero here" << std::endl;
    Matrix2x2 empty = Matrix2x2();
    empty.Print();
    std::cout << std::endl;

    std::cout << "6.2.2-3: Check copy constructor and constructor with four entires" << std::endl;
    std::cout << "Using constructor with four entries we get:" << std::endl;
    Matrix2x2 mat = Matrix2x2(1,2,3,4);
    mat.Print();
    std::cout << std::endl;
    std::cout << "The copy constructor makes the matrix:" << std::endl;
    Matrix2x2 mat_copy = Matrix2x2(mat);
    mat_copy.Print();
    std::cout << "\n" << std::endl;

    std::cout << "6.2.4: determinant" << std::endl;
    std::cout << "We will check the matrix from before A=[[1,2][3,4]]." << std::endl;
    std::cout << "The determinant should be -2." << std::endl;
    std::cout << "The code finds the determinant: " << mat.CalcDeterminant() << std::endl;
    std::cout << "\n" << std::endl;

    std::cout << "6.2.5: inverse matrix" << std::endl;
    std::cout << "We will check the matrix from before A=[[1,2][3,4]]." << std::endl;
    std::cout << "The inverse should be A^-1=[[-2,1][3/2,-1/2]]." << std::endl;
    std::cout << "The code finds the inverse:" << std::endl;
    Matrix2x2 inv = mat.CalcInverse();
    inv.Print();
    std::cout << "\n" << std::endl;

    std::cout << "6.2.6: assignment operator" << std::endl;
    std::cout << "We will check the matrix from before A=[[1,2][3,4]]." << std::endl;
    std::cout << "Using the assignment operator to assign this to a matrix B=A, B is:" << std::endl;
    Matrix2x2 B = mat;
    B.Print();
    std::cout << "\n" << std::endl;

    std::cout << "6.2.7: Overloading of the unary subtraction operator" << std::endl;
    std::cout << "We will check the matrix from before A=[[1,2][3,4]]." << std::endl;
    std::cout << "Using the assignment operator to assign this to a matrix B=-A, B is:" << std::endl;
    Matrix2x2 B_minus = -mat;
    B_minus.Print();
    std::cout << "\n" << std::endl;

    std::cout << "6.2.8: Overloading of the binary addition and subtraction operators" << std::endl;
    std::cout << "We will check the matrix from before A=[[1,2][3,4]]." << std::endl;
    std::cout << "If B = A+A, the code finds B to be:" << std::endl;
    Matrix2x2 A_plus_A = mat + mat;
    A_plus_A.Print();
    std::cout << "\n" << std::endl;
    std::cout << "If B = A-A, the code finds B to be:" << std::endl;
    Matrix2x2 A_minus_A = mat - mat;
    A_minus_A.Print();
    std::cout << "\n" << std::endl;

    std::cout << "6.2.9: multiplies a matrix by a specified double precision floating point variable" << std::endl;
    std::cout << "We will check the matrix from before A=[[1,2][3,4]] and multiply it by 2, the result is:" << std::endl;
    mat.MultScalar(2);
    mat.Print();
    std::cout << "\n" << std::endl;


    std::cout << " ------------- Checking 7.1 ------------- \n" << std::endl;
    std::cout << "Check the different classes of students, and their initialisations." << std::endl;
    std::cout << "For the MoneyOwed function, remember graduate students dont pay tuition fees, \nand phd-students don't pay at all." << std::endl;
    std::cout << std::endl;
    Student stud;
    Student stud2("stud", 10, 100);
    stud.print();
    stud2.print();
    GraduateStudent gstud;
    GraduateStudent gstud2("stud2", 10, 100, true);
    gstud.print();
    gstud2.print();
    PhdStudent pstud("stud3", 10, 100, true);
    pstud.print();
    std::cout << std::endl;

    std::cout << "______ DEBUGGING _______" << std::endl;
    // Can the problem be that setfines and getfines is defined in student.cpp and not in student.hpp and thus not present for graduate students?
    stud2.SetLibraryFines(-200);
    stud2.print();
    std::cout << "Printing the library fines: " << stud2.GetLibraryFines() << "\n" << std::endl;

    gstud2.SetLibraryFines(-200);
    gstud2.print();
    std::cout << "Printing the library fines: " << gstud2.GetLibraryFines() << "\n" << std::endl;

    pstud.SetLibraryFines(-200);
    pstud.print();
    std::cout << "Printing the library fines: " << pstud.GetLibraryFines() << "\n" << std::endl;

    /*

    std::cout << " ------------- Checking 8.2 ------------- \n" << std::endl;
    std::cout << "Template calculate absolute function." << std::endl;
    std::cout << "Abs(-3) = " << CalcAbs<int>(-3) << " and Abs(3) = " << CalcAbs<int>(3) << " when the inputs are int." << std::endl;
    std::cout << "Abs(-3.1) = " << CalcAbs<double>(-3.1) << " and Abs(3.1) = " << CalcAbs<double>(3.1) << " when the inputs are double." << std::endl;
    std::cout << std::endl;


    std::cout << " ------------- Checking 9.1 ------------- \n" << std::endl;    
    // Write a catch block which is able to catch a generic exception but can
    // also differentiate between these two types of errors.

    // Well, the differentiator is the tag - either FILE or RANGE. So we just
    // check the tag. This code is inspired by p. 168 in the book.
    for (int i=0; i<5; i++)
    {
        std::cout << "EXCEPTION NUMBER "<<i<<"\n";
        try
        {
            // do stuff
            int val = rand() % 3;
            if (val == 1)
            {
                // Throw an out of range exception
                std::cout << "Sending out of range\n";
                throw(OutOfRangeException("You're out of range dummy"));
            }
            else if (val == 2)
            {
                std::cout << "Sending File not open\n";
                throw(FileNotOpenException("File's not open, dummy"));
            }
            else
            {
                std::cout << "throwing generic exception\n";
                throw(Exception("GENERIC", "A generic problem"));
            }
        }
        catch (FileNotOpenException &error)
        {
            std::cout << "File not found error!\n";
            error.PrintDebug();
        }
        catch (OutOfRangeException &error)
        {
            std::cout << "Out of range exception!\n";
            error.PrintDebug();
        }
        catch (Exception &error)
        {
            std::cout << "Generic Exception!\n";
            error.PrintDebug();
        }
        std::cout << "\n";
    }
    */
    return 1;
}