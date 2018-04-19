#ifndef GAUSSIAN_H_INCLUDED
#define GAUSSIAN_H_INCLUDED

#include <vector>
#include "../../../../templates/matrix2D.h"
#include "../../../../templates/dataFile.h"
#include "../../../prior_struct_node.h"
#include "../../../../helpers/validation.h"

class GrayGaussian
{
private:
    std::vector<double> mu;
    Matrix2D<double> Sigma;     //size = 9

public:
    //constructors
    GrayGaussian(){};
#ifdef U_PTR_CONTAINER
    GrayGaussian(GrayGaussian& input)
#else
    GrayGaussian(const GrayGaussian& input)
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
    GrayGaussian& operator=(GrayGaussian& input)
#else
    GrayGaussian& operator=(const GrayGaussian& input)
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
    void initializeGrayGaussianData(StructNode& gray_g_metadata);
};

#endif // GAUSSIAN_H_INCLUDED
