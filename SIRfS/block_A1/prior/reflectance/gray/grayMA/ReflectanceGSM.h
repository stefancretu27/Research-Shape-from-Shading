#ifndef REFLECTANCEGSM_H_INCLUDED
#define REFLECTANCEGSM_H_INCLUDED

#include "limits"
#include "../../../height/MKZ/GSM/lut.h"

class ReflectanceGSM
{
private:
    int mu;
    Lut lutObj;
    vector<double> sigs;       //size = 40
    vector<double> pis;

public:
    //constructors
    ReflectanceGSM(){};
    ReflectanceGSM(const ReflectanceGSM& input)
    {
        this->mu = input.mu;
        this->sigs = input.sigs;
        this->pis = input.pis;
        this->lutObj = input.lutObj;
    };

    //operators overloading
    ReflectanceGSM& operator=(const ReflectanceGSM& input)
    {
        this->mu = input.mu;
        this->sigs = input.sigs;
        this->pis = input.pis;
        this->lutObj = input.lutObj;

        return *this;
    };

     //getters
    int getMu(){return this->mu;};
    Lut& getLut(){return this->lutObj;};
    vector<double>& getSigs(){return this->sigs;};
    vector<double>& getPis(){return this->pis;};

    //initialize reflectance gray data
    void initializeGSMReflectanceGrayData(StructNode& gray_ma_gsm_metadata);
};


#endif // REFLECTANCEGSM_H_INCLUDED
