#ifndef GRAYLABORATORY_H_INCLUDED
#define GRAYLABORATORY_H_INCLUDED

#include "gaussian.h"
#include "whitenParams.h"

class GrayLaboratory
{
private:
    GrayGaussian gaussian;
    GrayWhitenParams whiten_params;

public:
    //getters
    inline GrayGaussian& getGrayGaussian(){return this->gaussian;};
    inline GrayWhitenParams& getGrayWhitenParams(){return this->whiten_params;};

    //initialize data
    void initializeGrayLaboratoryData()
    {
        //initialize gaussian
        this->gaussian.initializeGrayLaboratoryGaussianData();
        //initialize whiten parameters
        this->whiten_params.initializeGrayLaboratoryWhitenParamsData();
    }
};

#endif // GRAYLABORATORY_H_INCLUDED
