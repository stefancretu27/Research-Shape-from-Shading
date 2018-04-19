#ifndef MA_H_INCLUDED
#define MA_H_INCLUDED

#include "ColorMA/GSM_mvn.h"

class ColorMA
{
private:
    GSM_mvn gsm_mvn;

public:
    //constructors
    ColorMA(){};
#ifdef U_PTR_CONTAINER
    ColorMA(ColorMA& input)
#else
    ColorMA(const ColorMA& input)
#endif
    {
        this->gsm_mvn = input.gsm_mvn;
    };

    //operators overloading
#ifdef U_PTR_CONTAINER
    ColorMA& operator=(ColorMA& input)
#else
    ColorMA& operator=(const ColorMA& input)
#endif
    {
        this->gsm_mvn = input.gsm_mvn;
        return *this;
    };

    //getter
    inline GSM_mvn& getGsm_mvn(){return this->gsm_mvn;};

    //initialize class instance
    inline void initializeColorMAData(StructNode& color_ma_metadata)
    {
        vector<StructNode*> nodes4 = color_ma_metadata.getChildrenNodes();

        this->gsm_mvn.initializeGSM_mvnData(*nodes4[0]);
    }
};

#endif // MA_H_INCLUDED
