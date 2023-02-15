#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF
#include "Vector.hpp"

// Adding a template parameter so that we can store arbitrary values of type T instead of only doubles
template<class T>

class Matrix
{
private:
    std::vector<T> mData; // entries of matrix (in row major format)
	int mNumRows, mNumCols; // dimensions of the matrix

public:
    // Copy constructor (this can be automatically done by the compiler)
    /*
	Matrix(const Matrix& otherMatrix){
        // Copy the members
        mNumRows = otherMatrix.mNumRows;
        mNumCols = otherMatrix.mNumCols;
        mData = otherMatrix.mData;
    }
    */

    // Default constructor
	Matrix(int numRows, int numCols){

        // Make sure that the dimensions make sense
        assert(numRows > 0);
        assert(numCols > 0);

        // Set the members according to input
        mNumRows = numRows;
        mNumCols = numCols;

        // Initialise mData as zeros
        mData.resize(numRows*numCols);
    }

    // This is left as is
	int GetNumberOfRows() const{
        return mNumRows;
    }

    // This is left as is
	int GetNumberOfColumns() const{
        return mNumCols;
    }

    // Get data from i,j'th index (the return type is changed to T)
    // i indicate rownumber, j indicate column number
	T& operator()(int i, int j){
        // Ensure that the index is valid
        assert(i >= 0);
        assert(i < mNumRows);
        assert(j >= 0);
        assert(j < mNumCols);

        return mData[mNumCols * i + j];
    }

    //ncols*i+j

    // Get data from i,j'th index (the return type is changed to T)
    // i indicate rownumber, j indicate column number
	T const& operator()(int i, int j) const{
        // Ensure that the index is valid
        assert(i >= 0);
        assert(i < mNumRows);
        assert(j >= 0);
        assert(j < mNumCols);

        return mData[mNumCols * i + j];
    }

	// Overload the assignment operator (this can be automatically done by the compiler)
    /*
	Matrix& operator=(const Matrix& otherMatrix){
        // Ensure that the matrix is the same size, if not the assignment is not possible
        assert(mNumRows == otherMatrix.mNumRows);
        assert(mNumCols == otherMatrix.mNumCols);

        // Assign
        mData = otherMatrix.mData;

        return *this;
    }
    */

    // Overload the unary - operator (defines -M)
    Matrix operator-() const{

        // Define new matrix
        Matrix Mat(mNumRows, mNumCols);

        // Loop over rows and cols
        for (int i = 0; i < mNumRows; i++){
            for (int j = 0; j < mNumCols; j++){
                // Switch the sign of the appropriate entry
                Mat(i,j) = -mData[mNumCols * i + j];
            }
        }
        return Mat;
    }

    // Overload the binary - operator (defines A-B)
    Matrix operator-(const Matrix& m1) const{
        // Ensure that the matrix is the same size, if not the operation is invalid
        assert(mNumRows == m1.mNumRows);
        assert(mNumCols == m1.mNumCols);

        // Define a new matrix
        Matrix Mat(mNumRows, mNumCols);

        // Loop over rows and cols
        for (int i = 0; i < mNumRows; i++){
            for (int j = 0; j < mNumCols; j++){
                // Subtract the appropriate entries
                Mat(i,j) = mData[mNumCols * i + j] - m1.mData[mNumCols * i + j];
            }
        }
        return Mat;
    }

    // Overload the + operator (defines A+B)
    Matrix operator+(const Matrix& m1) const{
        // Ensure that the matrix is the same size, if not the operation is invalid
        assert(mNumRows == m1.mNumRows);
        assert(mNumCols == m1.mNumCols);

        // Define a new matrix
        Matrix Mat(mNumRows, mNumCols);

        // Loop over rows and cols
        for (int i = 0; i < mNumRows; i++){
            for (int j = 0; j < mNumCols; j++){
                // Add the appropriate entries
                Mat(i,j) = mData[mNumCols * i + j] + m1.mData[mNumCols * i + j];
            }
        }
        return Mat;
    }

