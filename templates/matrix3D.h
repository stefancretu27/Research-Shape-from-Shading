#ifndef MATRIX3D_H_INCLUDED
#define MATRIX3D_H_INCLUDED

#include <iostream>
#include "Matrix2D.h"

template <class Type>
class Matrix3D
{
private:
    Type ***matrix3d;
    unsigned int xDim, yDim, zDim;

public:
    //constructors
    Matrix3D(){};
    Matrix3D(unsigned int new_xDim, unsigned int new_yDim, unsigned int new_zDim);
    Matrix3D(const Matrix3D& new_matrix);
    //destructor
    ~Matrix3D();

    //getters
    inline int getXDim()const{return this->xDim;};
    inline int getYDim()const{return this->yDim;};
    inline int getZDim()const{return this->zDim;};
    inline unsigned int getDim(){return this->xDim*this->yDim*this->zDim;};
    inline Type getMatrixValue(int i, int j, int z) const {return this->matrix3d[i][j][z];};
    //setters
    inline void setXDim(int new_xDim){this->xDim = new_xDim;};
    inline void setYDim(int new_yDim){this->yDim = new_yDim;};
    inline void setZDim(int new_zDim){this->zDim = new_zDim;};
    inline void setMatrixValue(int i, int j, int z, Type value){this->matrix3d[i][j][z] = value;};

    //operators overloading
    Type& operator()(unsigned int new_xDim, unsigned int new_yDim, unsigned int new_zDim);
    Matrix3D& operator=(const Matrix3D& new_matrix);

    //matrix operations
    void normalizeData(int factor);
    void meanZ(Matrix2D<Type>&);
};

#endif // MATRIX3D_H_INCLUDED
