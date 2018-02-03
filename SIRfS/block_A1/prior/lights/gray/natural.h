#ifndef NATURAL_H_INCLUDED
#define NATURAL_H_INCLUDED

#include "gaussian.h"
#include "whitenParams.h"

class GrayNatural
{
private:
    GrayGaussian gaussian;
    GrayWhitenParams whiten_params;

public:
    //operators overloading
    GrayNatural& operator=(const GrayNatural& input)
    {
        this->gaussian = input.gaussian;
        this->whiten_params = input.whiten_params;
        return *this;
    };

    //getters
    inline GrayGaussian& getGrayGaussian(){return this->gaussian;};
    inline GrayWhitenParams& getGrayWhitenParams(){return this->whiten_params;};

    //initialize data
    void initializeGrayNaturalData()
    {
        //initialize gaussian
        this->gaussian.initializeGrayNaturalGaussianData();
        //initialize whiten parameters
        this->whiten_params.initializeGrayNaturalWhitenParamsData();
    }
};

#endif // NATURAL_H_INCLUDED
