#ifndef REFLECTANCECOLOR_H_INCLUDED
#define REFLECTANCECOLOR_H_INCLUDED

#include "color\MA.h"
#include "../../templates/matrix3D.h"
#include "../../templates/matrix3D.cpp"

class ReflectanceColor
{
private:
    std::vector<double> A_whiten;                 //size = 9
    std::vector<int> bin_low, bin_high;        //size = 3
    Matrix2D<double> A_train;           //size = [300000,3]
    Matrix3D<double> Aw_hist;          //size = 102
    ColorMA ma;

public:
    //getters
    inline std::vector<double>& getA_whiten(){return this->A_whiten;};
    inline Matrix3D<double>& getAw_hist(){return this->Aw_hist;};
    inline Matrix2D<double>& getA_train(){return this->A_train;};
    inline std::vector<int>& getBin_low(){return this->bin_low;};
    inline std::vector<int>& getBin_high(){return this->bin_high;};
    inline ColorMA& getMA(){return this->ma;};

    //initialize data
    ReflectanceColor();
    void initializeReflectanceColorData();
};

#endif // COLOR_H_INCLUDED
