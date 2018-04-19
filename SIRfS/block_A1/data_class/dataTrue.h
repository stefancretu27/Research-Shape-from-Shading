#ifndef DATATRUE_H_INCLUDED
#define DATATRUE_H_INCLUDED

#include "../../templates/matrix2D.h"

class DataTrue
{
private:
    //they store data already available in other matrixes from main, so made them point to those matrixes
    Matrix2D<double> inputImage;
    Matrix2D<double> im;
    Matrix2D<double> log_im;
    Matrix2D<bool> mask;

public:
    //contructor initializes matrixes to point to one element. They get resized when new matrixesare assigned to them
    DataTrue():inputImage(), im(), log_im(), mask(){};
    //getters
    inline Matrix2D<double>& getInputImage(){return this->inputImage;};
    inline Matrix2D<double>& getIm(){return this->im;};
    inline Matrix2D<double>& getLogIm(){return this->log_im;};
    inline Matrix2D<bool>& getMask(){return this->mask;};

    //setters
    inline void setInputImage(Matrix2D<double>& in)
    {
#ifdef U_PTR_CONTAINER
         this->inputImage = std::move(in);
#else
        this->inputImage = in;
#endif // U_PTR_CONTAINER
    };

    inline void setIm(Matrix2D<double>& in)
    {
#ifdef U_PTR_CONTAINER
        this->im = std::move(in);
#else
        this->im = in;
#endif // U_PTR_CONTAINER
    };

    inline void setLogIm(Matrix2D<double>& in)
    {
#ifdef U_PTR_CONTAINER
        this->log_im = std::move(in);
#else
        this->log_im = in;
#endif // U_PTR_CONTAINER
    };

    inline void setMask(Matrix2D<bool>& in)
    {
#ifdef U_PTR_CONTAINER
        this->mask = std::move(in);
#else
        this->mask = in;
#endif // U_PTR_CONTAINER
    };
};

#endif // TRUE_H_INCLUDED