	// Overload the scalar multiplication M*a (IN THAT ORDER)
	Matrix operator*(double scalar) const{
        // Define new matrix
        Matrix Mat(mNumRows, mNumCols);

        // Loop over rows and cols
        for (int i = 0; i < mNumRows; i++){
            for (int j = 0; j < mNumCols; j++){
                // Multiply the entry with the scalar
                Mat(i,j) = scalar * mData[mNumCols * i + j];
            }
        }
        return Mat;
    }
    
    // Get reference to internal vector
    std::vector<T> const& getStorage() const{
        return mData;
    }

    // EXTRA: add a Print method
    void print() const{
        std::cout << "size: "
                  << "(" << mNumRows << "," << mNumCols << ")"
                  << ", data:\n";
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols - 1; j++)
            {
                std::cout << mData[mNumCols * i + j] << ", ";
            }
            std::cout << mData[mNumCols * i + (mNumCols - 1)] << "\n";
        }
    }

    // Overload the insertion << operator (how it is printed)
    friend std::ostream& operator<<(std::ostream& output, const Matrix& M){
        
        // Loop over rows
        for (int i=0; i<M.mNumRows; i++){
            
            // Begin with a new line for a new row
            output << "\n";

            // Loop over columns
            for (int j=0; j<M.mNumCols; j++){

                // Add element to output
                output << M.mData[M.mNumCols * i + j];

                // Add commas, except if it is the last element of the row
                if (j<M.mNumCols-1){
                    output << ", ";
                }
            }
        }
        return output;
        }

}; // Class Matrix


//Matrix-vector multiplication
/* When creating template functions (ie, outside the main class definition,) we
   need to add a template of type T. And also, of course, specify the type we
   use in the functions. */
template <typename T>
Vector<T> operator*(const Matrix<T>& M, const Vector<T>& V){
    /* 
    Function that calculates the product Mxb for a (p x q) matrix M and a (l x 1) vector b.
    This is only possible if q=l. The output is then a vector of len p.
    */

    // Define the len (l) of the original vector
    int original_vector_size = V.size();

    // Assert that q=l (number of columns in M should be the number of elements in b)
	assert(M.GetNumberOfColumns() == original_vector_size);

    // Initialise the result vector with length p (number of rows in M)
	int new_vector_size = M.GetNumberOfRows();
	Vector<T> result(new_vector_size);

    // Loop over columns and rows in matrix M
	for (int i = 0; i < new_vector_size; i++){
		for (int j = 0; j < original_vector_size; j++){

            // Fill in the result by multiplying elements of each row in the matrix with the corresponding element in b
            // Essentially a scalar product between a row and b
			result[i] += M(i,j) * V[j];
		}
	}
	return result;
}

//Vector-matrix multiplication
template <typename T>
Vector<T> operator*(const Vector<T>& V, const Matrix<T>& M){
    /* 
    Function that calculates the product bxM for a (1 x l) vector and a (p x q) matrix.
    This is only possible if p=l. The output is then a vector of len q.
    */

    // Define the len (l) of the original vector
	int original_vector_size = V.size();

    // Ensure that p=l (number of rows in matrix should be the same as elements in b)
	assert(M.GetNumberOfRows() == original_vector_size);

    // Initialise result vector with q elements
	int new_vector_size = M.GetNumberOfColumns();
	Vector<T> result(new_vector_size);

    // Loop over rows and columns in M
	for (int i = 0; i < new_vector_size; i++){
		for (int j = 0; j < original_vector_size; j++){

            // Fill in the result by multiplying elements of b with the corresponding element in each column in the matrix.
            // Essentially a scalar product between b and a column.
			result[i] += V[j] * M(j,i);
		}
	}
	return result;
}

    /* ____ UNNECESSARY FUNCTIONS/METHODS ____

    ~Matrix()
    {
        for (int i = 0; i < mNumRows; i++)
        {
            delete[] mData[i];
        }
        delete[] mData;
    }

    ___________________________________________*/


#endif
