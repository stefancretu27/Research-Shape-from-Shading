#ifndef DATAFILE_H_INCLUDED
#define DATAFILE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

#include "keyValue.h"
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
            int idx = 0;
            Type temp;

            if(precision)
            {
                while(fileObject >> setprecision(precision) >> temp)
               {
                   dest.push_back(temp);
               }
            }
            else
            {
                for(idx = 0; idx < dim; idx++)
                {
                    fileObject >> dest[idx];
                }
            }
        }
        else
        {
            cout<<"File "<<filename<<" could not be open to read the vector"<<endl;
        }
        fileObject.close();
    }

    void writeVector(string filename, std::vector <Type> &source, int precision, int alterValue)
    {
        fileObject.open(filename.c_str(), ios::out);

        if(fileObject.is_open())
        {
            unsigned int idx;

            if(precision)
            {
                 for(idx = 0; idx < source.size(); idx++)
                {
                    fileObject << setprecision(precision) << source[idx]+alterValue;
                    fileObject << " ";
                }
            }
            else
            {
                for(idx = 0; idx < source.size(); idx++)
                {
                    fileObject << source[idx]+alterValue;
                    fileObject << " ";
                }
            }
        }
        else
        {
            cout<<"File "<<filename<<" could not be open to write the vector"<<endl;
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
        else
        {
            cout<<"File "<<filename<<" could not be open to read the matrix2d"<<endl;
        }
        fileObject.close();
    }

    void  writeMatrix2D(const char* filename, Matrix2D<Type> &source, int precision, int alterValue)
    {
        fileObject.open(filename, ios::out);

        if(fileObject.is_open())
        {
             int xIdx, yIdx;

            if(precision)
            {
                for(xIdx = 0; xIdx < source.getRows(); xIdx++)
                {
                    for(yIdx = 0; yIdx < source.getCols(); yIdx++)
                    {
                        fileObject << setprecision(precision) << source(xIdx, yIdx)+alterValue;
                        fileObject << " ";
                    }
                    fileObject << endl;
                }
            }
            else
            {
                for(xIdx = 0; xIdx < source.getRows(); xIdx++)
                {
                    for(yIdx = 0; yIdx < source.getCols(); yIdx++)
                    {
                        fileObject << source(xIdx, yIdx)+alterValue;
                        fileObject << " ";
                    }
                    fileObject << endl;
                }
            }
        }
        else
        {
            cout<<"File "<<filename<<" could not be open to write the matrix2d"<<endl;
        }
        fileObject.close();
    }

    //It is known the input matrixes have 1 column
    void writeKeysValueMatrix2D(string filename, Matrix2D<KeysValue<Type> > **source, int alterValue)
    {
        fstream fileObject;

        fileObject.open(filename.c_str(), ios::out);

        if(fileObject.is_open())
        {
            for(int x = 0; x < (**source).getRows(); x++)
            {
                fileObject << (**source)(x, 0).getKeyX()+alterValue<<" "<<(**source)(x, 0).getKeyY()+alterValue<<" "<<(**source)(x, 0).getValue()<<endl;
                //fileObject<< (**source)(x, 1).getKeyX()+alterValue<<" "<<(**source)(x, 1).getKeyY()+alterValue<<" "<<(**source)(x, 1).getValue()<<endl;
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
        else
        {
            cout<<"File "<<filename<<" could not be open to read the matrix3d"<<endl;
        }
        fileObject.close();
    }
};
#endif // DATAFILE_H_INCLUDED
