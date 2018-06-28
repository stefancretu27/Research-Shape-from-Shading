#ifndef COLORGAUSSIAN_H_INCLUDED
#define COLORGAUSSIAN_H_INCLUDED

#include <iostream>
#include <vector>

#include "../../../../helpers/prior_struct_node.h"
//needed for natural and laboratory
#include "../../../../templates/dataFile.h"
#include "../../../../helpers/validation.h"

class ColorGaussian
{
private:
    std::vector<double> mu;
    Matrix2D<double> Sigma;     //size = 27

public:
    //constructors
    ColorGaussian(){};
    ColorGaussian(const ColorGaussian& input)
    {
        this->mu = input.mu;
        this->Sigma = input.Sigma;
    };

    //operators overloading
    ColorGaussian& operator=(const ColorGaussian& input)
    {
        this->mu = input.mu;
        this->Sigma = input.Sigma;
        return *this;
    };

    //getters
    inline std::vector<double>& getMu(){return this->mu;};
    inline Matrix2D<double>& getSigma(){return this->Sigma;};

    //initialize data
    void initializeColorGaussianData(StructNode& color_g_metadata);
};

#endif // COLORGAUSSIAN_H_INCLUDED
