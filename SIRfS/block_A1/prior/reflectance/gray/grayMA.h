#ifndef GRAYMA_H_INCLUDED
#define GRAYMA_H_INCLUDED

#include "../../height/MKZ/GSM.h"
#include <vector>

//using namespace std;

class GrayMA
{
private:
    GSM gsm;
    std::vector<double> MA_train;        //size = 300000

public:
    //operators overloading
    GrayMA& operator=(const GrayMA& input)
    {
        this->gsm = input.gsm;
        this->MA_train = input.MA_train;
        return *this;
    };

    //getters
    inline GSM getGsm(){return this->gsm;};
    inline std::vector<double>& getMA_train(){return this->MA_train;};

    //initialize data
    void initializeGrayMAdata();
};

#endif // GRAYMA_H_INCLUDED
