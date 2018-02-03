#ifndef COLORNATURAL_H_INCLUDED
#define COLORNATURAL_H_INCLUDED

#include "gaussian.h"
#include "whitenParams.h"

class ColorNatural
{
private:
    ColorGaussian gaussian;
    ColorWhitenParams whiten_params;

public:
    //getters
    inline ColorGaussian& getColorGaussian(){return this->gaussian;};
    inline ColorWhitenParams& getColorWhitenParams(){return this->whiten_params;};

    //initialize data
    void initializeColorNaturalData()
    {
        //initialize gaussian
        this->gaussian.initializeColorNaturalGaussianData();
        //initialize whiten parameters
        this->whiten_params.initializeColorNaturalWhitenParamsData();
    }
};

#endif // COLORNATURAL_H_INCLUDED
