#ifndef REFLECTANCEGRAY_H_INCLUDED
#define REFLECTANCEGRAY_H_INCLUDED

#include "../../../helpers/range.h"
#include "gray/grayMA.h"


class ReflectanceGray
{
private:
    std::vector<double> A_spline;      //size = 256
    std::vector<double> A_train;     //size = 300000
    Range A_range;
    GrayMA MA;

public:
    //constructors
    ReflectanceGray(){};
#ifdef U_PTR_CONTAINER
    //move constructor and assignment operator
    ReflectanceGray(ReflectanceGray& input)
    {
        this->A_spline = std::move(input.A_spline);
        this->A_train = std::move(input.A_train);
        this->A_range = input.A_range;
        this->MA = input.MA;
    }

    ReflectanceGray& operator=(ReflectanceGray& input)
    {
        this->A_spline = std::move(input.A_spline);
        this->A_train = std::move(input.A_train);
        this->A_range = input.A_range;
        this->MA = input.MA;
        return *this;
    }
#else
    ReflectanceGray(const ReflectanceGray& input)
    {
        this->A_spline = input.A_spline;
        this->A_train = input.A_train;
        this->A_range = input.A_range;
        this->MA = input.MA;
    };
    //operators overloading
    ReflectanceGray& operator=(const ReflectanceGray& input)
    {
        this->A_spline = input.A_spline;
        this->A_train = input.A_train;
        this->A_range = input.A_range;
        this->MA = input.MA;
        return *this;
    };
#endif

    //getters
    inline std::vector<double>& getA_spline(){return this->A_spline;};
    inline std::vector<double>& getA_train(){return this->A_train;};
    inline GrayMA& getGrayMA(){return this->MA;};
    inline Range& getARange(){return this->A_range;};

    //initialize reflectance data
    void initializeReflectanceGrayData(StructNode& gray_metadata);
};

#endif // GRAY_H_INCLUDED
