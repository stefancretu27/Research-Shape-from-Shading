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
