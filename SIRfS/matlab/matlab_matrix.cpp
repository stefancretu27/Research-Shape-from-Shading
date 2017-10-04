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

Matrix2D<KeysValue<double> >* appendMatrixBelow(Matrix2D<KeysValue<double> >* source1, Matrix2D<KeysValue<double> >& source2)
{
    //create the result matrix: allocate memory + set sizes
    Matrix2D<KeysValue<double> >* result = new Matrix2D<KeysValue<double> >(source1->getRows() + source2.getRows(), source1->getCols());

    int idx, idy;

    for(idx = 0; idx < (*source1).getRows(); idx++)
        for(idy = 0; idy < (*source1).getCols(); idy++)
    {
        (*result)(idx, idy).setKeysValue((*source1)(idx, idy).getKeyX(), (*source1)(idx, idy).getKeyY(), (*source1)(idx, idy).getValue());
    }

    for(idx = (*source1).getRows(); idx < result->getRows(); idx++)
        for(idy = 0; idy < source2.getCols(); idy++)
    {
        (*result)(idx, idy).setKeysValue( source2(idx - (*source1).getRows(), idy).getKeyX(), source2(idx - (*source1).getRows(), idy).getKeyY(), source2(idx - (*source1).getRows(), idy).getValue());
    }

    return result;
}
