#include "../templates/matrix2D.h"
#include "kernels_wrappers.h"
#include <time.h>

#define D 5
#define PATCH_DIM 11
#define PATCH_BLOCK_DIM 64

__global__ void conv2mat_kernel(int* device_i0, int* device_j0, int oi, int oj, int maskRows, int maskCols, int* device_idx)
{
	int global_index = threadIdx.x + blockIdx.x*blockDim.x;
	int maskLinearSize = maskRows*maskCols;
	//device_counter_dim = 0;
	
	__shared__ int i[THREADS_PER_ONE_DIM_BLOCK], j[THREADS_PER_ONE_DIM_BLOCK], keep[THREADS_PER_ONE_DIM_BLOCK];
	
	if(global_index < maskLinearSize)
	{
		i[threadIdx.x] = device_i0[global_index] + oi;
		j[threadIdx.x] = device_j0[global_index] + oj;
		
		keep[threadIdx.x] = (i[threadIdx.x] < maskRows) & (j[threadIdx.x] < maskCols);
		
		if(keep[threadIdx.x])
		{
			//If the updated indeces are within the mask matrix dimensions range, linearize them and store them in a vector (idx)
			// Matlab's sub2ind  loops firstly on each row, then on columns thus the linearization below (reads column by column, not line by line)
			device_idx[global_index] = i[threadIdx.x] + maskRows * j[threadIdx.x];
		}
		else
		{
			//if the updated indeces are out of range, store -1 as linear index and increase counter
			device_idx[global_index] = -1;
		}
	}
}

cudaError_t launch_conv2mat_kernel(int** i0, int** j0, int oi, int oj, int maskRows, int maskCols, int** idx)
{
	int *device_i0, *device_j0, *device_idx;
	int mask_matrix_linear_size = maskRows*maskCols;
	
	//allocate GPU memory for inputs
	cudaMalloc((void**)&device_i0, sizeof(int) * mask_matrix_linear_size);
	cudaMalloc((void**)&device_j0, sizeof(int) * mask_matrix_linear_size);
	
	//allocate GPU memory for outputs
	cudaMalloc((void**)&device_idx, sizeof(int) * mask_matrix_linear_size);
	
	//transfer data to GPU RAM
	cudaMemcpy(device_i0, *i0, sizeof(int) * mask_matrix_linear_size, cudaMemcpyHostToDevice);
	cudaMemcpy(device_j0, *j0, sizeof(int) * mask_matrix_linear_size, cudaMemcpyHostToDevice);
	
	//launch kernel
	dim3 dimBlock(64);
	dim3 dimGrid((mask_matrix_linear_size + dimBlock.x -1)/dimBlock.x);
	
	conv2mat_kernel <<<dimGrid, dimBlock>>> (device_i0, device_j0, oi, oj, maskRows, maskCols, device_idx);
	
	//copy the results from GPU RAM into CPU RAM
	cudaMemcpy(*idx, device_idx, sizeof(int) * mask_matrix_linear_size, cudaMemcpyDeviceToHost);
	
	cudaFree(device_i0);
	cudaFree(device_j0);
	cudaFree(device_idx);
	
	cudaDeviceSynchronize();
	return cudaGetLastError();
}

__global__ void getBorderNormals_computePatch(bool *mask, double *P, int* device_d_vector, bool* device_patch, int *counter, int P_rows, int mask_rows, int mask_cols)
{
	int global_index = threadIdx.x + blockIdx.x*blockDim.x;
	
	if(global_index < P_rows)
	{
		int mask_x[PATCH_DIM], mask_y[PATCH_DIM];
		
		//compute indeces of mask
		for(int j = 0; j < PATCH_DIM; j++)
		{
			mask_x[j] = device_d_vector[j] + P[2*global_index];
			mask_y[j] = device_d_vector[j] + P[2*global_index + 1];	
		}
		
		for(int i = 0; i < PATCH_DIM; i++)
        {
			for(int j = 0; j < PATCH_DIM; j++)
			{
				device_patch[global_index*PATCH_DIM*PATCH_DIM + i*PATCH_DIM +j]  = mask[ mask_x[i]*mask_cols + mask_y[j] ];
            
				if(mask[ mask_x[i]*mask_cols + mask_y[j] ] != 0)
					counter[global_index]++;

			}
        }
    }
}

