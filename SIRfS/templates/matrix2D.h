#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <limits>

//cuda libraries
#include <cuda.h>
#include <cuda_runtime.h>

#include "keyValue.h"
#include "../helpers/enums.h" 

#define CUDA_CORES_NO 768
#define THREADS_PER_ONE_DIM_BLOCK 256
#define THREADS_PER_TWO_DIM_BLOCK 16

//forward declarations of kernels to be used inside Matrix2D class 
template<class Type> cudaError_t operator_multiply(Type* device_A, Type* device_B, Type *result, dim3 grid_dim, dim3 block_dim, int A_rows, int B_rows, int B_cols);
template<class Type> cudaError_t conv2D_full_kernel_launcher(Type* input, Type* kernel, Type* output, dim3 grid_dim, dim3 block_dim, \
															int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols);
template<class Type> cudaError_t conv2D_valid_kernel_launcher(Type* input, Type* kernel, Type* output, dim3 grid_dim, dim3 block_dim, \
															int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols);
template<class Type> cudaError_t conv2D_same_kernel_launcher(Type* input, Type* kernel, Type* output, dim3 grid_dim, dim3 block_dim, \
															int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols);

//https://devtalk.nvidia.com/default/topic/519806/what-is-__host__-__device__/

template <class Type>
class Matrix2D
{
private:
    Type *container;
    int rows, cols;

public:
    //constructors
    Matrix2D(){this->rows = 0; this->cols = 0; this->container = nullptr;};
    //overloaded constructors
    Matrix2D(int new_rows, int new_cols);
    Matrix2D(int new_rows, int new_cols, Type value);
    //copy constructor
    Matrix2D(const Matrix2D<Type>& input_matrix);
    //destructor
    ~Matrix2D()
    {
		//delete the array
		delete [] this->container;
    };

    //indexes operations
    inline unsigned int getLinearIndex(int i, int j)
    {
        return i*this->cols + j;
    };
    void get2DIndecesFromLinearIndex(int index, int &rows, int &cols)
    {
        rows = index/this->cols;  //integer division . This is x
        cols = index - rows; //This is y
    };

    //getters
    inline int getRows() const              //inline tells compiler to replace function with its definition => faster execution as there is less linking
    {
        return this->rows;
    };
    inline int getCols() const
    {
        return this->cols;
    };
    inline int getDim() const
    {
        return this->rows*this->cols;
    };
    inline Type* getContainerPointer()
    {
        return this->container;
    };
    inline Type getMatrixValue(int i, int j) const
    {
        return this->container[i*this->cols + j];
    };
    inline Type getMatrixValue(unsigned linearindex) const
    {
        return this->container[linearindex];
    };

    //setters
    inline void setRows(int new_rows)
    {
        this->rows = new_rows;
    };
    inline void setCols(int new_cols)
    {
        this->cols = new_cols;
    };
    inline void setDims(int new_rows, int new_cols)
    {
        this->cols = new_cols;
        this->rows = new_rows;
    };
    inline void setMatrixValue(int i, int j, Type value)
    {
        this->container[i*this->cols +j] = value;
    };
    inline void setMatrixValue(unsigned int linearindex, Type value)
    {
        this->container[linearindex] = value;
    };
    void setMatrix2D(Type* data, int new_rows,  int new_cols, bool transp);

    //operators overloading
    inline Type& operator() (int rowsIdx, int colsIdx) const
    {
        return this->container[rowsIdx * this->cols + colsIdx];
    };
    bool operator==(const Matrix2D<Type>& operand_matrix);
    Matrix2D& operator=(const Matrix2D<Type>& operand_matrix);
    Matrix2D& operator+(Matrix2D<Type>& operand_matrix);
    Matrix2D& operator-(Matrix2D<Type>& operand_matrix);
    Matrix2D& multiply_input_matrices(Matrix2D<Type>& input_A, Matrix2D<Type>& input_B, bool useCUDA);
    
    //helper: separate function from constructors, used data copying
    void initializeMatrixValues(Type value);

    //convolution: apply kernel to the input matrix and store the conv result in the caller matrix
    void conv2DFull(Matrix2D<Type>& kernel, Matrix2D<Type>& input, bool useCUDA);
    void conv2DValid(Matrix2D<Type>& kernel,  Matrix2D<Type>& input, bool useCUDA);
    void conv2DSame(Matrix2D<Type>& kernel, Matrix2D<Type>& input, bool useCUDA);

    //matrix operations. They are the C++ implementations for Matlab library functions for 2D matrices
    /*
    *mask related operations
    */
    //It gets as input a matrice's  mask and the changes are made to the caller
    void insertNaNValues(Matrix2D<bool>& mask);
    //creates a mask by comparing the caller's values to the given treshold
    void compareValuesToTreshold(Matrix2D<bool>& result, Type treshold, Comparison comp);
//CHANGED
    void negateMatrixMask(const Matrix2D<bool>& input_mask);
    //returns the # of non-zero elements
    int logicalAnd(Matrix2D<bool>& result, const Matrix2D<Type>& input);
    //only the number of columns has to be equal to size of vector
    void compareMatrixColumnsToVector(Matrix2D<bool>& result, const Type* input, int input_size, Comparison comp);
    void applyVectorMask(const Matrix2D<Type>& input, bool* mask);
    void applyDoubleVectorMask(const Matrix2D<Type>& input, const std::vector<bool> mask1, const std::vector<bool> mask2);
    void applyMatrixMask(const Matrix2D<Type>& input, const Matrix2D<bool> mask);
    void sortLines();

