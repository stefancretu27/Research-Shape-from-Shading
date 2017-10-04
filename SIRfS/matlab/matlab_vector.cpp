#include "matlab_vector.h"

using namespace std;

/*
Input mask should be initialized to false.
*/
template <class Type>
void createVectorMask(vector<Type>& source, vector<bool>& mask, int treshold)
{
    for(unsigned int i = 0; i < source.size(); i++)
    {
        if(source[i] == treshold)
            mask[i] = true;
        else
            mask[i] = false;
    }
}

template <class Type>
void convertVectorOfVectorsToMatrix(vector<vector<Type> > &source, Matrix2D<Type>& dest)
{
    for(unsigned int i = 0; i < source.size(); i ++)
        for(unsigned int j = 0; j < source[i].size(); j++)
    {
        //put a vector's elements on the same column, not on the same line
        dest.setMatrixValue(j, i, source[i][j]);
    }
}