cudaError_t launch_getBorderNormals_computePatch(Matrix2D<bool> &mask, Matrix2D<double> &P, int **d_vector, std::vector<Matrix2D<bool> > &patch_vector, int **counter, int P_rows, int mask_rows, int mask_cols)
{
	bool *device_mask, *device_patch;
	double *device_P;
	int *device_d_vector;
	int *device_counter;
	int d = 5;

	//allocate GPU memory for inputs
	cudaHostAlloc((void**)&device_mask, sizeof(bool) * mask.getDim(), cudaHostAllocDefault);
    cudaHostAlloc((void**)&device_P, sizeof(double) * P.getDim(), cudaHostAllocDefault);
    cudaHostAlloc((void**)&device_d_vector, sizeof(int) * (2*d + 1), cudaHostAllocDefault);
    cudaHostAlloc((void**)&device_counter, sizeof(int) * P.getRows(), cudaHostAllocDefault);
    //allocate GPU memory for output
    cudaHostAlloc((void**)&device_patch, sizeof(bool) * (2*d + 1)*(2*d + 1)*P.getRows(), cudaHostAllocDefault);
    
    //transfer data to GPU RAM
    cudaMemcpy(device_P, P.getContainerPointer(), sizeof(double) * P.getDim(), cudaMemcpyHostToDevice);
    cudaMemcpy(device_mask, mask.getContainerPointer(), sizeof(bool) * mask.getDim(), cudaMemcpyHostToDevice);
    cudaMemcpy(device_d_vector, *d_vector, sizeof(int) * (2*d + 1), cudaMemcpyHostToDevice);
    cudaMemcpy(device_counter, *counter, sizeof(int) * P.getRows(), cudaMemcpyHostToDevice);
    
    //launch kernel
    dim3 dimBlock(64);
	dim3 dimGrid((P.getRows()+dimBlock.x-1)/dimBlock.x);

	getBorderNormals_computePatch <<<dimGrid, dimBlock>>> (device_mask, device_P, device_d_vector, device_patch, device_counter, P.getRows(), mask.getRows(), mask.getCols());
	
	//copy the results from GPU RAM into CPU RAM
    for(int i = 0; i < P.getRows(); i++)
		cudaMemcpy(patch_vector[i].getContainerPointer(), device_patch + i*(2*d + 1)*(2*d + 1), sizeof(bool)*(2*d + 1)*(2*d + 1), cudaMemcpyDeviceToHost);
	cudaMemcpy(*counter, device_counter, sizeof(int) * P.getRows(), cudaMemcpyDeviceToHost);
	
	//free GPU memory
	cudaFreeHost(device_mask);
	cudaFreeHost(device_patch);
	cudaFreeHost(device_d_vector);
	cudaFreeHost(device_P);
	
	cudaDeviceSynchronize();
	return cudaGetLastError();
}

__global__ void borderNormals_compute_temp_a(int* ii, int *jj, int dim, bool *temp_a, int* substract_ii, int *substract_jj)
{
	int row = threadIdx.y + blockIdx.y*blockDim.y;
	int col = threadIdx.x + blockIdx.x*blockDim.x;
	
	if(row < dim && col < dim)
	{
		substract_ii[row*dim +col] =  ii[row] - ii[col];
		substract_jj[row*dim +col] =  jj[row] - jj[col];
		
		__syncthreads();
		substract_ii[row*dim +col] = substract_ii[row*dim +col]*substract_ii[row*dim +col];
		substract_jj[row*dim +col] = substract_jj[row*dim +col]*substract_jj[row*dim +col];
		
		__syncthreads();
		substract_ii[row*dim +col] = substract_ii[row*dim +col] + substract_jj[row*dim +col];
		
		__syncthreads();
		if(substract_ii[row*dim +col] <= 2)
		{
			temp_a[row*dim +col] = 1;
		}
		else
		{
			temp_a[row*dim +col] = 0;
		}
	}
}