    /*
    *basic math-operations
    */
    void getAbsoluteValuesMatrix(const Matrix2D<Type>& input);
    void logNatMatrix(const Matrix2D<Type>& input);
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
    void vFindIndeces(int* x, int* y, int input_vectors_dim, Type value, Comparison cmp);
    //same as above, but stores the values in a 3rd vector
    void vFindIndecesAndValues(int* x, int* y, Type* val, Type value, Comparison cmp);
    //per matrix element operation
    void elementsOperation(Matrix2D<Type>& result, Type value, Operation op);
    void allNonZero(bool* result, int direction);
    int countValuesDifferentFromInput(Type value);
    /*
    *matrix conversions
    */
    void copyMatrixColumnToVector(std::vector<Type> &result, int col);
    void copyMatrixRowToVector(std::vector<Type> &result, int row);
    void reshapeToVector(std::vector<Type>& dest);
//CHANGED
    void getSubMatrix(const Matrix2D<Type>& input, int x_first, int x_last, int y_first, int y_last);
//CHANGED
    void reverseMatrix(const Matrix2D<Type>& input);
    void getTranspose(Matrix2D<Type>** result);
    //same as above, but result is stored in the caller (caller data is lost)
    void TransposeMatrix();
    
    //for debug purposes
    void printMatrixValues()
    {
        for(int i = 0; i < this->rows; i++)
        {
            for(int j = 0; j < this->cols; j++)
            {
                std::cout<<this->container[i*this->cols + j]<<" ";
            }
            std::cout<<std::endl;
		}
	}
      
};


/*
*Constructors
*/
//Creates a matrix2D with specified dimensions
template <class Type>
Matrix2D<Type>::Matrix2D(int new_rows, int new_cols):rows(new_rows), cols(new_cols)
{
    if(this->rows > 0 && this->cols > 0)
    {
        //allocate memory
        this->container = new Type[this->rows*this->cols];
    }
    else
    {
        //set everything to 0 so to avoid garbage values being stored in
        this->rows = this->cols = 0;
        this->container = nullptr;
    }
}

//Constructor with data initializations: this constructor creates a matrix2D that has the specified dimensions and whose elements are initialized to the given value
template <class Type>
Matrix2D<Type>::Matrix2D( int new_rows,  int new_cols, Type value):rows(new_rows), cols(new_cols)
{
    if(this->rows > 0 && this->cols > 0)
    {
        //allocate memory
        this->container = new Type[this->rows*this->cols];

        for(unsigned int idx = 0; idx < this->getDim(); idx++)
        {
            this->container[idx] = value;
        }
    }
    else
    {
        //set everything to 0 so to avoid garbage values being stored in
        this->rows = this->cols = 0;
        this->container = nullptr;
    }
}

//Copy constructor: The calling matrix is a clone of the input matrix, being allocated and initialized to the latter's values
template <class Type>
Matrix2D<Type>::Matrix2D(const Matrix2D<Type>& input_matrix):rows(input_matrix.getRows()), cols(input_matrix.getCols())
{
    if(this->rows > 0 && this->cols > 0)
    {
        //allocate memory
        this->container = new Type[this->rows*this->cols];

        //copy elements
        for(unsigned int idx = 0; idx < this->getDim(); idx++)
        {
            this->container[idx] = input_matrix.getMatrixValue(idx);
        }
    }
    else
    {
        //set everything to 0 so to avoid garbage values being stored in
        this->rows = this->cols = 0;
        this->container = nullptr;
    }
}

