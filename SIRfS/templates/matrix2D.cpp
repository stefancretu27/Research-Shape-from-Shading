#include "matrix2D.h"

using namespace std;

/*
*Constructors
*/
//Creates a matrix2D with specified dimensions
template <class Type>
Matrix2D<Type>::Matrix2D( int new_rows,  int new_cols):rows(new_rows), cols(new_cols)
{
    //allocate memory
    if(rows != 0 && cols !=0)
    {
        this->container = new Type[this->rows*this->cols];
    }
    else
    {
        this->container = NULL;
    }
}

//Constructor with data initializations: this constructor creates a matrix2D that has the specified dimensions and whose elements are initialized to the given value
template <class Type>
Matrix2D<Type>::Matrix2D( int new_rows,  int new_cols, Type value):rows(new_rows), cols(new_cols)
{
    //allocate memory
    this->container = new Type[this->rows*this->cols];

    /*
    for(int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++ )
        for(int colsIdx = 0; colsIdx < this->cols; colsIdx++)
        {
            this->setMatrixValue(rowsIdx, colsIdx, value);
        }
        */
    for(unsigned int idx = 0; idx < this->getDim(); idx++)
    {
        this->container[idx] = value;
    }
}

//Copy constructor: The calling matrix is a clone of the input matrix, being allocated and initialized to the latter's values
template <class Type>
Matrix2D<Type>::Matrix2D(const Matrix2D<Type>& new_matrix):rows(new_matrix.getRows()), cols(new_matrix.getCols())
{
    //allocate memory
    this->container = new Type[this->rows*this->cols];

    //copy elements
    /*
    for( int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
        for( int colsIdx = 0; colsIdx < this->cols; colsIdx++)
        {
            this->setMatrixValue(rowsIdx, colsIdx, new_matrix.getMatrixValue(rowsIdx, colsIdx));
        }
        */
    for(unsigned int idx = 0; idx < this->getDim(); idx++)
    {
        this->container[idx] = new_matrix.getMatrixValue(idx);
    }
}

//Destructor
template <class Type>
Matrix2D<Type>::~Matrix2D()
{
    //delete the array
    delete [] this->container;
}

