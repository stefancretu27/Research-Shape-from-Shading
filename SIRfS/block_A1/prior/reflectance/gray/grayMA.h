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
#ifdef U_PTR_CONTAINER
    GrayMA(GrayMA& input)
    {
        this->gsm = input.gsm;
        this->MA_train = std::move(input.MA_train);
    };
    //operators overloading
    GrayMA& operator=(GrayMA& input)
    {
        this->gsm = input.gsm;
        this->MA_train = std::move(input.MA_train);
        return *this;
    };
#else
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
#endif

    //getters
    inline ReflectanceGSM& getGsm(){return this->gsm;};
    inline std::vector<double>& getMA_train(){return this->MA_train;};

    //initialize data
    void initializeGrayMAdata(StructNode& gray_ma_metadata);
};

#endif // GRAYMA_H_INCLUDED
