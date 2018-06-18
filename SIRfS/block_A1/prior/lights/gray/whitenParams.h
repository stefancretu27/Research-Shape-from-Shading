#ifndef WHITENPARAMS_H_INCLUDED
#define WHITENPARAMS_H_INCLUDED

#include <vector>
#include "../../../../templates/matrix2D_cuda.h"
#include "../../../../helpers/prior_struct_node.h"


class GrayWhitenParams
{
private:
    std::vector<double> mean;
    Matrix2D<double> mapp, inverse, V, D, iD, C, iC;        //size = 9

public:
    //constructors
    GrayWhitenParams(){};
    GrayWhitenParams(const GrayWhitenParams& input)
    {
        this->mean = input.mean;
        this->mapp = input.mapp;
        this->inverse = input.inverse;
        this->iC = input.iC;
        this->C = input.C;
        this->iD = input.iD;
        this->D = input.D;
        this->V = input.V;
    };
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
    inline std::vector<double>& getMean(){return this->mean;};
    inline Matrix2D<double>& getMapp(){return this->mapp;};
    inline Matrix2D<double>& getInverse(){return this->inverse;};
    inline Matrix2D<double>& getV(){return this->V;};
    inline Matrix2D<double>& getD(){return this->D;};
    inline Matrix2D<double>& getiD(){return this->iD;};
    inline Matrix2D<double>& getC(){return this->C;};
    inline Matrix2D<double>& getiC(){return this->iC;};

    //initialize data
    void initializeGrayWhitenParamsData(StructNode& gray_wp_metadata);
};

#endif // WHITENPARAMS_H_INCLUDED