template <class Type>
void Matrix2D<Type>::setMatrix2D(Type* data, int new_rows,  int new_cols, bool transp)
{
    this->rows = new_rows;
    this->cols = new_cols;

    this->container = new Type[this->rows*this->cols];

    //in Matlab the matrices are stored column after column, in the contiguous array gotten as parameters (data), so it needs to be transposed
    if(transp)
    {
        //copy elements
        for( int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
            for( int colsIdx = 0; colsIdx < this->cols; colsIdx++)
            {
                //this->setMatrixValue(rowsIdx, colsIdx, data[rowsIdx + this->rows*colsIdx]);
                this->container[rowsIdx*this->cols +colsIdx] = data[rowsIdx + this->rows*colsIdx];
            }
    }
    else
    {
        //copy elements
        for(unsigned int idx = 0; idx < this->getDim(); idx++)
        {
            this->container[idx] = data[idx];
        }
    }
}

/*
Operators overloading
*/
//Override attribution operator to allow for operations such as A = B, where A,B are Matrix2D instances
template <class Type>
bool Matrix2D<Type>::operator==(const Matrix2D<Type>& new_matrix)
{
    bool k = true;

    if(this->getDim() != new_matrix.getDim())
    {
        cout<<"The matrices have different dimensions and cannot be compared"<<endl;
        exit(0);
    }
    else
    {
        /*for(unsigned int idx = 0; idx < this->getRows(); idx++)
        {
            for(unsigned int idy = 0; idy < this->getCols(); idy++)
                if(this->getMatrixValue(idx, idy) != new_matrix.getMatrixValue(idx, idy))
                {
                    k = false;
                }
        }*/

        for(unsigned int idx = 0; idx < this->getDim() && k; idx++)
        {
            if(this->container[idx]!= new_matrix.getMatrixValue(idx))
            {
                k = false;
                break;
            }
        }
    }

    return k;
}

template <class Type>
Matrix2D<Type>& Matrix2D<Type>::operator=(const Matrix2D<Type>& new_matrix)
{
    this->rows = new_matrix.getRows();
    this->cols = new_matrix.getCols();

    //allocate memory
    if(this->container != NULL)
    {
        delete this->container;
    }
    this->container = new Type[this->rows*this->cols];

    //copy elements
    /*
    for( int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
        for( int colsIdx = 0; colsIdx < this->cols; colsIdx++)
        {
            this->setMatrixValue(rowsIdx, colsIdx, new_matrix.getMatrixValue(rowsIdx, colsIdx));
        }
    */
    for(unsigned int idx = 0; idx < this->getDim(); idx++)
    {
        this->container[idx] = new_matrix.getMatrixValue(idx);
    }

    return *this;
}

template <class Type>
Matrix2D<Type>& Matrix2D<Type>::operator+(Matrix2D<Type>& new_matrix)
{
    Type sum = 0;

    if(this->getRows() != new_matrix.getRows() || this->getCols() != new_matrix.getCols())
    {
        cout<<"Couldn't add matrices. They have different dimensions"<<endl;
        exit(0);
    }

    //sum up elements
    /*for( int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
        for( int colsIdx = 0; colsIdx < this->cols; colsIdx++)
        {
            sum = this->getMatrixValue(rowsIdx, colsIdx) + new_matrix.getMatrixValue(rowsIdx, colsIdx);
            this->setMatrixValue(rowsIdx, colsIdx, sum);
        }
        */
    for(unsigned int idx = 0; idx < this->getDim(); idx++)
    {
        this->container[idx] += new_matrix.getMatrixValue(idx);
    }

    return *this;
}

template <class Type>
Matrix2D<Type>& Matrix2D<Type>::operator-(Matrix2D<Type>& new_matrix)
{
    Type diff = 0;

    if(this->getRows() != new_matrix.getRows() || this->getCols() != new_matrix.getCols())
    {
        cout<<"Couldn't substract matrices. They have different dimensions"<<endl;
        exit(0);
    }

    //substract elements
    /*for( int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
        for( int colsIdx = 0; colsIdx < this->cols; colsIdx++)
        {
            diff = this->getMatrixValue(rowsIdx, colsIdx) - new_matrix.getMatrixValue(rowsIdx, colsIdx);
            this->setMatrixValue(rowsIdx, colsIdx, diff);
        }
        */
    for(unsigned int idx = 0; idx < this->getDim(); idx++)
    {
        this->container[idx] -= new_matrix.getMatrixValue(idx);
    }

    return *this;
}

/*
*helpers
*/
template <class Type>
void Matrix2D<Type>::initializeMatrixValues(Type value)
{
    for(unsigned int idx = 0; idx < this->getDim(); idx++)
    {
        this->container[idx] = value;
    }
}


/*
*Convolution
*/
template <class Type>
void Matrix2D<Type>::conv2DFull(Matrix2D<Type>& kernel, Matrix2D<Type>& result)
{
    Type temp;
    int i, j, m, n, sourceIdx, sourceIdy;
    //find kernel center
    int kCenterX = (kernel.getCols()+1)/2, kCenterY = (kernel.getRows()+1)/2;

    for(i = 0; i < result.getRows(); i++)
    {
        for(j = 0; j < result.getCols(); j++)                           // columns
        {
            for(m = 0; m < kernel.getRows(); m++)
            {
                for(n = 0; n < kernel.getCols() ; n++)
                {
                    sourceIdx = i + m - kCenterY;
                    sourceIdy =  j + n - kCenterX;

                    if( sourceIdx < this->getRows() && sourceIdx >= 0 && sourceIdy  <  this->getCols() && sourceIdy  >= 0)
                    {
                        temp = result.getMatrixValue(i, j) + this->getMatrixValue(sourceIdx, sourceIdy) * kernel.getMatrixValue(m, n);
                        result.setMatrixValue(i, j, temp);
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
                    temp = result.getMatrixValue(i, j) + this->getMatrixValue(i+m, j+n) * kernel.getMatrixValue(m, n);
                    result.setMatrixValue(i, j, temp);
                }
            }
        }
    }
}

template <class Type>
void Matrix2D<Type>::conv2DSame(Matrix2D<Type>& kernel, Matrix2D<Type>& result)
{
    Type temp;
    int i, j, m, n, sourceIdx, sourceIdy;
    //find kernel center
    int kCenterX = (kernel.getCols()-1)/2, kCenterY = (kernel.getRows()-1)/2;

    for(i = 0; i < this->getRows(); i++)
    {
        for(j = 0; j < this->getCols(); j++)                           // columns
        {
            for(m = 0; m < kernel.getRows(); m++)
            {
                for(n = 0; n < kernel.getCols() ; n++)
                {
                    sourceIdx = i + m - kCenterY;
                    sourceIdy =  j + n - kCenterX;

                    if( sourceIdx < this->getRows() && sourceIdx >= 0 && sourceIdy  <  this->getCols() && sourceIdy  >= 0)
                    {
                        temp = result.getMatrixValue(i, j) + this->getMatrixValue(sourceIdx, sourceIdy) * kernel.getMatrixValue(m, n);
                        result.setMatrixValue(i, j, temp);
                    }
                }
            }
        }
    }
}

/*
* matrix operations
*/
//the input si always a mask, whose Type == bool
template <class Type>
void Matrix2D<Type>::insertNaNValues(Matrix2D<bool>& mask)
{
    if(mask.getRows() != this->getRows() || mask.getCols() != this->getCols())
    {
        cout<<"Couldn't insert NaN values"<<endl;
        exit(0);
    }
    else
    {
        /*
        for(int i = 0; i < mask.getRows(); i++)
            for(int j = 0; j < mask.getCols(); j++)
            {
                //if the mask has value 1 at (i,j) index
                if(mask.getMatrixValue(i,j) == 1)
                {
                    this->setMatrixValue(i, j, numeric_limits<double>::quiet_NaN());
                }
            }
            */
        for(unsigned int idx = 0; idx < this->getDim(); idx++)
        {
            if(mask.getMatrixValue(idx) == 1)
            {
                this->container[idx] = numeric_limits<double>::quiet_NaN();
            }
        }
    }
}

//create mask by comparing caller's values to a given treshold, that is a single value. The result's Type == bool as it is always a mask
template <class Type>
void Matrix2D<Type>::compareValuesToTreshold(Matrix2D<bool>& result, Type treshold, Comparison comp)
{
    int i, j;

    switch(comp)
    {
        case 0:
            /*
            for(i = 0; i < this->getRows(); i++)
                for(j = 0; j < this->getCols(); j++)
                {
                    if(this->getMatrixValue(i, j) == treshold)
                    {
                        result.setMatrixValue(i, j, 1);
                    }
                    else
                    {
                        result.setMatrixValue(i, j, 0);
                    }
                }
                */
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                if(this->container[idx] == treshold)
                {
                    result.setMatrixValue(idx, 1);
                }
                else
                {
                    result.setMatrixValue(idx, 0);
                }
            }
            break;
        case 1:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                if(this->container[idx] != treshold)
                {
                    result.setMatrixValue(idx, 1);
                }
                else
                {
                    result.setMatrixValue(idx, 0);
                }
            }
            break;
        case 2:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                if(this->container[idx] < treshold)
                {
                    result.setMatrixValue(idx, 1);
                }
                else
                {
                    result.setMatrixValue(idx, 0);
                }
            }
            break;
        case 3:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                if(this->container[idx] <= treshold)
                {
                    result.setMatrixValue(idx, 1);
                }
                else
                {
                    result.setMatrixValue(idx, 0);
                }
            }
            break;
        case 4:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                if(this->container[idx] >= treshold)
                {
                    result.setMatrixValue(idx, 1);
                }
                else
                {
                    result.setMatrixValue(idx, 0);
                }
            }
            break;
        case 5:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                if(this->container[idx] > treshold)
                {
                    result.setMatrixValue(idx, 1);
                }
                else
                {
                    result.setMatrixValue(idx, 0);
                }
            }
            break;
    }
}

