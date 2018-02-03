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
    void initializeReflectanceData()
    {
        //cout<<"Reflectance initializer"<<endl;

        this->gray.initializeReflectanceGrayData();
        this->color.initializeReflectanceColorData();
    }
};

#endif // REFLECTANCE_H_INCLUDED
