#include "matrix3D.h"

template <class Type>
void Matrix3D<Type>::get3DIndecesFromLinearIndex(int index, int *w, int *h, int *d)
{
    *w = index/(this->height*this->depth);  //Note the integer division . This is x
    *h = (index - (*w)*this->height*this->depth)/this->depth; //This is y
    *d = index - (*w)*this->height*this->depth - (*h)*this->depth;//This is z
}

//constructor
template <class Type>
Matrix3D<Type>::Matrix3D(unsigned int new_xDim, unsigned int new_yDim, unsigned int new_zDim)
{
    this->width = new_xDim;
    this->height = new_yDim;
    this->depth = new_zDim;

    //allocate memory
    this->matrix3d = new Type[this->width*this->height*this->depth];
}

//destructor
template <class Type>
Matrix3D<Type>::~Matrix3D()
{
    delete [] this->matrix3d;
}

//used to read data from MAT file
template <class Type>
void Matrix3D<Type>::setMatrix3D(Type* data, int new_width,  int new_height, int new_depth)
{
    this->width = new_width;
    this->height = new_height;
    this->depth = new_depth;

    //allocate memory
    this->matrix3d = new Type[this->width*this->height*this->depth];

    //copy elements
    for(unsigned int xIdx = 0; xIdx < this->width; xIdx++)
        for(unsigned int yIdx = 0; yIdx < this->height; yIdx++)
            for(unsigned int zIdx = 0; zIdx < this->depth; zIdx++)
        {
            this->setMatrixValue(xIdx, yIdx, zIdx, data[xIdx+ yIdx*this->width + zIdx*this->height*this->width]);
        }
}

//indexing operator
template <class Type>
Type& Matrix3D<Type>::operator()(unsigned int xIdx, unsigned int yIdx, unsigned int zIdx)
{
    return this->matrix3d[xIdx*this->height*this->depth + yIdx*this->depth + zIdx];
}

template <class Type>
Matrix3D<Type>& Matrix3D<Type>::operator=(const Matrix3D<Type>& new_matrix)
{
    this->width = new_matrix.getWidth();
    this->height = new_matrix.getHeight();
    this->depth = new_matrix.getDepth();

    //allocate memory
    this->matrix3d = new Type[this->width*this->height*this->depth];

    //copy elements
    for(unsigned int xIdx = 0; xIdx < this->width; xIdx++)
        for(unsigned int yIdx = 0; yIdx < this->height; yIdx++)
            for(unsigned int zIdx = 0; zIdx < this->depth; zIdx++)
    {
        this->setMatrixValue(xIdx, yIdx, zIdx, new_matrix.getMatrixValue(xIdx, yIdx, zIdx));
    }

    return *this;
}

//copy constructor. Not mandatory
template <class Type>
Matrix3D<Type>::Matrix3D(const Matrix3D<Type>& new_matrix)
{
    this->width = new_matrix.getWidth();
    this->height = new_matrix.getHeight();
    this->depth = new_matrix.getDepth();

    //allocate memory
    this->matrix3d = new Type[this->width*this->height*this->depth];

    //copy elements
    for(unsigned int xIdx = 0; xIdx < this->width; xIdx++)
        for(unsigned int yIdx = 0; yIdx < this->height; yIdx++)
            for(unsigned int zIdx = 0; zIdx < this->depth; zIdx++)
    {
        this->setMatrixValue(xIdx, yIdx, zIdx, new_matrix.getMatrixValue(xIdx, yIdx, zIdx));
    }
}

template <class Type>
void  Matrix3D<Type>::normalizeData(int factor)
{
    for(int i = 0; i< this->getWidth(); i++)
        for(int j = 0; j < this->getHeight(); j++)
            for(int k = 0; k < this->getDepth(); k++)
    {
        this->matrix3d[i*this->getHeight()*this->getDepth() + j*this->getDepth() + k] /= (double)factor;
    }
}

template <class Type>
void Matrix3D<Type>::meanZ(Matrix2D<Type>& result)
{
    Type sum = 0;

    for(int i = 0; i< this->getWidth(); i++)
        for(int j = 0; j < this->getHeight(); j++)
        {
            for(int k = 0; k < this->getDepth(); k++)
                sum += this->getMatrixValue(i, j, k);

            result.getMat2D()[i][j] = (Type) sum/this->getZDim();
        }
}