cudaError_t launch_borderNormals_compute_temp_a(int **ii, int **jj, int dim, Matrix2D<bool>& temp_a)
{
	bool *device_temp_a;
	int *device_ii, *device_jj, *substract_ii, *substract_jj;
	Matrix2D<int> sub_ii(dim, dim);
	
	//allocate GPU memory for inputs
	cudaMalloc((void**)&device_ii, sizeof(int) * dim);
	cudaMalloc((void**)&device_jj, sizeof(int) * dim);
	cudaMalloc((void**)&substract_ii, sizeof(int) * dim*dim);
	cudaMalloc((void**)&substract_jj, sizeof(int) * dim*dim);
	
	//allocate GPU memory for output
	cudaMalloc((void**)&device_temp_a, sizeof(bool) * temp_a.getDim());
	
	//transfer data to GPU RAM
	cudaMemcpy(device_ii, *ii, sizeof(int) * dim, cudaMemcpyHostToDevice);
	cudaMemcpy(device_jj, *jj, sizeof(int) * dim, cudaMemcpyHostToDevice);
	
	//launch kernel
	dim3 dimBlock(8, 8);
	dim3 dimGrid((dim + dimBlock.x -1)/dimBlock.x, (dim + dimBlock.y -1)/dimBlock.y);
	
	
	borderNormals_compute_temp_a <<<dimGrid, dimBlock>>> (device_ii, device_jj, dim, device_temp_a, substract_ii, substract_jj);
	
	
	//copy the results from GPU RAM into CPU RAM
	cudaMemcpy(temp_a.getContainerPointer(), device_temp_a, sizeof(bool) * temp_a.getDim(), cudaMemcpyDeviceToHost);
	
	cudaFree(device_temp_a);
	cudaFree(device_ii);
	cudaFree(device_jj);
	cudaFree(substract_ii);
	cudaFree(substract_jj);
	
	cudaDeviceSynchronize();
	return cudaGetLastError();
}

__global__ void initCounter(int *result) 
{
	*result = 0;
}

__global__ void borderNormals_compute_maskedP(double *P, int P_rows, double *device_P_plus, double *device_P_minus, bool *device_P_plus_mask, bool *device_P_minus_mask, bool *device_allNonZeroLines, \
int *device_notzero_lines_in_P, int mask_rows, int mask_cols)
{
	int global_index = threadIdx.x + blockIdx.x*blockDim.x;
	int d = 5;
	
	if(global_index < P_rows*2)
	{
		device_P_plus[global_index] = P[global_index]+d;
		device_P_minus[global_index] = P[global_index]-d;
		
		syncthreads();
		
		//take each column
		if(global_index %2 == 0)
		{
			if(device_P_plus[global_index] < mask_rows)
			{
				device_P_plus_mask[global_index] = 1;
			}
			else
			{
				device_P_plus_mask[global_index] = 0;
			}
		}
		else
		{
			if(device_P_plus[global_index] < mask_cols)
			{
				device_P_plus_mask[global_index] = 1;
			}
			else
			{
				device_P_plus_mask[global_index] = 0;
			}
		}
		
		if(device_P_minus[global_index] >= 1)
		{
			device_P_minus_mask[global_index] = 1;
		}
		else
		{
			device_P_minus_mask[global_index] = 0;
		}
		
		syncthreads();
		
		device_P_plus_mask[global_index] = device_P_plus_mask[global_index] & device_P_minus_mask[global_index];
		
		__syncthreads();
		
		if(global_index %2 == 0)
		{
			if(device_P_plus_mask[global_index] == 0 || device_P_plus_mask[global_index+1] == 0)
			{
				device_allNonZeroLines[global_index/2] = 0;
			}
			else
			{
				device_allNonZeroLines[global_index/2] = 1;
				atomicAdd(device_notzero_lines_in_P, 1);	
			}
		}
		
		__syncthreads();
		
		//printf("%d  ", device_notzero_lines_in_P);
	}

}

