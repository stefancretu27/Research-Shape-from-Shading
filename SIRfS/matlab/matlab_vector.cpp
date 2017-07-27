#include "matlab_vector.h"

using namespace std;

//vector operations
/*template <class Type>
Type findFirstNonZeroIndex(vector<Type>& source)
{
    //for(std::vector<int>::iterator i = source.begin(); i != source.end(); i++)
    for(unsigned int i = 0; i < source.size(); i++)
    {
        if(source[i] != 0)
        {
            return i;
        }

    }

    return -1;
}

template <class Type>
Type findLastNonZeroIndex(vector<Type>& source)
{
    for(int i = source.size(); i > 0; i--)
    {
        if(source[i] != 0)
        {
            return i;
        }
    }
    return -1;
}
*/

/*
Input mask should be initialized to 0.
*/
template <class Type>
void createVectorMask(vector<Type>& source, vector<bool>& mask, int treshold)
{
    for(unsigned int i = 0; i < source.size(); i++)
    {
        if(source[i] == treshold)
            mask[i] = 1;
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
