#include "SIRfS_Functions.h"

#include "templates/matrix2D.cpp"
#include "matlab/matlab_vector.cpp"

using namespace std;

//SIRfS operations
void conv2mat(int maskRows, int maskCols, Matrix2D<int> input_filter, Matrix2D<double>& result)
{
    int x, y, index, counter_dim = 0, min_index_array_dim = 0;
    int matrix_linear_size = maskRows*maskCols;                         //also referred as n in matlab code
    Matrix2D<int> F(input_filter.getRows(), input_filter.getCols(), 0);

    //reverse values from the input_filter and store them in F matrix
    F.reverseMatrix(input_filter);

    vector<int> i0(matrix_linear_size, 0), j0( matrix_linear_size, 0), idx0(matrix_linear_size, 0);
    vector<int> i(matrix_linear_size, 0), j( matrix_linear_size, 0), idx(matrix_linear_size, 0);

    //this vector stores non zero values from each input_filter(F)
    vector<int> fs;                                                                //(F.getRows(), F.getCols());
    //for each such a non-zero value, store how many values do not fit in the range when computing the vector containing indeces
    vector<int> counter_zero_indeces;
    //this vector contains the dimensions of each index-vector computed for each non-zero value in input_filter (F). Might not be necesary
    vector<int> dims;

    //vector<bool> keep(matrix_linear_size, 0);
    //vector that contains for each filter F a vector of NaN of  matrix_linear_size dimensions each (250x200)
    vector< vector<int> > idxs;                                         //( F.getRows()*F.getCols(), vector<int>(matrix_linear_size));

    //indeces of non-zero elements in a matrix that contains only logical ones . The indeces are stored in 2 vectors. They are used as follows A(i0[0], j0[0])
    for(x = 0; x < maskRows; x++)
        for(y = 0; y < maskCols; y++)
        {
            i0[x + y*maskRows] = x;
            j0[x + y*maskRows] = y;
            //linearize the matrix indexing
            idx0[x*maskCols + y] = x*maskCols + y;
        }

        for(int oi = 0; oi < F.getRows(); oi++)
            for(int oj = 0; oj < F.getCols(); oj++)
            {
                if(F.getMatrixValue(oi, oj) != 0)
                {
                    //used to count how many 0 values will be in idx array. It is reset to 0 for each new non-zero value of F matrix
                    counter_zero_indeces.push_back(0);

                    for(index = 0; index < matrix_linear_size; index++)
                    {
                        i[index] = i0[index] + oi ;
                        j[index] = j0[index] + oj ;

                        //keep[index] = (i[index] < maskRows) & (j[index] < maskCols);

                        //check if the newly computed indeces are in the given range. Don't need to use 'keep' vector for this, but it's similar to verifying if keep[index] == 1
                        if((i[index] < maskRows) & (j[index] < maskCols))
                        {
                            //Matlab's sub2ind  loops firstly on each rows then on columns
                            idx[index] = i[index] + maskRows * j[index];
                        }
                        else
                        {
                            idx[index] = 0;
                            counter_zero_indeces[counter_dim]++;
                        }
                    }

                    //replace 0 values in idx with -1. Normally, there should be NaN values, but since they represent indeces, negative values work as well in order to distinguish them
                    if(counter_zero_indeces[counter_dim] != 0)
                    {
                        for(int k = 0; k < idx.size(); k++)
                        {
                            if(idx[k] == 0)
                            {
                                idx[k] = -1;
                            }
                        }
                    }

                    //idxs.push_back(idx);
                    idxs.push_back(idx);
                    fs.push_back(F.getMatrixValue(oi, oj)) ;
                    dims.push_back(idx.size() - counter_zero_indeces[counter_dim]);
                    counter_dim++;
                }
            }

        Matrix2D<int> idxsMat( idx.size(), idxs.size());
        convertVectorOfVectorsToMatrix(idxs, idxsMat);

        min_index_array_dim = *std::min_element(dims.begin(), dims.end());

        Matrix2D<int> idxsMat_noNaN( min_index_array_dim, idxs.size());
        /*
        for(x = 0; x < idxsMat.getRows()-counterNaN; x++)
            for(y = 0; y < idxsMat.getCols(); y++)
            {
                idxsMat_noNaN.setMatrixValue(x, y, idxsMat.getMatrixValue(x, y));
            }

        //int m = idxsMat_noNaN.getRows();
        Matrix2D<double> A(matrix_linear_size, matrix_linear_size);         //matrix_linear_size = 50000, but I noticed the rows are 49104 , value that depends on the instruction above that has ???
        Matrix2D<double> sparse(matrix_linear_size, matrix_linear_size, 0);

        for(y = 0; y < idxsMat_noNaN.getCols(); y++)
        {
            for(x = 0; x < matrix_linear_size; x++)
                //for(int k = 0; k < matrix_linear_size; k++)
            {
                sparse.setMatrixValue(x, x, fs[y]);
            }
            A = A + sparse;
        }
        */
}


