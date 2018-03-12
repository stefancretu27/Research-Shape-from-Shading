#ifndef GRAYMA_H_INCLUDED
#define GRAYMA_H_INCLUDED

#include "grayMA/ReflectanceGSM.h"
#include <vector>

//using namespace std;

class GrayMA
{
private:
    ReflectanceGSM gsm;
    std::vector<double> MA_train;        //size = 300000

public:
    //operators overloading
    GrayMA(){};
    GrayMA(const GrayMA& input)
    {
        this->gsm = input.gsm;
        this->MA_train = input.MA_train;
    };

    //operators overloading
    GrayMA& operator=(const GrayMA& input)
    {
        this->gsm = input.gsm;
        this->MA_train = input.MA_train;
        return *this;
    };

    //getters
    inline ReflectanceGSM& getGsm(){return this->gsm;};
    inline std::vector<double>& getMA_train(){return this->MA_train;};

    //initialize data
    void initializeGrayMAdata(StructNode& gray_ma_metadata);
};

#endif // GRAYMA_H_INCLUDED
