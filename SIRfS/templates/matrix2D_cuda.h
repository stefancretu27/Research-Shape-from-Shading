#ifndef MATRIX2D_CUDA_H
#define MATRIX2D_CUDA_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <limits>

//cuda libraries
#include <cuda.h>
#include <cuda_runtime.h>

#include "../helpers/enums.h" 

template <typename Type>
__device__ class Matrix2D_CUDA
{
private:
    Type *container;
    int rows, cols;

public:
    //constructors
    __device__ Matrix2D_CUDA(){this->rows = 0; this->cols = 0; this->container = nullptr;};
    //overloaded constructors
    __device__ Matrix2D_CUDA(int new_rows, int new_cols);
    __device__ Matrix2D_CUDA(int new_rows, int new_cols, Type value);
    //copy constructor
    __device__ Matrix2D_CUDA(const Matrix2D_CUDA<Type>& input_matrix);
    //destructor
    __device__ ~Matrix2D_CUDA()
    {
		//delete the array
		cudaFree(this->container);
    };

    //indexes operations
    __device__ inline unsigned int getLinearIndex(int i, int j)
    {
        return i*this->cols + j;
    };
    __device__ void get2DIndecesFromLinearIndex(int index, int &rows, int &cols)
    {
        rows = index/this->cols;  //integer division . This is x
        cols = index - rows; //This is y
    };

    //getters
    __device__ inline int getRows() const              //inline tells compiler to replace function with its definition => faster execution as there is less linking
    {
        return this->rows;
    };
    __device__ inline int getCols() const
    {
        return this->cols;
    };
    __device__ inline int getDim() const
    {
        return this->rows*this->cols;
    };
    __device__ inline Type* getContainerPointer()
    {
        return this->container;
    };
    __device__ inline Type getMatrixValue(int i, int j) const
    {
        return this->container[i*this->cols + j];
    };
    __device__ inline Type getMatrixValue(unsigned linearindex) const
    {
        return this->container[linearindex];
    };

    //setters
    __device__ inline void setRows(int new_rows)
    {
        this->rows = new_rows;
    };
    __device__ inline void setCols(int new_cols)
    {
        this->cols = new_cols;
    };
    __device__ inline void setDims(int new_rows, int new_cols)
    {
        this->cols = new_cols;
        this->rows = new_rows;
    };
    __device__ inline void setMatrixValue(int i, int j, Type value)
    {
        this->container[i*this->cols +j] = value;
    };
    __device__ inline void setMatrixValue(unsigned int linearindex, Type value)
    {
        this->container[linearindex] = value;
    };

    //operators overloading
    __device__ inline Type& operator() (int rowsIdx, int colsIdx) const
    {
        return this->container[rowsIdx * this->cols + colsIdx];
    };
    __device__ bool operator==(const Matrix2D_CUDA<Type>& operand_matrix);
    __device__ Matrix2D_CUDA& operator=(const Matrix2D_CUDA<Type>& operand_matrix);
    __device__ Matrix2D_CUDA& operator+(Matrix2D_CUDA<Type>& operand_matrix);
    __device__ Matrix2D_CUDA& operator-(Matrix2D_CUDA<Type>& operand_matrix);
    __device__ Matrix2D_CUDA& multiply_input_matrices(Matrix2D_CUDA<Type>& input_A, Matrix2D_CUDA<Type>& input_B);
    
    //helper: separate function from constructors, used data copying
    __device__ void initializeMatrixValues(Type value);
   
};


/*
*Constructors
*/
//Creates a matrix2D with specified dimensions
template <class Type>
__device__ Matrix2D_CUDA<Type>::Matrix2D_CUDA(int new_rows, int new_cols):rows(new_rows), cols(new_cols)
{
    if(this->rows > 0 && this->cols > 0)
    {
        //allocate memory
        cudaMalloc(this->container, sizeof(Type)*this->rows*this->cols);
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
__device__ Matrix2D_CUDA<Type>::Matrix2D_CUDA( int new_rows,  int new_cols, Type value):rows(new_rows), cols(new_cols)
{
    if(this->rows > 0 && this->cols > 0)
    {
        //allocate memory
        cudaMalloc(this->container, sizeof(Type)*this->rows*this->cols);

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
__device__ Matrix2D_CUDA<Type>::Matrix2D_CUDA(const Matrix2D_CUDA<Type>& input_matrix):rows(input_matrix.getRows()), cols(input_matrix.getCols())
{
    if(this->rows > 0 && this->cols > 0)
    {
        //allocate memory
        cudaMalloc(this->container, sizeof(Type)*this->rows*this->cols);

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

//operators overloading
template <class Type>
__device__ bool Matrix2D_CUDA<Type>::operator==(const Matrix2D_CUDA<Type>& operand_matrix)
{
    bool k = true;

    if(this->getDim() != operand_matrix.getDim())
    {
        printf("The matrices have different dimensions and cannot be compared!\n");
        exit(0);
    }

    if(this->getDim() == 0 || operand_matrix.getDim() == 0)
    {
        prinyf("At least one of the matrices has no elements, thus comparison failed!\n");
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
__device__ Matrix2D_CUDA<Type>& Matrix2D_CUDA<Type>::operator=(const Matrix2D_CUDA<Type>& operand_matrix)
{
    //get new dimensions
    this->rows = operand_matrix.getRows();
    this->cols = operand_matrix.getCols();

    //delete previously stored data, if any
    if(this->container != nullptr)
    {
        cudaFree(this->container);
    }

    if(this->rows > 0 && this->cols > 0)
    {
        //allocate memory
        cudaMalloc(this->container, sizeof(Type)*this->rows*this->cols);

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
__device__ Matrix2D_CUDA<Type>& Matrix2D_CUDA<Type>::operator+(Matrix2D_CUDA<Type>& operand_matrix)
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
__device__ Matrix2D_CUDA<Type>& Matrix2D_CUDA<Type>::operator-(Matrix2D_CUDA<Type>& operand_matrix)
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
__device__ Matrix2D_CUDA<Type>& Matrix2D_CUDA<Type>::multiply_input_matrices(Matrix2D_CUDA<Type>& input_A, Matrix2D_CUDA<Type>& input_B)
{
    if(input_A.getCols() != input_B.getRows())
    {
        std::cout<<"Couldn't multiply matrices."<<std::endl;
        exit(0);
    }

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

    return *this;
}

/*
*helpers
*/
template <class Type>
__device__ void Matrix2D_CUDA<Type>::initializeMatrixValues(Type value)
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

#endif