template <class Type>
void Matrix2D<Type>::setMatrix2D(Type* data, int new_rows,  int new_cols, bool transp)
{
    this->rows = new_rows;
    this->cols = new_cols;

    if(this->rows > 0 && this->cols > 0)
    {
        //allocate memory
        this->container = new Type[this->rows*this->cols];

        //in Matlab the matrices are stored column after column, in the contiguous array gotten as parameters (data), so it needs to be transposed
        if(transp)
        {
            //copy elements
            for( int rowsIdx = 0; rowsIdx < this->rows; rowsIdx++)
                for( int colsIdx = 0; colsIdx < this->cols; colsIdx++)
                {
                    //this->setMatrixValue(rowsIdx, colsIdx, data[rowsIdx + this->rows*colsIdx]);
                    this->container[rowsIdx*this->cols +colsIdx] = data[rowsIdx + this->rows*colsIdx];
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
        this->rows = this->cols = 0;
        this->container = nullptr;
    }
}

//operators overloading
template <class Type>
bool Matrix2D<Type>::operator==(const Matrix2D<Type>& operand_matrix)
{
    bool k = true;

    if(this->getDim() != operand_matrix.getDim())
    {
        std::cout<<"The matrices have different dimensions and cannot be compared!"<<std::endl;
        exit(0);
    }

    if(this->getDim() == 0 || operand_matrix.getDim() == 0)
    {
        std::cout<<"At least one of the matrices has no elements, thus comparison failed!"<<std::endl;
        exit(0);
    }

    for(unsigned int idx = 0; idx < this->getDim() && k; idx++)
    {
        if(this->container[idx]!= operand_matrix.getMatrixValue(idx))
        {
            k = false;
            break;
        }
    }

    return k;
}

template <class Type>
Matrix2D<Type>& Matrix2D<Type>::operator=(const Matrix2D<Type>& operand_matrix)
{
    //get new dimensions
    this->rows = operand_matrix.getRows();
    this->cols = operand_matrix.getCols();

    //delete previously stored data, if any
    if(this->container != nullptr)
    {
        delete this->container;
    }

    if(this->rows > 0 && this->cols > 0)
    {
        //allocate memory
        this->container = new Type[this->rows*this->cols];

        //copy elements
        for(unsigned int idx = 0; idx < this->getDim(); idx++)
        {
            this->container[idx] = operand_matrix.getMatrixValue(idx);
        }
    }
    else
    {
        //set everything to 0 so to avoid garbage values being stored in
        this->rows = this->cols = 0;
        this->container = nullptr;
    }

    return *this;
}

template <class Type>
Matrix2D<Type>& Matrix2D<Type>::operator+(Matrix2D<Type>& operand_matrix)
{
    if(this->getRows() != operand_matrix.getRows() || this->getCols() != operand_matrix.getCols())
    {
        std::cout<<"Couldn't add matrices. They have different dimensions"<<std::endl;
        exit(0);
    }

	for(unsigned int idx = 0; idx < this->getDim(); idx++)
	{
		this->container[idx] += operand_matrix.getMatrixValue(idx);
	}

    return *this;
}

template <class Type>
Matrix2D<Type>& Matrix2D<Type>::operator-(Matrix2D<Type>& operand_matrix)
{
    if(this->getRows() != operand_matrix.getRows() || this->getCols() != operand_matrix.getCols())
    {
        std::cout<<"Couldn't substract matrices. They have different dimensions"<<std::endl;
        exit(0);
    }

	for(unsigned int idx = 0; idx < this->getDim(); idx++)
	{
		this->container[idx] -= operand_matrix.getMatrixValue(idx);
	}

    return *this;
}

template <class Type>
Matrix2D<Type>& Matrix2D<Type>::multiply_input_matrices(Matrix2D<Type>& input_A, Matrix2D<Type>& input_B, bool useCUDA)
{
    if(input_A.getCols() != input_B.getRows())
    {
        std::cout<<"Couldn't multiply matrices."<<std::endl;
        exit(0);
    }

	if(useCUDA)
	{
		Type *device_A, *device_B, *device_result;
		//alocate memory on GPU
		cudaMalloc((void**)&device_A, sizeof(Type) * input_A.getDim());
		cudaMalloc((void**)&device_B, sizeof(Type) * input_B.getDim());
		cudaMalloc((void**)&device_result, sizeof(Type) * this->getDim());
		
		//copy elements in GPU RAM. Parameters: destination, source, size, flag
		cudaMemcpy(device_A, input_A.getContainerPointer(), sizeof(Type) * input_A.getDim(), cudaMemcpyHostToDevice);
		cudaMemcpy(device_B, input_B.getContainerPointer(), sizeof(Type) * input_B.getDim(), cudaMemcpyHostToDevice);
		
		//Specify the number of threads per block and blocks per grid, as well as their dimensions (bi dimensional in this case)
		dim3 block_dim(THREADS_PER_TWO_DIM_BLOCK, THREADS_PER_TWO_DIM_BLOCK);
		//make sure there are enough blocks to cover the matrices, as their dimensions are not exponential of 2
		dim3 grid_dim( (input_B.getCols() + THREADS_PER_TWO_DIM_BLOCK - 1)/THREADS_PER_TWO_DIM_BLOCK, (input_A.getRows()+ THREADS_PER_TWO_DIM_BLOCK - 1)/THREADS_PER_TWO_DIM_BLOCK);
		//call kernel launcher
		operator_multiply(device_A, device_B, device_result, grid_dim, block_dim, input_A.getRows(), input_B.getRows(), input_B.getCols());
		//copy the results from GPU RAM into CPU RAM
		cudaMemcpy(this->getContainerPointer(), device_result, sizeof(Type) * this->getDim(), cudaMemcpyDeviceToHost);

		//deallocate GPU memory
		cudaFree(device_A);
		cudaFree(device_B);
		cudaFree(device_result);
	}
	else
	{
		Type accum;

		for(unsigned int idx = 0; idx < input_A.getRows(); idx++)
		{
			for(unsigned int idy = 0; idy < input_B.getCols(); idy++)
			{
				accum = (Type) 0;
				for(unsigned int idz = 0; idz < input_B.getRows(); idz++)
				{
					accum+= input_A.getMatrixValue(idx, idz)*input_B.getMatrixValue(idz, idy);
				}
				
				this->container[idx*this->cols + idy] = accum;
			}
		}
	}

    return *this;
}

/*
*helpers
*/
template <class Type>
void Matrix2D<Type>::initializeMatrixValues(Type value)
{
    if(this->rows > 0 && this->cols > 0 && this->container != nullptr)
    {
        for(unsigned int idx = 0; idx < this->getDim(); idx++)
        {
            this->container[idx] = value;
        }
    }
    else
    {
        std::cout<<"Couldn't initialize matrix values"<<std::endl;
        exit(0);
    }
}


/*
*Convolution
*/
template <class Type>
void Matrix2D<Type>::conv2DFull(Matrix2D<Type>& kernel, Matrix2D<Type>& input, bool useCUDA)
{
	if(useCUDA)
	{
		Type *device_output, *device_input, *device_kernel;
		//alocate memory on GPU
		cudaMalloc((void**)&device_output, sizeof(Type) * this->getDim());
		cudaMalloc((void**)&device_input, sizeof(Type) * input.getDim());
		cudaMalloc((void**)&device_kernel, sizeof(Type) * kernel.getDim());
		
		//copy elements in GPU RAM. Parameters: destination, source, size, flag
		cudaMemcpy(device_input, input.getContainerPointer(), sizeof(Type) * input.getDim(), cudaMemcpyHostToDevice);
		cudaMemcpy(device_kernel, kernel.getContainerPointer(), sizeof(Type) * kernel.getDim(), cudaMemcpyHostToDevice);
		
		dim3 threads_per_block(THREADS_PER_TWO_DIM_BLOCK, THREADS_PER_TWO_DIM_BLOCK);
		dim3 dimGrid( (this->getCols() + THREADS_PER_TWO_DIM_BLOCK -1)/THREADS_PER_TWO_DIM_BLOCK, (this->getRows() + THREADS_PER_TWO_DIM_BLOCK -1)/THREADS_PER_TWO_DIM_BLOCK );
		//call kernel launcher
		conv2D_full_kernel_launcher(device_input, device_kernel, device_output, dimGrid, threads_per_block, input.getRows(), input.getCols(), kernel.getRows(), kernel.getCols(), this->getRows(), this->getCols() );
		//copy the results from GPU RAM into CPU RAM
		cudaMemcpy(this->getContainerPointer(), device_output, sizeof(Type) * this->getDim(), cudaMemcpyDeviceToHost);

		//deallocate GPU memory
		cudaFree(device_input);
		cudaFree(device_kernel);
		cudaFree(device_output);
	}
	else
	{
		Type temp;
		int i, j, m, n, sourceIdx, sourceIdy;
		//find kernel center
		int kCenterX = (kernel.getCols()+1)/2, kCenterY = (kernel.getRows()+1)/2;

		for(i = 0; i < this->getRows(); i++)
		{
			for(j = 0; j < this->getCols(); j++)                           // columns
			{
				for(m = 0; m < kernel.getRows(); m++)
				{
					for(n = 0; n < kernel.getCols() ; n++)
					{
						sourceIdx = i + m - kCenterY;
						sourceIdy =  j + n - kCenterX;

						if( sourceIdx < input.getRows() && sourceIdx >= 0 && sourceIdy  <  input.getCols() && sourceIdy  >= 0)
						{
							temp = this->getMatrixValue(i, j) + input.getMatrixValue(sourceIdx, sourceIdy) * kernel.getMatrixValue(m, n);
							this->setMatrixValue(i, j, temp);
						}
					}
				}
			}
		}
	}
}


template <class Type>
void Matrix2D<Type>::conv2DValid(Matrix2D<Type>& kernel,  Matrix2D<Type>& input, bool useCUDA)
{
	if(useCUDA)
	{
		Type *device_output, *device_input, *device_kernel;
		//alocate memory on GPU
		cudaMalloc((void**)&device_output, sizeof(Type) * this->getDim());
		cudaMalloc((void**)&device_input, sizeof(Type) * input.getDim());
		cudaMalloc((void**)&device_kernel, sizeof(Type) * kernel.getDim());
		
		//copy elements in GPU RAM. Parameters: destination, source, size, flag
		cudaMemcpy(device_input, input.getContainerPointer(), sizeof(Type) * input.getDim(), cudaMemcpyHostToDevice);
		cudaMemcpy(device_kernel, kernel.getContainerPointer(), sizeof(Type) * kernel.getDim(), cudaMemcpyHostToDevice);
		
		dim3 threads_per_block(THREADS_PER_TWO_DIM_BLOCK, THREADS_PER_TWO_DIM_BLOCK);
		dim3 dimGrid( (this->getCols() + THREADS_PER_TWO_DIM_BLOCK -1)/THREADS_PER_TWO_DIM_BLOCK, (this->getRows() + THREADS_PER_TWO_DIM_BLOCK -1)/THREADS_PER_TWO_DIM_BLOCK );
		//call kernel launcher
		conv2D_valid_kernel_launcher(device_input, device_kernel, device_output, dimGrid, threads_per_block, input.getRows(), input.getCols(), kernel.getRows(), kernel.getCols(), this->getRows(), this->getCols() );
		//copy the results from GPU RAM into CPU RAM
		cudaMemcpy(this->getContainerPointer(), device_output, sizeof(Type) * this->getDim(), cudaMemcpyDeviceToHost);

		//deallocate GPU memory
		cudaFree(device_input);
		cudaFree(device_kernel);
		cudaFree(device_output);
	}
	else
	{
		Type temp;
		int i, j, m, n;

		for(i = 0; i < this->getRows(); i++)
		{
			for(j = 0; j < this->getCols(); j++)
			{
			   for(m = 0; m < kernel.getRows(); m++)
				{
					for(n = 0; n < kernel.getCols() ; n++)
					{
						temp = this->getMatrixValue(i, j) + input.getMatrixValue(i+m, j+n) * kernel.getMatrixValue(m, n);
						this->setMatrixValue(i, j, temp);
					}
				}
			}
		}
	}
}

template <class Type>
void Matrix2D<Type>::conv2DSame(Matrix2D<Type>& kernel, Matrix2D<Type>& input, bool useCUDA)
{
	if(useCUDA)
	{
		Type *device_output, *device_input, *device_kernel;
		//alocate memory on GPU
		cudaMalloc(&device_output, sizeof(Type) * this->getDim());
		cudaMalloc(&device_input, sizeof(Type) * input.getDim());
		cudaMalloc(&device_kernel, sizeof(Type) * kernel.getDim());
		
		//copy elements in GPU RAM. Parameters: destination, source, size, flag
		cudaMemcpy(device_input, input.getContainerPointer(), sizeof(Type) * input.getDim(), cudaMemcpyHostToDevice);
		cudaMemcpy(device_kernel, kernel.getContainerPointer(), sizeof(Type) * kernel.getDim(), cudaMemcpyHostToDevice);
		
		dim3 threads_per_block(THREADS_PER_TWO_DIM_BLOCK, THREADS_PER_TWO_DIM_BLOCK);
		dim3 dimGrid( (this->getCols() + THREADS_PER_TWO_DIM_BLOCK -1)/THREADS_PER_TWO_DIM_BLOCK, (this->getRows() + THREADS_PER_TWO_DIM_BLOCK -1)/THREADS_PER_TWO_DIM_BLOCK );
		//call kernel launcher
		conv2D_same_kernel_launcher(device_input, device_kernel, device_output, dimGrid, threads_per_block, input.getRows(), input.getCols(), kernel.getRows(), kernel.getCols(), this->getRows(), this->getCols() );
		//copy the results from GPU RAM into CPU RAM
		cudaMemcpy(this->getContainerPointer(), device_output, sizeof(Type) * this->getDim(), cudaMemcpyDeviceToHost);

		//deallocate GPU memory
		cudaFree(device_input);
		cudaFree(device_kernel);
		cudaFree(device_output);
	}
	else
	{
		Type temp;
		int i, j, m, n, sourceIdx, sourceIdy;
		//find kernel center
		int kCenterX = (kernel.getCols()-1)/2, kCenterY = (kernel.getRows()-1)/2;

		for(i = 0; i < input.getRows(); i++)
		{
			for(j = 0; j < input.getCols(); j++)                           // columns
			{
				for(m = 0; m < kernel.getRows(); m++)
				{
					for(n = 0; n < kernel.getCols() ; n++)
					{
						sourceIdx = i + m - kCenterY;
						sourceIdy =  j + n - kCenterX;

						if( sourceIdx < input.getRows() && sourceIdx >= 0 && sourceIdy  <  input.getCols() && sourceIdy  >= 0)
						{
							temp = this->getMatrixValue(i, j) + input.getMatrixValue(sourceIdx, sourceIdy) * kernel.getMatrixValue(m, n);
							this->setMatrixValue(i, j, temp);
						}
					}
				}
			}
		}
	}
}

/*
* matrix operations
*/
//the input si always a mask, whose Type == bool
template <class Type>
void Matrix2D<Type>::insertNaNValues(Matrix2D<bool>& mask)
{
    if(mask.getRows() != this->getRows() || mask.getCols() != this->getCols())
    {
        std::cout<<"Couldn't insert NaN values"<<std::endl;
        exit(0);
    }
    else
    {
        for(unsigned int idx = 0; idx < this->getDim(); idx++)
        {
            if(mask.getMatrixValue(idx) == 1)
            {
                this->container[idx] = std::numeric_limits<double>::quiet_NaN();
            }
        }
    }
}

//create mask by comparing caller's values to a given treshold, that is a single value. The result's Type == bool as it is always a mask
template <class Type>
void Matrix2D<Type>::compareValuesToTreshold(Matrix2D<bool>& result, Type treshold, Comparison comp)
{
    switch(comp)
    {
        case 0:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                if(this->container[idx] == treshold)
                {
                    result.setMatrixValue(idx, 1);
                }
                else
                {
                    result.setMatrixValue(idx, 0);
                }
            }
            break;
        case 1:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                if(this->container[idx] != treshold)
                {
                    result.setMatrixValue(idx, 1);
                }
                else
                {
                    result.setMatrixValue(idx, 0);
                }
            }
            break;
        case 2:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                if(this->container[idx] < treshold)
                {
                    result.setMatrixValue(idx, 1);
                }
                else
                {
                    result.setMatrixValue(idx, 0);
                }
            }
            break;
        case 3:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                if(this->container[idx] <= treshold)
                {
                    result.setMatrixValue(idx, 1);
                }
                else
                {
                    result.setMatrixValue(idx, 0);
                }
            }
            break;
        case 4:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                if(this->container[idx] >= treshold)
                {
                    result.setMatrixValue(idx, 1);
                }
                else
                {
                    result.setMatrixValue(idx, 0);
                }
            }
            break;
        case 5:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                if(this->container[idx] > treshold)
                {
                    result.setMatrixValue(idx, 1);
                }
                else
                {
                    result.setMatrixValue(idx, 0);
                }
            }
            break;
    }
}

