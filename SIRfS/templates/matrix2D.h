#ifndef MATRIX2D_H_INCLUDED
#define MATRIX2D_H_INCLUDED

#include <vector>
#include <iostream>
#include <math.h>
#include <limits>

#include "keyValue.h"
#include "../helpers/enums.h"

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

    bool operator==(const Matrix2D<Type>& new_matrix);
    Matrix2D& operator=(const Matrix2D<Type>& new_matrix);
    Matrix2D& operator+(Matrix2D<Type>& new_matrix);
    Matrix2D& operator-(Matrix2D<Type>& new_matrix);

    //helpers: separate functions from constructors, used for memory allocation, initialization and data copying
    void allocateMemory(int dimX, int dimY);
    void copyElementsFromMatrix(Matrix2D<Type>& source);
    void initializeMatrixValues(Type value);

    //convolution
    void conv2DFull(Matrix2D<Type>& kernel, Matrix2D<Type>& result);
    void conv2DValid(Matrix2D<Type>& kernel, Matrix2D<Type>& result);
    void conv2DSame(Matrix2D<Type>& kernel, Matrix2D<Type>& result);

    //matrix operations. They are the C++ implementations for Matlab library functions for 2D matrices
    /*
    *mask related operations
    */
    //It gets as input a matrice's  mask and the changes are made to the caller
    void insertNaNValues(Matrix2D<bool>& mask);
    //creates a mask by comparing the caller's values to the given treshold
    void compareValuesToTreshold(Matrix2D<bool>& result, Type treshold, Comparison comp);
    void negateMatrixMask(Matrix2D<bool>& result);
    //returns the # of non-zero elements
    int logicalAnd(Matrix2D<bool>& result, Matrix2D<Type>& input);
    //only the number of columns has to be equal to size of vector
    void compareMatrixColumnsToVector(Matrix2D<bool>& result, std::vector<Type>& input, Comparison comp);
    void applyVectorMask(Matrix2D<Type>& result, std::vector<bool> mask);
    void applyDoubleVectorMask(Matrix2D<Type>& result, std::vector<bool> mask1, std::vector<bool> mask2);
    void applyMatrixMask(Matrix2D<Type>& result, Matrix2D<bool> mask);
    void sortLines();

    /*
    *basic math-operations
    */
    void getAbsoluteValuesMatrix(Matrix2D<Type>& source);
    void logNatMatrix(Matrix2D<Type>& source);
    void findFirstNonEqualElement(int &x_first, int &y_first, Type value);
    void findLastNonEqualElement(int &x_last, int &y_last, Type value);
    //for the following 2 functions, the output is a vector
    void anyNonZero(std::vector<int>& result, int direction);
    void anyGreater(std::vector<int>& result, int direction, int treshold);
    bool checkNonZero();
    //the equivalent of  'find' Matlab function, but stores indeces in a matrix with 2 columns
    void mFindIndeces(Matrix2D<int>& result, Type value, Comparison cmp);
    //same as above but the output is a matrix with 3 column, as the 3rd stores also the values
    void mFindIndecesAndValues(Matrix2D<Type>& result, Type value, Comparison cmp);
    //same as mFindIndeces, but stores output indeces in 2 separate vectors
    void vFindIndeces(std::vector<int>& x, std::vector<int>&  y, Type value, Comparison cmp);
    //same as above, but stores the values in a 3rd vector
    void vFindIndecesAndValues(std::vector<int>& x, std::vector<int>&  y, std::vector<Type>&  val, Type value, Comparison cmp);
    //per matrix element operation
    void elementsOperation(Matrix2D<Type>& result, Type value, Operation op);
    void allNonZero(std::vector<bool>& result, int direction);
    int countValuesDifferentFromInput(Type value);
    /*
    *matrix conversions
    */
    void copyMatrixColumnToVector(std::vector<Type> &result, int col);
    void copyMatrixRowToVector(std::vector<Type> &result, int row);
    void reshapeToVector(std::vector<Type>& dest);
    void getSubMatrix(Matrix2D<Type>& source, int x_first, int x_last, int y_first, int y_last);
    void reverseMatrix(Matrix2D<Type>& source);
    void getTranspose(Matrix2D<Type>** result);
    void linearizeIndeces(std::vector<Type>& result, int rows, int cols);

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
