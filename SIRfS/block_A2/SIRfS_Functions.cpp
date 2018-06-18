#include "SIRfS_Functions.h"

#include "../matlab/matlab_vector.cpp"

using namespace std;

//SIRfS operations
//conv2mat return of output would fail due to =operator failure as it doesn't know hoe to assign pointers to KeyValue.
//Instead use an adress of a pointer declared in medianFilterMatMask, which is allocated  inside conv2mat
void conv2mat(int maskRows, int maskCols, Matrix2D<int> input_filter, Matrix2D<KeysValue<double>  >** output)
{
    int x, y, col, index, counter_dim = 0;
    int mask_matrix_linear_size = maskRows*maskCols;                         //also referred as n in matlab code
    Matrix2D<int> F(input_filter.getRows(), input_filter.getCols(), 0);

    //reverse values from the input_filter and store them in F matrix
    F.reverseMatrix(input_filter);

    //vectors used to store indeces before applying filter
    vector<int> i0(mask_matrix_linear_size, 0), j0( mask_matrix_linear_size, 0), idx0(mask_matrix_linear_size, 0);
    //vectors used to store indeces after applying filter
    vector<int> i(mask_matrix_linear_size, 0), j( mask_matrix_linear_size, 0), idx(mask_matrix_linear_size, 0);
    //this vector stores non zero values from each input_filter(F)
    vector<int> fs;
    //for each such a non-zero value, store how many values do not fit in the range when computing the vector containing indeces
    vector<int> count_out_of_range_indeces;
    vector<bool> keep(mask_matrix_linear_size, 0);
    //vector that contains for each filter F a vector of NaN of  matrix_linear_size dimensions each (250x200)
    vector< vector<int> > idxs;

    //indeces of non-zero elements in a matrix that contains only logical ones . The indeces are stored in 2 vectors. They are used as follows A(i0[0], j0[0])
    for(x = 0; x < maskRows; x++)
    {
        for(y = 0; y < maskCols; y++)
        {
            //firstly, compute 2 vectors that store indeces for the input mask
            i0[x + y*maskRows] = x;
            j0[x + y*maskRows] = y;
            //linearize the mask matrix indexing
            idx0[x*maskCols + y] = x*maskCols + y;
        }
	}

    for(int oi = 0; oi < F.getRows(); oi++)
    {
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

                    keep[index] = (i[index] < maskRows) & (j[index] < maskCols);

                    //check if the newly computed indeces are in the given range. Don't need to use 'keep' vector for this, but it's similar to verifying if keep[index] == 1
                    if(keep[index])
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
                //dims.push_back(idx.size() - count_out_of_range_indeces[counter_dim]);
                //count how many non zero values are in the reversed input filter F
                counter_dim++;
            }
        }
	}

	//the vectors computed in the previous double loop are stored in a vector of vectors (idxs) which is now converted into a matrix
	Matrix2D<int> idxsMat( mask_matrix_linear_size, idxs.size());
	//convertVectorOfVectorsToMatrix(idxs, idxsMat);
	for(unsigned int i = 0; i < idxs.size(); i ++)
		for(unsigned int j = 0; j < idxs[i].size(); j++)
		{
			//put a vector's elements on the same column, not on the same line
			idxsMat.setMatrixValue(j, i, idxs[i][j]);
		}


	//a new matrix is computed. It stores all the lines in the idxsMat that do not have a Nan (-1) value.
	//Thus, it's number of lines equals the number of lines of the vectors in idxs with the most Nan values (-1)
	Matrix2D<int> idxsMat_noNaN( mask_matrix_linear_size, idxs.size(), 0);
	vector<int> nan_values_line_index(mask_matrix_linear_size);
	int nan_counter = 0;

	//iterate over the maximum number of lines
	for(x = 0; x < mask_matrix_linear_size; x++)
	{
		//loop over the elements of each line to check for -1 values
		for( y = 0; y < (int) idxs.size(); y++)
		{
			//find the first -1 value, store its line index and increase the counter
			if(idxsMat.getMatrixValue(x, y) == -1)
			{
				nan_values_line_index[nan_counter++] = x;
				break;
			}
		}

		//if the current line does not contain any -1 (nan) values, copy it to idxsMat_noNaN
		if(x != nan_values_line_index[nan_counter-1])
		{
			for( y = 0; y < (int) idxs.size(); y++)
			{
				idxsMat_noNaN(x - nan_counter, y) = idxsMat(x, y);
			}
		}
	}

	//the number of lines for the output matrix is the linear size of the input mask subtsracting the # lines containing NaN values
	int m = mask_matrix_linear_size - nan_counter;

   //almost 50k by 50k it takes some time to allocate it, especially if it contains double values.
   //matrix initialization takes almost 15-16 secs
	//Since it is impossible to work with such big matrices as the system goes out of RAM, use a matrix that stores only non zero values
	//These values are actually  triples (keyX, keyY, value), hat are indices in a spare matrix and the afferent value
	//output is a double pointer as it can't be allocated outside this function, since its dimensions are only known here
	*output = new Matrix2D<KeysValue<double> >(m, idxsMat_noNaN.getCols());

	//Instead of storing a sparse matrix, use a vector for saving memory.
	//By this way, the idea of sparse matrix from Matlab is preserved, as it is meant to save memory by not storing 0 values
	vector<int> sparse_vec(mask_matrix_linear_size, 0);
	int temp_idx;

	for(y = 0; y < idxsMat_noNaN.getCols(); y++)
	{
		//In MATLAB the matrix is generating to store the values in ascending order of their column indexes
		//Thus check if these indexes are in ascending order. If not, change value of y so it indexes in reverse order
		if(idxsMat_noNaN.getCols() > 1 && idxsMat_noNaN(0, 0) > idxsMat_noNaN(0, 1))
		{
			//idxsMat_noNaN.sortLines();
			col = idxsMat_noNaN.getCols() - 1 - y;
		}
		else
		{
			col = y;
		}

		//for each column in idxsMat_noNaN, m values are stored in mask_matrix_linear_size sized array, where m <= mask_matrix_linear_size
		//the values do not necessarily start with 0, as they might start indexing from 502, for instance
		for(x = 0; x < m; x++)
		{
			temp_idx = idxsMat_noNaN(x, col);
			//the values from filter fs are stored in the vector sparse_vec at the index shown by idxsMat_noNan
			sparse_vec[temp_idx] = fs[col];

			//if 2 or more values were on the same line, they will still be, as A stores on the lines x a number of y KeysValue triple
			(**output)(x, y) .setKeysValue(x, temp_idx, sparse_vec[temp_idx]);
		}
	}
}

