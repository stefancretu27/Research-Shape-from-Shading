#ifndef GRAY_H_INCLUDED
#define GRAY_H_INCLUDED

#include "gray/laboratory.h"
#include "gray/natural.h"

class LightsGray
{
private:
    GrayLaboratory lab;
    GrayNatural nat;

public:
    //operators overloading
    LightsGray& operator=(const LightsGray& input)
    {
        this->lab = input.lab;
        this->nat = input.nat;
        return *this;
    };

    //getters
    inline GrayLaboratory& getGrayLaboratory(){return this->lab;};
    inline GrayNatural& getGrayNatural(){return this->nat;};

    //initialize Light gray data
    void initializeLightsGrayData()
    {
        //initialize lab
        this->lab.initializeGrayLaboratoryData();
        //initialize nat
        this->nat.initializeGrayNaturalData();
    }
};

#endif // GRAY_H_INCLUDED
