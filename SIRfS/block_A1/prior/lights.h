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
    //constructors
    Lights(){};
#ifdef U_PTR_CONTAINER
    Lights(Lights &input)
#else
    Lights(const Lights &input)
#endif
    {
        this->color = input.color;
        this->gray = input.gray;
    };

    //operators overloading
#ifdef U_PTR_CONTAINER
    Lights& operator=(Lights& new_light)
#else
    Lights& operator=(const Lights& new_light)
#endif
    {
        this->color = new_light.color;
        this->gray = new_light.gray;
        return *this;
    };

    //getters
    inline LightsGray& getLightsGray(){return this->gray;};
    inline LightsColor& getLightsColor(){return this->color;};

    //initialize data
    void initializeLightsData(StructNode& lights_metadata)
    {
        vector<StructNode*>  nodes2 = lights_metadata.getChildrenNodes();

        for(int ii = 0; ii < nodes2.size(); ii++)
        {
            if(strcmp(nodes2[ii]->getStructureP()->name, "color") == 0)
            {
                this->color.initializeLightColorData(*nodes2[ii]);
            }
            if(strcmp(nodes2[ii]->getStructureP()->name, "gray") == 0)
            {
                this->gray.initializeLightsGrayData(*nodes2[ii]);
            }
        }
    }
};
#endif // LIGHT_H_INCLUDED
