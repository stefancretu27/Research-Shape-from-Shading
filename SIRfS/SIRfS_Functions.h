#ifndef SIRFS_FUNCTIONS_H_INCLUDED
#define SIRFS_FUNCTIONS_H_INCLUDED

//used for std::min_element
#include <algorithm>
#include <memory>
#include <iterator>

#include "matlab/matlab_vector.h"
#include "matlab/matlab_matrix.h"
#include "templates/keyValue.h"

//This header contains the signatures of SIRfS functions
Matrix2D<KeysValue<double>* >* conv2mat(int maskRows, int maskCols, Matrix2D<int> input_filter);
void medianFilterMatMask(Matrix2D<bool>& input_mask, int half_width, Matrix2D<KeysValue<double>* >& output);


#endif // SIRFS_FUNCTIONS_H_INCLUDED
