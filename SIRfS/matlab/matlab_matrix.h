#ifndef MATLAB_MATRIX_H_INCLUDED
#define MATLAB_MATRIX_H_INCLUDED

#include <vector>
#include <limits>

#include "../templates/matrix2D.h"
#include "../templates/keyValue.h"

//matrix operations
void computeMatrixMask(Matrix2D<double>& source, Matrix2D<bool>& mask, int treshold);
void insertNaNValues(Matrix2D<double>& dest, Matrix2D<bool>& mask);
void checkMatrixAgainstTreshold(Matrix2D<int>& source, Matrix2D<double>& result, int treshold);
void convertBoolToDoubleMatrix2D(Matrix2D<bool>& source, Matrix2D<double>& dest);
void copyKeysValueMatrix(Matrix2D<KeysValue<double>* >& source, Matrix2D<KeysValue<double> *>& dest);
void applyVectorMask(std::vector<bool>& mask, Matrix2D<KeysValue<double> >** source, Matrix2D<KeysValue<double> > *dest);
Matrix2D<KeysValue<double> >* appendMatrixBelow(Matrix2D<KeysValue<double> >* source1, Matrix2D<KeysValue<double> >& source2);


#endif // MATLAB_MATRIX_H_INCLUDED