//usually the caller's Type == bool, as it is a amsk which is negated
template <class Type>
void Matrix2D<Type>::negateMatrixMask(Matrix2D<bool>& result)
{
    /*for(int i = 0; i < this->getRows(); i++)
        for(int j = 0; j < this->getCols(); j++)
    {
        result.setMatrixValue(i, j, 1 - this->getMatrixValue(i,j));
    }
    */

    for(unsigned int idx = 0; idx < this->getDim(); idx++)
    {
        result.setMatrixValue(idx, 1 - this->container[idx]);
    }
}

//Return the number of 1 values in the computed mask, which is obtained as logical and between input and caller, which usually are also masks (Type ==bool)
template <class Type>
int Matrix2D<Type>::logicalAnd(Matrix2D<bool>& result, Matrix2D<Type>& input)
{
    unsigned int counter = 0;

    /*for(i = 0; i < this->getRows(); i++)
        for(j = 0; j < this->getCols(); j++)
    {
        result.setMatrixValue(i, j, this->getMatrixValue(i,j ) & input.getMatrixValue(i, j));
        if(result.getMatrixValue(i, j) == 1)
            counter++;
    }
    */

    for(unsigned int idx = 0; idx < this->getDim(); idx++)
    {
        result.setMatrixValue(idx, this->container[idx] & input.getMatrixValue(idx));

        if(result.getMatrixValue(idx) == 1)
        {
            counter++;
        }
    }

    return counter;
}