//usually the caller's Type == bool, as it is a amsk which is negated
template <class Type>
void Matrix2D<Type>::negateMatrixMask(const Matrix2D<bool>& input_mask)
{
    for(unsigned int idx = 0; idx < input_mask.getDim(); idx++)
    {
        this->setMatrixValue(idx, 1 - input_mask.getMatrixValue(idx));
    }
}

//Return the number of 1 values in the computed mask, which is obtained as logical and between input and caller, which usually are also masks (Type ==bool)
template <class Type>
int Matrix2D<Type>::logicalAnd(Matrix2D<bool>& result, const Matrix2D<Type>& input)
{
    unsigned int counter = 0;

    for(unsigned int idx = 0; idx < this->getDim(); idx++)
    {
        result.setMatrixValue(idx, this->container[idx] & input.getMatrixValue(idx));

        if(result.getMatrixValue(idx) == 1)
        {
            counter++;
        }
    }

    return counter;
}

//Each element from a column of the caller matrix is compared to one value from the input vector. Elements from next column are compared to next value and so on till the end.
//No of  caller matrix columns  = size of input vector
template <class Type>
void Matrix2D<Type>::compareMatrixColumnsToVector(Matrix2D<bool>& result, const Type *input, int input_size, Comparison comp)
{
    int i , j;

    if((unsigned) this->getCols() != input_size)
    {
        std::cout<<"Comparison couldn't be done. Input vector's size doesn't match caller matrix number of columns."<<std::endl;
        exit(0);
    }

    switch(comp)
    {
        case 0:
            for(j = 0; j < this->getCols(); j++)
                for(i = 0; i < this->getRows(); i++)
                {
                    if(this->getMatrixValue(i, j) == input[j])
                    {
                        result.setMatrixValue(i, j, 1);
                    }
                    else
                    {
                        result.setMatrixValue(i, j, 0);
                    }
                }
            break;
        case 1:
            for(j = 0; j < this->getCols(); j++)
                for(i = 0; i < this->getRows(); i++)
                {
                    if(this->getMatrixValue(i, j) != input[j])
                    {
                        result.setMatrixValue(i, j, 1);
                    }
                    else
                    {
                        result.setMatrixValue(i, j, 0);
                    }
                }
            break;
        case 2:
            for(j = 0; j < this->getCols(); j++)
                for(i = 0; i < this->getRows(); i++)
                {
                    if(this->getMatrixValue(i, j) < input[j])
                    {
                        result.setMatrixValue(i, j, 1);
                    }
                    else
                    {
                        result.setMatrixValue(i, j, 0);
                    }
                }
            break;
        case 3:
            for(j = 0; j < this->getCols(); j++)
                for(i = 0; i < this->getRows(); i++)
                {
                    if(this->getMatrixValue(i, j) <= input[j])
                    {
                        result.setMatrixValue(i, j, 1);
                    }
                    else
                    {
                        result.setMatrixValue(i, j, 0);
                    }
                }
            break;
        case 4:
            for(j = 0; j < this->getCols(); j++)
                for(i = 0; i < this->getRows(); i++)
                {
                    if(this->getMatrixValue(i, j) >= input[j])
                    {
                        result.setMatrixValue(i, j, 1);
                    }
                    else
                    {
                        result.setMatrixValue(i, j, 0);
                    }
                }
            break;
        case 5:
            for(j = 0; j < this->getCols(); j++)
                for(i = 0; i < this->getRows(); i++)
                {
                    if(this->getMatrixValue(i, j) > input[j])
                    {
                        result.setMatrixValue(i, j, 1);
                    }
                    else
                    {
                        result.setMatrixValue(i, j, 0);
                    }
                }
            break;
    }
}

