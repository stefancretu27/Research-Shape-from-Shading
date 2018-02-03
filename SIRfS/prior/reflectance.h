#ifndef REFLECTANCE_H_INCLUDED
#define REFLECTANCE_H_INCLUDED

#include "reflectance\gray.h"
#include "reflectance\color.h"

class Reflectance
{
private:
    ReflectanceGray gray;
    ReflectanceColor color;

public:
    //getters
    inline ReflectanceGray& getReflectanceGray(){return this->gray;};
    inline ReflectanceColor& getReflectanceColor(){return this->color;};

    //initialize class instances
    void initializeRefllectanceData()
    {
        //cout<<"Reflectance initializer"<<endl;

        this->gray.initializeReflectanceGrayData();
        this->color.initializeReflectanceColorData();
    }
};

#endif // REFLECTANCE_H_INCLUDED
