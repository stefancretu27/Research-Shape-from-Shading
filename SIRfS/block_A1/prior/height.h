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
    //operators overloading
    Height& operator=(const Height& new_height)
    {
        this->nz_train = new_height.nz_train;
        this->mkz = new_height.mkz;
        this->normal = new_height.normal;
        return *this;
    };

    //getters
    inline MKZ& getMKZ(){return this->mkz;};
    inline Normal& getNormal(){return this->normal;};
    inline vector<double>& getNZ_train(){return this->nz_train;};

    //initialize data
    void initializeHeightData();
};


#endif // HEIGHT_H_INCLUDED
