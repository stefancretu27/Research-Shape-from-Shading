#ifndef REFLECTANCE_H_INCLUDED
#define REFLECTANCE_H_INCLUDED

#include "reflectance/gray.h"
#include "reflectance/color.h"

class Reflectance
{
private:
    ReflectanceGray gray;
    ReflectanceColor color;

public:
    //constructors
    Reflectance(){};
    Reflectance(const Reflectance& new_reflectance)
    {
        this->color = new_reflectance.color;
        this->gray = new_reflectance.gray;

    };
    //operators overloading
    Reflectance& operator=(const Reflectance& new_reflectance)
    {
        this->color = new_reflectance.color;
        this->gray = new_reflectance.gray;
        return *this;
    };

    //getters
    inline ReflectanceGray& getReflectanceGray(){return this->gray;};
    inline ReflectanceColor& getReflectanceColor(){return this->color;};

    //initialize class instances
    void initializeReflectanceData(StructNode& reflectance_metadata)
    {
        vector<StructNode*>  nodes2 = reflectance_metadata.getChildrenNodes();

        for(unsigned int ii = 0; ii < nodes2.size(); ii++)
        {
            if(strcmp(nodes2[ii]->getStructureP()->name, "color") == 0)
            {
                this->color.initializeReflectanceColorData(*nodes2[ii]);
            }
            if(strcmp(nodes2[ii]->getStructureP()->name, "gray") == 0)
            {
                this->gray.initializeReflectanceGrayData(*nodes2[ii]);
            }
        }
    }
};

#endif // REFLECTANCE_H_INCLUDED
