#ifndef WHITENPARAMS_H_INCLUDED
#define WHITENPARAMS_H_INCLUDED

#include <vector>
#include "../../../../templates/matrix2D.h"
#include "../../../../templates/dataFile.h"

class GrayWhitenParams
{
private:
    std::vector<double> mean;
    Matrix2D<double> mapp, inverse, V, D, iD, C, iC;        //size = 9

public:
    GrayWhitenParams():mapp(9,9), inverse(9,9), V(9,9), D(9,9), iD(9,9), C(9,9), iC(9,9){};
     //operators overloading
    GrayWhitenParams& operator=(const GrayWhitenParams& input)
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
    void initializeGrayLaboratoryWhitenParamsData();
    void initializeGrayNaturalWhitenParamsData();
};

#endif // WHITENPARAMS_H_INCLUDED
