#ifndef HEIGHT_H_INCLUDED
#define HEIGHT_H_INCLUDED

#include "height\MKZ.h"
#include "height\normal.h"

class Height
{

private:
    vector<double> nz_train;            //size = 300000
    MKZ mkz;
    Normal normal;

public:
    //getters
    inline MKZ& getMKZ(){return this->mkz;};
    inline Normal& getNormal(){return this->normal;};
    inline vector<double>& getNZ_train(){return this->nz_train;};

    //initialize data
    void initializeHeightData();
};


#endif // HEIGHT_H_INCLUDED
