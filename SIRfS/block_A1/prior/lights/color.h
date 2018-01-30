#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include "color/laboratory.h"
#include "color/natural.h"

class LightsColor
{
private:
    ColorLaboratory lab;
    ColorNatural nat;

public:
    //operators overloading
    LightsColor& operator=(const LightsColor& input)
    {
        this->lab = input.lab;
        this->nat = input.nat;
        return *this;
    };

    //getters
    inline ColorLaboratory& getColorLaboratory(){return this->lab;};
    inline ColorNatural& getColorNatural(){return this->nat;};

    //initialize Lights color data
    void initializeLightColorData()
    {
        //initialize lab
        this->lab.initializeColorLaboratoryData();
        //initialize nat
        this->nat.initializeColorNaturalData();
    }
};

#endif // COLOR_H_INCLUDED
