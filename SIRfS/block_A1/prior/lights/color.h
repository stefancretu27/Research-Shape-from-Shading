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
    //constructors
    LightsColor(){};
    LIghtsColor(const LightsColor &input)
    {
        this->lab = input.lab;
        this->nat = input.nat;
    };
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
    void initializeLightColorData(StructNode& color_metadata)
    {
        //create a StructNode instance for 3rd level fields, that are natural and laboratory structs, which are inner structs for both color and gray
        vector<StructNode*> nodes3 = color_metadata.getChildrenNodes();

        for(int iii = 0; iii < nodes3.size(); iii++)
        {
            if(strcmp(nodes3[iii]->getStructureP()->name, "laboratory") == 0)
            {
                //initialize lab
                this->lab.initializeColorLaboratoryData(*nodes3[iii]);
            }
            if(strcmp(nodes3[iii]->getStructureP()->name, "natural") == 0)
            {
                //initialize nat
                this->nat.initializeColorNaturalData(*nodes3[iii]);
            }
        }
    }
};

#endif // COLOR_H_INCLUDED
