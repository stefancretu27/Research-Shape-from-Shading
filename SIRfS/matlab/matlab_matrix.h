#ifndef MATLAB_MATRIX_H_INCLUDED
#define MATLAB_MATRIX_H_INCLUDED

#include <vector>

#include "../templates/matrix3D.h"
#include "../templates/keyValue.h"

//matrix operations
void convertBoolToDoubleMatrix2D(Matrix2D<bool>& source, Matrix2D<double>& dest);
void convertDoubleToIntMatrix2D(Matrix2D<double>& source, Matrix2D<int>& dest);
void convertIntToDoubleMatrix2D(Matrix2D<int>& source, Matrix2D<double>& dest);
void applyMaskOnKeysValueMatrix(std::vector<bool> &mask, Matrix2D<KeysValue<double> >** source, Matrix2D<KeysValue<double> > *dest);
//input is vector of matrices, output is a matrix whose number of rows is the sum of all matrices rows from the vector  = appended below
void meshgrid(int x_min, int x_max, int y_min, int y_max, Matrix2D<double>& result_X, Matrix2D<double>& result_Y);
void appendMatrixBelow(std::vector< Matrix2D<KeysValue<double> > > source, Matrix2D<KeysValue<double>>** dest);

#endif // MATLAB_MATRIX_H_INCLUDED
