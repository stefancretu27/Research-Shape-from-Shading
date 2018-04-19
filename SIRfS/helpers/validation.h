#ifndef VALIDATION_H_INCLUDED
#define VALIDATION_H_INCLUDED

#include <vector>
#include <cstring>

#include "templates/dataFile.h"
#include "templates/matrix2d.h"
#include "templates/matrix3d.h"
#include "enums.h"

//#define TEST_INPUT_IMAGE 0
//#define TEST_PRIOR_HEIGHT 1
//#define TEST_PRIOR_LIGHT 2
//#define TEST_PRIOR_REFLECTANCE 3
//#define TEST_BLOCK_A2 4

/*
* Function used to test 2 vectors.
* First vector is read from a file that stores data output from Matlab code
* The second vector represents the one computed by the ported code. The pointer is used for memory efficiency, so the values can be read from the same memory location
*/
template <class Type>
bool test_vectors(const char* filename1, const vector<Type> &cpp_data, DataType dtype)
{
    bool verification_result = true;
    //create file reader object. For each type of data, create apropriate destination to read data into, from the input files
    switch(dtype)
    {
        //bool case is treated as int
        case 0:
        case 1:
        {
            DataFile<int> fileReader;
            vector<int>  matlab_data(cpp_data.size());
            fileReader.readVector(filename1, matlab_data, cpp_data.size(), 0);

            for(int i = 0; i < cpp_data.size(); i++)
                if((matlab_data[i] != cpp_data[i]))
                {
                    verification_result = false;
                    break;
                }
        }
        break;
        case 2:
        {
            DataFile<float> fileReader;
            vector<float>  matlab_data(cpp_data.size());
            fileReader.readVector(filename1, matlab_data, cpp_data.size(), 0);

            for(int i = 0; i < cpp_data.size(); i++)
                if(fabs(matlab_data[i] - cpp_data[i]) > pow(10, -15))
                {
                    verification_result = false;
                    break;
                }
        }
        break;
        case 3:
        {
            DataFile<double> fileReader;
            vector<double>  matlab_data(cpp_data.size());
            fileReader.readVector(filename1, matlab_data, cpp_data.size(), 0);

            for(int i = 0; i < cpp_data.size(); i++)
                if(fabs(matlab_data[i] - cpp_data[i]) > pow(10, -14))
                {
                    cout<<i<<" "<<matlab_data[i]<<" "<<cpp_data[i]<<endl;
                    verification_result = false;
                    break;
                }
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
bool test_matrix2D(const char* filename1,  const Matrix2D<Type> &cpp_data, DataType dtype)
{
    bool verification_result = true, do_loop = true;
    //create file reader object. For each type of data, create apropriate destination to read data into, from the input files
    switch(dtype)
    {
        //bool case is treated as int
        case 0:
        case 1:
        {
            DataFile<int> fileReader;
            Matrix2D<int>  matlab_data(cpp_data.getRows(), cpp_data.getCols());
            fileReader.readMatrix2D(filename1, matlab_data, cpp_data.getRows(), cpp_data.getCols(), 0);

            for(int i = 0; i < cpp_data.getRows() && do_loop; i++)
            {
                for(int j = 0; j < cpp_data.getCols() && do_loop; j++)
                {
                    if(matlab_data(i, j) != cpp_data(i, j))
                    {
                        verification_result = false;
                        do_loop = false;
                        break;
                    }
                }
            }
        }
        break;
        case 2:
        {
            DataFile<float> fileReader;
            Matrix2D<float>  matlab_data(cpp_data.getRows(), cpp_data.getCols());
            fileReader.readMatrix2D(filename1, matlab_data, cpp_data.getRows(), cpp_data.getCols(), 0);

            for(int i = 0; i < cpp_data.getRows() && do_loop; i++)
            {
                for(int j = 0; j < cpp_data.getCols() && do_loop; j++)
                {
                    if(fabs(matlab_data(i, j) - cpp_data(i, j)) > pow(10, -15))
                    {
                        verification_result = false;
                        do_loop = false;
                        break;
                    }
                }
            }
        }
        break;
        case 3:
        {
            DataFile<double> fileReader;
            Matrix2D<double>  matlab_data(cpp_data.getRows(), cpp_data.getCols() );
            fileReader.readMatrix2D(filename1, matlab_data, cpp_data.getRows(), cpp_data.getCols(), 0);

            for(int i = 0; i < cpp_data.getRows() && do_loop;i++)
            {
                for(int j = 0; j < cpp_data.getCols() && do_loop; j++)
                {
                    if(fabs(matlab_data(i, j) - cpp_data(i, j)) > pow(10, -15))
                    {
                        cout<<i<<" "<<j<<" "<<matlab_data(i,j)<<" "<<cpp_data(i,j)<<endl;
                        verification_result = false;
                        do_loop = false;
                        break;
                    }
                }
            }
        }
        break;
    }

    return verification_result;
}

template <class Type>
bool test_matrix3D(const char* filename1,  Matrix3D<Type> &cpp_data, DataType dtype)
{
    bool verification_result = true, do_loop = true;
    //create file reader object. For each type of data, create apropriate destination to read data into, from the input files
    switch(dtype)
    {
        //bool case is treated as int
        case 0:
        case 1:
        {
            DataFile<int> fileReader;
            Matrix3D<int>  matlab_data(cpp_data.getWidth(), cpp_data.getHeight(), cpp_data.getDepth());
            fileReader.readMatrix3D(filename1, matlab_data, cpp_data.getWidth(), cpp_data.getHeight(), cpp_data.getDepth(), 0);

            for(int i = 0; i < cpp_data.getWidth() && do_loop; i++)
            {
                for(int j = 0; j < cpp_data.getHeight() && do_loop; j++)
                {
                    for(int k = 0; k < cpp_data.getDepth(); k++)
                    {
                        if(matlab_data(i, j, k) != cpp_data(i,  j, k))
                        {
                            verification_result = false;
                            do_loop = false;
                            break;
                        }
                    }
                }
            }
        }
        break;
        case 2:
        {
            DataFile<float> fileReader;
            Matrix3D<float>  matlab_data(cpp_data.getWidth(), cpp_data.getHeight(), cpp_data.getDepth());
            fileReader.readMatrix3D(filename1, matlab_data, cpp_data.getWidth(), cpp_data.getHeight(), cpp_data.getDepth(), 0);

            for(int i = 0; i < cpp_data.getWidth() && do_loop; i++)
            {
                for(int j = 0; j < cpp_data.getHeight() && do_loop; j++)
                {
                    for(int k = 0; k < cpp_data.getDepth(); k++)
                    {
                        if(fabs(matlab_data(i, j, k) - cpp_data(i, j, k)) > pow(10, -15))
                        {
                            verification_result = false;
                            do_loop = false;
                            break;
                        }
                    }
                }
            }
        }
        break;
        case 3:
        {
            DataFile<double> fileReader;
            Matrix3D<double>  matlab_data(cpp_data.getWidth(), cpp_data.getHeight(), cpp_data.getDepth() );
            fileReader.readMatrix3D(filename1, matlab_data, cpp_data.getWidth(), cpp_data.getHeight(), cpp_data.getDepth(), 0);

            for(int i = 0; i < cpp_data.getWidth() && do_loop; i++)
            {
                for(int j = 0; j < cpp_data.getHeight() && do_loop; j++)
                {
                    for(int k = 0; k < cpp_data.getDepth(); k++)
                    {
                        if(fabs(matlab_data(i, j, k) - cpp_data(i, j, k)) > pow(10, -15))
                        {
                            verification_result = false;
                            do_loop = false;
                            break;
                        }
                    }
                }
            }
        }
        break;
    }

    return verification_result;
}
#endif // VALIDATION_H_INCLUDED
