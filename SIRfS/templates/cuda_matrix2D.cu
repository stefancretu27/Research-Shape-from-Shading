#include "matrix2D_cuda.h"

#define BLOCK_SIZE 16

template<class Type>
__global__ void matrix_multiply(Type* device_A, Type* device_B, Type* device_C, int rows_A, int rows_B, int cols_B)
{
	int y = threadIdx.y;
	int x = threadIdx.x;

	int row = y + blockIdx.y * blockDim.y;
	int col = x + blockIdx.x * blockDim.x;
	
	int cols_A = rows_B;
	//accumulator
	Type accu = (Type) 0;

	
	//shared memory where each block of threads loads submatrices of A and B
	__shared__ Type shared_A[BLOCK_SIZE][BLOCK_SIZE];
	__shared__ Type shared_B[BLOCK_SIZE][BLOCK_SIZE];
	
	int block_row, block_col, block_index;
	
	for(int index = 0; index < (cols_A + BLOCK_SIZE -1)/BLOCK_SIZE; index++)
	{
		//don't exceed matrix dimensions
		if(row < rows_A && (index*BLOCK_SIZE + x) < cols_A)
		{
			//identify the line of blocks
			block_row = row * cols_A;
			//identify block in the current line of blocks
			block_index = index*BLOCK_SIZE;
			
			//load current element in current block
			shared_A[y][x] = device_A[block_row + block_index + x];
		}
		else
		{
			shared_A[y][x] = 0.0;
		}
		
		//don't exceed matrix dimensions
		if(col < cols_B && (index*BLOCK_SIZE +y) < rows_B)
		{
			//indetify the column of blocks
			block_col = col;
			//identify block in current column of blocks
			block_index = index*BLOCK_SIZE*cols_B;
			//load element from the current block
			
			shared_B[y][x] = device_B[block_col + block_index + y*cols_B];
		}
		else
		{
			shared_B[y][x] = 0.0;
		}
		
		__syncthreads();
		
		//multiply the loaded blocks
		for(int j = 0; j < BLOCK_SIZE; j++)
			accu += shared_A[y][j]*shared_B[j][x];
			
		__syncthreads();
	}
	
	if(row < rows_A && col < cols_B)
		device_C[row*cols_B + col] = accu;
}

template<class Type> cudaError_t operator_multiply(Type* device_A, Type* device_B, Type *result, dim3 grid_dim, dim3 block_dim, int A_rows, int B_rows, int B_cols)
{
	matrix_multiply <<<grid_dim, block_dim>>> (device_A, device_B, result, A_rows, B_rows, B_cols);
	
	cudaDeviceSynchronize();
	return cudaGetLastError();
}
//specializations
template cudaError_t operator_multiply<double>(double* device_A, double* device_B, double *result, dim3 grid_dim, dim3 block_dim, int A_rows, int B_rows, int B_cols);
template cudaError_t operator_multiply<float>(float* device_A, float* device_B, float *result, dim3 grid_dim, dim3 block_dim, int A_rows, int B_rows, int B_cols);
template cudaError_t operator_multiply<int>(int* device_A, int* device_B, int *result, dim3 grid_dim, dim3 block_dim, int A_rows, int B_rows, int B_cols);

template<class Type>
__global__ void matrix_add(Type* A, Type* B, int matrix_dim)
{
	//int row = threadIdx.y + blockIdx.y*blockDim.y;
	int col = threadIdx.x + blockIdx.x*blockDim.x;
	
	if(col < matrix_dim)
	{
		A[col] += B[col];	
	}
}

//wrapper for callin the above kernel
template<class Type>
cudaError_t operator_add(Type* A, Type* B, int grid_dim, int block_dim, int matrix_dim)
{
	matrix_add <<<grid_dim, block_dim>>> (A, B, matrix_dim);
	
	cudaDeviceSynchronize();
	return cudaGetLastError();
}
//specialization
template cudaError_t operator_add<double>(double* A, double* B, int grid_dim, int block_dim, int matrix_dim);
template cudaError_t operator_add<float>(float* A, float* B, int grid_dim, int block_dim, int matrix_dim);
template cudaError_t operator_add<int>(int* A, int* B, int grid_dim, int block_dim, int matrix_dim);

template<class Type>
__global__ void matrix_substract(Type* A, Type* B, int matrix_dim)
{
	//int row = threadIdx.y + blockIdx.y*blockDim.y;
	int col = threadIdx.x + blockIdx.x*blockDim.x;
	
	if(col < matrix_dim)
	{
		A[col] -= B[col];
	}
}

//wrapper for callin the above kernel
template<class Type>
cudaError_t operator_substract(Type* A, Type* B, int grid_dim, int block_dim, int matrix_dim)
{
	matrix_substract <<<grid_dim, block_dim>>> (A, B, matrix_dim);
	
	cudaDeviceSynchronize();
	return cudaGetLastError();
}
//specializations
template cudaError_t operator_substract<double>(double* A, double* B, int grid_dim, int block_dim, int matrix_dim);
template cudaError_t operator_substract<float>(float* A, float* B, int grid_dim, int block_dim, int matrix_dim);
template cudaError_t operator_substract<int>(int* A, int* B, int grid_dim, int block_dim, int matrix_dim);

