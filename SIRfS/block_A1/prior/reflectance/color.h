#ifndef REFLECTANCECOLOR_H_INCLUDED
#define REFLECTANCECOLOR_H_INCLUDED

#include "color\MA.h"
#include "../../../templates/matrix3D.h"
#include "../../../templates/matrix3D.cpp"

class ReflectanceColor
{
private:
    std::vector<double> A_whiten;                 //size = 9
    std::vector<int> bin_low, bin_high;        //size = 3
    Matrix2D<double> A_train;           //size = [300000,3]
    Matrix3D<double> Aw_hist;          //size = 102
    ColorMA ma;

public:
    //constructors
    ReflectanceColor(){};

#ifdef U_PTR_CONTAINER
    //move constructor and assignment operator
    ReflectanceColor(ReflectanceColor& input)
    {
        this->Aw_hist = std::move(input.Aw_hist);
        this->A_whiten = std::move(input.A_whiten);
        this->A_train = std::move(input.A_train);
        this->bin_low = std::move(input.bin_low);
        this->bin_high = std::move(input.bin_high);
        this->ma = input.ma;
    }

    ReflectanceColor& operator=(ReflectanceColor& input)
    {
        this->Aw_hist = std::move(input.Aw_hist);
        this->A_whiten = std::move(input.A_whiten);
        this->A_train = std::move(input.A_train);
        this->bin_low = std::move(input.bin_low);
        this->bin_high = std::move(input.bin_high);
        this->ma = input.ma;

        return *this;
    }
#else
    ReflectanceColor(const ReflectanceColor& input)
    {
        this->Aw_hist = input.Aw_hist;
        this->A_whiten = input.A_whiten;
        this->A_train = input.A_train;
        this->ma = input.ma;
        this->bin_low = input.bin_low;
        this->bin_high = input.bin_high;
    };
    //operators overloading
    ReflectanceColor& operator=(const ReflectanceColor& input)
    {
        this->Aw_hist = input.Aw_hist;
        this->A_whiten = input.A_whiten;
        this->A_train = input.A_train;
        this->ma = input.ma;
        this->bin_low = input.bin_low;
        this->bin_high = input.bin_high;
        return *this;
    };
#endif

    //getters
    inline std::vector<double>& getA_whiten(){return this->A_whiten;};
    inline Matrix3D<double>& getAw_hist(){return this->Aw_hist;};
    inline Matrix2D<double>& getA_train(){return this->A_train;};
    inline std::vector<int>& getBin_low(){return this->bin_low;};
    inline std::vector<int>& getBin_high(){return this->bin_high;};
    inline ColorMA& getMA(){return this->ma;};

    //initialize data
    void initializeReflectanceColorData(StructNode& color_metadata);
};

#endif // COLOR_H_INCLUDED