/*
Compute median filter
*/
void medianFilterMatMask(Matrix2D<bool>& input_mask, int half_width, Matrix2D<double>& output)
{
    int width = 2*half_width + 1;
    int fs_size = width*width - 1;                  //Might be necessary to do -1,a s it is actually 24 not 25
    Matrix2D<int> *fs = new Matrix2D<int>[fs_size];

   //declare data outside the for loops for a better efficiency
    Matrix2D<int>  f(width, width);
    int i, j, fs_index, x_first, x_last, y_first, y_last;

   for(i = -half_width; i <= half_width; i++)
        for(j = -half_width; j<= half_width; j++)
        {
                if ((i == 0) && (j == 0))
                    continue;

                f.initializeMatrixValues(0);
                f.setMatrixValue(i + half_width, j + half_width, -1);
                f.setMatrixValue(half_width , half_width , 1);

                //get indeces of the first and last non zero elements
                f.findFirstNonEqualElement(x_first, y_first, 0);
                f.findLastNonEqualElement(x_last, y_last, 0);

                //allocate space for sub matrix
                Matrix2D<int> f_sub(abs(x_last - x_first) + 1, abs(y_last - y_first) + 1);
                f_sub.getSubMatrix(f, x_first, x_last, y_first, y_last);

                //it's a vector of matrix2D. Iterate from 0.
                fs_index = (i+half_width)*width + (j+half_width);
                //index #12 is missed as it corresponds to i == 0 and j == 0 case that is omitted, thus it needs an adjustment
                if(fs_index > half_width*width + half_width)
                {
                    fs_index -= 1;
                }

                fs[fs_index] = f_sub;
        }

    vector<int> do_remove(fs_size, 0);
    //fs size = 25.
    for(i = 0; i < fs_size; i++)
        for(j = i+1;  j < fs_size - i; j++)
    {
        //declare matrices whose values are the absolute values of the matrices contained by the vector fs
        Matrix2D<int> absi(fs[i].getRows(), fs[i].getCols()), absj(fs[j].getRows(), fs[j].getCols());
        absi.getAbsoluteValuesMatrix(fs[i]);
        absj.getAbsoluteValuesMatrix(fs[j]);

        //declare the matrix that will hold the convolution's result an dinitialize it to 0
        Matrix2D<int> C(abs(fs[i].getRows() - fs[j].getRows()) + 1, abs(fs[i].getCols() - fs[j].getCols()) + 1);
        C.initializeMatrixValues(0);
        //create a result vector that contains values of 1 if in C is a column containing a value >=2
        vector<int> res(C.getCols());

        //2D convolution product between absi and absj only if the kernel's size can fit in the input matrix
        if(fs[i].getRows() >= fs[j].getRows() && fs[i].getCols() >= fs[j].getCols())
        {
            absi.conv2DValid(absj, C);
            C.anyGreater(res, 1, 1);
        }
        else
        {
            fill(res.begin(), res.end(), 0);
        }

        for(int k = 0; k < C.getCols(); k++)
        {
            //find a non zero element in result vector
            if(res[k] != 0)
            {
                do_remove[j] = 1;
            }
            break;
        }

    }

    Matrix2D<double> d_input_mask(input_mask.getRows(), input_mask.getCols()), conv_res(input_mask.getRows(), input_mask.getCols());
    vector<double> R(input_mask.getRows()*input_mask.getCols());
    vector<bool>  keep(input_mask.getRows()*input_mask.getCols(), 0);
    Matrix2D<double>  *A = new Matrix2D<double>[fs_size];            //the max size is fs_size

    //How to use A: A.push_back(Matrix<double>(2, 2, false));

    //for(int k = 0; k < fs_size; k++)    //k = 0:11
    int k = 0;
    {
        if(do_remove[k] == 0)
        {
            //work with fs[k]
            conv2mat(input_mask.getRows(), input_mask.getCols(), fs[k], A[k]);
            /*Matrix2D<double> f( fs[k].getRows(), fs[k].getCols(), 0);
            checkMatrixAgainstTreshold( fs[k], f, 0);

            convertBoolToDoubleMatrix2D(input_mask, d_input_mask);
            //conv2(double(invalid), f, 'valid');

            //do reshape
            d_input_mask.reshapeToVector(R);
            //compute 'keep' mask vector
            createVectorMask(R, keep, 0);

            //A{i} has already values set by conv2mat and is a sparse matrix (many 0)
            //didn't understand this Matlab code A{i} = A{i}(keep,:);
            */
        }
    }

}
