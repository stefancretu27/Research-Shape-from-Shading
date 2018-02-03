#ifndef REFLECTANCEGRAY_H_INCLUDED
#define REFLECTANCEGRAY_H_INCLUDED

#include "../../../helpers/range.h"
#include "gray/grayMA.h"


class ReflectanceGray
{
private:
    std::vector<double> A_spline;      //size = 256
    std::vector<double> A_train;     //size = 300000
    Range range;
    GrayMA MA;

public:
    //operators overloading
    ReflectanceGray& operator=(const ReflectanceGray& input)
    {
        this->A_spline = input.A_spline;
        this->A_train = input.A_train;
        this->range = input.range;
        this->MA = input.MA;
        return *this;
    };

    //getters
    inline std::vector<double>& getA_spline(){return this->A_spline;};
    inline std::vector<double>& getA_train(){return this->A_train;};
    inline GrayMA& getGrayMA(){return this->MA;};
    inline Range& getRange(){return this->range;};

    //initialize reflectance data
    void initializeReflectanceGrayData();
};

#endif // GRAY_H_INCLUDED
