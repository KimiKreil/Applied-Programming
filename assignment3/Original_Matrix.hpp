#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF
#include "Vector.hpp"

class Matrix
{
private:
	double** mData; // entries of matrix
	int mNumRows, mNumCols; // dimensions

public:
    // copy constructor
	Matrix(const Matrix& otherMatrix)
    {
        mNumRows = otherMatrix.mNumRows;
        mNumCols = otherMatrix.mNumCols;
        mData = new double* [mNumRows];

        for (int i = 0; i < mNumRows; i++)
        {
            mData[i] = new double [mNumCols];
        }
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mData[i][j] = otherMatrix.mData[i][j];
            }
        }
    }

	Matrix(int numRows, int numCols)
    {
        assert(numRows > 0);
        assert(numCols > 0);

        mNumRows = numRows;
        mNumCols = numCols;
        mData = new double* [mNumRows];

        for (int i = 0; i < mNumRows; i++)
        {
            mData[i] = new double [mNumCols];
        }
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mData[i][j] = 0.0;
            }
        }
    }

	~Matrix()
    {
        for (int i = 0; i < mNumRows; i++)
        {
            delete[] mData[i];
        }
        delete[] mData;
    }

	int GetNumberOfRows() const
    {
        return mNumRows;
    }

	int GetNumberOfColumns() const
    {
        return mNumCols;
    }

	double& operator()(int i, int j)
    {
        assert(i >= 0);
        assert(i < mNumRows);
        assert(j >= 0);
        assert(j < mNumCols);

        return mData[i][j];
    }

	double const& operator()(int i, int j) const
    {
        assert(i >= 0);
        assert(i < mNumRows);
        assert(j >= 0);
        assert(j < mNumCols);

        return mData[i][j];
    }

	// overloaded assignment operator
	Matrix& operator=(const Matrix& otherMatrix)
    {
        assert(mNumRows == otherMatrix.mNumRows);
        assert(mNumCols == otherMatrix.mNumCols);

        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mData[i][j] = otherMatrix.mData[i][j];
            }
        }
        return *this;
    }

	Matrix operator-() const // unary -
    {
        Matrix mat(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mat(i,j) = -mData[i][j];
            }
        }
        return mat;
    }

	Matrix operator+(const Matrix& m1) const // binary +
    {
        assert(mNumRows == m1.mNumRows);
        assert(mNumCols == m1.mNumCols);

        Matrix mat(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mat(i,j) = mData[i][j] + m1.mData[i][j];
            }
        }
        return mat;
    }

	Matrix operator-(const Matrix& m1) const // binary -
    {
        assert(mNumRows == m1.mNumRows);
        assert(mNumCols == m1.mNumCols);

        Matrix mat(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mat(i,j) = mData[i][j] - m1.mData[i][j];
            }
        }
        return mat;
    }

	// scalar multiplication
	Matrix operator*(double a) const
    {
        Matrix mat(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mat(i,j) = a*mData[i][j];
            }
        }
        return mat;
    }
}; // class Matrix


//matrix-vector multiplications
Vector operator*(const Matrix& m, const Vector& v)
{
    int original_vector_size = v.size();
	assert(m.GetNumberOfColumns() == original_vector_size);

	int new_vector_length = m.GetNumberOfRows();
	Vector new_vector(new_vector_length);

	for (int i = 0; i < new_vector_length; i++)
	{
		for (int j = 0; j < original_vector_size; j++)
		{
			new_vector[i] += m(i,j)*v[j];
		}
	}

	return new_vector;
}

Vector operator*(const Vector& v, const Matrix& m)
{
	int original_vector_size = v.size();
	assert(m.GetNumberOfRows() == original_vector_size);

	int new_vector_length = m.GetNumberOfColumns();
	Vector new_vector(new_vector_length);

	for (int i = 0; i < new_vector_length; i++)
	{
		for (int j = 0; j < original_vector_size; j++)
		{
			new_vector[i] += v[j]*m(j,i);
		}
	}

	return new_vector;
}


#endif