//Each element from a column of the caller matrix is compared to one value from the input vector. Elements from next column are compared to next value and so on till the end.
//No of  caller matrix columns  = size of input vector
template <class Type>
void Matrix2D<Type>::compareMatrixColumnsToVector(Matrix2D<bool>& result, std::vector<Type>& input, Comparison comp)
{
    int i , j;

    if((unsigned) this->getCols() != input.size())
    {
        cout<<"Comparison couldn't be done. Input vector's size doesn't match calle rmatrix number of columns."<<endl;
        exit(0);
    }

    switch(comp)
    {
        case 0:
            for(j = 0; j < this->getCols(); j++)
                for(i = 0; i < this->getRows(); i++)
                {
                    if(this->getMatrixValue(i, j) == input[j])
                    {
                        result.setMatrixValue(i, j, 1);
                    }
                    else
                    {
                        result.setMatrixValue(i, j, 0);
                    }
                }
            break;
        case 1:
            for(j = 0; j < this->getCols(); j++)
                for(i = 0; i < this->getRows(); i++)
                {
                    if(this->getMatrixValue(i, j) != input[j])
                    {
                        result.setMatrixValue(i, j, 1);
                    }
                    else
                    {
                        result.setMatrixValue(i, j, 0);
                    }
                }
            break;
        case 2:
            for(j = 0; j < this->getCols(); j++)
                for(i = 0; i < this->getRows(); i++)
                {
                    if(this->getMatrixValue(i, j) < input[j])
                    {
                        result.setMatrixValue(i, j, 1);
                    }
                    else
                    {
                        result.setMatrixValue(i, j, 0);
                    }
                }
            break;
        case 3:
            for(j = 0; j < this->getCols(); j++)
                for(i = 0; i < this->getRows(); i++)
                {
                    if(this->getMatrixValue(i, j) <= input[j])
                    {
                        result.setMatrixValue(i, j, 1);
                    }
                    else
                    {
                        result.setMatrixValue(i, j, 0);
                    }
                }
            break;
        case 4:
            for(j = 0; j < this->getCols(); j++)
                for(i = 0; i < this->getRows(); i++)
                {
                    if(this->getMatrixValue(i, j) >= input[j])
                    {
                        result.setMatrixValue(i, j, 1);
                    }
                    else
                    {
                        result.setMatrixValue(i, j, 0);
                    }
                }
            break;
        case 5:
            for(j = 0; j < this->getCols(); j++)
                for(i = 0; i < this->getRows(); i++)
                {
                    if(this->getMatrixValue(i, j) > input[j])
                    {
                        result.setMatrixValue(i, j, 1);
                    }
                    else
                    {
                        result.setMatrixValue(i, j, 0);
                    }
                }
            break;
    }
}

