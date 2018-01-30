#ifndef LUT_H_INCLUDED
#define LUT_H_INCLUDED

#include <vector>
#include <fstream>
#include <iostream>

#include "../../../../../helpers/range.h"
#include "../../../../../templates/dataFile.h"

class Lut
{
private:
    double bin_width;
    vector<double>  F_LL, F_cost;       //size = 20000
    vector<unsigned int> N_train;         //size = 20000
    int n_bins;
    Range bin_range;

public:
    //operators overloading
    Lut& operator=(const Lut& new_lut)
    {
        this->bin_width = new_lut.bin_width;
        this->F_LL = new_lut.F_LL;
        this->F_cost = new_lut.F_cost;
        this->N_train = new_lut.N_train;
        this->n_bins = new_lut.n_bins;
        this->bin_range = new_lut.bin_range;
        return *this;
    };

    //getters
    inline double getBin_width(){return this->bin_width;};
    inline int getN_bins(){return this->n_bins;};
    inline Range& getBin_range(){return this->bin_range;};
    inline vector<double>& getF_cost() {return this->F_cost;};
    inline vector<double>& getF_LL() {return this->F_LL;};
    inline vector<unsigned int>& getN_train() {return this->N_train;};

    //initialize height data
    void initializeLutHeightData();
    //initialize reflectance gray data
    void initializeLutReflectanceGrayData();
};

#endif // LUT_H_INCLUDED
