#ifndef MKZ_H_INCLUDED
#define MKZ_H_INCLUDED

#include "MKZ\GSM.h"

class MKZ
{
private:
    std::vector<double> MKZ_train;       //size = 300000
    GSM gsm;

public:
    //constructors
    MKZ(){};
    MKZ(const MKZ& new_mkz)
    {
        this->MKZ_train = new_mkz.MKZ_train;
        this->gsm = new_mkz.gsm;
    }

    //operators overloading
    MKZ& operator=(const MKZ& new_mkz)
    {
        this->MKZ_train = new_mkz.MKZ_train;
        this->gsm = new_mkz.gsm;
        return *this;
    };

    //getters
    inline GSM& getGsm(){return this->gsm;};
    inline std::vector<double> getMKZ_train(){return this->MKZ_train;};

    //initialize height data
    void initilalizeMKZData(StructNode& MKZ_metadata);
};

#endif // MKZ_H_INCLUDED
