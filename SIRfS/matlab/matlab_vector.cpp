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

//input is considered a column vector and result is  matrix obtained after each element in the column vector performs operation 'op' with each element in the transpose vector
template <class Type>
void vectorOpItsTranspose(Type* input, int input_size, Matrix2D<Type>& result, Operation op)
{
    unsigned int i, j;

    switch(op)
    {
    case 0:
        for(j = 0; j < input_size; j++)
            for(i = 0; i < input_size; i++)
            {
                result.setMatrixValue(i, j, input[i] + input[j]);
            }
        break;
    case 1:
        for(j = 0; j < input_size; j++)
            for(i = 0; i < input_size; i++)
            {
                result.setMatrixValue(i, j, input[i] - input[j]);
            }
        break;
    case 2:
        for(j = 0; j < input_size; j++)
            for(i = 0; i < input_size; i++)
            {
                result.setMatrixValue(i, j, input[i] * input[j]);
            }
        break;
    case 3:
        for(j = 0; j < input_size; j++)
            for(i = 0; i < input_size; i++)
            {
                result.setMatrixValue(i, j, input[i]/input[j]);
            }
        break;
    case 4:
        for(j = 0; j < input_size; j++)
            for(i = 0; i < input_size; i++)
            {
                result.setMatrixValue(i, j, pow(input[i], input[j]));
            }
        break;
    case 5:
        break;
    }
}
