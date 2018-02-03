#ifndef VALIDATION_H_INCLUDED
#define VALIDATION_H_INCLUDED

#include <vector>
#include <cstring>

#include "templates/dataFile.h"
#include "templates/matrix2d.h"
#include "enums.h"

/*
* Function used to test 2 vectors.
* First vector is read from a file that stores data output from Matlab code
* The second vector represents the one computed by the ported code. The pointer is used for memory efficiency, so the values can be read from the same memory location
*/
template <class Type>
bool test_vectors(const char* filename1, vector<Type> *cpp_data, DataType dtype)
{
    bool verification_result;
    //create file reader object. For each type of data, create apropriate destination to read data into, from the input files
    switch(dtype)
        {
            //bool case is treated as int
            case 0:
            case 1:
            {
                DataFile<int> fileReader;
                vector<int>  matlab_data(cpp_data->size());
                fileReader.readVector(filename1, matlab_data, cpp_data->size(), 0);
                verification_result = matlab_data == *cpp_data;
            }
            break;
            case 2:
            {
                DataFile<float> fileReader;
                vector<float>  matlab_data(cpp_data->size());
                fileReader.readVector(filename1, matlab_data, cpp_data->size(), 0);
                verification_result = matlab_data == *cpp_data;
            }
            break;
            case 3:
            {
                DataFile<double> fileReader;
                vector<double>  matlab_data(cpp_data->size());
                fileReader.readVector(filename1, matlab_data, cpp_data->size(), 0);
                verification_result = matlab_data == *cpp_data;
            }
            break;
        }
        return verification_result;
}

/*
* Function used to test 2 matrixes.
* First matrix is read from a file that stores data output from Matlab code
* The second matrix represents the one computed by the ported code. The pointer is used for memory efficiency, so the values can be read from the same memory location
*/
template <class Type>
bool test_matrixes(const char* filename1, Matrix2D<Type> *cpp_data, DataType dtype)
{
    bool verification_result;
    //create file reader object. For each type of data, create apropriate destination to read data into, from the input files
    switch(dtype)
        {
            //bool case is treated as int
            case 0:
            case 1:
            {
                DataFile<int> fileReader;
                Matrix2D<int>  matlab_data(cpp_data->getRows(), cpp_data->getCols());
                fileReader.readMatrix2D(filename1, matlab_data, cpp_data->getRows(), cpp_data->getCols(), 0);
                verification_result = matlab_data == *cpp_data;

            }
            break;
            case 2:
            {
                DataFile<float> fileReader;
                Matrix2D<float>  matlab_data(cpp_data->getRows(), cpp_data->getCols());
                fileReader.readMatrix2D(filename1, matlab_data, cpp_data->getRows(), cpp_data->getCols(), 0);
                verification_result = matlab_data == *cpp_data;
            }
            break;
            case 3:
            {
                DataFile<double> fileReader;
                Matrix2D<double>  matlab_data(cpp_data->getRows(), cpp_data->getCols() );
                fileReader.readMatrix2D(filename1, matlab_data, cpp_data->getRows(), cpp_data->getCols(), 0);
                verification_result = matlab_data == *cpp_data;
            }
            break;
        }

        return verification_result;
}
#endif // VALIDATION_H_INCLUDED
