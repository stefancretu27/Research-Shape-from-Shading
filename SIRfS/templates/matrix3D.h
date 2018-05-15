#ifndef MATRIX3D_H_INCLUDED
#define MATRIX3D_H_INCLUDED

#include "matrix2D.h"

template <class Type>
class Matrix3D
{
private:
    Type *container;
    unsigned int width, height, depth;

public:
    //constructors
    Matrix3D():width(0), height(0), depth(0)
    {
        this->container = nullptr;
    };
    Matrix3D(unsigned int new_xDim, unsigned int new_yDim, unsigned int new_zDim);
    Matrix3D(const Matrix3D& new_matrix);
    //destructor
    ~Matrix3D()
    {
        delete [] this->container;
    };

    //indexes operations
    inline unsigned int getLinearIndex(int i, int j, int k)
    {
        return i*this->height*this->depth + j*this->depth + k;
    };
    void get3DIndecesFromLinearIndex(int linearindex, int &w, int &h, int &d);

    //getters
    inline unsigned int getDim()
    {
        return this->width*this->height*this->depth;
    };
    inline int getWidth()const
    {
        return this->width;
    };
    inline int getHeight()const
    {
        return this->height;
    };
    inline int getDepth()const
    {
        return this->depth;
    };
    inline Type* getContainer()const
    {
        return this->container;
    };
    inline Type getMatrixValue(int i, int j, int k) const
    {
        return this->container[i*height*depth + j*depth + k];
    };
    inline Type getMatrixValue(unsigned int linearindex) const
    {
        return this->container[linearindex];
    };

    //setters
    inline void setWidth(int new_xDim)
    {
        this->width = new_xDim;
    };
    inline void setHeight(int new_yDim)
    {
        this->height = new_yDim;
    };
    inline void setDepth(int new_zDim)
    {
        this->depth = new_zDim;
    };
    inline void setDims(int new_xDim, int new_yDim, int new_zDim)
    {
        this->width = new_xDim;
        this->height = new_yDim;
        this->depth = new_zDim;
    };
    inline void setMatrixValue(int x, int y, int z, Type value)
    {
        this->matrix3d[this->getLinearIndex(x, y, z)] = value;
    };
    void setMatrix3D(Type* data, int new_width,  int new_height, int new_depth, bool transp);

    //operators overloading
    Type& operator()(unsigned int new_xDim, unsigned int new_yDim, unsigned int new_zDim);
    Matrix3D& operator=(const Matrix3D& new_matrix);

    //matrix operations
    void normalizeData(int factor);
    void meanZ(Matrix2D<Type>&);
};

#endif // MATRIX3D_H_INCLUDED