template <class Type>
void Matrix2D<Type>::applyVectorMask(Matrix2D<Type>& result, std::vector<bool> mask)
{
    int t_idx = 0;

    //mask.getRows = source.getRows. For each line, check if mask is 1, then iterate through cols, allocate memory for KeyValue object, then set ts values
    for(int idx = 0; idx <this->getRows(); idx++)
    {
        if(mask[idx] == 1)
        {
            for( int idy = 0; idy < this->getCols(); idy++)
            {
                result.setMatrixValue(t_idx, idy, this->getMatrixValue(idx, idy));
            }
            t_idx++;
        }
    }
}

//asks are applied simultaneously, where boths' values are 1 the result will store a non zero value
template <class Type>
void Matrix2D<Type>::applyDoubleVectorMask(Matrix2D<Type>& result, std::vector<bool> mask1, std::vector<bool> mask2)
{
    int idx = 0, idy = 0;

    for(int i = 0; i < result.getRows(); i++)
    {
        for(int j =0; j < result.getCols(); j++)
        {
            if(mask1[i] == 1 && mask2[j] == 1)
            {
                result.setMatrixValue(i, j, this->getMatrixValue(idx, idy));
                idy++;
            }
        }
        if(idy == this->getCols())
        {
            idx++;
            idy = 0;
        }
    }
}

//caller, mask and result have same dimensions
template <class Type>
void Matrix2D<Type>::applyMatrixMask(Matrix2D<Type>& result, Matrix2D<bool> mask)
{
    /*for(int i = 0; i < this->getRows(); i++)
        for(int j = 0; j < this->getCols(); j++)
    {
        if(mask(i, j) == 1)
        {
            result.setMatrixValue(i, j, this->getMatrixValue(i, j));
        }
    }
    */
    for(unsigned int idx = 0; idx < this->getDim(); idx++)
    {
        if(mask.getMatrixValue(idx) == 1)
        {
            result.setMatrixValue(idx, this->container[idx]);
        }
    }

}

template <class Type>
void Matrix2D<Type>::sortLines()
{
    Type aux;

    for(int i = 0; i < this->getRows(); i++)
    {
        for(int j = 0; j < this->getCols()-1; j++)
        {
            if(this->getMatrixValue(i, j) > this->getMatrixValue(i, j+1))
            {
                aux = this->getMatrixValue(i, j);
                this->setMatrixValue(i, j, this->getMatrixValue(i, j+1));
                this->setMatrixValue(i, j+1, aux);
            }
        }
    }
}

/*
*basic math-operations
*/
//Returns a matrix whose all values are >=0. The orginal values are those in the input "source"
template <class Type>
void Matrix2D<Type>::getAbsoluteValuesMatrix(Matrix2D<Type>& source)
{
    /*for(int i = 0; i < source.getRows(); i++)
        for(int j = 0; j < source.getCols(); j++)
    {
        this->setMatrixValue(i, j, abs(source.getMatrixValue(i,j)));
    }*/
    for(unsigned int idx = 0; idx < this->getDim(); idx++)
    {
        this->container[idx] = abs(source.getMatrixValue(idx));
    }
}

//For the calling matrix object, it computes the natural logarithm of each element of the input matrix object. Both matrices have same dimensions.
template <class Type>
void Matrix2D<Type>::logNatMatrix(Matrix2D<Type>& source)
{
    /*for(int i = 0; i < this->getRows(); i++)
        for(int j = 0; j < this->getCols(); j++)
        {
            this->setMatrixValue(i, j, log(source.getMatrixValue(i,j)));
        }
        */
    for(unsigned int idx = 0; idx < this->getDim(); idx++)
    {
        this->container[idx] = log(source.getMatrixValue(idx));
    }
}

