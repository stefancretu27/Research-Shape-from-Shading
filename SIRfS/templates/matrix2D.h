#ifndef MATRIX2D_H_INCLUDED
#define MATRIX2D_H_INCLUDED

#include <vector>
#include <iostream>
#include <math.h>
#include <limits>
//for smart pointers
#include <memory>

#include "keyValue.h"
#include "../helpers/enums.h"

//#define U_PTR_CONTAINER 0

template <class Type>
class Matrix2D
{
private:
#ifdef U_PTR_CONTAINER
    std::unique_ptr<Type []> container;
#else
    Type *container;
#endif
     int rows, cols;

public:
    //constructors
    Matrix2D():rows(0), cols(0), container(nullptr){};
    //overload constructor
    Matrix2D( int new_rows,  int new_cols);
    Matrix2D( int new_rows,  int new_cols, Type value);
#ifdef  U_PTR_CONTAINER
    //move constructor
    Matrix2D(Matrix2D<Type>&& new_matrix);
#else
    //copy constructor
    Matrix2D(const Matrix2D<Type>& new_matrix);
#endif

    //destructor
    ~Matrix2D()
    {
#ifndef  U_PTR_CONTAINER
        //delete the array
        delete [] this->container;
#endif
    }

    //indexes operations
    inline unsigned int getLinearIndex(int i, int j)
    {
        return i*this->cols + j;
    };
    void get2DIndecesFromLinearIndex(int index, int &rows, int &cols)
    {
        rows = index/this->cols;  //integer division . This is x
        cols = index - rows; //This is y
    };

    //getters
    inline int getRows() const              //inline tells compiler to replace function with its definition => faster execution as there is less linking
    {
        return this->rows;
    };
    inline int getCols() const
    {
        return this->cols;
    };
    inline int getDim() const
    {
        return this->rows*this->cols;
    };
#ifdef U_PTR_CONTAINER
    inline std::unique_ptr<Type []> getContainer()
    {
        return std::move(this->container);
    }
#else
    inline Type* getContainer()const
    {
        return this->container;
    };
#endif // U_PTR_CONTAINER
    inline Type getMatrixValue(int i, int j) const
    {
        return this->container[i*this->cols + j];
    };
    inline Type getMatrixValue(unsigned linearindex) const
    {
        return this->container[linearindex];
    };

    //setters
    inline void setRows(int new_rows)
    {
        this->rows = new_rows;
    };
    inline void setCols(int new_cols)
    {
        this->cols = new_cols;
    };
    inline void setDims(int new_rows, int new_cols)
    {
        this->cols = new_cols;
        this->rows = new_rows;
    };
    inline void setMatrixValue(int i, int j, Type value)
    {
        this->container[i*this->cols +j] = value;
    };
    inline void setMatrixValue(unsigned int linearindex, Type value)
    {
        this->container[linearindex] = value;
    };
    void setMatrix2D(Type* data, int new_rows,  int new_cols, bool transp);

    //operators overloading
    inline Type& operator() (int rowsIdx, int colsIdx) const
    {
        return this->container[rowsIdx * this->cols + colsIdx];
    };
#ifdef U_PTR_CONTAINER
    bool operator==(Matrix2D<Type>&& new_matrix);
    Matrix2D& operator=(Matrix2D<Type>&& new_matrix);
    Matrix2D& operator+(Matrix2D<Type>&& new_matrix);
    Matrix2D& operator-(Matrix2D<Type>&& new_matrix);
#else
    bool operator==(const Matrix2D<Type>& new_matrix);
    Matrix2D& operator=(const Matrix2D<Type>& new_matrix);
    Matrix2D& operator+(const Matrix2D<Type>& new_matrix);
    Matrix2D& operator-(const Matrix2D<Type>& new_matrix);
#endif // U_PTR_CONTAINER

    //helper: separate function from constructors, used data copying
    void initializeMatrixValues(Type value);

    //convolution
#ifdef U_PTR_CONTAINER
    void conv2DFull(Matrix2D<Type>&& kernel, Matrix2D<Type>&& input);
    void conv2DValid(Matrix2D<Type>&& kernel, Matrix2D<Type>&& input);
    void conv2DSame(Matrix2D<Type>&& kernel, Matrix2D<Type>&& input);
#else
    void conv2DFull(const Matrix2D<Type>& kernel, const Matrix2D<Type>& input);
    void conv2DValid(const Matrix2D<Type>& kernel, const Matrix2D<Type>& input);
    void conv2DSame(const Matrix2D<Type>& kernel,  const Matrix2D<Type>& input);
#endif // U_PTR_CONTAINER

