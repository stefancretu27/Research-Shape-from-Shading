#ifndef MATRIX3D_H_INCLUDED
#define MATRIX3D_H_INCLUDED

#include <iostream>
#include "Matrix2D.h"

template <class Type>
class Matrix3D
{
private:
    Type *matrix3d;
    unsigned int width, height, depth;

public:
    //constructors
    Matrix3D(){};
    Matrix3D(unsigned int new_xDim, unsigned int new_yDim, unsigned int new_zDim);
    Matrix3D(const Matrix3D& new_matrix);
    //destructor
    ~Matrix3D();

    //getters
    inline int getWidth()const{return this->width;};
    inline int getHeight()const{return this->height;};
    inline int getDepth()const{return this->depth;};
    inline unsigned int getDim(){return this->width*this->height*this->depth;};
    inline unsigned int getLinearIndex(int i, int j, int k){return i*this->height*this->depth + j*this->depth + k;};
    inline void get3DIndecesFromLinearIndex(int linearindex, int *w, int *h, int *d);
    inline Type getMatrixValue(int i, int j, int k) const {return this->matrix3d[i*height*depth + j*depth + k];};

    //setters
    inline void setWidth(int new_xDim){this->width = new_xDim;};
    inline void setHeight(int new_yDim){this->height = new_yDim;};
    inline void setDepth(int new_zDim){this->depth = new_zDim;};
    inline void setMatrixValue(int x, int y, int z, Type value){this->matrix3d[x*this->height*this->depth + y*this->depth +z] = value;};
    void setMatrix3D(Type* data, int new_width,  int new_height, int new_depth);

    //operators overloading
    Type& operator()(unsigned int new_xDim, unsigned int new_yDim, unsigned int new_zDim);
    Matrix3D& operator=(const Matrix3D& new_matrix);

    //matrix operations
    void normalizeData(int factor);
    void meanZ(Matrix2D<Type>&);
};

#endif // MATRIX3D_H_INCLUDED
