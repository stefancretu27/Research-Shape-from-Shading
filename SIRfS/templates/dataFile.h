#ifndef DATAFILE_H_INCLUDED
#define DATAFILE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "matrix2D.h"
#include "matrix3D.h"

using namespace std;

template <class Type>
class DataFile
{
private:
    std::fstream fileObject;        //input file stream used to read information from files

public:
    void readVector(const char* filename, std::vector <Type> &dest, int dim, int precision)
    {
        fileObject.open(filename, ios::in);

        if(fileObject.is_open())
        {
            int idx;
            Type temp;

            if(precision)
            {
                while(fileObject >> setprecision(precision) >> temp)
               {
                   dest.push_back(temp);
               }
                /*for(idx = 0; idx < dim; idx++)
                //{
                    //fileObject >> setprecision(precision) >> dest[idx];
                //}
                if(typeid(Type)== typeid(double))*/
            }
            else
            {
                for(idx = 0; idx < dim; idx++)
                {
                    fileObject >> dest[idx];
                }
            }
        }
        fileObject.close();
    }

    void  readMatrix2D(const char* filename, Matrix2D<Type> &dest, int rows, int cols, int precision)
    {
        fileObject.open(filename, ios::in);

        if(fileObject.is_open())
        {
             int xIdx, yIdx;
            //Type temp;

            if(precision)
            {
                for(xIdx = 0; xIdx < rows; xIdx++)
                    for(yIdx = 0; yIdx < cols; yIdx++)
                {
                    fileObject >> setprecision(precision) >> dest(xIdx, yIdx);
                }
            }
            else
            {
                for(xIdx = 0; xIdx < rows; xIdx++)
                    for(yIdx = 0; yIdx < cols; yIdx++)
                {
                    fileObject >> dest(xIdx, yIdx);
                }
            }
        }
        fileObject.close();
    }

    void  readMatrix3D(const char* filename, Matrix3D<Type> &dest,  int xDim,  int yDim,  int zDim,  int precision)
    {
        fileObject.open(filename, ios::in);

        if(fileObject.is_open())
        {
             int xIdx, yIdx, zIdx;
            //Type temp;

            if(precision)
            {
                for(xIdx = 0; xIdx < xDim; xIdx++)
                    for(yIdx = 0; yIdx < yDim; yIdx++)
                        for(zIdx = 0; zIdx < zDim; zIdx++)
                {
                    fileObject >> setprecision(precision) >> dest(xIdx, yIdx, zIdx);
                }
            }
            else
            {
                for(xIdx = 0; xIdx < xDim; xIdx++)
                    for(yIdx = 0; yIdx < yDim; yIdx++)
                        for(zIdx = 0; zIdx < zDim; zIdx++)
                {
                    fileObject >> dest(xIdx, yIdx, zIdx);
                }
            }
        }
        fileObject.close();
    }

};

#endif // DATAFILE_H_INCLUDED