/* convolution */
template<class Type>
__global__ void conv2D_full(Type* input, Type* kernel, Type* output, int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols)
{
	int col = threadIdx.x + blockIdx.x*blockDim.x;
	int row = threadIdx.y + blockIdx.y*blockDim.y;
	int m, n, sourceIdx, sourceIdy;
	
	//find kernel center
	int kCenterX = (kernel_cols + 1)/2;
	int kCenterY = (kernel_rows + 1)/2;
	
	//initialize output value to 0, to accumulate to it
	output[row*output_cols + col] = 0;
	
	if(col < output_cols && row < output_rows)
	{
		for(m = 0; m < kernel_rows; m++)
		{
			for(n = 0; n < kernel_cols; n++)
			{
				sourceIdx = row + m - kCenterY;
				sourceIdy = col + n - kCenterX;

				if( sourceIdx < input_rows && sourceIdx >= 0 && sourceIdy < input_cols && sourceIdy  >= 0)
				{
					output[row*output_cols + col] += input[sourceIdx*input_cols + sourceIdy]*kernel[m*kernel_cols + n];
				}
			}
		}
	}
}

template<class Type> cudaError_t conv2D_full_kernel_launcher(Type* input, Type* kernel, Type* output, dim3 grid_dim, dim3 block_dim, \
															int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols)
{
	
	conv2D_full <<<grid_dim, block_dim>>> (input, kernel, output, input_rows, input_cols, kernel_rows, kernel_cols, output_rows, output_cols);
	
	cudaDeviceSynchronize();
	return cudaGetLastError();
}
//specializations
template cudaError_t conv2D_full_kernel_launcher<double>(double* input, double* kernel, double* output, dim3 grid_dim, dim3 block_dim, \
															int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols);
template cudaError_t conv2D_full_kernel_launcher<float>(float* input, float* kernel, float* output, dim3 grid_dim, dim3 block_dim, \
															int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols);
template cudaError_t conv2D_full_kernel_launcher<int>(int* input, int* kernel, int* output, dim3 grid_dim, dim3 block_dim, \
															int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols);

template<class Type>
__global__ void conv2D_valid(Type* input, Type* kernel, Type* output, int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols)
{
	int col = threadIdx.x + blockIdx.x*blockDim.x;
	int row = threadIdx.y + blockIdx.y*blockDim.y;
	int m, n, in_row, in_col;
	
	//initialize output value to 0, to accumulate to it
	output[row*output_cols + col] = 0;
	
	if(col < output_cols && row < output_rows)
	{
		for(m = 0; m < kernel_rows; m++)
		{
			for(n = 0; n < kernel_cols; n++)
			{
				in_row = row + m;
				in_col = col + n;
				if( in_row < input_rows && in_col < input_cols)
				{
					output[row*output_cols + col] += input[in_row*input_cols + in_col] * kernel[m*kernel_cols + n];
				}
			}
		}
	}
}


template<class Type> cudaError_t conv2D_valid_kernel_launcher(Type* input, Type* kernel, Type* output, dim3 grid_dim, dim3 block_dim, \
															int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols)
{
	
	conv2D_valid <<<grid_dim, block_dim>>> (input, kernel, output, input_rows, input_cols, kernel_rows, kernel_cols, output_rows, output_cols);
	
	cudaDeviceSynchronize();
	return cudaGetLastError();
}
//specializations
template cudaError_t conv2D_valid_kernel_launcher<double>(double* input, double* kernel, double* output, dim3 grid_dim, dim3 block_dim, \
															int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols);
template cudaError_t conv2D_valid_kernel_launcher<float>(float* input, float* kernel, float* output, dim3 grid_dim, dim3 block_dim, \
															int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols);
template cudaError_t conv2D_valid_kernel_launcher<int>(int* input, int* kernel, int* output, dim3 grid_dim, dim3 block_dim, \
															int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols);
	
template<class Type>
__global__ void conv2D_same(Type* input, Type* kernel, Type* output, int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols)
{
	int col = threadIdx.x + blockIdx.x*blockDim.x;
	int row = threadIdx.y + blockIdx.y*blockDim.y;
	int m, n, sourceIdx, sourceIdy;
	
	//find kernel center
	int kCenterX = (kernel_cols - 1)/2;
	int kCenterY = (kernel_rows - 1)/2;
	
	//initialize output value to 0, to accumulate to it
	output[row*output_cols + col] = (Type) 0;

	if(col < output_cols && row < output_rows)
	{
		for(m = 0; m < kernel_rows; m++)
		{
			for(n = 0; n < kernel_cols; n++)
			{
				sourceIdx = row + m - kCenterY;
				sourceIdy = col + n - kCenterX;

				if( sourceIdx < input_rows && sourceIdx >= 0 && sourceIdy < input_cols && sourceIdy >= 0)
				{
					output[row*output_cols + col] += input[sourceIdx*input_cols + sourceIdy]*kernel[m*kernel_cols + n];
				}
			}
		}
	}
}
														
template<class Type> cudaError_t conv2D_same_kernel_launcher(Type* input, Type* kernel, Type* output, dim3 grid_dim, dim3 block_dim, \
															int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols)
{
	
	conv2D_same <<<grid_dim, block_dim>>> (input, kernel, output, input_rows, input_cols, kernel_rows, kernel_cols, output_rows, output_cols);
	
	cudaDeviceSynchronize();
	return cudaGetLastError();
}
//specializations
template cudaError_t conv2D_same_kernel_launcher<double>(double* input, double* kernel, double* output, dim3 grid_dim, dim3 block_dim, \
															int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols);
template cudaError_t conv2D_same_kernel_launcher<float>(float* input, float* kernel, float* output, dim3 grid_dim, dim3 block_dim, \
															int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols);
template cudaError_t conv2D_same_kernel_launcher<int>(int* input, int* kernel, int* output, dim3 grid_dim, dim3 block_dim, \
															int input_rows, int input_cols, int kernel_rows, int kernel_cols, int output_rows, int output_cols);
