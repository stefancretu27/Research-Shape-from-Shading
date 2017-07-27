#ifndef GSM_H_INCLUDED
#define GSM_H_INCLUDED

#include "limits"
#include "GSM\lut.h"

class GSM
{
private:
    float mu;
    Lut lutObj;
    std::vector<double> sigs;       //size = 40
    std::vector<long double> pis;

public:
     //getters
    inline float getMu(){return this->mu;};
    inline Lut& getLut(){return this->lutObj;};
    inline std::vector<double>& getSigs(){return this->sigs;};
    inline std::vector<long double>& getPis(){return this->pis;};

    //initialize height data
    void initializeGSMHeightData();

    //initialize reflectance gray data
    void initializeGSMReflectanceGrayData();
};

#endif // GSM_H_INCLUDED