template <class Type>
void Matrix2D<Type>::applyVectorMask(const Matrix2D<Type>& input, bool *mask)
{
    int t_idx = 0;

    //mask.getRows = source.getRows. For each line, check if mask is 1, then iterate through cols, allocate memory for KeyValue object, then set ts values
    for(int idx = 0; idx <this->getRows(); idx++)
    {
        if(mask[idx] == 1)
        {
            for( int idy = 0; idy < input.getCols(); idy++)
            {
                this->setMatrixValue(t_idx, idy, input.getMatrixValue(idx, idy));
            }
            t_idx++;
        }
    }
}

//asks are applied simultaneously, where boths' values are 1 the result will store a non zero value
template <class Type>
void Matrix2D<Type>::applyDoubleVectorMask(const Matrix2D<Type>& input, const std::vector<bool> mask1, const std::vector<bool> mask2)
{
    int idx = 0, idy = 0;

    for(int i = 0; i < input.getRows(); i++)
    {
        for(int j =0; j < input.getCols(); j++)
        {
            if(mask1[i] == 1 && mask2[j] == 1)
            {
                this->setMatrixValue(i, j, input.getMatrixValue(idx, idy));
                idy++;
            }
        }
        if(idy == this->getCols())
        {
            idx++;
            idy = 0;
        }
    }
}

