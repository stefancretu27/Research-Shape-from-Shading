#ifndef COLORWHITENPARAMS_H_INCLUDED
#define COLORWHITENPARAMS_H_INCLUDED

#include <iostream>
#include <vector>
#include "../../../templates/matrix2D.h"
#include "../../../templates/dataFile.h"

class ColorWhitenParams
{
private:
    std::vector<double> mean;
    Matrix2D<double> mapp, inverse, V, D, iD, C, iC;         //size = 27


public:
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
    ColorWhitenParams();
    void initializeColorLaboratoryWhitenParamsData();
    void initializeColorNaturalWhitenParamsData();

};

#endif // COLORWHITENPARAMS_H_INCLUDED
