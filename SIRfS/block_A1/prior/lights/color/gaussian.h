#ifndef COLORGAUSSIAN_H_INCLUDED
#define COLORGAUSSIAN_H_INCLUDED

#include <iostream>
#include <vector>
#include "../../../../templates/matrix2D.h"
#include "../../../../templates/dataFile.h"
#include "../../../prior_struct_node.h"
#include "../../../../helpers/validation.h"

class ColorGaussian
{
private:
    std::vector<double> mu;
    Matrix2D<double> Sigma;     //size = 27

public:
    //constructors
    ColorGaussian(){};
#ifdef U_PTR_CONTAINER
    ColorGaussian(ColorGaussian& input)
#else
    ColorGaussian(const ColorGaussian& input)
#endif
    {
        this->mu = input.mu;
#ifdef U_PTR_CONTAINER
        this->Sigma = std::move(input.Sigma);
#else
        this->Sigma = input.Sigma;
#endif
    };

    //operators overloading
#ifdef U_PTR_CONTAINER
    ColorGaussian& operator=(ColorGaussian& input)
#else
    ColorGaussian& operator=(const ColorGaussian& input)
#endif
    {
        this->mu = input.mu;
#ifdef U_PTR_CONTAINER
        this->Sigma = std::move(input.Sigma);
#else
        this->Sigma = input.Sigma;
#endif
        return *this;
    };

    //getters
    inline std::vector<double>& getMu(){return this->mu;};
    inline Matrix2D<double>& getSigma(){return this->Sigma;};

    //initialize data
    void initializeColorGaussianData(StructNode& color_g_metadata);
};

#endif // COLORGAUSSIAN_H_INCLUDED
