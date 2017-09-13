#include "matrix2D.h"

using namespace std;

//constructors
/*
Creates a matrix2D with specified dimensions
*/
template <class Type>
Matrix2D<Type>::Matrix2D( int new_rows,  int new_cols)//:rows(new_rows), cols(new_cols)
{
    this->rows = new_rows;
    this->cols = new_cols;

    //allocate memory for the rows. It is an array that contains pointers to Type.
    matrix2d = new Type* [this->rows];
    //allocate memory for each column. That is, for each line, allocate space for each element in the matrix.
    for( int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
    {
        this->matrix2d[rowsIdx] = new Type[this->cols];
    }
}

/*
This constructor creates a matrix2D that has the specified dimensions and whose elements are initialized to value
*/
template <class Type>
Matrix2D<Type>::Matrix2D( int new_rows,  int new_cols, Type value)
{
    this->rows = new_rows;
    this->cols = new_cols;

    //allocate memory for the rows. It is an array that contains pointers to Type.
    matrix2d = new Type* [this->rows];
    //allocate memory for each column. That is, for each line, allocate space for each element in the matrix.
    for( int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
    {
        this->matrix2d[rowsIdx] = new Type[this->cols];
    }

    for(int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++ )
        for(int colsIdx = 0; colsIdx < this->cols; colsIdx++)
        {
            this->matrix2d[rowsIdx][colsIdx] = value;
        }
}

//copy constructor
/*
The calling matrix is a clone of the input matrix, being allocated and initialized to the latter's values
*/
template <class Type>
Matrix2D<Type>::Matrix2D(const Matrix2D<Type>& new_matrix)
{
    this->rows = new_matrix.getRows();
    this->cols = new_matrix.getCols();

    //allocate memory for the rows. It is an array that contains pointers to Type.
    this->matrix2d = new Type* [this->rows];
    //allocate space for each column. That is, for each line, allocate space for each element in the matrix.
    for(int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
    {
        this->matrix2d[rowsIdx] = new Type[this->cols];
    }

    //copy elements
    for( int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
        for( int colsIdx = 0; colsIdx < this->cols; colsIdx++)
        {
            this->matrix2d[rowsIdx][colsIdx] = new_matrix.getMatrixValue(rowsIdx, colsIdx);
        }
}

template <class Type>
void Matrix2D<Type>::allocateMemory(int dimX, int dimY)
{
    //allocate memory for the rows. It is an array that contains pointers to Type.
    this->matrix2d = new Type* [dimX];
    //allocate space for each column. That is, for each line, allocate space for each element in the matrix.
    for( int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
    {
        this->matrix2d[rowsIdx] = new Type[dimY];
    }
}

//destructor
template <class Type>
Matrix2D<Type>::~Matrix2D()
{
    //delete the columns
    for( int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
    {
        delete [] this->matrix2d[rowsIdx];
    }

    //delete the array that contains pointers to Type
    delete [] this->matrix2d;
}

/*
Overload attribution operators to allow for operatrions such as A = B, where A,B are Matrix2D instances
*/
template <class Type>
Matrix2D<Type>& Matrix2D<Type>::operator=(const Matrix2D<Type>& new_matrix)
{
    this->rows = new_matrix.getRows();
    this->cols = new_matrix.getCols();

    //allocate memory for the rows. It is an array that contains pointers to Type.
    this->matrix2d = new Type* [this->rows];
    //allocate space for each column. That is, for each line, allocate space for each element in the matrix.
    for( int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
    {
        this->matrix2d[rowsIdx] = new Type[this->cols];
    }

    //copy elements
    for( int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
        for( int colsIdx = 0; colsIdx < this->cols; colsIdx++)
        {
            this->matrix2d[rowsIdx][colsIdx] = new_matrix.getMatrixValue(rowsIdx, colsIdx);
        }

    return *this;
}


template <class Type>
Matrix2D<Type>& Matrix2D<Type>::operator+(Matrix2D<Type>& new_matrix)
{
    //copy elements
    for( int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
        for( int colsIdx = 0; colsIdx < this->cols; colsIdx++)
        {
            this->matrix2d[rowsIdx][colsIdx] += new_matrix.getMatrixValue(rowsIdx, colsIdx);
        }

    return *this;
}

//matrix operations
template <class Type>
void Matrix2D<Type>::initializeMatrixValues(Type value)
{
    for( int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
        for( int colsIdx = 0; colsIdx < this->cols; colsIdx++)
        {
            this->setMatrixValue(rowsIdx, colsIdx, value);
        }
}

template <class Type>
void Matrix2D<Type>::copyElementsFromMatrix(Matrix2D<Type>& source)
{
    for( int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
        for( int colsIdx = 0; colsIdx < this->cols; colsIdx++)
        {
            //this->matrix2d[rowsIdx][colsIdx] = source(rowsIdx, colsIdx);
            this->setMatrixValue(rowsIdx, colsIdx, source.getMatrixValue(rowsIdx, colsIdx));
        }
}

/*
It gets as input a matrix mask (only 1 and 0 values) and sets the calling matrix's values to negated source's values
*/
template <class Type>
void Matrix2D<Type>::negateMatrixMask(Matrix2D<Type>& sourceMask)
{
    for(int i = 0; i < this->getRows(); i++)
        for(int j = 0; j < this->getCols(); j++)
    {
        this->matrix2d[i][j] = 1 - sourceMask.getMatrixValue(i,j) ;
    }
}

/*
For the calling matrix object, it computes the natural logarithm of each element of the input matrix object.
Both matrices have same dimensions.
*/
template <class Type>
void Matrix2D<Type>::logNatMatrix(Matrix2D<Type>& source)
{
    for(int i = 0; i < this->getRows(); i++)
        for(int j = 0; j < this->getCols(); j++)
        {
            this->matrix2d[i][j] = log(source.getMatrixValue(i,j));
        }
}

template <class Type>
void Matrix2D<Type>::findFirstNonEqualElement(int &x_first, int &y_first, Type value)
{
    for(int i = 0; i < this->rows; i++)
        for(int j = 0; j < this->cols; j++)
    {
        if(this->matrix2d[i][j] != value)
        {
            x_first = i;
            y_first = j;
            return;
        }
    }

    return;
}

template <class Type>
void Matrix2D<Type>::findLastNonEqualElement(int &x_first, int &y_first, Type value)
{
    for(int i = this->rows - 1; i>=0; i--)
        for(int j = this->cols - 1; j>=0; j--)
    {
        if(this->matrix2d[i][j] != value)
        {
            x_first = i;
            y_first = j;
            return ;
        }
    }

    return;
}

/*
Returns 1 if a row/column has at least a non-zero value, else it returns 0 for that row/column. The output is a vector
Direction: 1 = check on columns
                2 = check on rows
*/
template <class Type>
void Matrix2D<Type>::anyNonZero(vector<int>& result, int direction)
{
    if(direction == 1)
    {
        for(int j = 0; j < this->getCols(); j++)
            for(int i = 0; i < this->getRows(); i++)
            {
                if(this->getMatrixValue(i, j) != 0)
                {
                    result[j] = 1;
                }
            }
    }

    if(direction ==2)
    {
        for(int i = 0; i < this->getRows(); i++)
            for(int j = 0; j < this->getCols(); j++)
            {
                if(this->getMatrixValue(i, j) != 0)
                {
                    result[i] = 1;
                }
            }
    }
}

template <class Type>
void Matrix2D<Type>::anyGreater(vector<int>& result, int direction, int treshold)
{
    //check if a column contains the given value
    if(direction == 1)
    {
        for(int j = 0; j < this->getCols(); j++)
            for(int i = 0; i < this->getRows(); i++)
            {
                if(this->getMatrixValue(i, j) > treshold)
                {
                    result[j] = 1;
                }
            }
    }

    //check if a row contains the given value
    if(direction == 2)
    {
        for(int i = 0; i < this->getRows(); i++)
            for(int j = 0; j < this->getCols(); j++)
            {
                if(this->getMatrixValue(i, j) > treshold)
                {
                    result[i] = 1;
                }
            }
    }
}

/*
The caller is a sub matrix of source input, taking elements between the specified indeces
*/
template <class Type>
void Matrix2D<Type>::getSubMatrix(Matrix2D<Type>& source, int x_first, int x_last, int y_first, int y_last)
{
    int x_min = min(x_first, x_last);
    int x_max = max(x_first, x_last);
    int y_min = min(y_first, y_last);
    int y_max = max(y_first, y_last);

    for(int i = x_min; i <= x_max; i++)
        for(int j = y_min; j <= y_max; j++)
    {
        //index the caller matrix from 0
        this->setMatrixValue(i - x_min, j - y_min, source.getMatrixValue(i, j));
    }
}

template <class Type>
void Matrix2D<Type>::getAbsoluteValuesMatrix(Matrix2D<Type>& source)
{
    for(int i = 0; i < source.getRows(); i++)
        for(int j = 0; j < source.getCols(); j++)
    {
        this->matrix2d[i][j] = abs(source.getMatrixValue(i,j));
    }
}

template <class Type>
void Matrix2D<Type>::conv2DFull(Matrix2D<Type>& kernel, Matrix2D<Type>& result)
{
    Type temp;
    int i, j, ii, jj, m, n, mm, nn;
    //find kernel center
    int kCenterX = kernel.getCols()/2, kCenterY = kernel.getRows()/2;

    for(i = 0; i < this->getRows(); i++)
    {
        for(j = 0; j < this->getCols(); j++)                           // columns
        {
            for(m = kernel.getRows()-1; m>=0; m--)             // kernel rows
            {
                mm = kernel.getRows() - 1 - m;                     // row index of flipped kernel

                for(n = kernel.getCols(); n>=0; n--)             // kernel columns
                {
                    nn = kernel.getRows() - 1 - n;                  // column index of flipped kernel

                    // index of input signal, used for checking boundary
                    ii = i + mm;
                    jj = j + nn;

                    // ignore input samples which are out of bound
                    if( ii >= 0 && ii < this->getRows() + kernel.getRows() -1 && jj >= 0 && jj < this->getCols() + kernel.getCols() -1 )
                    {
                        temp = result.getMatrixValue(ii,jj) + this->matrix2d[i][j] * kernel.getMatrixValue(m, n);
                        result.setMatrixValue(ii,jj, temp);
                    }
                }
            }
        }
    }
}

template <class Type>
void Matrix2D<Type>::conv2DValid(Matrix2D<Type>& kernel, Matrix2D<Type>& result)
{
    Type temp;
    int i, j, m, n;

    for(i = 0; i < result.getRows(); i++)
    {
        for(j = 0; j < result.getCols(); j++)
        {
           for(m = 0; m < kernel.getRows(); m++)
            {
                for(n = 0; n < kernel.getCols() ; n++)
                {
                    temp = result.getMatrixValue(i, j) + this->matrix2d[i+m ][j+n] * kernel.getMatrixValue(m, n);
                    result.setMatrixValue(i, j, temp);
                }
            }
        }
    }
}

/*
Check if calling matrix doesn't have only zeros
*/
template <class Type>
bool Matrix2D<Type>::checkNonZero()
{
    for(int i = 0; i < this->getRows(); i++)
        for(int j = 0; j < this->getCols(); j++)
        {
            if(this->matrix2d[i][j] != 0)
                return true;
        }
    return false;
}


/*
Convert calling matrix to vector, by putting the columns one after another*/
template <class Type>
void Matrix2D<Type>::reshapeToVector(vector<Type>& dest)
{
    for(int j = 0; j < this->getCols(); j++)
        for(int i = 0; i < this->getRows(); i++)
        {
            dest[i + j*this->getRows()] = this->matrix2d[i][j];
        }
}


template <class Type>
void Matrix2D<Type>::reverseMatrix(Matrix2D<Type>& source)
{
    Type temp;

    for(int i = 0; i < source.getRows()/2 + 1; i++)
        for(int j = 0; j < source.getCols(); j++)
    {
        //for matrices with odd number of lines, for the middle line stop indexing columns before it achieves the half of columns number
        if(source.getRows()%2 != 0 && i == (int) source.getRows()/2)
        {
            if(j == source.getCols())
            {
                break;
            }
        }

        temp = source(i,j);
        this->setMatrixValue(i, j, source(source.getRows()-i-1, source.getCols()-j-1));
        this->setMatrixValue(source.getRows() - i - 1, source.getCols() - j - 1, temp);
    }
}