    //matrix operations. They are the C++ implementations for Matlab library functions for 2D matrices
    /*
    *mask related operations
    */
#ifdef U_PTR_CONTAINER
    //It gets as input a matrice's  mask and the changes are made to the caller
    void insertNaNValues(Matrix2D<bool>&& mask);
    //creates a mask by comparing the caller's values to the given treshold
    void compareValuesToTreshold(Matrix2D<bool>&& result, Type treshold, Comparison comp);
    void negateMatrixMask(Matrix2D<bool>&& input);
    //returns the # of non-zero elements
    int logicalAnd(Matrix2D<bool>&& result, Matrix2D<Type>&& input);
    //only the number of columns has to be equal to size of vector
    void compareMatrixColumnsToVector(Matrix2D<bool>&& result, std::vector<Type>& input, Comparison comp);
    void applyVectorMask(Matrix2D<Type>&& input, std::vector<bool> mask);
    void applyDoubleVectorMask(Matrix2D<Type>&& input, std::vector<bool> mask1, std::vector<bool> mask2);
    void applyMatrixMask(Matrix2D<Type>&& input, Matrix2D<bool> mask);
#else
    //It gets as input a matrice's  mask and the changes are made to the caller
    void insertNaNValues(const Matrix2D<bool>& mask);
    //creates a mask by comparing the caller's values to the given treshold
    void compareValuesToTreshold(Matrix2D<bool>& result, Type treshold, Comparison comp);
    void negateMatrixMask( Matrix2D<bool>& input);
    //returns the # of non-zero elements
    int logicalAnd(Matrix2D<bool>& result, Matrix2D<Type>& input);
    //only the number of columns has to be equal to size of vector
    void compareMatrixColumnsToVector(Matrix2D<bool>& result, std::vector<Type>& input, Comparison comp);
    void applyVectorMask(const Matrix2D<Type>& input, std::vector<bool> mask);
    void applyDoubleVectorMask(const Matrix2D<Type>& input, std::vector<bool> mask1, std::vector<bool> mask2);
    void applyMatrixMask(const Matrix2D<Type>& input, Matrix2D<bool> mask);
#endif // U_PTR_CONTAINER
    void sortLines();

    /*
    *basic math-operations
    */
#ifdef U_PTR_CONTAINER
    void getAbsoluteValuesMatrix(Matrix2D<Type>&& input);
    void logNatMatrix(Matrix2D<Type>&& input);
#else
    void getAbsoluteValuesMatrix(const Matrix2D<Type>& input);
    void logNatMatrix( const Matrix2D<Type>& input);
#endif
    void findFirstNonEqualElement(int &x_first, int &y_first, Type value);
    void findLastNonEqualElement(int &x_last, int &y_last, Type value);
    //for the following 2 functions, the output is a vector
    void anyNonZero(std::vector<int>& result, int direction);
    void anyGreater(std::vector<int>& result, int direction, int treshold);
    bool checkNonZero();
    //the equivalent of  'find' Matlab function, but stores indeces in a matrix with 2 columns. The result is always a Matrix2D of integers
#ifdef U_PTR_CONTAINER
    void mFindIndeces(Matrix2D<int>&& result, Type value, Comparison cmp);
    //same as above but the output is a matrix with 3 column, as the 3rd stores also the values
    void mFindIndecesAndValues(Matrix2D<int>&& result, Type value, Comparison cmp);
#else
    void mFindIndeces(Matrix2D<int>& result, Type value, Comparison cmp);
    //same as above but the output is a matrix with 3 column, as the 3rd stores also the values
    void mFindIndecesAndValues(Matrix2D<int>& result, Type value, Comparison cmp);
#endif
    //same as mFindIndeces, but stores output indeces in 2 separate vectors
    void vFindIndeces(std::vector<int>& x, std::vector<int>&  y, Type value, Comparison cmp);
    //same as above, but stores the values in a 3rd vector
    void vFindIndecesAndValues(std::vector<int>& x, std::vector<int>&  y, std::vector<Type>&  val, Type value, Comparison cmp);
    //per matrix element operation
#ifdef U_PTR_CONTAINER
    void elementsOperation(Matrix2D<Type>&& result, Type value, Operation op);
#else
    void elementsOperation(Matrix2D<Type>& result, Type value, Operation op);
#endif // U_PTR_CONTAINER
    void allNonZero(std::vector<bool>& result, int direction);
    int countValuesDifferentFromInput(Type value);
    /*
    *matrix conversions
    */
    void copyMatrixColumnToVector(std::vector<Type> &result, int col);
    void copyMatrixRowToVector(std::vector<Type> &result, int row);
    void reshapeToVector(std::vector<Type>& dest);
#ifdef U_PTR_CONTAINER
    void getSubMatrix(Matrix2D<Type>&& input, int x_first, int x_last, int y_first, int y_last);
    void reverseMatrix(Matrix2D<Type>&& input);
#else
    void getSubMatrix(Matrix2D<Type>& input, int x_first, int x_last, int y_first, int y_last);
    void reverseMatrix(Matrix2D<Type>& input);
#endif
    void getTranspose(Matrix2D<Type>** result);
    //same as above, but result is stored in the caller (caller data is lost)
    void TransposeMatrix();

    //for debug purposes
    void printMatrixValues()
    {
        for(int i = 0; i < this->rows; i++)
        {
            for(int j = 0; j < this->cols; j++)
            {
                std::cout<<this->container[i*this->cols + j]<<" ";
            }
            std::cout<<std::endl;
        }
    }
};



#endif // MATRIX2D_H_INCLUDED
