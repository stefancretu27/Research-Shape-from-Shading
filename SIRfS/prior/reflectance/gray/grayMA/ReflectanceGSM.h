#ifndef REFLECTANCEGSM_H_INCLUDED
#define REFLECTANCEGSM_H_INCLUDED

#include "limits"
#include "../../../height/MKZ/GSM/lut.h"

class ReflectanceGSM
{
private:
    float mu;
    Lut lutObj;

public:
    vector<double> sigs;       //size = 40
    vector<long double> pis;

     //getters
    float getMu(){return this->mu;};
    Lut& getLut(){return this->lutObj;};
    vector<double>& getSigs(){return this->sigs;};
    vector<long double>& getPis(){return this->pis;};

    //initialize height data
    //void initializeGSMHeightData();

    //initialize reflectance gray data
    void initializeGSMReflectanceGrayData();
};


#endif // REFLECTANCEGSM_H_INCLUDED
