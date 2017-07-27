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
    Matrix3D(Matrix3D& new_matrix);
    //destructor
    ~Matrix3D();

    //getters
    inline int getXDim(){return this->xDim;};
    inline int getYDim(){return this->yDim;};
    inline int getZDim(){return this->zDim;};
    inline unsigned int getDim(){return this->xDim*this->yDim*this->zDim;};
    //setters
    inline void setXDim(int new_xDim){this->xDim = new_xDim;};
    inline void setYDim(int new_yDim){this->yDim = new_yDim;};
    inline void setZDim(int new_zDim){this->zDim = new_zDim;};

    //operators overloading
    Type& operator()(unsigned int new_xDim, unsigned int new_yDim, unsigned int new_zDim);
    Matrix3D& operator=(Matrix3D& new_matrix);

    //matrix operations
    void normalizeData(int factor);
    void meanZ(Matrix2D<Type>&);
};

#endif // MATRIX3D_H_INCLUDED
