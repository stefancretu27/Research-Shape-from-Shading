#ifndef DATATRUE_H_INCLUDED
#define DATATRUE_H_INCLUDED

#include "templates/Matrix2D.h"

class DataTrue
{
private:
    Matrix2D<double> inputImage, im, log_im;
    Matrix2D<bool> mask;

public:
    DataTrue():inputImage(1,1), im(1,1), log_im(1,1), mask(1,1){};
    //getters
    inline Matrix2D<double>& getInputImage(){return this->inputImage;};
    inline Matrix2D<double>& getIm(){return this->im;};
    inline Matrix2D<double>& getLogIm(){return this->log_im;};
    inline Matrix2D<bool>& getMask(){return this->mask;};
};

#endif // TRUE_H_INCLUDED
