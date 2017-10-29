#ifndef DATATRUE_H_INCLUDED
#define DATATRUE_H_INCLUDED

#include "templates/Matrix2D.h"

class DataTrue
{
private:
    Matrix2D<double> inputImage;
    Matrix2D<double> im;
    Matrix2D<double> log_im;
    Matrix2D<bool> mask;

public:
    DataTrue(){};//:inputImage(1,1), im(1,1), log_im(1,1), mask(1,1){};
    //getters
    inline Matrix2D<double>& getInputImage(){return this->inputImage;};
    inline Matrix2D<double>& getIm(){return this->im;};
    inline Matrix2D<double>& getLogIm(){return this->log_im;};
    inline Matrix2D<bool>& getMask(){return this->mask;};

    //setters
    inline void setInputImage(Matrix2D<double>& in){this->inputImage = in;};
    inline void setIm(Matrix2D<double>& in){this->im = in;};
    inline void setLogIm(Matrix2D<double>& in){this->log_im = in;};
    inline void setMask(Matrix2D<bool>& in){this->mask = in;};
};

#endif // TRUE_H_INCLUDED
