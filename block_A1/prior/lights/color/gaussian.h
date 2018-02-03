#ifndef COLORGAUSSIAN_H_INCLUDED
#define COLORGAUSSIAN_H_INCLUDED

#include <iostream>
#include <vector>
#include "../../../../templates/matrix2D.h"
#include "../../../../templates/dataFile.h"

class ColorGaussian
{
private:
    std::vector<long double> mu;
    Matrix2D<double> Sigma;     //size = 27

public:
    //operators overloading
    ColorGaussian& operator=(const ColorGaussian& input)
    {
        this->mu = input.mu;
        this->Sigma = input.Sigma;
        return *this;
    };

    //getters
    inline std::vector<long double>& getMu(){return this->mu;};
    inline Matrix2D<double>& getSigma(){return this->Sigma;};

    //initialize data
    ColorGaussian();
    void initializeColorLaboratoryGaussianData();
    void initializeColorNaturalGaussianData();
};

#endif // COLORGAUSSIAN_H_INCLUDED
