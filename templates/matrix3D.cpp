#include "matrix3D.h"

//constructor
template <class Type>
Matrix3D<Type>::Matrix3D(unsigned int new_xDim, unsigned int new_yDim, unsigned int new_zDim)
{
    this->xDim = new_xDim;
    this->yDim = new_yDim;
    this->zDim = new_zDim;

    //allocate memory for the x size. It is an array that contains double pointers to Type.
    this->matrix3d = new Type** [this->xDim];
    //allocate space for the  y size. It will contain pointers to Type.
    for(unsigned int xIdx = 0; xIdx < this->xDim; xIdx++)
    {
        this->matrix3d[xIdx] = new Type* [this->yDim];

        //allocate memory for z size.
        for(unsigned int yIdx = 0; yIdx < this->yDim; yIdx++)
        {
            this->matrix3d[xIdx][yIdx] = new Type [this->zDim];
        }
    }
}

//destructor
template <class Type>
Matrix3D<Type>::~Matrix3D()
{
    for(unsigned int xIdx = 0; xIdx < this->xDim; xIdx++)
        for(unsigned int yIdx = 0; yIdx < this->yDim; yIdx++)
    {
        delete [] this->matrix3d[xIdx][yIdx];
    }

    delete [] this->matrix3d;
}

//indexing operator
template <class Type>
Type& Matrix3D<Type>::operator()(unsigned int xIdx, unsigned int yIdx, unsigned int zIdx)
{
    return this->matrix3d[xIdx][yIdx][zIdx];
}

template <class Type>
Matrix3D<Type>& Matrix3D<Type>::operator=(const Matrix3D<Type>& new_matrix)
{
    this->xDim = new_matrix.getXDim();
    this->yDim = new_matrix.getYDim();
    this->zDim = new_matrix.getZDim();

    //allocate memory for the x size. It is an array that contains double pointers to Type.
    this->matrix3d = new Type** [this->xDim];
    //allocate space for the  y size. It will contain pointers to Type.
    for(unsigned int xIdx = 0; xIdx < this->xDim; xIdx++)
    {
        this->matrix3d[xIdx] = new Type* [this->yDim];

        //allocate memory for z size.
        for(unsigned int yIdx = 0; yIdx < this->yDim; yIdx++)
        {
            this->matrix3d[xIdx][yIdx] = new Type [this->zDim];
        }
    }

    //copy elements
    for(unsigned int xIdx = 0; xIdx < this->xDim; xIdx++)
        for(unsigned int yIdx = 0; yIdx < this->yDim; yIdx++)
            for(unsigned int zIdx = 0; zIdx < this->zDim; zIdx++)
    {
        this->setMatrixValue(xIdx, yIdx, zIdx, new_matrix.getMatrixValue(xIdx, yIdx, zIdx));
    }

    return *this;
}

//copy constructor. Not mandatory
template <class Type>
Matrix3D<Type>::Matrix3D(const Matrix3D<Type>& new_matrix)
{
    this->xDim = new_matrix.getXDim();
    this->yDim = new_matrix.getYDim();
    this->zDim = new_matrix.getZDim();

    //allocate memory for the x size. It is an array that contains double pointers to Type.
    this->matrix3d = new Type** [this->xDim];
    //allocate space for the  y size. It will contain pointers to Type.
    for(unsigned int xIdx = 0; xIdx < this->xDim; xIdx++)
    {
        this->matrix3d[xIdx] = new Type* [this->yDim];

        //allocate memory for z size.
        for(unsigned int yIdx = 0; yIdx < this->yDim; yIdx++)
        {
            this->matrix3d[xIdx][yIdx] = new Type [this->zDim];
        }
    }

    //copy elements
    for(unsigned int xIdx = 0; xIdx < this->xDim; xIdx++)
        for(unsigned int yIdx = 0; yIdx < this->yDim; yIdx++)
            for(unsigned int zIdx = 0; zIdx < this->zDim; zIdx++)
    {
        this->setMatrixValue(xIdx, yIdx, zIdx, new_matrix.getMatrixValue(xIdx, yIdx, zIdx));
    }
}

template <class Type>
void  Matrix3D<Type>::normalizeData(int factor)
{
    for(int i = 0; i< this->getXDim(); i++)
        for(int j = 0; j < this->getYDim(); j++)
            for(int k = 0; k < this->getZDim(); k++)
    {
        this->matrix3d[i][j][k] /= (double)factor;
    }
}

template <class Type>
void Matrix3D<Type>::meanZ(Matrix2D<Type>& result)
{
    Type sum = 0;

    for(int i = 0; i< this->getXDim(); i++)
        for(int j = 0; j < this->getYDim(); j++)
        {
            for(int k = 0; k < this->getZDim(); k++)
                sum += this->matrix3d[i][j][k];

            result.getMat2D()[i][j] = (Type) sum/this->getZDim();
        }
}
