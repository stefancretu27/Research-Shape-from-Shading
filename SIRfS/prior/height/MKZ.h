#ifndef MKZ_H_INCLUDED
#define MKZ_H_INCLUDED

#include "MKZ\GSM.h"

class MKZ
{
private:
    std::vector<double> mkz_train;       //size = 300000
    GSM gsm;

public:
    //getters
    inline GSM& getGsm(){return this->gsm;};
    inline std::vector<double> &getMKZ_train(){return this->mkz_train;};

    //initialize height data
    void initilalizeMKZData();
};

#endif // MKZ_H_INCLUDED
