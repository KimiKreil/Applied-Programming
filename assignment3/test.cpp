#include "Vector.hpp"
#include "Matrix.hpp"
#include "SparseVector.hpp"
#include <iostream>

int main(){

    //////////////////////
    // Check Vector.hpp //
    //////////////////////
    std::cout << " ------------ Testing the Vector class ------------ \n" << std::endl;
    
    std::cout << "Testing the initialisation of vectors:" << std::endl;
    Vector<int> V(3);
    std::cout << "1) Initialise with size=3 (filled with zeros). We obtain the vector V = " << V << std::endl;

    V[0] = 1;
    V[1] = 2;
    V[2] = 3;
    Vector<int> V_const(V);
    std::cout << "2) Initialise with another vector, should be [1,2,3]. The obtain the vector V = " << V_const << std::endl;
    std::cout << std::endl;
    
    std::cout << "Testing Function to get size. The size obtained is " << V.size() << std::endl;
    std::cout << std::endl;

    std::cout << "Testing the [] operator. The third entry is V[2] = " << V[2] << std::endl;
    std::cout << std::endl;

    Vector<int> V_copy(3);
    V_copy = V;
    std::cout << "Testing the = operator. V_copy = V. V_copy is then: " << V_copy << std::endl;
    std::cout << std::endl;

    std::cout << "Testing the - unary operator. We find that: -V = " << -V << std::endl;
    std::cout << std::endl;
    
    Vector<int> W(3);
    W[0] = 4;
    W[1] = 5;
    W[2] = 6;
    std::cout << "Testing the - binary operator. We define the vector W=[4,5,6]." << std::endl;
    std::cout << "We find that W-V = " << W-V << std::endl;
    std::cout << std::endl;

    std::cout << "We test the + operator. We find that V+W =" << V+W << std::endl;
    std::cout << std::endl;

    std::cout << "We test multiplication by scalar * operator. We find that V*2 = " << V*2 << std::endl;
    std::cout << std::endl;

    std::cout << "We test the CalculateNorm function. We find that the norm of V with p=2 is: " << V.CalculateNorm(2) << std::endl;
    std::cout << "The correct answer is sqrt(1^2+2^3+3^2) = 3.74" << std::endl;
    std::cout << std::endl;

    std::vector<int> data = V.getStorage();
    std::cout << "We test the function getStorage (reference to interval vector). The entries of V are (in order):" << std::endl;
    std::cout << data[0] << ", " << data[1] << ", " << data[2] << ", " << std::endl;
    std::cout << std::endl;


    //////////////////////
    // Check Matrix.hpp //
    //////////////////////
    std::cout << " ------------ Testing the Matrix class------------ \n" << std::endl;

    std::cout << "Testing the initialisation of matrices:" << std::endl;

    Matrix<int> M(2,2);
    std::cout << "1) Initialise with dimensions: nrows=2, ncols=2 (should be filled with zeros). We obtain the matrix M = " << M << std::endl;
    std::cout << std::endl;

    M(0, 0) = 1;
    M(0, 1) = 2;
    M(1, 0) = 3;
    M(1, 1) = 4;
    Matrix<int> M_const(M);
    std::cout << "2) Initialise with another vector (copy constructor), should be [[1,2],[3,4]]. We obtain M = " << M_const << std::endl;
    std::cout << "This has also checked the operator (), which we used to define the entries." << std::endl;
    std::cout << std::endl;

    std::cout << "Testing functions to get dimensions. Number of rows found: " << 
                M.GetNumberOfRows() << ". Number of columns: " << M.GetNumberOfColumns() << std::endl;
    std::cout << std::endl;

    Matrix<int> M_copy(2,2);
    M_copy = M;
    std::cout << "Testing the = operator. M_copy = M. M_copy is the defined as: " << M_copy << std::endl;
    std::cout << std::endl;

    std::cout << "Testing the - unary operator. We find that: -M = " << -M << std::endl;
    std::cout << std::endl;

    Matrix<int> A(2,2);
    A(0, 0) = 5;
    A(0, 1) = 6;
    A(1, 0) = 7;
    A(1, 1) = 8;
    std::cout << "Testing the - binary operator. We define the matrix W=[[5,6],[7,8]]." << std::endl;
    std::cout << "We find that A-M = " << A-M << std::endl;
    std::cout << std::endl;

    std::cout << "We test the + operator. We find that A+M =" << A+M << std::endl;
    std::cout << std::endl;

    std::cout << "We test multiplication by scalar * operator. We find that M*2 = " << M*2 << std::endl;
    std::cout << std::endl;

    std::vector<int> M_data = M.getStorage();
    std::cout << "We test the function getStorage (reference to interval vector). The entries of M are (in row-major order):" << std::endl;
    std::cout << M_data[0] << ", " << M_data[1] << ", " << M_data[2] << ", " << M_data[3] << ", " << std::endl;
    std::cout << std::endl;

    std::cout << "Testing matrix x vector multiplication, and vector x matrix multiplication. We define the vector V=[3,2]." << std::endl;
    Vector<int> V2(2);
    V2[0] = 3;
    V2[1] = 2;
    std::cout << "V x M = " << V2*M << ". The true answer is [9, 14]." << std::endl;
    std::cout << "M x V = " << M*V2 << ". The true answer is [7, 17]." << std::endl;
    std::cout << std::endl;


    ////////////////////////////
    // Check SparseVector.hpp //
    ////////////////////////////
    std::cout << " ------------ Testing the SparseVector class------------ \n" << std::endl;

    std::cout << "s: Empty vector of size 10:\n";
    SparseVector<int> s(10);
    s.print();

    std::cout << "\ns2: Empty vector of size 0:\n";
    SparseVector<int> s2;
    s2.print();

    std::cout << "\nSet 4 values of s, out of order.\n";
    s.setValue(1, 3);
    s.setValue(3, 4);
    s.setValue(6, 1);
    s.setValue(2, 5);


    std::cout << "Then print s:\n";
    for (int i = 0; i<10; i++)
    {
        std::cout << i << ", " << s.getValue(i) << "\n";
    }

    std::cout << "\ns3\n"; 
    SparseVector<int> s3(10);
    s3.setValue(1, 4);
    s3.setValue(0, 3);
    s3.print();

    std::cout << "\ns+s3:\n";
    (s+s3).print();

    std::cout << "\ns-s3:\n";
    (s-s3).print();

    Matrix<int> sm(5, 5);
    sm(0,0) = 1;
    sm(1,1) = 1;
    sm(0,3) = 1;
    sm(2,0) = 1;
    sm(2,2) = 1;
    sm(3,3) = 1;
    sm(4,4) = 1;

    SparseVector<int> s4(5);
    s4.setValue(1, 3);
    s4.setValue(3, 2);

    std::cout << "\ntesting matrix-vector product. Matrix:\n";
    sm.print();
    std::cout << "vector [0, 3, 0, 2, 0]. Result should be [2,3,0,2,0]\n";
    (sm*s4).print();

    std::cout << "vector-matrix product of same matrix/vector.\n"
              << "Result should be [0, 3, 0, 2, 0]\n";
    (s4*sm).print();


    return 1;
}