#ifndef MKZ_H_INCLUDED
#define MKZ_H_INCLUDED

#include "MKZ\GSM.h"

class MKZ
{
private:
    std::vector<double> mkz_train;       //size = 300000
    GSM gsm;

public:
    //operators overloading
    MKZ& operator=(const MKZ& new_mkz)
    {
        this->mkz_train = new_mkz.mkz_train;
        this->gsm = new_mkz.gsm;
        return *this;
    };

    //getters
    inline GSM& getGsm(){return this->gsm;};
    inline std::vector<double> &getMKZ_train(){return this->mkz_train;};

    //initialize height data
    void initilalizeMKZData();
};

#endif // MKZ_H_INCLUDED
