#ifndef SIRFS_FUNCTIONS_H_INCLUDED
#define SIRFS_FUNCTIONS_H_INCLUDED

//used for std::min_element
#include <algorithm>
#include <tr1/memory>
#include <iterator>
#include <string>
#include <sstream>

#include "../matlab/matlab_vector.h"
#include "../matlab/matlab_matrix.h"
#include "../templates/dataFile.h"
#include "../block_A1/data_class/border.h"
#include "../helpers/validation.h"

#define USE_CPU_PTHREAD

#ifdef USE_CPU_PTHREAD
typedef struct medianfilter_thread_args
{
	Matrix2D<bool> mask;
	int half_width;
	
}medianfilter_thread_args;
#endif


//This header contains the signatures of SIRfS functions
void conv2mat(int maskRows, int maskCols, Matrix2D<int> input_filter, Matrix2D<KeysValue<double> >** output);
#ifdef USE_CPU_PTHREAD
void* medianFilterMatMask(void *args);
void* getBorderNormals(void *args);
#else
void medianFilterMatMask(Matrix2D<bool>& input_mask, int half_width, Matrix2D<double>** output);
void getBorderNormals(Matrix2D<bool> mask, Border& border);
#endif

#endif // SIRFS_FUNCTIONS_H_INCLUDED
