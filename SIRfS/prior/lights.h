#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include "lights\color.h"
#include "lights\gray.h"

class Lights
{
private:
    LightsColor color;
    LightsGray gray;

public:
    inline LightsGray& getLightsGray(){return this->gray;};
    inline LightsColor& getLightsColor(){return this->color;};

    //initialize data
    void initializeLightsData()
    {
        //initialize gaussian
        this->color.initializeLightColorData();
        //initialize whiten parameters
        this->gray.initializeLightsGrayData();
    }

};

#endif // LIGHT_H_INCLUDED