/*
Compute median filter
*/
void medianFilterMatMask(Matrix2D<bool>& input_mask, int half_width, Matrix2D<double>** output)
{
    int width = 2*half_width + 1;
    int fs_size = width*width - 1;
    Matrix2D<int> *fs = new Matrix2D<int>[fs_size];

   //declare data outside the for loops for a better efficiency
    Matrix2D<int>  f(width, width);
    int i, j, fs_index, x_first, x_last, y_first, y_last;

   for(i = -half_width; i <= half_width; i++)
   {
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
	}
	
    vector<int> do_remove(fs_size, 0);
    for(i = 0; i < fs_size; i++)
    {
        for(j = i+1;  j < fs_size - i; j++)
        {
            //declare matrices whose values are the absolute values of the matrices contained by the vector fs
            Matrix2D<int> absi(fs[i].getRows(), fs[i].getCols(), 0), absj(fs[j].getRows(), fs[j].getCols(), 0);
            absi.getAbsoluteValuesMatrix(fs[i]);
            absj.getAbsoluteValuesMatrix(fs[j]);

            //declare the matrix that will hold the convolution's result an dinitialize it to 0
            Matrix2D<int> C(abs(fs[i].getRows() - fs[j].getRows()) + 1, abs(fs[i].getCols() - fs[j].getCols()) + 1, 0);
            //create a result vector that contains values of 1 if in C is a column containing a value >=2
            vector<int> res(C.getCols());

            //2D convolution product between absi and absj only if the kernel's size can fit in the input matrix
            if(fs[i].getRows() >= fs[j].getRows() && fs[i].getCols() >= fs[j].getCols())
            {
                C.conv2DValid(absj, absi);
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
	}

	
    //all float data sets should have been double, but in order to save some memory...
    Matrix2D<double> d_input_mask(input_mask.getRows(), input_mask.getCols(), 0);

    //use it as temporary matrix, to store output from conv2mat, It is allocated and gets its values set inside conv2mat
    Matrix2D<KeysValue<double> > *A;
    //vector of matrices
    vector<Matrix2D<KeysValue<double> > > matrices_vector(fs_size);
	
    for(int k = 0; k < fs_size; k++)
    {
        if(do_remove[k] == 0)
        {
            //A is dynamically allocated in conv2mat
            conv2mat(input_mask.getRows(), input_mask.getCols(), fs[k], &A);

            Matrix2D<bool> bool_f( fs[k].getRows(), fs[k].getCols(), false);
            //if a value is not zero, store 1, else store 1 in the new matrix f
            fs[k].compareValuesToTreshold(bool_f, 0, NonEqual);
            //convert into double
            Matrix2D<double> f( fs[k].getRows(), fs[k].getCols(), 0);
            //convertBoolToDoubleMatrix2D(bool_f, f);
            for(int idx = 0; idx < bool_f.getDim(); idx++)
            {
                f.setMatrixValue(idx, (double) bool_f.getMatrixValue(idx));
            }
			
            //convert matrix input_mask to double
            //convertBoolToDoubleMatrix2D(input_mask, d_input_mask);
            for(int idx = 0; idx < input_mask.getDim(); idx++)
            {
                d_input_mask.setMatrixValue(idx,  (double) input_mask.getMatrixValue(idx));
            }

            //Apply convolution between filter f and input_mask (after converted to double). Store the result in the matrix conv_res
            Matrix2D<double> conv_res( abs(d_input_mask.getRows() - f.getRows() + 1), abs(d_input_mask.getCols() - f.getCols() + 1), 0);
            conv_res.conv2DValid(f, d_input_mask);

            //reshape conv_res matrix to vector R. R's dimension should be equal to A.getRows()
            vector<double> R((*A).getRows(), 0);
            conv_res.reshapeToVector(R);

            //compute 'keep' mask vector
            vector<bool>  keep(R.size(), false);
            createVectorMask(R, keep, 0);
            int notnull_lines_in_A = count(keep.begin(), keep.end(), true);

			
            //temp_A stores the lines in A corresponding to true values in keep mask
            Matrix2D<KeysValue<double> > temp_A(notnull_lines_in_A,  (*A).getCols());
            //apply mask to A and  store in temp_A
            applyMaskOnKeysValueMatrix(keep, &A,  &temp_A);
            
            //int t_idx = 0;
            //mask.getRows = source.getRows. For each line, check if mask is 1, then iterate through cols,  then set the values
            /*for(int idx = 0; idx < A->getRows(); idx++)
            {
                if(keep[idx] == true)
                {
                    for( int idy = 0; idy < A->getCols(); idy++)
                    {
                        temp_A(t_idx,idy).setKeysValue(t_idx,  (*A)(idx, idy).getKeyY(), (*A)(idx, idy).getValue());
                    }
                    t_idx++;
                }
            }*/
			

             //store temp_A in the vector of matrixes
             matrices_vector.push_back(temp_A);
        }
    }
	
	
    int temp_rows_nr = 0;
    //All matrixes from the vector of matrixes Av are concatenated by putting the 2nd one's first row after the 1st ones last row and so on.
    //Thus they form a big matrix wihich has as as number of rows the sum of those matrixes rows
    for(unsigned int idx = 0; idx < matrices_vector.size(); idx++)
    {
        //compute total number of rows by adding the number of rows for each matrix in the vector of matrixes
        temp_rows_nr += matrices_vector[idx].getRows();
    }

    //allocate memory for the result matrix
    Matrix2D<KeysValue<double> > *keysVal_output = new Matrix2D<KeysValue<double> >(temp_rows_nr, matrices_vector[0].getCols());

    //input is vector of matrices, output is a matrix whose number of rows is the sum of all matrices rows from the vector of matrixes
    //appendMatrixBelow(matrices_vector,  &keysVal_output);
    int start, finish;
    //iterate through the vector of matrices
    for(unsigned int id = 0; id < matrices_vector.size(); id++)
    {
        KeysValue<double> temp;
        //for the first matrix, start indexing output's rows from 0
        if(id == 0)
        {
            start = 0;
            finish = matrices_vector[0].getRows();
        }
        //for the rest of matrices, the index starts with the sum of the previous matrices rows
        else
        {
            start += matrices_vector[id - 1].getRows();
            finish  = start + matrices_vector[id].getRows();
        }

        for(int idx = start; idx < finish; idx++)
        {
            for(int idy = 0; idy < keysVal_output->getCols(); idy++)
            {
                temp = matrices_vector[id].getMatrixValue(idx-start, idy);
                temp.setKeyX(idx);
                keysVal_output->setMatrixValue(idx, idy, temp);
            }
        }
    }

    *output = new Matrix2D<double>(temp_rows_nr , keysVal_output->getCols()*3);

    //add 1 to indeces values, as MATLAB uses 1-based indexing
    for(int idx = 0; idx < (**output).getRows(); idx++)
    {
        (**output)(idx, 0) = idx+1;
        (**output)(idx, 1) = (*keysVal_output)(idx, 0).getKeyY() +1;
        (**output)(idx, 2) = (*keysVal_output)(idx, 0).getValue();
        (**output)(idx, 3) = idx + 1;
        (**output)(idx, 4) = (*keysVal_output)(idx, 1).getKeyY() + 1;
        (**output)(idx, 5) = (*keysVal_output)(idx, 1).getValue();
    }
}

//outputs 4 matrices stored in Border object
void getBorderNormals(Matrix2D<bool> mask, Border& border)
{
    int d = 5;

    //build filter as a matrix of booleans
    Matrix2D<double> filter(3, 3), reversed_filter(3, 3);
    filter.setMatrixValue(0, 0, 0); filter.setMatrixValue(0, 1, 1), filter.setMatrixValue(0, 2, 0);
    filter.setMatrixValue(1, 0, 1); filter.setMatrixValue(1, 1, 1), filter.setMatrixValue(1, 2, 1);
    filter.setMatrixValue(2, 0, 0); filter.setMatrixValue(2, 1, 1), filter.setMatrixValue(2, 2, 0);
    //it seems Matlab reverses filter when applies it
    reversed_filter.reverseMatrix(filter);

    //build ~mask matrix
    Matrix2D<bool>negated_mask(mask.getRows(), mask.getCols(), false), conv_greater_than(mask.getRows(), mask.getCols(), false), B(mask.getRows(), mask.getCols(), false);
    negated_mask.negateMatrixMask(mask);
    //convert the negated mask from bool to double
    Matrix2D<double> d_negated_mask(mask.getRows(), mask.getCols()), conv_same(mask.getRows(), mask.getCols(), 0);
    //convertBoolToDoubleMatrix2D(negated_mask, d_negated_mask);
    for(int idx = 0; idx < negated_mask.getDim(); idx++)
    {
        d_negated_mask.setMatrixValue(idx, (double) negated_mask.getMatrixValue(idx));
    }

    //convolution result: conv_same returns a result with the same size as the input (calller)
    conv_same.conv2DSame(reversed_filter, d_negated_mask);
    //once convolution is computed, it checks which values are greater than 0, creating a bolean matrix storing the results (1 if greater, 0 else)
    conv_same.compareValuesToTreshold(conv_greater_than, 0, GreaterThan);
    //Calculate B: the obtained boolean matrix and the input mask perform a logical and operation, storing the result in B and returning the number of non zero elements
    int no_nonzeros_in_B = 0;
    no_nonzeros_in_B = conv_greater_than.logicalAnd(B, mask);
    //store the indeces of nonzero elements in this matrix. In comparison to the Matlab ones, they'll always  lower by 1 (0 vs 1 base indexing)
    Matrix2D<int>int_P(no_nonzeros_in_B, 2, 0);
    B.mFindIndeces(int_P, 1, Equal);
    //Convert the previous matrix from int to double
    Matrix2D<double>P(no_nonzeros_in_B, 2, 0);
    //convertIntToDoubleMatrix2D(int_P, P);
    for(int idx = 0; idx < P.getDim(); idx++)
    {
        P.setMatrixValue(idx, (double) int_P.getMatrixValue(idx));
    }

    //create meshgrid
    Matrix2D<double>X_meshgrid(2*d +1, 2*d + 1, 0), Y_meshgrid(2*d + 1, 2*d +1, 0), pow_X_meshgrid(2*d +1, 2*d + 1, 0), pow_Y_meshgrid(2*d + 1, 2*d +1, 0);
    meshgrid(-d, d, -d, d, X_meshgrid, Y_meshgrid);
    //square matrices elements
    X_meshgrid.elementsOperation(pow_X_meshgrid, 2, Pow);
    Y_meshgrid.elementsOperation(pow_Y_meshgrid, 2, Pow);
    //add powered matrices
    pow_X_meshgrid + pow_Y_meshgrid;
    //Multiply by -5/d^2
    Matrix2D<double>factorized_sum_of_powered_meshgrids(2*d + 1, 2*d +1, 0), gaussian(2*d + 1, 2*d +1, 0);
    double multiply_factor = -5/pow(d, 2);
    pow_X_meshgrid.elementsOperation(factorized_sum_of_powered_meshgrids, multiply_factor, Multiply);
    //finally, compute gaussian
    factorized_sum_of_powered_meshgrids.elementsOperation(gaussian, 0, Exp);

    //compute inner operations needed for the new P
    Matrix2D<double>P_plus_d(no_nonzeros_in_B, 2, 0), P_minus_d(no_nonzeros_in_B, 2, 0);
    P.elementsOperation(P_plus_d, d, Sum);
    P.elementsOperation(P_minus_d, d, Substract);

    //compute the  masks for the above matrices, afterwards perform logical and on them
    Matrix2D<bool>P_plus_d_mask(no_nonzeros_in_B, 2, false), P_minus_d_mask(no_nonzeros_in_B, 2, false), and_P_masks(no_nonzeros_in_B, 2, false);
    //create size vector containing V's dimensions, needed for comparison
    vector<double>size_mask(2);
    size_mask[0] = mask.getRows(); size_mask[1] =  mask.getCols();
    //compute the bsxfun operations, which return boolean matrices
    P_plus_d.compareMatrixColumnsToVector(P_plus_d_mask, size_mask, LessThanOrEqual);
    P_minus_d.compareValuesToTreshold(P_minus_d_mask, 1, GreaterThanOrEqual);
    //logical AND between the above resulted boolean matrices
    P_plus_d_mask.logicalAnd(and_P_masks, P_minus_d_mask);

    //check rows that contain at least one 0 value
    vector<bool>allNonZeroLines(and_P_masks.getRows());
    and_P_masks.allNonZero(allNonZeroLines, 2);
    //count the number of 1 values in the above computed mask. It will tell how many rows from P will be kept. In comparison to the Matlab ones, P's values are always  lower by 1 (0 vs 1 base indexing)
    int notzero_lines_in_P = count(allNonZeroLines.begin(), allNonZeroLines.end(), true);
    //declare N, matrix for storing normal's values computed in the for loop. Also, masked_P stores values from P kept after applying mask
    Matrix2D<double> masked_P(notzero_lines_in_P, P.getCols(), 0), N(notzero_lines_in_P, masked_P.getCols(), numeric_limits<double>::quiet_NaN());
    masked_P.applyVectorMask(P, allNonZeroLines);

    //create [-d:d] vector and initialize it. It is needed inside the for loop
    vector<int>d_vector(2*d + 1);
    for(unsigned int i = 0; i < d_vector.size(); i++)
    {
        d_vector[i] = i - d;
    }

    //P matrix has only 2 columns
    for(int i = 0; i < P.getRows(); i++)
    {
        //vectors of indeces used ot get submatrix of mask input
        vector<int> mask_x(2*d + 1), mask_y(2*d + 1);
        //compute indeces by adding the current matrix values (for the current line) to d_vector computed before the loop
        for(unsigned int j = 0;  j < mask_x.size(); j++)
        {
            mask_x[j] = d_vector[j] + P.getMatrixValue(i, 0);
            mask_y[j] = d_vector[j] + P.getMatrixValue(i, 1);
        }

        //compute patch matrix
        Matrix2D<bool> patch(2*d + 1, 2*d + 1, 0);
        for(int idx = 0; idx < patch.getRows(); idx++)
            for(int idy = 0; idy < patch.getCols(); idy++)
        {
            patch.setMatrixValue(idx, idy, mask.getMatrixValue(mask_x[idx], mask_y[idy]));
        }

        int no_nonzeros_in_patch = 0;
        no_nonzeros_in_patch = patch.countValuesDifferentFromInput(0);
        //store the indeces of nonzero elements in this matrix. In comparison to the Matlab ones, they'll always  lower by 1 (0 vs 1 base indexing)
        vector<int> ii(no_nonzeros_in_patch), jj(no_nonzeros_in_patch);
        patch.vFindIndeces(ii, jj, 1, Equal);

        //start computing 'a' matrix
        Matrix2D<bool> a(patch.getDim(), patch.getDim(), false), temp_a(no_nonzeros_in_patch, no_nonzeros_in_patch, false);
        //convert patch to vector
        vector<bool> vector_patch(patch.getDim());
        patch.reshapeToVector(vector_patch);

        //calculate bsxfun substractions
        Matrix2D<int> substract_ii(no_nonzeros_in_patch, no_nonzeros_in_patch, 0), substract_jj(no_nonzeros_in_patch, no_nonzeros_in_patch, 0);
        vectorOpItsTranspose(ii, substract_ii, Substract);
        vectorOpItsTranspose(jj, substract_jj, Substract);
        //square up the above matrices' elements
        Matrix2D<int> sq_substract_ii(no_nonzeros_in_patch, no_nonzeros_in_patch, 0), sq_substract_jj(no_nonzeros_in_patch, no_nonzeros_in_patch, 0);
        substract_ii.elementsOperation(sq_substract_ii,  2, Pow);
        substract_jj.elementsOperation(sq_substract_jj,  2, Pow);
        //add the precedently computed and store the result in sq_substract_ii (overwrite tis values)
        sq_substract_ii + sq_substract_jj;
        sq_substract_ii.compareValuesToTreshold(temp_a, 2, LessThanOrEqual);
        a.applyDoubleVectorMask(temp_a, vector_patch, vector_patch);

        //apply patch mask to the gaussian
        Matrix2D<double> d_patch(patch.getRows(), patch.getCols(), 0);
        d_patch.applyMatrixMask(gaussian, patch);
        //then, get indeces and values of non zeros in d_patch
        int no_nonzeros_in_d_patch = 0;
        no_nonzeros_in_d_patch = d_patch.countValuesDifferentFromInput(0);
        vector<int>patch_i(no_nonzeros_in_d_patch), patch_j(no_nonzeros_in_d_patch);
        vector<double> v(no_nonzeros_in_d_patch), d_patch_i(no_nonzeros_in_d_patch), d_patch_j(no_nonzeros_in_d_patch);
        d_patch.vFindIndecesAndValues(patch_i, patch_j, v, 0, NonEqual);
        //substract d+1 from the above index vectors/ Actually, substract only d, since the indeces are already lower by 1
        for(int idx = 0; idx < no_nonzeros_in_d_patch; idx++)
        {
            patch_i[idx] -= d;
            patch_j[idx] -= d;
        }
        //multiply each value in patch_i and patch_j by the corresponding value in d_val
        for(int idx = 0; idx < no_nonzeros_in_d_patch; idx++)
        {
            d_patch_i[idx] = patch_i[idx] * v[idx];
            d_patch_j[idx] = patch_j[idx] * v[idx];
        }
        //compute the mean in the above computed vectors, and store the result in a vector
        double sum_i = 0, sum_j = 0;
        for(int idx = 0; idx < no_nonzeros_in_d_patch; idx++)
        {
            sum_i += d_patch_i[idx];
            sum_j += d_patch_j[idx];
        }
        vector<double>n(2);
        double sqrt_sum_squared_n;
        n[0] = -sum_i/no_nonzeros_in_d_patch;
        n[1] = -sum_j/no_nonzeros_in_d_patch;
        sqrt_sum_squared_n = sqrt(pow(n[0], 2) + pow(n[1], 2));
        //scale n vector by the previously computed value
        n[0] /= sqrt_sum_squared_n;
        n[1] /= sqrt_sum_squared_n;
        //store final results in matrix N
        N.setMatrixValue(i, 0, n[0]);
        N.setMatrixValue(i, 1, n[1]);
    }

    Matrix2D<double> T(N.getRows(), N.getCols(), 0);
    for(int idx = 0; idx< T.getRows(); idx++)
    {
        //T's first column is N's 2nd column * -1
        T.setMatrixValue(idx, 0, N.getMatrixValue(idx, 1) * (-1) );
        //T's 2nd column is N's 1st column
        T.setMatrixValue(idx, 1, N.getMatrixValue(idx, 0));
    }

    //convert indeces stored in masked_P to linear form with respect to input mask's size
    vector<double> idx(masked_P.getRows());
    //these values = matlab values -1 - mask.getRows()
    for(unsigned int i = 0; i< idx.size(); i++)
    {
        //since idx stores indexes, they have to be incremented by 1 due to 1-based Matlab indexing
        idx[i] = masked_P(i, 0) + masked_P(i, 1)*mask.getRows() + 1;
    }

    //since masked_P stores indexes, they have to be incremented by 1 due to 1-based Matlab indexing
    masked_P.elementsOperation(masked_P, 1, Sum);

    border.setIdx(idx);
    border.setPosition(masked_P);
    border.setNormal(N);
    border.setTangent(T);
}
