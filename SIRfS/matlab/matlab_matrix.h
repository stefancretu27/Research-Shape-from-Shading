#ifndef MATLAB_MATRIX_H_INCLUDED
#define MATLAB_MATRIX_H_INCLUDED

#include <vector>
#include <limits>

#include "../templates/matrix2D.h"

//matrix operations
void computeMatrixMask(Matrix2D<double>& source, Matrix2D<bool>& mask, int treshold);
void insertNaNValues(Matrix2D<double>& dest, Matrix2D<bool>& mask);
void checkMatrixAgainstTreshold(Matrix2D<int>& source, Matrix2D<double>& result, int treshold);
void convertBoolToDoubleMatrix2D(Matrix2D<bool>& source, Matrix2D<double>& dest);

#endif // MATLAB_MATRIX_H_INCLUDED