//find first element in matrix that differs from the input value
template <class Type>
void Matrix2D<Type>::findFirstNonEqualElement(int &x_first, int &y_first, Type value)
{
    for(int i = 0; i < this->rows; i++)
        for(int j = 0; j < this->cols; j++)
    {
        if(this->getMatrixValue(i,j) != value)
        {
            x_first = i;
            y_first = j;
            return;
        }
    }

    return;
}

//find last element in matrix that differs from the input value
template <class Type>
void Matrix2D<Type>::findLastNonEqualElement(int &x_first, int &y_first, Type value)
{
    for(int i = this->rows - 1; i>=0; i--)
        for(int j = this->cols - 1; j>=0; j--)
    {
        if(this->getMatrixValue(i,j) != value)
        {
            x_first = i;
            y_first = j;
            return ;
        }
    }

    return;
}

//Returns 1 if a row/column has at least a non-zero value, else it returns 0 for that row/column. The output is a vector. Direction: 1 = check on columns; 2 = check on rows
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

//Result is a vector containing 1 if the line/column has  all elements grater than input value.Direction: 1 = check on columns; 2 = check on rows
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

//Check if calling matrix doesn't have only zeros
template <class Type>
bool Matrix2D<Type>::checkNonZero()
{
    /*for(int i = 0; i < this->getRows(); i++)
        for(int j = 0; j < this->getCols(); j++)
        {
            if(this->getMatrixValue(i, j) != 0)
                return true;
        }
        */
    for(unsigned int idx = 0; idx < this->getDim(); idx++)
    {
        if(this->container[idx] != 0)
            return true;
    }

    return false;
}

template <class Type>
void Matrix2D<Type>::mFindIndeces(Matrix2D<int>& result, Type value, Comparison cmp)
{
    int res_i = 0, i, j;

    switch(cmp)
    {
    case 0:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) == value)
            {
                result.setMatrixValue(res_i, 0, i);
                result.setMatrixValue(res_i, 1, j);
                res_i++;
            }
        }
        break;
    case 1:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) != value)
            {
                result.setMatrixValue(res_i, 0, i);
                result.setMatrixValue(res_i, 1, j);
                res_i++;
            }
        }
        break;
    case 2:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) < value)
            {
                result.setMatrixValue(res_i, 0, i);
                result.setMatrixValue(res_i, 1, j);
                res_i++;
            }
        }
        break;
    case 3:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) <= value)
            {
                result.setMatrixValue(res_i, 0, i);
                result.setMatrixValue(res_i, 1,  j);
                res_i++;
            }
        }
        break;
    case 4:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) >= value)
            {
                result.setMatrixValue(res_i, 0,  i);
                result.setMatrixValue(res_i, 1,  j);
                res_i++;
            }
        }
        break;
    case 5:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) > value)
            {
                result.setMatrixValue(res_i, 0,  i);
                result.setMatrixValue(res_i, 1,  j);
                res_i++;
            }
        }
        break;
    }
}

template <class Type>
void Matrix2D<Type>::mFindIndecesAndValues(Matrix2D<Type>& result, Type value, Comparison cmp)
{
    int res_i = 0, i, j;

    switch(cmp)
    {
    case 0:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) == value)
            {
                result.setMatrixValue(res_i, 0,  i);
                result.setMatrixValue(res_i, 1,  j);
                result.setMatrixValue(res_i, 2, this->getMatrixValue(i,j));
                res_i++;
            }
        }
        break;
    case 1:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) != value)
            {
                result.setMatrixValue(res_i, 0,  i);
                result.setMatrixValue(res_i, 1,  j);
                result.setMatrixValue(res_i, 2,  this->getMatrixValue(i,j));
                res_i++;
            }
        }
        break;
    case 2:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) < value)
            {
                result.setMatrixValue(res_i, 0,  i);
                result.setMatrixValue(res_i, 1,  j);
                result.setMatrixValue(res_i, 2,  this->getMatrixValue(i,j));
                res_i++;
            }
        }
        break;
    case 3:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) <= value)
            {
                result.setMatrixValue(res_i, 0,  i);
                result.setMatrixValue(res_i, 1,  j);
                result.setMatrixValue(res_i, 2,  this->getMatrixValue(i,j));
                res_i++;
            }
        }
        break;
    case 4:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) >= value)
            {
                result.setMatrixValue(res_i, 0, i);
                result.setMatrixValue(res_i, 1,  j);
                result.setMatrixValue(res_i, 2,  this->getMatrixValue(i,j));
                res_i++;
            }
        }
        break;
    case 5:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) > value)
            {
                result.setMatrixValue(res_i, 0,  i);
                result.setMatrixValue(res_i, 1,  j);
                result.setMatrixValue(res_i, 2,  this->getMatrixValue(i,j));
                res_i++;
            }
        }
        break;
    }
}

