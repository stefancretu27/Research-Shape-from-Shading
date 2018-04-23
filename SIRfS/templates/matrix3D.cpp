#include "matrix3D.h"

using namespace std;

//http://www.drdobbs.com/a-c-matrix-template-class/184403323

//constructor
template <class Type>
Matrix3D<Type>::Matrix3D(unsigned int new_xDim, unsigned int new_yDim, unsigned int new_zDim):width(new_xDim), height(new_yDim), depth(new_zDim)
{
    if(this->height > 0 && this->width > 0 && this->depth > 0)
    {
        this->container = new Type[width*height*depth];
    }
    else
    {
        //set everything to 0 so to avoid garbage values being stored in
        this->width = this->height = this->depth = 0;
        this->container = nullptr;
    }
}

//copy constructor
template <class Type>
Matrix3D<Type>::Matrix3D(const Matrix3D<Type>& new_matrix):width(new_matrix.getWidth()), height(new_matrix.getHeight()), depth(new_matrix.getDepth())
{
    if(this->height > 0 && this->width > 0 && this->depth > 0)
    {
        this->container = new Type[width*height*depth];

        for(unsigned int idx = 0; idx < this->getDim(); idx++)
            this->container[idx] = new_matrix.getMatrixValue(idx);
    }
    else
    {
        //set everything to 0 so to avoid garbage values being stored in
        this->width = this->height = this->depth = 0;
        this->container = nullptr;
    }
}

//index related operations
template <class Type>
void Matrix3D<Type>::get3DIndecesFromLinearIndex(int index, int &w, int &h, int &d)
{
    w = index/(this->height*this->depth);  //integer division . This is x
    h = (index - w*this->height*this->depth)/this->depth; //This is y
    d = index - w*this->height*this->depth - h*this->depth;//This is z
}

//used to read data from MAT file
template <class Type>
void Matrix3D<Type>::setMatrix3D(Type* data, int new_width,  int new_height, int new_depth, bool transp)
{
    this->width = new_width;
    this->height = new_height;
    this->depth = new_depth;

    if(this->height > 0 && this->width > 0 && this->depth > 0)
    {
        //allocate memory
        this->container = new Type[width*height*depth];

        //copy elements
        if(transp)
        {
            for(unsigned int xIdx = 0; xIdx < this->width; xIdx++)
                for(unsigned int yIdx = 0; yIdx < this->height; yIdx++)
                    for(unsigned int zIdx = 0; zIdx < this->depth; zIdx++)
                    {
                        //this->matrix3d.push_back(data[xIdx+ yIdx*this->width + zIdx*this->height*this->width]);
                        //better execution time than push_back
                        this->container[this->getLinearIndex(xIdx,yIdx,zIdx)] = data[xIdx+ yIdx*this->width + zIdx*this->height*this->width];
                    }
        }
        else
        {
            //copy elements
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                this->container[idx] = data[idx];
            }
        }
    }
    else
    {
        //set everything to 0 so to avoid garbage values being stored in
        this->width = this->height = this->depth = 0;
        this->container = nullptr;
    }
}

//operators overloading
//indexing operator
template <class Type>
Type& Matrix3D<Type>::operator()(unsigned int xIdx, unsigned int yIdx, unsigned int zIdx)
{
    return this->container[xIdx*this->height*this->depth + yIdx*this->depth + zIdx];
}

template <class Type>
Matrix3D<Type>& Matrix3D<Type>::operator=(const Matrix3D<Type>& new_matrix)
{
    this->width = new_matrix.getWidth();
    this->height = new_matrix.getHeight();
    this->depth = new_matrix.getDepth();

    if(this->height > 0 && this->width > 0 && this->depth > 0)
    {
        //allocate memory and copy elements
        this->container = new Type[width*height*depth];

        for(unsigned int idx = 0; idx < this->getDim(); idx++)
        {
            this->container[idx] = new_matrix.getMatrixValue(idx);
        }
    }
    else
    {
        //set everything to 0 so to avoid garbage values being stored in
        this->width = this->height = this->depth = 0;
        this->container = nullptr;
    }
    return *this;
}

//matrix operations
template <class Type>
void  Matrix3D<Type>::normalizeData(int factor)
{
    //iterator and size-Type require a known type and not a generical one
    for(unsigned int  i = 0; i < this->getDim(); i++)
        this->container[i] /= (double)factor;
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

            result.setMatrixValue(i , j, (Type) sum/this->getZDim());
        }
}
