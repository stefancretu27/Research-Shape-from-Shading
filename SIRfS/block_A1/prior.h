#ifndef PRIOR_H_INCLUDED
#define PRIOR_H_INCLUDED

#include "prior\height.h"
#include "prior\lights.h"
#include "prior\reflectance.h"

class Prior
{
private:
    Height height;
    Lights light;
    Reflectance reflectance;

public:
    //operators overloading
    Prior& operator=(const Prior& new_prior)
    {
        this->height = new_prior.height;
        this->light = new_prior.light;
        this->reflectance = new_prior.reflectance;
        return *this;
    };

    //getters
    Height& getHeight(){return this->height;};
    Lights& getLights(){return this->light;};
    Reflectance& getReflectance(){return this->reflectance;};

    //setter: initialize data
    void initializePriorData()
    {
        //cout<<"Prior initializer"<<endl;

        //initialize classes instances
        this->height.initializeHeightData();
        this->light.initializeLightsData();
        this->reflectance.initializeReflectanceData();
    }

};

#endif // PRIOR_H_INCLUDED