//caller, mask and result have same dimensions
template <class Type>
void Matrix2D<Type>::applyMatrixMask(const Matrix2D<Type>& input, const Matrix2D<bool> mask)
{
    for(unsigned int idx = 0; idx < input.getDim(); idx++)
    {
        if(mask.getMatrixValue(idx) == 1)
        {
            this->setMatrixValue(idx, input.getMatrixValue(idx));
        }
    }
}

template <class Type>
void Matrix2D<Type>::sortLines()
{
    Type aux;

    for(int i = 0; i < this->getRows(); i++)
    {
        for(int j = 0; j < this->getCols()-1; j++)
        {
            if(this->getMatrixValue(i, j) > this->getMatrixValue(i, j+1))
            {
                aux = this->getMatrixValue(i, j);
                this->setMatrixValue(i, j, this->getMatrixValue(i, j+1));
                this->setMatrixValue(i, j+1, aux);
            }
        }
    }
}

/*
*basic math-operations
*/
//Returns a matrix whose all values are >=0. The orginal values are those in the input "source"
template <class Type>
void Matrix2D<Type>::getAbsoluteValuesMatrix(const Matrix2D<Type>& input)
{
    for(unsigned int idx = 0; idx < input.getDim(); idx++)
    {
        this->container[idx] = abs(input.getMatrixValue(idx));
    }
}

//For the calling matrix object, it computes the natural logarithm of each element of the input matrix object. Both matrices have same dimensions.
template <class Type>
void Matrix2D<Type>::logNatMatrix(const Matrix2D<Type>& input)
{
    for(unsigned int idx = 0; idx < input.getDim(); idx++)
    {
        this->container[idx] = log(input.getMatrixValue(idx));
    }
}

//find first element in matrix that differs from the input value
template <class Type>
void Matrix2D<Type>::findFirstNonEqualElement(int &x_first, int &y_first, Type value)
{
    for(int i = 0; i < this->rows; i++)
        for(int j = 0; j < this->cols; j++)
    {
        if(this->getMatrixValue(i,j) != value)
        {
            x_first = i;
            y_first = j;
            return;
        }
    }

    return;
}

//find last element in matrix that differs from the input value
template <class Type>
void Matrix2D<Type>::findLastNonEqualElement(int &x_first, int &y_first, Type value)
{
    for(int i = this->rows - 1; i>=0; i--)
        for(int j = this->cols - 1; j>=0; j--)
    {
        if(this->getMatrixValue(i,j) != value)
        {
            x_first = i;
            y_first = j;
            return ;
        }
    }
}

//Returns 1 if a row/column has at least a non-zero value, else it returns 0 for that row/column. The output is a vector. Direction: 1 = check on columns; 2 = check on rows
template <class Type>
void Matrix2D<Type>::anyNonZero(std::vector<int>& result, int direction)
{
    if(direction == 1)
    {
        for(int j = 0; j < this->getCols(); j++)
            for(int i = 0; i < this->getRows(); i++)
            {
                if(this->getMatrixValue(i, j) != 0)
                {
                    result[j] = 1;
                }
            }
    }

    if(direction ==2)
    {
        for(int i = 0; i < this->getRows(); i++)
            for(int j = 0; j < this->getCols(); j++)
            {
                if(this->getMatrixValue(i, j) != 0)
                {
                    result[i] = 1;
                }
            }
    }
}

//Result is a vector containing 1 if the line/column has  all elements grater than input value.Direction: 1 = check on columns; 2 = check on rows
template <class Type>
void Matrix2D<Type>::anyGreater(std::vector<int>& result, int direction, int treshold)
{
    //check if a column contains the given value
    if(direction == 1)
    {
        for(int j = 0; j < this->getCols(); j++)
            for(int i = 0; i < this->getRows(); i++)
            {
                if(this->getMatrixValue(i, j) > treshold)
                {
                    result[j] = 1;
                }
            }
    }

    //check if a row contains the given value
    if(direction == 2)
    {
        for(int i = 0; i < this->getRows(); i++)
            for(int j = 0; j < this->getCols(); j++)
            {
                if(this->getMatrixValue(i, j) > treshold)
                {
                    result[i] = 1;
                }
            }
    }
}