cudaError_t launch_borderNormals_compute_maskedP(Matrix2D<double>& P, bool *allNonZeroLines, int *notzero_lines_in_P, int mask_rows, int mask_cols)
{
	cudaError_t code;
	double *device_P, *device_P_plus, *device_P_minus, *host_P, *host_P_plus, *host_P_minus;
	bool *device_P_plus_mask, *device_P_minus_mask, *device_allNonZeroLines, *host_P_plus_mask, *host_P_minus_mask;
	int *device_notzero_lines_in_P;
	
	//allocate GPU memory for inputs
	code =cudaHostAlloc((void**)&host_P, sizeof(double) * P.getRows()*2, cudaHostAllocMapped);
	if(code != cudaSuccess)
		printf("GPUassert: %s %s %d\n", cudaGetErrorString(code), __FILE__, __LINE__);
	code =cudaHostAlloc((void**)&host_P_plus, sizeof(double) * P.getRows()*2, cudaHostAllocMapped);
	if(code != cudaSuccess)
		printf("GPUassert: %s %s %d\n", cudaGetErrorString(code), __FILE__, __LINE__);
    code =cudaHostAlloc((void**)&host_P_minus, sizeof(double) * P.getRows()*2, cudaHostAllocMapped);
    if(code != cudaSuccess)
		printf("GPUassert: %s %s %d\n", cudaGetErrorString(code), __FILE__, __LINE__);
    code =cudaHostAlloc((void**)&host_P_plus_mask, sizeof(bool) * P.getRows()*2, cudaHostAllocMapped);
    if(code != cudaSuccess)
		printf("GPUassert: %s %s %d\n", cudaGetErrorString(code), __FILE__, __LINE__);
    code =cudaHostAlloc((void**)&host_P_minus_mask, sizeof(bool) * P.getRows()*2, cudaHostAllocMapped);
    if(code != cudaSuccess)
		printf("GPUassert: %s %s %d\n", cudaGetErrorString(code), __FILE__, __LINE__);
    
    //allocate GPU memory for outputs
    code =cudaHostAlloc((void**)&device_notzero_lines_in_P, sizeof(int), cudaHostAllocDefault);
    if(code != cudaSuccess)
		printf("GPUassert: %s %s %d\n", cudaGetErrorString(code), __FILE__, __LINE__);

	//transfer data to GPU RAM: 
	cudaMemcpy(host_P, P.getContainerPointer(), sizeof(double) * P.getRows()*2, cudaMemcpyHostToDevice);
	//for(int i = 0; i < P.getRows()*2; i++)
		//host_P[i] = P.getMatrixValue(i);
	
	// get device pointer
	code = cudaHostGetDevicePointer(&device_P, host_P, 0);
	if(code != cudaSuccess)
	printf("GPUassert: %s %s %d\n", cudaGetErrorString(code), __FILE__, __LINE__);
	
	code = cudaHostGetDevicePointer(&device_P_plus, host_P_plus, 0);
	if(code != cudaSuccess)
		printf("GPUassert: %s %s %d\n", cudaGetErrorString(code), __FILE__, __LINE__);
	
	code = cudaHostGetDevicePointer(&device_P_minus, host_P_minus, 0);
	if(code != cudaSuccess)
		printf("GPUassert: %s %s %d\n", cudaGetErrorString(code), __FILE__, __LINE__);
	
	code = cudaHostGetDevicePointer(&device_P_plus_mask, host_P_plus_mask, 0);
	if(code != cudaSuccess)
		printf("GPUassert: %s %s %d\n", cudaGetErrorString(code), __FILE__, __LINE__);
	
	code = cudaHostGetDevicePointer(&device_P_minus_mask, host_P_minus_mask, 0);
	if(code != cudaSuccess)
		printf("GPUassert: %s %s %d\n", cudaGetErrorString(code), __FILE__, __LINE__);
	
	code = cudaHostGetDevicePointer(&device_allNonZeroLines, allNonZeroLines, 0);
	if(code != cudaSuccess)
		printf("GPUassert: %s %s %d\n", cudaGetErrorString(code), __FILE__, __LINE__);
	
	//launch kernel
    dim3 dimBlock(64);
	dim3 dimGrid((2*P.getRows()+dimBlock.x-1)/dimBlock.x);

	initCounter<<<1,1>>>(device_notzero_lines_in_P);
	borderNormals_compute_maskedP <<<dimGrid, dimBlock>>> (device_P, P.getRows(), device_P_plus, device_P_minus, device_P_plus_mask, device_P_minus_mask, device_allNonZeroLines, device_notzero_lines_in_P, mask_rows, mask_cols);
	
	cudaDeviceSynchronize();
	
	//cudaMemcpy(*allNonZeroLines, device_allNonZeroLines, sizeof(bool) * P.getRows(), cudaMemcpyDeviceToHost);
	cudaMemcpy(notzero_lines_in_P, device_notzero_lines_in_P, sizeof(int), cudaMemcpyDeviceToHost);
	
	std::cout<<*notzero_lines_in_P<<std::endl;

	//free GPU memory
	/*cudaFreeHost(device_P);
	cudaFreeHost(device_P_plus);
	cudaFreeHost(device_P_minus);
	cudaFreeHost(device_P_plus_mask);
	cudaFreeHost(device_P_minus_mask);
	cudaFreeHost(device_allNonZeroLines);
	cudaFreeHost(device_notzero_lines_in_P);
	*/
	
	cudaFreeHost(host_P);
	cudaFreeHost(host_P_plus);
	cudaFreeHost(host_P_minus);
	cudaFreeHost(host_P_plus_mask);
	cudaFreeHost(host_P_minus_mask);
	cudaFreeHost(device_notzero_lines_in_P);
	

	cudaDeviceSynchronize();
	return cudaGetLastError();
}
