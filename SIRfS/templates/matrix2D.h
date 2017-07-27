#ifndef MATRIX2D_H_INCLUDED
#define MATRIX2D_H_INCLUDED

#include <vector>
#include <iostream>
#include <math.h>

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
    Matrix2D(Matrix2D& new_matrix);
    //destructor
    ~Matrix2D();

    //getters
    inline int getRows(){return this->rows;};                                           //inline tells compiler to replace function with its definition => faster execution as there is less linking
    inline int getCols(){return this->cols;};
    inline int getDim(){return this->rows*this->cols;};
    inline Type** getMat2D(){return this->matrix2d;};
    inline Type getMatrixValue(int i, int j){return this->matrix2d[i][j];};
    //setters
    inline void setRows(int new_rows){this->rows = new_rows;};
    inline void setCols(int new_cols){this->cols = new_cols;};
    inline void setMatrixValue(int i, int j, Type value){this->matrix2d[i][j] = value;};

    //operators overloading
    inline Type& operator()(int rowsIdx, int colsIdx)
    {
        return this->matrix2d[rowsIdx][colsIdx];
    };
    Matrix2D& operator=(Matrix2D& new_matrix);
    Matrix2D& operator+(Matrix2D& new_matrix);

    //matrix operations. They are the C++ implementations for Matlab library functions for 2D matrices
    void initializeMatrixValues(Type value);
    void negateMatrixMask(Matrix2D<Type>& sourceMask);
    void logNatMatrix(Matrix2D<Type>& source);
    void findFirstNonEqualElement(int &x_first, int &y_first, Type value);
    void findLastNonEqualElement(int &x_last, int &y_last, Type value);
    void anyNonZero(std::vector<int>& result, int direction);
    void getSubMatrix(Matrix2D<Type>& source, int x_first, int x_last, int y_first, int y_last);
    void getAbsoluteValuesMatrix(Matrix2D<Type>& source);
    void conv2DFull(Matrix2D<Type>& kernel, Matrix2D<Type>& result);
    void conv2DValid(Matrix2D<Type>& kernel, Matrix2D<Type>& result);
    bool checkNonZero();
    void anyGreater(std::vector<int>& result, int direction, int treshold);
    void reshapeToVector(std::vector<Type>& dest);
    void reverseMatrix(Matrix2D<Type>& source);

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
