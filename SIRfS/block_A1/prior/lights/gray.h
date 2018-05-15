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
    //constructors
    LightsGray(){};
    LightsGray(const LightsGray &input)
    {
        this->lab = input.lab;
        this->nat = input.nat;
    };
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
    void initializeLightsGrayData(StructNode& gray_metadata)
    {
        //create a StructNode instance for 3rd level fields, that are natural and laboratory structs, which are inner structs for both color and gray
        vector<StructNode*> nodes3 = gray_metadata.getChildrenNodes();

        for(unsigned int iii = 0; iii <  nodes3.size(); iii++)
        {
            if(strcmp(nodes3[iii]->getStructureP()->name, "laboratory") == 0)
            {
                //initialize lab
                this->lab.initializeGrayLaboratoryData(*nodes3[iii]);
            }
            if(strcmp(nodes3[iii]->getStructureP()->name, "natural") == 0)
            {
                //initialize nat
                this->nat.initializeGrayNaturalData(*nodes3[iii]);
            }
        }
    }
};

#endif // GRAY_H_INCLUDED
