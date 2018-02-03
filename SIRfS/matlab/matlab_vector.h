#ifndef MATLAB_VECTOR_H_INCLUDED
#define MATLAB_VECTOR_H_INCLUDED

#include <vector>

#include "../templates/matrix2D.h"

//vector operations
template <class Type> void createVectorMask(std::vector<Type>& source, std::vector<bool>& mask, int treshold);
template <class Type> void convertVectorOfVectorsToMatrix(std::vector<std::vector<Type> > &source, Matrix2D<Type>& dest);
template <class Type>  void vectorOpItsTranspose(std::vector<Type>& input, Matrix2D<Type>& result, Operation op);

#endif // MATLAB_VECTOR_H_INCLUDED