//Check if calling matrix doesn't have only zeros
template <class Type>
bool Matrix2D<Type>::checkNonZero()
{
    for(unsigned int idx = 0; idx < this->getDim(); idx++)
    {
        if(this->container[idx] != 0)
            return true;
    }

    return false;
}

template <class Type>
void Matrix2D<Type>::mFindIndeces(Matrix2D<int>& result, Type value, Comparison cmp)
{
    int res_i = 0, i, j;

    switch(cmp)
    {
    case 0:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) == value)
            {
                result.setMatrixValue(res_i, 0, i);
                result.setMatrixValue(res_i, 1, j);
                res_i++;
            }
        }
        break;
    case 1:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) != value)
            {
                result.setMatrixValue(res_i, 0, i);
                result.setMatrixValue(res_i, 1, j);
                res_i++;
            }
        }
        break;
    case 2:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) < value)
            {
                result.setMatrixValue(res_i, 0, i);
                result.setMatrixValue(res_i, 1, j);
                res_i++;
            }
        }
        break;
    case 3:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) <= value)
            {
                result.setMatrixValue(res_i, 0, i);
                result.setMatrixValue(res_i, 1,  j);
                res_i++;
            }
        }
        break;
    case 4:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) >= value)
            {
                result.setMatrixValue(res_i, 0,  i);
                result.setMatrixValue(res_i, 1,  j);
                res_i++;
            }
        }
        break;
    case 5:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) > value)
            {
                result.setMatrixValue(res_i, 0,  i);
                result.setMatrixValue(res_i, 1,  j);
                res_i++;
            }
        }
        break;
    }
}

template <class Type>
void Matrix2D<Type>::mFindIndecesAndValues(Matrix2D<Type>& result, Type value, Comparison cmp)
{
    int res_i = 0, i, j;

    switch(cmp)
    {
    case 0:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) == value)
            {
                result.setMatrixValue(res_i, 0,  i);
                result.setMatrixValue(res_i, 1,  j);
                result.setMatrixValue(res_i, 2, this->getMatrixValue(i,j));
                res_i++;
            }
        }
        break;
    case 1:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) != value)
            {
                result.setMatrixValue(res_i, 0,  i);
                result.setMatrixValue(res_i, 1,  j);
                result.setMatrixValue(res_i, 2,  this->getMatrixValue(i,j));
                res_i++;
            }
        }
        break;
    case 2:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) < value)
            {
                result.setMatrixValue(res_i, 0,  i);
                result.setMatrixValue(res_i, 1,  j);
                result.setMatrixValue(res_i, 2,  this->getMatrixValue(i,j));
                res_i++;
            }
        }
        break;
    case 3:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) <= value)
            {
                result.setMatrixValue(res_i, 0,  i);
                result.setMatrixValue(res_i, 1,  j);
                result.setMatrixValue(res_i, 2,  this->getMatrixValue(i,j));
                res_i++;
            }
        }
        break;
    case 4:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) >= value)
            {
                result.setMatrixValue(res_i, 0, i);
                result.setMatrixValue(res_i, 1,  j);
                result.setMatrixValue(res_i, 2,  this->getMatrixValue(i,j));
                res_i++;
            }
        }
        break;
    case 5:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) > value)
            {
                result.setMatrixValue(res_i, 0,  i);
                result.setMatrixValue(res_i, 1,  j);
                result.setMatrixValue(res_i, 2,  this->getMatrixValue(i,j));
                res_i++;
            }
        }
        break;
    }
}

template <class Type>
void Matrix2D<Type>::vFindIndeces(int* x, int* y, int input_vectors_dim, Type value, Comparison cmp)
{
    int res_i = 0, i, j;

    switch(cmp)
    {
    case 0:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) == value)
            {
                x[res_i] = i;
                y[res_i] = j;
                res_i++;
            }
        }
        break;
    case 1:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) != value)
            {
                x[res_i] = i;
                y[res_i] = j;
                res_i++;
            }
        }
        break;
    case 2:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) < value)
            {
                x[res_i] = i;
                y[res_i] = j;
                res_i++;
            }
        }
        break;
    case 3:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) <= value)
            {
                x[res_i] = i;
                y[res_i] = j;
                res_i++;
            }
        }
        break;
    case 4:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) >= value)
            {
                x[res_i] = i;
                y[res_i] = j;
                res_i++;
            }
        }
        break;
    case 5:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) > value)
            {
                x[res_i] = i;
                y[res_i] = j;
                res_i++;
            }
        }
        break;
    }
}

template <class Type>
void Matrix2D<Type>::vFindIndecesAndValues(int* x, int*  y, Type*  val, Type value, Comparison cmp)
{
    int res_i = 0, i, j;

    switch(cmp)
    {
    case 0:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) == value)
            {
                x[res_i] = i;
                y[res_i] = j;
                val[res_i] = this->getMatrixValue(i,j);
                res_i++;
            }
        }
        break;
    case 1:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) != value)
            {
                x[res_i] = i;
                y[res_i] = j;
                val[res_i] = this->getMatrixValue(i,j);
                res_i++;
            }
        }
        break;
    case 2:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) < value)
            {
                x[res_i] = i;
                y[res_i] = j;
                val[res_i] = this->getMatrixValue(i,j);
                res_i++;
            }
        }
        break;
    case 3:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) <= value)
            {
                x[res_i] = i;
                y[res_i] = j;
                val[res_i] = this->getMatrixValue(i,j);
                res_i++;
            }
        }
        break;
    case 4:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) >= value)
            {
                x[res_i] = i;
                y[res_i] = j;
                val[res_i] = this->getMatrixValue(i,j);
                res_i++;
            }
        }
        break;
    case 5:
        for(j = 0; j < this->getCols(); j++)
            for(i = 0; i < this->getRows(); i++)
        {
            if(this->getMatrixValue(i, j) > value)
            {
                x[res_i] = i;
                y[res_i] = j;
                val[res_i] = this->getMatrixValue(i,j);
                res_i++;
            }
        }
        break;
    }
}

