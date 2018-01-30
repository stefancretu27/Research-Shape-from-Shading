#ifndef COLORWHITENPARAMS_H_INCLUDED
#define COLORWHITENPARAMS_H_INCLUDED

#include <iostream>
#include <vector>
#include "../../../../templates/matrix2D.h"
#include "../../../../templates/dataFile.h"

class ColorWhitenParams
{
private:
    std::vector<double> mean;
    Matrix2D<double> mapp, inverse, V, D, iD, C, iC;         //size = 27


public:
     ColorWhitenParams():mapp(27,27), inverse(27,27), V(27,27), D(27,27), iD(27,27), C(27,27), iC(27,27){};

    //operators overloading
    ColorWhitenParams& operator=(const ColorWhitenParams& input)
    {
        this->mean = input.mean;
        this->mapp = input.mapp;
        this->inverse = input.inverse;
        this->iC = input.iC;
        this->C = input.C;
        this->iD = input.iD;
        this->D = input.D;
        this->V = input.V;
        return *this;
    };

    //getters
    inline vector<double>& getMean(){return this->mean;};
    inline Matrix2D<double>& getMapp(){return this->mapp;};
    inline Matrix2D<double>& getInverse(){return this->inverse;};
    inline Matrix2D<double>& getV(){return this->V;};
    inline Matrix2D<double>& getD(){return this->D;};
    inline Matrix2D<double>& getiD(){return this->iD;};
    inline Matrix2D<double>& getC(){return this->C;};
    inline Matrix2D<double>& getiC(){return this->iC;};

    //initialize data
    void initializeColorLaboratoryWhitenParamsData();
    void initializeColorNaturalWhitenParamsData();

};

#endif // COLORWHITENPARAMS_H_INCLUDED
