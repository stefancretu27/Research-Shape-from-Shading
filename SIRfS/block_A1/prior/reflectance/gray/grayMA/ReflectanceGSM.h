#ifndef REFLECTANCEGSM_H_INCLUDED
#define REFLECTANCEGSM_H_INCLUDED

#include "limits"
#include "../../../height/MKZ/GSM/lut.h"

class ReflectanceGSM
{
private:
    float mu;
    Lut lutObj;
    vector<double> sigs;       //size = 40
    vector<long double> pis;

public:
    //operators overloading
    ReflectanceGSM& operator=(const ReflectanceGSM& input);
    {
        this->mu = input.mu;
        this->sigs = input.sigs;
        this->pis = input.pis;
        this->lutObj = input.lutObj:
    };

     //getters
    float getMu(){return this->mu;};
    Lut& getLut(){return this->lutObj;};
    vector<double>& getSigs(){return this->sigs;};
    vector<long double>& getPis(){return this->pis;};

    //initialize reflectance gray data
    void initializeGSMReflectanceGrayData();
};


#endif // REFLECTANCEGSM_H_INCLUDED
