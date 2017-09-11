#include "SIRfS_Functions.h"

#include "templates/matrix2D.cpp"
#include "matlab/matlab_vector.cpp"
//#include "matlab/matlab_matrix.cpp"

using namespace std;

//SIRfS operations
void conv2mat(int maskRows, int maskCols, Matrix2D<int> input_filter, Matrix2D<KeysValue<double> >& result)
{
    int x, y, index, counter_dim = 0, min_index_array_dim = 0;
    int mask_matrix_linear_size = maskRows*maskCols;                         //also referred as n in matlab code
    Matrix2D<int> F(input_filter.getRows(), input_filter.getCols(), 0);

    //reverse values from the input_filter and store them in F matrix
    F.reverseMatrix(input_filter);

    //vectors used to store indeces before applying filter
    vector<int> i0(mask_matrix_linear_size, 0), j0( mask_matrix_linear_size, 0), idx0(mask_matrix_linear_size, 0);
    //vectors used to store indeces after applying filter
    vector<int> i(mask_matrix_linear_size, 0), j( mask_matrix_linear_size, 0), idx(mask_matrix_linear_size, 0);
    //this vector stores non zero values from each input_filter(F)
    vector<int> fs;     //(F.getRows(), F.getCols());
    //for each such a non-zero value, store how many values do not fit in the range when computing the vector containing indeces
    vector<int> count_out_of_range_indeces;
    //this vector contains the dimensions of each index-vector computed for each non-zero value in input_filter (F). Might not be necesary
    vector<int> dims;
    //vector<bool> keep(matrix_linear_size, 0);
    //vector that contains for each filter F a vector of NaN of  matrix_linear_size dimensions each (250x200)
    vector< vector<int> > idxs;   //( F.getRows()*F.getCols(), vector<int>(matrix_linear_size));

    //indeces of non-zero elements in a matrix that contains only logical ones . The indeces are stored in 2 vectors. They are used as follows A(i0[0], j0[0])
    for(x = 0; x < maskRows; x++)
        for(y = 0; y < maskCols; y++)
        {
            //firstly, compute 2 vectors that store indeces for the input mask
            i0[x + y*maskRows] = x;
            j0[x + y*maskRows] = y;
            //linearize the mask matrix indexing
            idx0[x*maskCols + y] = x*maskCols + y;
        }

        for(int oi = 0; oi < F.getRows(); oi++)
            for(int oj = 0; oj < F.getCols(); oj++)
            {
                //for each non zero value in the reversed input filter compute an array of indeces
                if(F.getMatrixValue(oi, oj) != 0)
                {
                    //used to count how many 0 values will be in idx array. It is reset to 0 for each new non-zero value of F matrix
                    count_out_of_range_indeces.push_back(0);

                    for(index = 0; index < mask_matrix_linear_size; index++)
                    {
                        //the reversed filter is applied to the mask so, new vectors storing the updated indeces are computed
                        i[index] = i0[index] + oi ;
                        j[index] = j0[index] + oj ;

                        //keep[index] = (i[index] < maskRows) & (j[index] < maskCols);

                        //check if the newly computed indeces are in the given range. Don't need to use 'keep' vector for this, but it's similar to verifying if keep[index] == 1
                        if((i[index] < maskRows) & (j[index] < maskCols))
                        {
                            //If the updated indeces are within the mask matrix dimensions range, linearize them and store them in a vector (idx)
                            // Matlab's sub2ind  loops firstly on each row, then on columns thus the linearization below (reads column by column, not line by line)
                            idx[index] = i[index] + maskRows * j[index];
                        }
                        else
                        {
                            //if the updated indeces are out of range, store 0 as linear index and increase counter
                            idx[index] = 0;
                            count_out_of_range_indeces[counter_dim]++;
                        }
                    }

                    //replace 0 values in idx with -1. Normally, there should be NaN values, but since they represent indeces, negative values work as well in order to distinguish them
                    if(count_out_of_range_indeces[counter_dim] != 0)
                    {
                        for(unsigned int k = 0; k < idx.size(); k++)
                        {
                            if(idx[k] == 0)
                            {
                                idx[k] = -1;
                            }
                        }
                    }

                    //store the newly computed vector (the new idx) in the vector of vectors
                    idxs.push_back(idx);
                    //store each non zero value found in the reversed input filter (F)
                    fs.push_back(F.getMatrixValue(oi, oj)) ;
                    //store the size of each newly computed vector (idx).
                    //If all updated indeces are within mask matrix range, the size of idx vector will be mask_matrix_linear_size. Otherwise, it will be less, depending
                    dims.push_back(idx.size() - count_out_of_range_indeces[counter_dim]);
                    //count how many non zero values are in the reversed input filter F
                    counter_dim++;
                }
            }

        //the vectors computed in the previous double loop are stored in a vector of vectors (idxs) which is now converted into a matrix
        Matrix2D<int> idxsMat( mask_matrix_linear_size, idxs.size());
        convertVectorOfVectorsToMatrix(idxs, idxsMat);

        //find the minmum value of the sizes of all vectors in idxs
        min_index_array_dim = *std::min_element(dims.begin(), dims.end());

        //a new matrix is computed. It stores all the lines in the idxsMat that do not have a Nan (-1) value.
        //Thus, it's number of lines equals the number of lines of the vectors in idxs with the most Nan values (-1)
        Matrix2D<int> idxsMat_noNaN( min_index_array_dim, idxs.size());
        vector<int> nan_values_line_index(min_index_array_dim);
        int nan_line_index_size = 0, nan_counter = 0;


        //iterate over the maximum number of lines
        for(x = 0; x < mask_matrix_linear_size; x++)
        {
            //loop over the elements of each line to check for -1 values
            for( y = 0; y < (int) idxs.size(); y++)
            {
                //find the first -1 value, store its line index and increase the counter
                if(idxsMat.getMatrixValue(x, y) == -1)
                {
                    nan_values_line_index[nan_line_index_size++] = x;
                    nan_counter++;
                    break;
                }
            }

            //if the current line does not contain any -1 (nan) values, copy it to idxsMat_noNaN
            if(x != nan_values_line_index[nan_line_index_size-1])
            {
                for( y = 0; y < (int) idxs.size(); y++)
                {
                    idxsMat_noNaN(x - nan_counter, y) = idxsMat(x, y);
                }
            }
        }

       int m = idxsMat_noNaN.getRows();

       //almost 50k by 50k it takes some time to allocate it, especially if it contains double values.
       //matrix initialization takes almost 15-16 secs
        //Matrix2D<float> A(m, mask_matrix_linear_size, 0);

        //Since it is impossible to work with such bug matrices as the system goes out of RAM, use a matrix that stores only non zero values
        //These values are actually  triples (keyX, keyY, value), hat are indices in a spare matrix and the afferent value
        Matrix2D< KeysValue<double> > A(m, idxsMat_noNaN.getCols());

        //Matrix2D<int> sparse(m, mask_matrix_linear_size, 0);
        //Instead of store a sparse matrix, use a vector for saving memory.
        //By this way, the idea of sparse matrix from Matlab is preserved, as it is meant to save memory by not storing 0 values
        vector<int> sparse_vec(mask_matrix_linear_size, 0);
        int temp_idx;

        for(y = 0; y < idxsMat_noNaN.getCols(); y++)
        {
            //for each column in idxsMat_noNaN, m values are stored in mask_matrix_linear_size sized array, where m <= mask_matrix_linear_size
            //the values do not necessarily start with 0, as they might start indexing from 502, for instance
            for(x = 0; x < m; x++)
            {
                //sparse.setMatrixValue(x, idxsMat, fs[y]);
                temp_idx = idxsMat_noNaN(x, y);
                sparse_vec[temp_idx] = fs[y];

                //A(x, temp_idx) += sparse_vec[temp_idx];
                //if 2 or more values were on the same line, they will still be, as A stores on the lines x a number of y KeysValue triple
                A(x, y).setKeysValue(x, temp_idx, sparse_vec[temp_idx]);
            }
        }

        result = A;
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

    //all float data sets should have been double, but in order to save some memory...
    Matrix2D<double> d_input_mask(input_mask.getRows(), input_mask.getCols());
    //array of 2D matrices that store triples (keyX, keyY, value), hat are indices in a spare matrix and the afferent value
    Matrix2D<KeysValue<double> > *A_vec = new Matrix2D<KeysValue<double> >[fs_size];            //cannot store fs_size (divided by 2) 50k by 50k matrices
    //use it as temporary matrix
    Matrix2D<KeysValue<double> > A;
    int A_idx = 0;

    vector< Matrix2D <KeysValue<double> >* >  Av;

    ////How to use A: A.push_back(Matrix<double>(2, 2, false));

    for(int k = 0; k < fs_size; k++)    //k = 0:11
    {
        if(do_remove[k] == 0)
        {
            conv2mat(input_mask.getRows(), input_mask.getCols(), fs[k], A);

            Matrix2D<double> f( fs[k].getRows(), fs[k].getCols(), 0);
            //if a value is not zero, store 1, else store 1 in the new matrix f
            checkMatrixAgainstTreshold( fs[k], f, 0);
            //convert matrix input_mask to double
            convertBoolToDoubleMatrix2D(input_mask, d_input_mask);

            //Apply convolution between filter f and input_mask (after converted to double). Store the result in the matrix conv_res
            Matrix2D<double> conv_res( abs(d_input_mask.getRows() - f.getRows() + 1), abs(d_input_mask.getCols() - f.getCols() + 1), 0);
            d_input_mask.conv2DValid(f, conv_res);
            //reshape conv_res matrix to vector R. R's dimension should be equal to A.getRows()
            vector<double> R(conv_res.getRows()*conv_res.getCols(), 0);
            conv_res.reshapeToVector(R);

            //compute 'keep' mask vector
            vector<bool>  keep(R.size(), false);
            createVectorMask(R, keep, 0);

            //A{i} has already values set by conv2mat and is a sparse matrix (many 0)
            //It seems to keep only the lines in A{i} corresponding to 1 values in keep

            int notnull_lines_in_A = std::count(keep.begin(), keep.end(), true);
            //temp_A stores the lines in A corresponding to true values in keep mask
            Matrix2D<KeysValue<double> > temp_A(notnull_lines_in_A, A.getCols());

            int t_idx = 0;

            for(unsigned int idx = 0; idx < keep.size(); idx++)
            {
                if(keep[idx] == true)
                {
                    //store in temp_A the lines in A corresponding to true values in keep mask
                    for(int idy = 0; idy < A.getCols(); idy++)
                    {
                        //temp_A.setMatrixValue(t_idx, idy, A.getMatrixValue(idx, idy));
                        temp_A(t_idx, idy).setKeysValue( A(idx, idy).getKeyX(),  A(idx, idy).getKeyY(), A(idx, idy).getValue());
                    }

                    t_idx++;
                }
            }

            //crashes because of copy constructor that fails because of double (nested) templates
            //A_vec[A_idx] = temp_A;
            //sometimes crashes here
            Av.push_back(&temp_A);

            cout<<Av[k]->getRows()<<" "<<Av[k]->getCols()<<"  |  "<<temp_A.getRows()<<" "<<temp_A.getCols()<<endl;
            cout<<temp_A(0,0).getKeyX()<<" "<<temp_A(0,0).getKeyY()<<" "<<temp_A(0, 0).getValue()<<endl;
            cout<<Av[k]->getMatrixValue(0,0).getKeyX()<<" "<<Av[k]->getMatrixValue(0,0).getKeyY()<<" "<<Av[k]->getMatrixValue(0,0).getValue()<<endl;
            cout<<endl;

        }
    }

    //Matrix2D<KeysValue<double> > cat_A(A_vec[A_idx-1].getRows(), A_idx * A_vec[A_idx-1].getCols());
    //cout<<cat_A.getRows()<<" "<<cat_A.getCols()<<endl;
}
