#include "matlab_matrix.h"

using namespace std;

//matrix operations
/*
For an input Matrix2D it  computes a mask.
It verifies if each element si greater than the treshold and  puts 1 in the mask, 0 otherwise.

Like the function below, it couldn't be a member of Matrix2D as it accepts 2 different types which wouldn't fit in that template. Also, changing the template wouldn't ease the work, but complicate it.
*/
void computeMatrixMask(Matrix2D<double>& source, Matrix2D<bool>& mask, int treshold)
{
    for(int i = 0; i < source.getRows(); i++)
        for(int j = 0; j < source.getCols(); j++)
    {
        if(source.getMatrixValue(i,j) > treshold)
        {
             mask.setMatrixValue(i, j, 1);
        }
        else
        {
             mask.setMatrixValue(i, j, 0);
        }
    }
}

/*
It gets a sinputs a matrix and its mask.
If for a given position, the mask has value 1, the input matrix's value is set to NaN.
Usually, the input maks is firstly negated, leading to replacing all 0 values to NaN in input matrix.
*/
void insertNaNValues(Matrix2D<double>& dest, Matrix2D<bool>& mask)
{
    if(mask.getRows() != dest.getRows() || mask.getCols() != dest.getCols())
    {
        cout<<"Couldn't insert NaN values"<<endl;
    }
    else
    {
        for(int i = 0; i < mask.getRows(); i++)
            for(int j = 0; j < mask.getCols(); j++)
            {
                //if the mask has value 1 at i(,j) index
                if(mask.getMatrixValue(i,j) == 1)
                {
                    dest.setMatrixValue(i, j, numeric_limits<double>::quiet_NaN());
                }
            }
    }
}

/*
Result matrix is full of zeros. If in the source a value doesn't match the treshold, the result is set to 1 on that index
*/
void checkMatrixAgainstTreshold(Matrix2D<int>& source,  Matrix2D<double>& result, int treshold)
{
    for(int i = 0; i < source.getRows(); i++)
        for(int j = 0; j < source.getCols(); j++)
        {
            if(source.getMatrixValue(i, j) != treshold)
            {
                result.setMatrixValue(i, j, (double) 1);
            }
        }
}


void convertBoolToDoubleMatrix2D(Matrix2D<bool>& source, Matrix2D<double>& dest)
{
    for(int i = 0; i < source.getRows(); i++)
        for(int j = 0; j < source.getCols(); j++)
        {
            dest.setMatrixValue(i, j, (double) source.getMatrixValue(i,j));
        }
}

//store in dest the lines in sotrce corresponding to true values in  mask
void applyVectorMask(std::vector<bool>& mask, Matrix2D<KeysValue<double> >** source, Matrix2D<KeysValue<double> > *dest)
{
    int t_idx = 0;

    //mask.getRows = source.getRows. For each line, check if mask is 1, then iterate through cols, allocate memory for KeyValue object, then set ts values
    for(
         int idx = 0; idx < (**source).getRows(); idx++)
    {
        if(mask[idx] == true)
        {
            for( int idy = 0; idy < (**source).getCols(); idy++)
            {
                (*dest)(t_idx,idy).setKeysValue((**source)(idx, idy).getKeyX(),  (**source)(idx, idy).getKeyY(), (**source)(idx, idy).getValue());
            }
            t_idx++;
        }
    }
}

void appendMatrixBelow(vector< Matrix2D<KeysValue<double> > > source, Matrix2D< KeysValue<double> >** dest)
{
    int start, finish;
    //iterate through the vector of matrices
    for(unsigned int id = 0; id < source.size(); id++)
    {
        //for the first matrix, start indexing output's rows from 0
        if(id == 0)
        {
            start = 0;
            finish = source[0].getRows();
        }
        //for the rest of matrices, the index starts with the sum of the previous matrices rows
        else
        {
            start += source[id-1].getRows();
            finish  = start + source[id].getRows();
        }

        for(int idx = start; idx < finish; idx++)
        {
            for(int idy = 0; idy < (*dest)->getCols(); idy++)
            {
                (*dest)->setMatrixValue(idx, idy, source[id].getMatrixValue(idx-start, idy));
            }
        }
    }
}
