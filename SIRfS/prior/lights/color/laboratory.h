#ifndef COLORLABORATORY_H_INCLUDED
#define COLORLABORATORY_H_INCLUDED

#include "gaussian.h"
#include "whitenParams.h"

class ColorLaboratory
{
private:
    ColorGaussian gaussian;
    ColorWhitenParams whiten_params;

public:
    //getters
    inline ColorGaussian& getColorGaussian(){return this->gaussian;};
    inline ColorWhitenParams& getColorWhitenParams(){return this->whiten_params;};

    //initialize data
    void initializeColorLaboratoryData()
    {
        //initialize gaussian
        this->gaussian.initializeColorLaboratoryGaussianData();
        //initialize whiten parameters
        this->whiten_params.initializeColorLaboratoryWhitenParamsData();
    }
};

#endif // COLORLABORATORY_H_INCLUDED