template <class Type>
void Matrix2D<Type>::elementsOperation(Matrix2D<Type>& result, Type value, Operation op)
{
    switch(op)
    {
    case 0:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                result.setMatrixValue(idx, this->container[idx] + value);
            }
        break;
    case 1:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                result.setMatrixValue(idx, this->container[idx] - value);
            }
        break;
    case 2:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                result.setMatrixValue(idx, this->container[idx] * value);
            }
        break;
    case 3:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                result.setMatrixValue(idx, this->container[idx]/value);
            }
        break;
    case 4:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                result.setMatrixValue(idx, pow(this->container[idx], value));
            }
        break;
    case 5:
            for(unsigned int idx = 0; idx < this->getDim(); idx++)
            {
                result.setMatrixValue(idx, exp(this->container[idx]));
            }
        break;
    }
}

//Returns 1 if a row/column has at least a non-zero value, else it returns 0 for that row/column. The output is a vector. Direction: 1 = check on columns; 2 = check on rows
template <class Type>
void Matrix2D<Type>::allNonZero(bool* result, int direction)
{
    if(direction == 1)
    {
        for(int j = 0; j < this->getCols(); j++)
        {
            //for each column, initially suppose all its elements are non zero
            result[j] = 1;
            //search for each element in the given column
            for(int i = 0; i < this->getRows(); i++)
            {
                //if one is 0, set the result to 0 and continue with the next column
                if(this->getMatrixValue(i, j) == 0)
                {
                    result[j] = 0;
                    break;
                }
            }
        }

    }

    if(direction ==2)
    {
        for(int i = 0; i < this->getRows(); i++)
        {
            //for each row, initially suppose all its elements are non zero
            result[i] = 1;
            //search for each element in the given row
            for(int j = 0; j < this->getCols(); j++)
            {
                //if one is 0, set the result to 0 and continue with the next row
                if(this->getMatrixValue(i, j) == 0)
                {
                    result[i] = 0;
                    break;
                }
            }
        }
    }
}

//return # of elements whose value is different from input value. Useful when computing number of elements different from that value with Matlab's 'find'
template <class Type>
int Matrix2D<Type>::countValuesDifferentFromInput(Type value)
{
    int counter = 0;

    for(unsigned int idx = 0; idx < this->getDim(); idx++)
    {
        if(this->container[idx] != value)
            counter++;
    }

    return counter;
}

/*
* matrix conversions
*/

template <class Type>
void Matrix2D<Type>::copyMatrixColumnToVector(std::vector<Type> &result, int col)
{
    for(int i = 0; i < this->getRows(); i++)
        result[i] = this->getMatrixValue(i, col);
}

template <class Type>
void Matrix2D<Type>::copyMatrixRowToVector(std::vector<Type> &result, int row)
{
    for(int j = 0; j < this->getCols(); j++)
        result[j] = this->getMatrixValue(row, j);
}

//Convert calling matrix to vector, by putting the columns one after another
template <class Type>
void Matrix2D<Type>::reshapeToVector(std::vector<Type>& dest)
{
    for(int j = 0; j < this->getCols(); j++)
        for(int i = 0; i < this->getRows(); i++)
        {
            dest[i + j*this->getRows()] = this->getMatrixValue(i, j);
        }
}

//The caller is a matrix object whose values are a submatrix of "source" input. The indeces are considered those between the specified indeces
template <class Type>
void Matrix2D<Type>::getSubMatrix(const Matrix2D<Type>& input, int x_first, int x_last, int y_first, int y_last)
{
    int x_min = std::min(x_first, x_last);
    int x_max = std::max(x_first, x_last);
    int y_min = std::min(y_first, y_last);
    int y_max = std::max(y_first, y_last);

    for(int i = x_min; i <= x_max; i++)
        for(int j = y_min; j <= y_max; j++)
    {
        //index the caller matrix from 0
        this->setMatrixValue(i - x_min, j - y_min, input.getMatrixValue(i, j));
    }
}

//Reverse matrix elements: the first and the last lines are interchanged, the 2nd line with the 2nd-last one, but also th elements in the lines are reversed as the last becomes the first and viceversa
template <class Type>
void Matrix2D<Type>::reverseMatrix(const Matrix2D<Type>& input)
{
    Type temp;

    for(int i = 0; i < input.getRows()/2 + 1; i++)
        for(int j = 0; j < input.getCols(); j++)
    {
        //for matrices with odd number of lines, for the middle line stop indexing columns before it achieves the half of columns number
        if(input.getRows()%2 != 0 && i == (int) input.getRows()/2)
        {
            if(j == input.getCols())
            {
                break;
            }
        }

        temp = input(i,j);
        this->setMatrixValue(i, j, input(input.getRows()-i-1, input.getCols()-j-1));
        this->setMatrixValue(input.getRows() - i - 1, input.getCols() - j - 1, temp);
    }
}

//unlike  other methods, this one takes as input the matrix in which the result shall be stored
template <class Type>
void Matrix2D<Type>::getTranspose(Matrix2D<Type>** output)
{
    *output = new Matrix2D<Type>(this->getCols(), this->getRows());

    for(int idx = 0; idx < this->getRows(); idx++)
        for(int idy = 0; idy < this->getCols(); idy++)
    {
        (**output).setMatrixValue(idy, idx, this->getMatrixValue(idx, idy));
    }
}

//the result overwrites the input matrix. Only used for quadratic matrices
template <class Type>
void Matrix2D<Type>::TransposeMatrix()
{
    Type temp;

    //only for quadratic matrix
    if(this->getCols() == this->getRows())
    {
        for(int idx = 0; idx < this->getRows(); idx++)
            for(int idy = idx+1; idy < this->getCols(); idy++)
            {
                temp = this->getMatrixValue(idx, idy);
                this->setMatrixValue(idx, idy, this->getMatrixValue(idy, idx));
                this->setMatrixValue(idy, idx, temp);
            }
    }
}
#endif