template <class Type>
void Matrix2D<Type>::vFindIndeces(std::vector<int>& x, std::vector<int>&  y, Type value, Comparison cmp)
{
    int res_i = 0, i, j;

    switch(cmp)
    {
    case 0:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) == value)
            {
                x[res_i] = i;
                y[res_i] = j;
                res_i++;
            }
        }
        break;
    case 1:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) != value)
            {
                x[res_i] = i;
                y[res_i] = j;
                res_i++;
            }
        }
        break;
    case 2:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) < value)
            {
                x[res_i] = i;
                y[res_i] = j;
                res_i++;
            }
        }
        break;
    case 3:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) <= value)
            {
                x[res_i] = i;
                y[res_i] = j;
                res_i++;
            }
        }
        break;
    case 4:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) >= value)
            {
                x[res_i] = i;
                y[res_i] = j;
                res_i++;
            }
        }
        break;
    case 5:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) > value)
            {
                x[res_i] = i;
                y[res_i] = j;
                res_i++;
            }
        }
        break;
    }
}

template <class Type>
void Matrix2D<Type>::vFindIndecesAndValues(std::vector<int>& x, std::vector<int>&  y, std::vector<Type>&  val, Type value, Comparison cmp)
{
    int res_i = 0, i, j;

    switch(cmp)
    {
    case 0:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) == value)
            {
                x[res_i] = i;
                y[res_i] = j;
                val[res_i] = this->getMatrixValue(i,j);
                res_i++;
            }
        }
        break;
    case 1:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) != value)
            {
                x[res_i] = i;
                y[res_i] = j;
                val[res_i] = this->getMatrixValue(i,j);
                res_i++;
            }
        }
        break;
    case 2:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) < value)
            {
                x[res_i] = i;
                y[res_i] = j;
                val[res_i] = this->getMatrixValue(i,j);
                res_i++;
            }
        }
        break;
    case 3:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) <= value)
            {
                x[res_i] = i;
                y[res_i] = j;
                val[res_i] = this->getMatrixValue(i,j);
                res_i++;
            }
        }
        break;
    case 4:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) >= value)
            {
                x[res_i] = i;
                y[res_i] = j;
                val[res_i] = this->getMatrixValue(i,j);
                res_i++;
            }
        }
        break;
    case 5:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) > value)
            {
                x[res_i] = i;
                y[res_i] = j;
                val[res_i] = this->getMatrixValue(i,j);
                res_i++;
            }
        }
        break;
    }
}

template <class Type>
void Matrix2D<Type>::elementsOperation(Matrix2D<Type>& result, Type value, Operation op)
{
    int i, j;

    switch(op)
    {
    case 0:
        /*for(i = 0; i < this->getRows(); i++)
            for(j = 0; j < this->getCols(); j++)
            {
                result.setMatrixValue(i, j, this->getMatrixValue(i, j) + value);
            }
            */
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                result.setMatrixValue(idx, this->container[idx] + value);
            }
        break;
    case 1:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                result.setMatrixValue(idx, this->container[idx] - value);
            }
        break;
    case 2:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                result.setMatrixValue(idx, this->container[idx] * value);
            }
        break;
    case 3:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                result.setMatrixValue(idx, this->container[idx]/value);
            }
        break;
    case 4:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                result.setMatrixValue(idx, pow(this->container[idx], value));
            }
        break;
    case 5:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                result.setMatrixValue(idx, exp(this->container[idx]));
            }
        break;
    }
}

