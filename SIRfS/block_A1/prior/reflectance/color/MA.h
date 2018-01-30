#ifndef MA_H_INCLUDED
#define MA_H_INCLUDED

#include "ColorMA/GSM_mvn.h"

class ColorMA
{
private:
    GSM_mvn gsm_mvn;

public:
        //operators overloading
    ColorMA& operator=(const ColorMA& input)
    {
        this->gsm_mvn = input.gsm_mvn;
        return *this;
    };

    //getter
    inline GSM_mvn& getGsm_mvn(){return this->gsm_mvn;};

    //initialize class instance
    inline void initializeColorMAData()
    {
        //cout<<"Reflectance ColorMA initializer"<<endl;

        this->gsm_mvn.initializeGSM_mvnData();
    }
};

#endif // MA_H_INCLUDED
