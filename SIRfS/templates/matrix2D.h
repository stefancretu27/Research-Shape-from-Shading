#ifndef MATRIX2D_H_INCLUDED
#define MATRIX2D_H_INCLUDED

#include <vector>
#include <iostream>
#include <math.h>

#include "keyValue.h"

template <class Type>
class Matrix2D
{
private:
    Type **matrix2d;
     int rows, cols;

public:
    //constructors
    Matrix2D(){};                                                                                       //does nothing
    Matrix2D( int new_rows,  int new_cols);
    Matrix2D( int new_rows,  int new_cols, Type value);
    Matrix2D(const Matrix2D<Type>& new_matrix);

    //destructor
    ~Matrix2D();

    //getters
    inline int getRows() const {return this->rows;};                                           //inline tells compiler to replace function with its definition => faster execution as there is less linking
    inline int getCols() const {return this->cols;};
    inline int getDim(){return this->rows*this->cols;};
    inline Type** getMat2D(){return this->matrix2d;};
    inline Type getMatrixValue(int i, int j) const {return this->matrix2d[i][j];};
    //setters
    inline void setRows(int new_rows){this->rows = new_rows;};
    inline void setCols(int new_cols){this->cols = new_cols;};
    inline void setMatrixValue(int i, int j, Type value){this->matrix2d[i][j] = value;};

    //operators overloading
    inline Type& operator()(int rowsIdx, int colsIdx)
    {
        return this->matrix2d[rowsIdx][colsIdx];
    };

    Matrix2D& operator=(const Matrix2D<Type>& new_matrix);
    Matrix2D& operator+(Matrix2D<Type>& new_matrix);

    //separate functions from constructors, used for memory allocation, initialization and data copying
    void allocateMemory(int dimX, int dimY);
    void copyElementsFromMatrix(Matrix2D<Type>& source);
    void initializeMatrixValues(Type value);

    //matrix operations. They are the C++ implementations for Matlab library functions for 2D matrices
    //mask related operations
    void negateMatrixMask(Matrix2D<Type>& sourceMask);
    //basic math-operations related
    void getAbsoluteValuesMatrix(Matrix2D<Type>& source);
    void logNatMatrix(Matrix2D<Type>& source);
    void findFirstNonEqualElement(int &x_first, int &y_first, Type value);
    void findLastNonEqualElement(int &x_last, int &y_last, Type value);
    void anyNonZero(std::vector<int>& result, int direction);
    bool checkNonZero();
    void anyGreater(std::vector<int>& result, int direction, int treshold);
    //matrix conversions
    void getTranspose(Matrix2D<Type>& kernel, Matrix2D<Type>& result);
    void reshapeToVector(std::vector<Type>& dest);
    void getSubMatrix(Matrix2D<Type>& source, int x_first, int x_last, int y_first, int y_last);
    void reverseMatrix(Matrix2D<Type>& source);
    //convolution
    void conv2DFull(Matrix2D<Type>& kernel, Matrix2D<Type>& result);
    void conv2DValid(Matrix2D<Type>& kernel, Matrix2D<Type>& result);

    //for debug purposes
    void printMatrixValues()
    {
        for(int i = 0; i < this->rows; i++)
        {
            for(int j = 0; j < this->cols; j++)
            {
                std::cout<<this->matrix2d[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    }
};



#endif // MATRIX2D_H_INCLUDED
