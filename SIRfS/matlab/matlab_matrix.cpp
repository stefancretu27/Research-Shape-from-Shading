#include "matlab_matrix.h"

using namespace std;

//matrix operations
void convertBoolToDoubleMatrix2D(Matrix2D<bool>& source, Matrix2D<double>& dest)
{
    for(int j = 0; j < source.getDim(); j++)
    {
        dest.setMatrixValue(j, (double) source.getMatrixValue(j));
    }
}

void convertDoubleToIntMatrix2D(Matrix2D<double>& source, Matrix2D<int>& dest)
{
    for(int j = 0; j < source.getDim(); j++)
    {
        dest.setMatrixValue(j, (int) source.getMatrixValue(j));
    }
}

void convertIntToDoubleMatrix2D(Matrix2D<int>& source, Matrix2D<double>& dest)
{
    for(int j = 0; j < source.getDim(); j++)
    {
        dest.setMatrixValue(j, (double) source.getMatrixValue(j));
    }
}


//store in dest the lines in sotrce corresponding to true values in  mask
void applyMaskOnKeysValueMatrix(std::vector<bool>& mask, Matrix2D<KeysValue<double> >** source, Matrix2D<KeysValue<double> > *dest)
{
    int t_idx = 0;

    //mask.getRows = source.getRows. For each line, check if mask is 1, then iterate through cols,  then set the values
    for(int idx = 0; idx < (**source).getRows(); idx++)
    {
        if(mask[idx] == true)
        {
            for( int idy = 0; idy < (**source).getCols(); idy++)
            {
                (*dest)(t_idx,idy).setKeysValue(t_idx,  (**source)(idx, idy).getKeyY(), (**source)(idx, idy).getValue());
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
        KeysValue<double> temp;
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
                temp = source[id].getMatrixValue(idx-start, idy);
                temp.setKeyX(idx);
                (*dest)->setMatrixValue(idx, idy, temp);
            }
        }
    }
}

//result_X and result_Y have same dimensions
void meshgrid(int x_min, int x_max, int y_min, int y_max, Matrix2D<double>& result_X, Matrix2D<double>& result_Y)
{
    int i, j, x_value, y_value;

    for(j = 0; j < result_X.getCols(); j++)
        for (i = 0; i < result_X.getRows(); i++)
        {
            x_value = x_min + j;
            if(x_value <= x_max)
            {
                result_X.setMatrixValue(i, j, x_min + j);
            }

            y_value = y_min + i;
            if(y_value <= y_max)
            {
                result_Y.setMatrixValue(i, j, y_min + i);
            }
        }
}
