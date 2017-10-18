#ifndef SIRFS_FUNCTIONS_H_INCLUDED
#define SIRFS_FUNCTIONS_H_INCLUDED

//used for std::min_element
#include <algorithm>
#include <tr1/memory>
#include <iterator>

#include "matlab/matlab_vector.h"
#include "matlab/matlab_matrix.h"
#include "templates/keyValue.h"

//This header contains the signatures of SIRfS functions
void conv2mat(int maskRows, int maskCols, Matrix2D<int> input_filter, Matrix2D<KeysValue<double> >** output);
void medianFilterMatMask(Matrix2D<bool>& input_mask, int half_width, Matrix2D<KeysValue<double> >** output);
void getBorderNormals(Matrix2D<bool> mask);

#endif // SIRFS_FUNCTIONS_H_INCLUDED