//Returns 1 if a row/column has at least a non-zero value, else it returns 0 for that row/column. The output is a vector. Direction: 1 = check on columns; 2 = check on rows
template <class Type>
void Matrix2D<Type>::allNonZero(vector<bool>& result, int direction)
{
    if(direction == 1)
    {
        for(int j = 0; j < this->getCols(); j++)
        {
            //for each column, initially suppose all its elements are non zero
            result[j] = 1;
            //search for each element in the given column
            for(int i = 0; i < this->getRows(); i++)
            {
                //if one is 0, set the result to 0 and continue with the next column
                if(this->getMatrixValue(i, j) == 0)
                {
                    result[j] = 0;
                    break;
                }
            }
        }

    }

    if(direction ==2)
    {
        for(int i = 0; i < this->getRows(); i++)
        {
            //for each row, initially suppose all its elements are non zero
            result[i] = 1;
            //search for each element in the given row
            for(int j = 0; j < this->getCols(); j++)
            {
                //if one is 0, set the result to 0 and continue with the next row
                if(this->getMatrixValue(i, j) == 0)
                {
                    result[i] = 0;
                    break;
                }
            }
        }
    }
}

//return # of elements whose value is different from input value. Useful when computing number of elements different from that value with Matlab's 'find'
template <class Type>
int Matrix2D<Type>::countValuesDifferentFromInput(Type value)
{
    int counter = 0;

    /*
    for(int i = 0; i < this->getRows(); i++)
        for(int j = 0; j < this->getCols(); j++)
    {
        if(this->getMatrixValue(i, j) != value)
            counter++;
    }
    */

    for(unsigned int idx = 0; idx < this->getDim(); idx++)
    {
        if(this->container[idx] != value)
            counter++;
    }

    return counter;
}

/*
* matrix conversions
*/

template <class Type>
void Matrix2D<Type>::copyMatrixColumnToVector(vector<Type> &result, int col)
{
    for(int i = 0; i < this->getRows(); i++)
        result[i] = this->getMatrixValue(i, col);
}

template <class Type>
void Matrix2D<Type>::copyMatrixRowToVector(vector<Type> &result, int row)
{
    for(int j = 0; j < this->getCols(); j++)
        result[j] = this->getMatrixValue(row, j);
}

//Convert calling matrix to vector, by putting the columns one after another
template <class Type>
void Matrix2D<Type>::reshapeToVector(vector<Type>& dest)
{
    for(int j = 0; j < this->getCols(); j++)
        for(int i = 0; i < this->getRows(); i++)
        {
            dest[i + j*this->getRows()] = this->getMatrixValue(i, j);
        }
}

//The caller is a matrix object whose values are a submatrix of "source" input. The indeces are considered those between the specified indeces
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

//Reverse matrix elements: the first and the last lines are interchanged, the 2nd line with the 2nd-last one, but also th elements in the lines are reversed as the last becomes the first and viceversa
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

//unlike  other methods, this one takes as input the matrix in which the result shall be stored
template <class Type>
void Matrix2D<Type>::getTranspose(Matrix2D<Type>** output)
{
    *output = new Matrix2D<Type>(this->getCols(), this->getRows());

    for(int idx = 0; idx < this->getRows(); idx++)
        for(int idy = 0; idy < this->getCols(); idy++)
    {
        (**output).setMatrixValue(idy, idx, this->getMatrixValue(idx, idy));
    }
}

//the result overwrites the input matrix. Only used for quadratic matrices
template <class Type>
void Matrix2D<Type>::TransposeMatrix()
{
    Type temp;

    //only for quadratic matrix
    if(this->getCols() == this->getRows())
    {
        for(int idx = 0; idx < this->getRows(); idx++)
            for(int idy = idx+1; idy < this->getCols(); idy++)
            {
                temp = this->getMatrixValue(idx, idy);
                this->setMatrixValue(idx, idy, this->getMatrixValue(idy, idx));
                this->setMatrixValue(idy, idx, temp);
            }
    }
}
