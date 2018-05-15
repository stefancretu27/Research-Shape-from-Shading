#ifndef GAUSSIAN_H_INCLUDED
#define GAUSSIAN_H_INCLUDED

#include <vector>
#include "../../../../templates/matrix2D.h"
#include "../../../../templates/dataFile.h"
#include "../../../../helpers/prior_struct_node.h"
#include "../../../../helpers/validation.h"

class GrayGaussian
{
private:
    std::vector<double> mu;
    Matrix2D<double> Sigma;     //size = 9

public:
    //constructors
    GrayGaussian(){};
    GrayGaussian(const GrayGaussian& input)
    {
        this->mu = input.mu;
        this->Sigma = input.Sigma;
    };

    //operators overloading
    GrayGaussian& operator=(const GrayGaussian& input)
    {
        this->mu = input.mu;
        this->Sigma = input.Sigma;
        return *this;
    };
    //getters
    inline std::vector<double>& getMu(){return this->mu;};
    inline Matrix2D<double>& getSigma(){return this->Sigma;};

    //initialize data
    void initializeGrayGaussianData(StructNode& gray_g_metadata);
};

#endif // GAUSSIAN_H_INCLUDED
